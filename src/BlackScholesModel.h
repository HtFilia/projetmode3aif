/**
 * \file BlackScholesModel.h
 *
 *
 * \brief Fichier header de la classe BlackScholesModel
 *
 * \authors LEBIHAN Lucas, COUTE Lucas, MOMMEJA Léonard, PRÊTRE-HECKENROTH Raphaël
 * Fait le 11.09.2019
 *
 */

#ifndef PROJETMODPRO_BLACKSCHOLESMODEL_H
#define PROJETMODPRO_BLACKSCHOLESMODEL_H

#include "pnl/pnl_random.h"
#include "pnl/pnl_vector.h"
#include "pnl/pnl_matrix.h"

/**
 * \class BlackScholesModel
 *
 * \brief Classe représentant le modèle de Black & Scholes utilisé.
 *
 */
class BlackScholesModel {

private:

    /**
     * \brief size_ correspond au nombre d'actifs du modèle.
     *
     */
    int size_;

    /**
     * \brief r_ correspond au taux d'intérêt du zéro-coupon.
     *
     */
    double r_;

    /**
     * \brief rho_ correspond au paramètre de corrélation du modèle.
     *
     */
    double rho_;

    /**
     * \brief *sigma correspond au vecteur de volatilités.
     *
     */
    PnlVect *sigma_;

    /**
     * \brief *spot_ correspond au vecteur de valeurs initiales des sous-jacents.
     *
     */
    PnlVect *spot_;

public:

    /**
     * \brief Getter de l'attribut \refitem size_
     *
     * @return l'attribut \refitem size_
     *
     */
    int getSize() const;

    /**
     * \brief Getter de l'attribut \refitem r_
     *
     * @return l'attribut \refitem r_
     *
     */
    double getR() const;

    /**
     * \brief Getter de l'attribut \refitem rho_
     *
     * @return l'attribut \refitem rho_
     *
     */
    double getRho() const;

    /**
     * \brief Getter de l'attribut \refitem sigma_
     *
     * @return l'attribut \refitem sigma_
     *
     */
    PnlVect *getSigma() const;

    /**
     * \brief Getter de l'attrivut \refitem spot_
     *
     * @return l'attribut \refitem sigma_
     *
     */
    PnlVect *getSpot() const;

    /**
     * \brief Setter de l'attribut \refitem size_
     *
     * @param size le nouveau nombre d'actifs du modèle, \refitem size_
     *
     */
    void setSize(int size);

    /**
     * \brief Setter de l'attribut \refitem r_
     *
     * @param r le nouveau taux d'intérêt du ZC, \refitem r_
     */
    void setR(double r);

    /**
     * \brief Setter de l'attribut \refitem rho_
     *
     * @param rho la nouvelle corrélation du modèle, \refitem rho_
     *
     */
    void setRho(double rho);

    /**
     * \brief Setter de l'attribut \refitem sigma_
     *
     * @param sigma le nouveau vecteur de volatilités du modèle, \refitem sigma_
     *
     */
    void setSigma(PnlVect *sigma);

    /**
     * \brief Setter de l'attribut \refitem spot_
     *
     * @param spot le nouveau vecteur des spots initiaux du modèle, \refitem spot_
     *
     */
    void setSpot(PnlVect *spot);

    /**
     * Génère une trajectoire du modèle et la stocke dans path
     *
     * @param[out] path contient une trajectoire du modèle.
     * C'est une matrice de taille (nbTimeSteps+1) x d
     * @param[in] T  maturité
     * @param[in] nbTimeSteps nombre de dates de constatation
     */
    void asset(PnlMat *path, double T, int nbTimeSteps, PnlRng *rng);

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
    void asset(PnlMat *path, double t, double T, int nbTimeSteps, PnlRng *rng, const PnlMat *past);

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
    void shiftAsset(PnlMat *shift_path, const PnlMat *path, int d, double h, double t, double timestep);
};


#endif //PROJETMODPRO_BLACKSCHOLESMODEL_H
