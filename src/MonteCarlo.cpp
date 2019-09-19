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
    double interestRate = mod_->getR();
    double maturity = opt_->getMaturity();
    PnlMat* path = pnl_mat_create(opt_->getTimeSteps() + 1, mod_->getSize());
    prix = 0;
    double var = 0;

    for (int i = 0; i < nbSamples_; i++) {
        mod_->asset(path, maturity, opt_->getTimeSteps(), rng_);
        double tmp = opt_->payoff(path);
        prix += tmp;
        var += tmp * tmp;
    }

    prix /= nbSamples_;
    var = var / nbSamples_ - prix * prix;
    var *= exp(-2 * maturity * interestRate);
    ic = 2 * 1.96 * sqrt(var / (double)nbSamples_);
    prix *= exp(-maturity * interestRate);

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
    double interestRate = mod_->getR();
    double maturity = opt_->getMaturity();
    PnlMat* path = pnl_mat_create(opt_->getTimeSteps() + 1, mod_->getSize());
    prix = 0;
    double var = 0;

    for (int i = 0; i < nbSamples_; i++) {
        mod_->asset(path, t, maturity, opt_->getTimeSteps(), rng_, past);
        double tmp = opt_->payoff(path);
        prix += tmp;
        var += tmp * tmp;
    }

    prix /= nbSamples_;
    var = var / nbSamples_ - prix * prix;
    var *= exp(-2 * (maturity - t) * interestRate);
    ic = 2 * 1.96 * sqrt(var / (double)nbSamples_);
    prix *= exp(-(maturity - t) * interestRate);
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
    double interestRate = mod_->getR();
    double maturity = opt_->getMaturity();
    PnlMat* path = pnl_mat_create(opt_->getTimeSteps() + 1, mod_->getSize());
    PnlMat* shift_path = pnl_mat_create(opt_->getTimeSteps() + 1, mod_->getSize());

    for (int d = 0; d < mod_->getSize(); d++) {
        double delta_d = 0;
        double var = 0;
        for (int i = 0; i < nbSamples_; i++) {
            mod_->asset(path, t, maturity, opt_->getTimeSteps(), rng_, past);
            mod_->shiftAsset(shift_path, path, d, fdStep_, t, opt_->getMaturity() / opt_->getTimeSteps());
            double tmp = opt_->payoff(shift_path);
            mod_->shiftAsset(shift_path, path, d, -fdStep_, t, opt_->getMaturity() / opt_->getTimeSteps());
            tmp -= opt_->payoff(shift_path);
            tmp /= 2 * fdStep_ * pnl_mat_get(past, past->m - 1, d);
            delta_d += tmp;
            var += tmp * tmp;
        }
        delta_d /= nbSamples_;
        var = var / nbSamples_ - delta_d * delta_d;
        var *= exp(-2 * (maturity - t) * interestRate);
        double ic_d = 2 * 1.96 * sqrt(var / (double)nbSamples_);
        delta_d *= exp(-(maturity - t) * interestRate);

        pnl_vect_set(delta, d, delta_d);
        pnl_vect_set(ic, d, ic_d);
    }
}