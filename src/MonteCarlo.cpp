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

#include "MonteCarlo.h"

/**
 * \brief Getter de l'attribut \refitem mod_
 *
 * @return le pointeur vers le modèle utilisé, \refitem mod_
 *
 */
BlackScholesModel* MonteCarlo::getMod() {
    return mod_;
}

/**
 * \brief Getter de l'attribut \refitem opt_
 *
 * @return le pointeur vers l'option utilisée, \refitem opt_
 *
 */
Option* MonteCarlo::getOption() {
    return opt_;
}

/**
* \brief Getter de l'attribut \refitem rng_
*
* @return le pointeur vers générateur aléatoire utilisé, \refitem rng_
*
*/
PnlRng* MonteCarlo::getRng() {
    return rng_;
}

/**
 * \brief Getter de l'attribut \refitem fdStep_
 *
 * @return le pas de différence finie, \refitem fdStep_
 *
 */
double MonteCarlo::getStep() {
    return fdStep_;
}

/**
 * \brief Getter de l'attribut \refitem nbSamples_
 *
 * @return le nombre de tirages Monte Carlo souhaité, \refitem nbSamples_
 *
 */
int MonteCarlo::getSampleSize() {
    return nbSamples_;
}

/**
 * \brief Setter de l'attribut \refitem mod_
 *
 * @param[in] newModel le nouveau modèle utilisé.
 *
 */
void MonteCarlo::setMod(BlackScholesModel* newModel) {
    mod_ = newModel;
}

/**
 * \brief Setter de l'attribut \refitem opt_
 *
 * @param[in] newOption la nouvelle option utilisée.
 *
 */
void MonteCarlo::setOption(Option* newOption) {
    opt_ = newOption;
}

/**
 * \brief Setter de l'attribut \refitem rng_
 *
 * @param[in] newRng le nouveau générateur aléatoire utilisé.
 *
 */
void MonteCarlo::setRng(PnlRng* newRng) {
    rng_ = newRng;
}

/**
 * \brief Setter de l'attribut \refitem fdStep_
 *
 * @param[in] newStep le nouveau pas de différence finie, \refitem fdStep_
 *
 */
void MonteCarlo::setStep(double newStep) {
    fdStep_ = newStep;
}

/**
 * \brief Setter de l'attribut \refitem nbSamples_
 *
 * @param[in] newSampleSize le nouveau nombre de tirages Monte Carlo souhaité, \refitem nbSamples_
 */
void MonteCarlo::setSampleSize(int newSampleSize) {
    nbSamples_ = newSampleSize;
}

/**
* Calcule le prix de l'option à la date 0
*
* @param[out] prix valeur de l'estimateur Monte Carlo
* @param[out] ic largeur de l'intervalle de confiance
*/
void price(double &prix, double &ic) {
    //TODO
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
void price(const PnlMat *past, double t, double &prix, double &ic) {
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
void delta(const PnlMat *past, double t, PnlVect *delta, PnlVect *ic) {
    //TODO
}