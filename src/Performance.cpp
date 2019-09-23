/**
* \file Performance.cpp
*
* \brief Fichier source de la classe Performance
*
* \authors LEBIHAN Lucas, COUTE Lucas, MOMMEJA Léonard, PRÊTRE-HECKENROTH Raphaël
* Fait le 11.09.2019
*
*/

#include <iostream>

#include "Option.hpp"
#include "Performance.hpp"
#include "pnl/pnl_vector.h"
#include "pnl/pnl_mathtools.h"
#include "jlparser/parser.hpp"

/**
* \brief Constructeur du Performance Option.
*
*/
Performance::Performance(double maturity, int size, int nbTimeSteps, PnlVect* lambda) {
    this->T_ = maturity;
    this->size_ = size;
    this->nbTimeSteps_ = nbTimeSteps;
    this->lambda_ = lambda;
}

/**
* \brief Constructeur du Performance Option à partir d'un Fichier,
*        lecture à l'aide d'un Parser.
*
* @param[in] Le fichier contenant les paramètres de l'option Performance.
*
*/
Performance::Performance(const char *InputFile) {
    Parser *P = new Parser(InputFile);
    int size;
    P->extract("maturity", this->T_);
    P->extract("option size", size);
    this->size_ = size;
    P->extract("timestep number", this->nbTimeSteps_);
    P->extract("payoff coefficients", this->lambda_, size);
}

/**
* Destructeur
*/
//destructuer n'a pas à libérer le lambda, vous devez libérer les pnl_vect vous memes dans les tests selon moi
Performance::~Performance(){
    if (lambda_) {
        pnl_vect_free(&lambda_);
    }
}

void Performance::setLambda(PnlVect *lambda) {
    lambda_ = lambda;
}

/**
* \brief Calcule le payoff de l'option Basket suivant le marché qu'on lui donne.
*
* @param[out] path le marché contenant les spots des sous-jacents
* 					aux différents temps étudiés.
*
* @return la valeur du payoff du Call.
*
*/
double Performance::payoff(const PnlMat *path) {
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