/**
 * \file Performance.hpp
 *
 * \brief Fichier header de la classe Performance
 *
 * \authors LEBIHAN Lucas, COUTE Lucas, MOMMEJA Léonard, PRÊTRE-HECKENROTH Raphaël
 * Fait le 11.09.2019
 *
 */

#ifndef PROJETMODPRO_PERFORMANCE_H
#define PROJETMODPRO_PERFORMANCE_H

#include "iostream"
#include "Option.hpp"
#include "pnl/pnl_vector.h"
#include "pnl/pnl_mathtools.h"

class Performance: public Option {

private:

    /**
     * \brief lambda_ représente le vecteur des coefficients de l'option.
     *
     */
    PnlVect *lambda_;

public:

    /**
     * \brief Constructeur du Performance Option.
     *
     */
    Performance(double maturity, int size, int nbTimeSteps, PnlVect* lambda) {
        this->T_ = maturity;
        this->size_ = size;
        this->nbTimeSteps_ = nbTimeSteps;
        this->lambda_ = lambda;
    }

    Performance(const char *InputFile) {
        Parser *P = new Parser(InputFile);
        int size;
        P->extract("maturity", this->T_);
        P->extract("option size", size);
        this->size_ = size;
        P->extract("hedging dates number", this->nbTimeSteps_);
        P->extract("payoff coefficients", this->lambda_, size);
    }

    /**
     * Destructeur
     */
    ~Performance(){}

    /**
     * \brief Calcule le payoff de l'option Basket suivant le marché qu'on lui donne.
     *
     * @param[out] path le marché contenant les spots des sous-jacents
     * 					aux différents temps étudiés.
     *
     * @return la valeur du payoff du Call.
     *
     */
    double payoff(const PnlMat *path) {
        if (path->m != getTimeSteps() + 1) {
            throw std::string("Le nombre de pas ne correspond pas à la taille du marché");
        } else if (path->n != getSize()) {
            throw std::string("Le nombre d'actifs sous-jacents ne correspond pas au marché");
        } else {
            double res = 1;
            PnlVect *oldSpots = pnl_vect_new();
            pnl_mat_get_row(oldSpots, path, 0);
            PnlVect *currentSpots = pnl_vect_new();
            for (int i = 1; i <= getTimeSteps(); i++) {
                pnl_mat_get_row(currentSpots, path, i);
                res += MAX(pnl_vect_scalar_prod(lambda_, currentSpots) / pnl_vect_scalar_prod(lambda_, oldSpots) - 1, 0);
                pnl_vect_clone(oldSpots, currentSpots);
            }
            pnl_vect_free(&oldSpots);
            pnl_vect_free(&currentSpots);
            return res;
        }
    }
};

#endif //PROJETMODPRO_PERFORMANCE_H
