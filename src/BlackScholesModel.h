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

#include<libaio.h>
#include<vector>


/**
 * \class BlackScholesModel
 *
 * \brief Classe représentant le modèle de Black & Scholes utilisé.
 *
 */
class BlackScholesModel {

public:

    /**
     * \brief firstSpots représente le vecteur des spots initiaux.
     */
    std::vector<float> firstSpots;

    /**
     * \brief volatilities représente le vecteur des volatilités des sous-jacents.
     *
     */
    std::vector<float> volatilities;

    /**
     * \brief correlation représente la corrélation.
     *
     */
    float correlation;

    /**
     * \brief interestRate représente le taux d'intérêt du zéro-coupon.
     *
     */
    float interestRate;

    /**
     * \brief timestepNumber représente le nombre de discrétisations.
     *
     */
    int timestepNumber;

    /**
     * \brief asset simule le marché sous le modèle de Black&Scholes avec les paramètres en attribut.
     *
     * @return la matrice de taille (N+1)xD des spots aux différents temps des sous-jacents.
     *
     */
    void asset(float** &market);
};


#endif //PROJETMODPRO_BLACKSCHOLESMODEL_H
