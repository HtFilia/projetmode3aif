/**
 * \file MonteCarlo.cpp
 *
 *
 * \brief Fichier source de la classe MonteCarlo
 *
 * \authors LEBIHAN Lucas, COUTE Lucas, MOMMEJA Léonard, PRÊTRE-HECKENROTH Raphaël
 * Fait le 11.09.2019
 *
 */

#include <math.h>
#include <iostream>

#include "MonteCarlo.hpp"

/**
* Calcule le prix de l'option à la date 0
*
* @param[out] prix valeur de l'estimateur Monte Carlo
* @param[out] ic largeur de l'intervalle de confiance
*/
void MonteCarlo::price(double &prix, double &ic) {
    PnlMat* path = pnl_mat_create(opt_->getTimeSteps() + 1, mod_->getSize());
    prix = 0;
    double var = 0;

    for (int i = 0; i < nbSamples_; i++) {
        mod_->asset(path, opt_->getMaturity(), opt_->getTimeSteps(), rng_);
        double tmp = opt_->payoff(path);
        prix += tmp;
        var += SQR(tmp);
    }

    prix = exp(- mod_->getR() * opt_->getMaturity()) * prix / nbSamples_;
    var = exp(-2 * mod_->getR() * opt_->getMaturity()) * var / nbSamples_ - SQR(prix);
    ic = 2 * 1.96 * sqrt(var / (double)nbSamples_);

    //free
    pnl_mat_free(&path);
}

/**
 * Calcule le prix de l'option à la date t
 *
 * @param[in]  past contient la trajectoire du sous-jacent
 * jusqu'à l'instant t
 * @param[in] t date à laquelle le calcul est fait
 * @param[out] prix contient le prix
 * @param[out] ic contient la largeur de l'intervalle
 * de confiance sur le calcul du prix
 */
void MonteCarlo::price(const PnlMat *past, double t, double &prix, double &ic) {
    PnlMat* path = pnl_mat_create(opt_->getTimeSteps() + 1, mod_->getSize());
    prix = 0;
    double var = 0;

    for (int i = 0; i < nbSamples_; i++) {
        mod_->asset(path, t, opt_->getMaturity(), opt_->getTimeSteps(), rng_, past);
        double tmp = opt_->payoff(path);
        prix += tmp;
        var += SQR(tmp);
    }

    prix = exp(- mod_->getR() * (opt_->getMaturity() - t)) * prix / nbSamples_;
    var = exp(-2 *  mod_->getR() * (opt_->getMaturity() - t)) * var / nbSamples_ - SQR(prix);
    ic = 2 * 1.96 * sqrt(var / (double)nbSamples_);

    //free
    pnl_mat_free(&path);
}

/**
 * Calcule le delta de l'option à la date t
 *
 * @param[in] past contient la trajectoire du sous-jacent
 * jusqu'à l'instant t
 * @param[in] t date à laquelle le calcul est fait
 * @param[out] delta contient le vecteur de delta
 * @param[out] ic contient la largeur de l'intervalle
 * de confiance sur le calcul du delta
 */
void MonteCarlo::delta(const PnlMat *past, double t, PnlVect *delta, PnlVect *ic) {
    double timestep = opt_->getMaturity() / (double) opt_->getTimeSteps();
    PnlMat *path = pnl_mat_create(opt_->getTimeSteps() + 1, mod_->getSize());
    PnlMat *shift_path = pnl_mat_create(opt_->getTimeSteps() + 1, mod_->getSize());

    for (int d = 0; d < mod_->getSize(); d++) {
        double delta_d = 0;
        double var = 0;
        for (int i = 0; i < nbSamples_; i++) {
            mod_->asset(path, t, opt_->getMaturity(), opt_->getTimeSteps(), rng_, past);
            mod_->shiftAsset(shift_path, path, d, fdStep_, t, timestep);
            double tmp = opt_->payoff(shift_path);
            mod_->shiftAsset(shift_path, path, d, -fdStep_, t, timestep);
            tmp -= opt_->payoff(shift_path);
            delta_d += tmp;
            var += SQR(tmp);
        }
        delta_d = exp(-mod_->getR() * (opt_->getMaturity() - t)) *
                  (delta_d / (2 * fdStep_ * pnl_mat_get(past, past->m - 1, d))) / nbSamples_;
        var = exp(-2 * mod_->getR() * (opt_->getMaturity() - t)) *
              (var / SQR(2 * fdStep_ * pnl_mat_get(past, past->m - 1, d))) / nbSamples_ - SQR(delta_d);
        double ic_d = 2 * 1.96 * sqrt(var / (double) nbSamples_);

        pnl_vect_set(delta, d, delta_d);
        pnl_vect_set(ic, d, ic_d);
    }

    //free
    pnl_mat_free(&path);
    pnl_mat_free(&shift_path);
}

/**
 * Calcule le P&L le long d'une trajectoire de marché
 *
 * @param[in] path contient la trajectoire de marché
 * @param[out] deltas contient la matrice des deltas
 * @param[out] delta0 contient le vecteur des parts investies au tsr
 * @param[out] error contient l'erreur de couverture
 */
void MonteCarlo::profitAndLoss(const PnlMat *path, PnlMat *deltas, PnlVect *delta0, double &error) {
    int H = path->m -1;
    double prix = 0;
    double icPrix = 0;
    PnlVect *spots = pnl_vect_create(opt_->getSize());
    PnlVect *delta = pnl_vect_create(opt_->getSize());
    PnlVect *oldDelta = pnl_vect_create(opt_->getSize());
    PnlVect *icDelta = pnl_vect_create(opt_->getSize());
    PnlMat *past = pnl_mat_create(1, opt_->getSize());

    pnl_mat_get_row(spots, path, 0);
    pnl_mat_set_row(past, spots, 0);
    price(prix, icPrix);
    MonteCarlo::delta(past, 0, delta, icDelta);
    pnl_mat_set_row(deltas, delta, 0);
    pnl_vect_set(delta0, 0, prix - pnl_vect_scalar_prod(delta, spots));

    for (int i = 1; i < path->m; i++) {
        pnl_mat_get_row(spots, path, i);
        pnl_mat_add_row(past, past->m, spots);

        MonteCarlo::delta(past, i * opt_->getMaturity() / (double)H, delta, icDelta);
        pnl_mat_set_row(deltas, delta, i);

        pnl_mat_get_row(oldDelta, deltas, i - 1);
        pnl_vect_minus_vect(delta, oldDelta);

        pnl_vect_set(delta0, i, pnl_vect_get(delta0, i - 1) * exp(mod_->getR() * opt_->getMaturity() / (double)H) - pnl_vect_scalar_prod(delta, spots));
    }

    pnl_mat_get_row(delta, deltas, H);
    error = pnl_vect_get(delta0, H) + pnl_vect_scalar_prod(delta, spots) - opt_->payoff(path);

    pnl_vect_free(&spots);
    pnl_vect_free(&delta);
    pnl_vect_free(&oldDelta);
    pnl_vect_free(&icDelta);
    pnl_mat_free(&past);
}