/**
 * \file price0.cpp
 *
 * \brief Fichier source de l'application calculant le prix d'une option en 0 et
 *        les déviations standards des estimateurs pour un data donné en input.
 *
 * \authors LEBIHAN Lucas, COUTE Lucas, MOMMEJA Léonard, PRÊTRE-HECKENROTH Raphaël
 * Fait le 19.09.2019
 *
 */

#include <iostream>
#include <string>

#include "jlparser/parser.hpp"
#include "../src/BlackScholesModel.hpp"
#include "../src/Option.hpp"
#include "../src/Asian.hpp"
#include "../src/Performance.hpp"
#include "../src/Basket.hpp"
#include "../src/PricingResults.hpp"
#include "../src/MonteCarlo.hpp"
#include "pnl/pnl_vector.h"
#include "pnl/pnl_matrix.h"

using namespace std;

int main(int argc, char* argv[]) {

    // Resultat variables
    double prix, prix_std_dev;
    PnlVect* delta, *delta_std_dev;

    // Option
    double T, r, strike, payoffCoeff;
    PnlVect *spot, *sigma, *divid;
    string type;
    int size;
    int timestepNumber;
    size_t n_samples;
    Option *option;
    char *infile = argv[1];
    Param *P = new Parser(infile);

    P->extract("option type", type);
    P->extract("maturity", T);
    P->extract("option size", size);
    P->extract("spot", spot, size);
    P->extract("volatility", sigma, size);
    P->extract("interest rate", r);
    if (P->extract("dividend rate", divid, size, true) == false)
    {
        divid = pnl_vect_create_from_zero(size);
    }
    P->extract("strike", strike);
    P->extract("sample number", n_samples);
    P->extract("timestep number", timestepNumber);
    //P->extract("payoff coefficients", payoffCoeff);

    PnlVect* lambda;
    // pnl_vect_create_from_scalar(size, payoffCoeff);

    if (type == "basket") {
        option = new Basket(strike, T, size, timestepNumber, lambda);
    } else if (type == "asian") {
        option = new Asian(strike, T, size, timestepNumber, lambda);
    } else if (type == "performance") {
        option = new Performance(T, size, timestepNumber, lambda);
    }




    //TODO
    //PricingResults res(prix, prix_std_dev, delta, delta_std_dev);
    //std::cout << res << std::endl;

    //free
    pnl_vect_free(&spot);
    pnl_vect_free(&sigma);
    pnl_vect_free(&divid);
    delete P;

    return 0;
}