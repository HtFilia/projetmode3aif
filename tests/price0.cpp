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
#include <stdio.h>
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

int main(int argc, char **argv) {

    // Resultat variables
    double prix, prix_std_dev;
    PnlVect* delta, *delta_std_dev;

    // Option variables
    double T, strike, payoffCoeff;
    PnlVect *divid, *lambda;
    string type;
    int size;
    int timestepNumber;
    Option *option;

    // BSModel variables
    int dim;
    double r, rho;
    PnlVect *spot, *sigma;

    // MonteCarlo variables
    size_t n_samples;
    PnlRng *rng = pnl_rng_create(PNL_RNG_MERSENNE);
    pnl_rng_sseed(rng, 1);
    double fdSteps;

    // Parser and file to parse
    char *infile = argv[1];
    Param *P = new Parser(infile);

    // Parsing
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
    P->extract("payoff coefficients", lambda, size);
    P->extract("sample number", n_samples);
    fdSteps = T / n_samples;

    // Create Option according to parameters
    if (type == "basket") {
        option = new Basket(strike, T, size, timestepNumber, lambda);
    } else if (type == "asian") {
        option = new Asian(strike, T, size, timestepNumber, lambda);
    } else if (type == "performance") {
        option = new Performance(T, size, timestepNumber, lambda);
    }

    // Create BSModel according to parameters
    BlackScholesModel *bsModel = new BlackScholesModel(dim, r, rho, sigma, spot);

    // Create Market according to parameters
    PnlMat *path = pnl_mat_create(timestepNumber + 1, dim);
    bsModel->asset(path, T, timestepNumber, rng);
    pnl_rng_sseed(rng, time(NULL));

    // Create MonteCarlo according to parameters
    MonteCarlo *monteCarlo = new MonteCarlo(bsModel, option, rng, fdSteps, n_samples);

    // Get price, deltas and st.deviation
    monteCarlo->price(prix, prix_std_dev);
    monteCarlo->delta(path, 0, delta, delta_std_dev);

    // Print Results
    PricingResults res(prix, prix_std_dev, delta, delta_std_dev);
    std::cout << res << std::endl;

    //free
    pnl_vect_free(&spot);
    pnl_vect_free(&sigma);
    pnl_vect_free(&divid);
    pnl_rng_free(&rng);
    delete P;
    delete option;
    delete bsModel;
    delete monteCarlo;
    return 0;
}