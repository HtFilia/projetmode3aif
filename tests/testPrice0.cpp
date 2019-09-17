/**
 * \file testPrice0.cpp
 *
 * \brief Fichier test de la méthode Price en 0 pour différentes options.
 *
 * \authors LEBIHAN Lucas, COUTE Lucas, MOMMEJA Léonard, PRÊTRE-HECKENROTH Raphaël
 * Fait le 13.09.2019
 *
 */


#include <iostream>
#include <stdio.h>
#include "../src/MonteCarlo.hpp"
#include "../src/Basket.hpp"
#include "../src/Asian.hpp"
#include "../src/Performance.hpp"
#include "pnl/pnl_vector.h"
#include "pnl/pnl_matrix.h"

int main(int argc, char *argv[]) {
    // Hardcoded parameters
    double K = 100;
    int fdSteps = 2;
    int M = 100000;
    int N = 100;
    int d = 5;
    double r = 0.05;
    double rho = 0;
    double T = 0.5;
    PnlVect* lambda = pnl_vect_create_from_scalar(d, 0.2);
    PnlVect *sigma = pnl_vect_create_from_scalar(d, 0.1);
    PnlVect *spot = pnl_vect_create_from_scalar(d, 100);

    // Option Init
    Basket* basketAverageOption = new Basket(K, T, d, N, lambda);

    // BSModel Init
    BlackScholesModel *bsModel = new BlackScholesModel(d, r, rho, sigma, spot);
  
    // Market Path Init
    PnlMat* path = pnl_mat_create(N+1, d);

    // RNG Init
    PnlRng *rng = pnl_rng_create(PNL_RNG_MERSENNE);
    pnl_rng_sseed(rng, time(NULL));

    // Monte Carlo Init
    MonteCarlo* monteCarlo = new MonteCarlo(bsModel, basketAverageOption, rng, fdSteps, M);
    double price = 0;
    double ic = 0;

    // Test Pricer en 0
    monteCarlo->price(price, ic);
    std::cout << "Prix en 0 : " << price << std::endl;
    std::cout << "Largeur intervalle Confiance : " << ic << std::endl;

    return 0;
}


