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
        var += tmp * tmp;
    }

    prix = exp(- mod_->getR() * opt_->getMaturity()) * prix / nbSamples_;
    var = exp(-2 * mod_->getR() * opt_->getMaturity()) * var / nbSamples_ - prix * prix;
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
        var += tmp * tmp;
    }

    prix = exp(- mod_->getR() * (opt_->getMaturity() - t)) * prix / nbSamples_;
    var = exp(-2 *  mod_->getR() * (opt_->getMaturity() - t)) * var / nbSamples_ - prix * prix;
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
    double timestep = opt_->getMaturity() / opt_->getTimeSteps();
    PnlMat* path = pnl_mat_create(opt_->getTimeSteps() + 1, mod_->getSize());
    PnlMat* shift_path = pnl_mat_create(opt_->getTimeSteps() + 1, mod_->getSize());

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
            var += tmp * tmp;
        }
        delta_d  = exp(- mod_->getR() * (opt_->getMaturity() - t)) * (delta_d / 2 * fdStep_ * pnl_mat_get(past, past->m - 1, d)) / nbSamples_;
        var = exp(-2 * mod_->getR() * (opt_->getMaturity() - t)) * (var / SQR(2 * fdStep_ * pnl_mat_get(past, past->m - 1, d))) / nbSamples_ - delta_d * delta_d;
        double ic_d = 2 * 1.96 * sqrt(var / (double)nbSamples_);

        pnl_vect_set(delta, d, delta_d);
        pnl_vect_set(ic, d, ic_d);
    }

    //free
    pnl_mat_free(&path);
    pnl_mat_free(&shift_path);
}