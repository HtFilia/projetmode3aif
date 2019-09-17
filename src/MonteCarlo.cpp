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
    //TODO
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
    //TODO
}