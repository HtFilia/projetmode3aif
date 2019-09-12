/**
 * \file Option.h
 *
 * \brief Fichier header de la classe Option
 *
 * \authors LEBIHAN Lucas, COUTE Lucas, MOMMEJA Léonard, PRÊTRE-HECKENROTH Raphaël
 * Fait le 11.09.2019
 *
 */
#ifndef PROJETMODPRO_OPTION_H
#define PROJETMODPRO_OPTION_H

#include "pnl/pnl_vector.h"
#include "pnl/pnl_matrix.h"

/**
 * \class Option
 *
 * \brief Classe représentant une Option quelque soit son type.
 *
 */
class Option {


private:

    /**
     * \brief T_ représente la maturité de l'option.
     *
     */
    double T_;


    /**
     * \brief optionSize représente la dimension du modèle (redondant avec BlackScholesModel).
     *
     */
    int size_;

    /**
     * \brief nbTimeSteps_ représente le nombre de pas de temps de discrétisation.
     *
     */
    int nbTimeSteps_;

public:

    /**
     * \brief payoff calcule la valeur du payoff sur la trajectoire.
     *
     * \param[in] path est une matrice de taille (N+1) x D contenant une trajectoire du modèle telle que créée par la fonction asset.
     *
     * \return le payoff de l'option (c'est le résultat de la fonction phi appliqué à la trajectoire).
     */
    virtual double payoff(const PnlMat *path) = 0;


};


#endif //PROJETMODPRO_OPTION_H
