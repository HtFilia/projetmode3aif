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

#include <fstream>

#include "iostream"
#include "Option.hpp"
#include "pnl/pnl_vector.h"
#include "pnl/pnl_mathtools.h"
#include "jlparser/parser.hpp"

using namespace std;

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

	Basket(const char *InputFile) {
	    Parser *P = new Parser(InputFile);
	    int size;
        P->extract("maturity", this->T_);
        P->extract("option size", size);
        this->size_ = size;
        P->extract("strike", this->K_);
        P->extract("timestep number", this->nbTimeSteps_);
        P->extract("payoff coefficients", this->lambda_, size);
        delete P;
	}
    //destructuer n'a pas à libérer le lambda, vous devez libérer les pnl_vect vous memes dans les tests selon moi
	~Basket(){
	    //pnl_vect_free(&lambda_);
	}

    double getK() const {
        return K_;
    }

    PnlVect *getLambda() const {
        return lambda_;
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
        if (path->m != getTimeSteps() + 1) {
            throw std::string("Le nombre de pas ne correspond pas à la taille du marché");
        } else if (path->n != getSize()) {
            throw std::string("Le nombre d'actifs sous-jacents ne correspond pas au marché");
        } else {
            PnlVect *lastSpots = pnl_vect_new();
            pnl_mat_get_row(lastSpots, path, getTimeSteps());
            double res = MAX(pnl_vect_scalar_prod(lambda_, lastSpots) - K_, 0);
            pnl_vect_free(&lastSpots);
            return res;
        }
    }

    void RedirectToFile(const char *path){
        ofstream file;
        file.open(path);
        file << "model type                   <string>     bs\n";
        file << "maturity                     <float>      " << getMaturity() << "\n";
        file << "option size                  <int>        " << getSize() << "\n";
        file << "strike                       <float>      " << K_ << "\n";
        file << "option type                  <string>     basket" << "\n";
        double payoffcoeff = 1/((double) getSize());
        file << "payoff coefficients          <vector>     " << payoffcoeff << "\n";
        file << "timestep number              <int>        " << nbTimeSteps_ << "\n";
        file.close();
    }

};
//
//ostream &operator<<(ostream &os, const Basket &basket) {
//    os << "\nBasket option\n" << static_cast<const Option &>(basket) << "\nK_: " << basket.getK() << "\nlambda_: " << *(basket.getLambda()->array);
//    return os;
//}

#endif //PROJETMODPRO_BASKET_H
