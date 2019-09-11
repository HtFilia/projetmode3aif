/**
 * \file MonteCarlo.h
 *
 *
 * \brief Fichier header de la classe MonteCarlo.
 *
 * \authors LEBIHAN Lucas, COUTE Lucas, MOMMEJA Léonard, PRÊTRE-HECKENROTH Raphaël
 * Fait le 11.09.2019
 *
 */


#ifndef PROJETMODPRO_MONTECARLO_H
#define PROJETMODPRO_MONTECARLO_H


#include <utility>
#include "BlackScholesModel.h"
#include "Option.h"

/**
 * \class MonteCarlo
 *
 * \brief Classe statique permettant de calculer la valeur d'une option.
 *
 */

class MonteCarlo {

private:

    /**
     * \brief sampleNumber représente le nombre de simulations dans la méthode de MonteCarlo.
     *
     */
     long sampleNumber;


public:

    /**
     * \brief Getter de l'attribut \refitem sampleNumber.
     *
     * @return La valeur de l'attribut  \refitem sampleNumber.
     */
    long getSampleNumber() {
        return this->sampleNumber;
    }

    /**
     * \brief Setter de l'attribut \refitem sampleNumber.
     *
     * \param newSampleNumber La nouvelle valeur de \refitem sampleNumber.
     *
     */
    void setSampleNumber(long newSampleNumber) {
        this->sampleNumber = newSampleNumber;
    }

    /**
     * TODO
     * @param option
     * @param blackScholesModel
     * @return
     */
    std::pair<double, double> price (Option option,
            BlackScholesModel blackScholesModel);
};


#endif //PROJETMODPRO_MONTECARLO_H
