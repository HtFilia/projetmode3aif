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

private:

    /**
     * \brief K_ représente le strike de l'option.
     *
     */
    double K_;

    /**
     * \brief lambda_ représente le vecteur des coefficients de l'option.
     *
     */
    PnlVect *lambda_;

    virtual double payoff(PnlMat *path) {
        double res = pnl_vect_scalar_prod(lambda_, lambda_) - K;

        return res;
    }

};

#endif //PROJETMODPRO_BASKET_H
