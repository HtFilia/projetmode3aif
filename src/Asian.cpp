/**
* \file Asian.cpp
*
* \brief Fichier source de la classe Asian héritant de la classe Option.
*
* \authors LEBIHAN Lucas, COUTE Lucas, MOMMEJA Léonard, PRÊTRE-HECKENROTH Raphaël
* Fait le 11.09.2019
*
*/

#include <jlparser/parser.hpp>

#include "Option.hpp"
#include "Asian.hpp"
#include "pnl/pnl_vector.h"
#include "pnl/pnl_mathtools.h"

/**
* \class Asian
*
* \brief Classe Asian représentant une Option de type Asiatique.
*
*/
/**
* \brief Constructeur du Basket Option.
*
*/
Asian::Asian(double strike, double maturity, int size, int nbTimeSteps, PnlVect* lambda) {
    this->T_ = maturity;
    this->size_ = size;
    this->nbTimeSteps_ = nbTimeSteps;
    this->K_ = strike;
    this->lambda_ = lambda;
}

Asian::Asian(const char *InputFile) {
    Parser *P = new Parser(InputFile);
    int size;
    P->extract("maturity", this->T_);
    P->extract("option size", size);
    this->size_ = size;
    P->extract("strike", this->K_);
    P->extract("timestep number", this->nbTimeSteps_);
    P->extract("payoff coefficients", this->lambda_, size);
}

/**
* \brief Destructeur de la classe Asian.
*
*/
Asian::~Asian() {};

/**
* \brief Calcule le payoff de l'option Basket suivant le marché qu'on lui donne.
*
* @param[out] path le marché contenant les spots des sous-jacents
* 					aux différents temps étudiés.
*
* @return la valeur du payoff du Call.
*
*/
double Asian::payoff(const PnlMat *path) {
    if (path->m != getTimeSteps() + 1) {
        throw std::string("Le nombre de pas ne correspond pas à la taille du marché");
    } else if (path->n != getSize()) {
        throw std::string("Le nombre d'actifs sous-jacents ne correspond pas au marché");
    } else {
        PnlVect *averageSpots = pnl_vect_new();
        pnl_mat_sum_vect(averageSpots, path, 'r');
        pnl_vect_div_scalar(averageSpots, getTimeSteps() + 1);
        double res = MAX(pnl_vect_scalar_prod(lambda_, averageSpots) - K_, 0);
        pnl_vect_free(&averageSpots);
        return res;
    }
}
