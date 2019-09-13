/**
 * \file Basket.hpp
 *
 * \brief Fichier header de la classe Option
 *
 * \authors LEBIHAN Lucas, COUTE Lucas, MOMMEJA Léonard, PRÊTRE-HECKENROTH Raphaël
 * Fait le 11.09.2019
 *
 */

#ifndef PROJETMODPRO_BASKET_H
#define PROJETMODPRO_BASKET_H

#include "Option.hpp"
#include "pnl/pnl_vector.h"
#include "pnl/pnl_mathtools.h"

class Basket: public Option {

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

public:

	/**
	 * \brief Constructeur du Basket Option.
	 *
	 */
	Basket(double strike, double maturity, int size, int nbTimeSteps, PnlVect* lambda) {
		this->T_ = maturity;
		this->size_ = size;
        this->nbTimeSteps_ = nbTimeSteps;
	    this->K_ = strike;
		this->lambda_ = lambda;
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
	double payoff(const PnlMat *path) {
	    //TODO faire les exceptions sur la taille de la matrice : (N+1)xsize
		PnlVect lastSpots = pnl_vect_wrap_mat_row(path, getTimeSteps());
	    return MAX(
				pnl_vect_scalar_prod(
				        lambda_,
				        &lastSpots)
				- K_,
				0);
	}

};

#endif //PROJETMODPRO_BASKET_H
