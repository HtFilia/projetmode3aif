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

#include <libaio.h>
#include <vector>

/**
 * \class Option
 *
 * \brief Classe représentant une Option quelque soit son type.
 *
 */
class Option {


private:

    /**
     * \brief optionType représente le type de l'option.
     */
    char* optionType;

    /**
     * \brief optionSize représente le nombre de sous-jacents liés à l'option.
     *
     */
    int optionSize;

    /**
     * \brief strike représente le strike de l'option.
     *
     */
    float strike;

    /**
     * \brief maturity représente la maturité de l'option.
     *
     */
    float maturity;

    /**
     * \brief payoffCoefficients représente les coefficients appliqués aux différents sous-jacents lors
     *        du calcul du payoff.
     *
     */
     std::vector<float> payoffCoefficients;

public:

    /**
     * \brief payoff calcule le payoff de l'option à l'aide des différents paramètres.
     *
     * \param valuesShares matrice des spots des sous-jacents de l'option à chaque temps discrétisé.
     *
     * \return le payoff de l'option.
     */
    virtual float payoff(float** valuesShares) = 0;


};


#endif //PROJETMODPRO_OPTION_H
