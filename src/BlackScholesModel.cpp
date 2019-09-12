/**
 * \file BlackScholesModel.cpp
 *
 *
 * \brief Fichier source de la classe BlackScholesModel
 *
 * \authors LEBIHAN Lucas, COUTE Lucas, MOMMEJA Léonard, PRÊTRE-HECKENROTH Raphaël
 * Fait le 11.09.2019
 *
 */

#include "BlackScholesModel.h"

/**
 * \brief Getter de l'attribut \refitem size_
 *
 * @return l'attribut \refitem size_
 *
 */
int BlackScholesModel::getSize() const {
    return size_;
}

/**
 * \brief Getter de l'attribut \refitem r_
 *
 * @return l'attribut \refitem r_
 *
 */
double BlackScholesModel::getR() const {
    return r_;
}

/**
 * \brief Getter de l'attribut \refitem rho_
 *
 * @return l'attribut \refitem rho_
 *
 */
double BlackScholesModel::getRho() const {
    return rho_;
}

/**
 * \brief Getter de l'attribut \refitem sigma_
 *
 * @return l'attribut \refitem sigma_
 *
 */
PnlVect *BlackScholesModel::getSigma() const {
    return sigma_;
}

/**
 * \brief Getter de l'attrivut \refitem spot_
 *
 * @return l'attribut \refitem sigma_
 *
 */
PnlVect *BlackScholesModel::getSpot() const {
    return spot_;
}

/**
 * \brief Setter de l'attribut \refitem size_
 *
 * @param size le nouveau nombre d'actifs du modèle, \refitem size_
 *
 */
void BlackScholesModel::setSize(int size) {
    size_ = size;
}

/**
 * \brief Setter de l'attribut \refitem r_
 *
 * @param r le nouveau taux d'intérêt du ZC, \refitem r_
 */
void BlackScholesModel::setR(double r) {
    r_ = r;
}

/**
 * \brief Setter de l'attribut \refitem rho_
 *
 * @param rho la nouvelle corrélation du modèle, \refitem rho_
 *
 */
void BlackScholesModel::setRho(double rho) {
    rho_ = rho;
}

/**
 * \brief Setter de l'attribut \refitem sigma_
 *
 * @param sigma le nouveau vecteur de volatilités du modèle, \refitem sigma_
 *
 */
void BlackScholesModel::setSigma(PnlVect *sigma) {
    sigma_ = sigma;
}

/**
 * \brief Setter de l'attribut \refitem spot_
 *
 * @param spot le nouveau vecteur des spots initiaux du modèle, \refitem spot_
 *
 */
void BlackScholesModel::setSpot(PnlVect *spot) {
    spot_ = spot;
}

/**
 * Génère une trajectoire du modèle et la stocke dans path
 *
 * @param[out] path contient une trajectoire du modèle.
 * C'est une matrice de taille (nbTimeSteps+1) x d
 * @param[in] T  maturité
 * @param[in] nbTimeSteps nombre de dates de constatation
 */
void BlackScholesModel::asset(PnlMat *path, double T, int nbTimeSteps, PnlRng *rng) {
    //TODO
}

/**
 * Calcule une trajectoire du modèle connaissant le
 * passé jusqu' à la date t
 *
 * @param[out] path  contient une trajectoire du sous-jacent
 * donnée jusqu'à l'instant t par la matrice past
 * @param[in] t date jusqu'à laquelle on connait la trajectoire.
 * t n'est pas forcément une date de discrétisation
 * @param[in] nbTimeSteps nombre de pas de constatation
 * @param[in] T date jusqu'à laquelle on simule la trajectoire
 * @param[in] past trajectoire réalisée jusqu'a la date t
 */
void BlackScholesModel::asset(PnlMat *path, double t, double T, int nbTimeSteps, PnlRng *rng, const PnlMat *past) {
    //TODO
}

/**
 * Shift d'une trajectoire du sous-jacent
 *
 * @param[in]  path contient en input la trajectoire
 * du sous-jacent
 * @param[out] shift_path contient la trajectoire path
 * dont la composante d a été shiftée par (1+h)
 * à partir de la date t.
 * @param[in] t date à partir de laquelle on shift
 * @param[in] h pas de différences finies
 * @param[in] d indice du sous-jacent à shifter
 * @param[in] timestep pas de constatation du sous-jacent
 */
void BlackScholesModel::shiftAsset(PnlMat *shift_path, const PnlMat *path, int d, double h, double t, double timestep) {
    //TODO
}

