/**
 * \file Option.h
 *
 * \brief Fichier header de la classe Option
 *
 * \authors LEBIHAN Lucas, COUTE Lucas, MOMMEJA Léonard, PRÊTRE-HECKENROTH Raphaël
 * Fait le 11.09.2019
 *
 */

#ifndef PROJETMODPRO_BASKET_H
#define PROJETMODPRO_BASKET_H

class Basket : public Option {

    virtual float payoff(float** valuesShares) {
        float res = 0;
        for (int d = O; d < optionSize; d++) {
            res += 0;
        }
        return 0;
    }

};

#endif //PROJETMODPRO_BASKET_H
