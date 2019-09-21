/**
 * \file testProfitAndLoss.cpp
 *
 * \brief Fichier test de la méthode P&L pour différentes options.
 *
 * \authors LEBIHAN Lucas, COUTE Lucas, MOMMEJA Léonard, PRÊTRE-HECKENROTH Raphaël
 * Fait le 21.09.2019
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
    double fdSteps = 0.1;
    int M = 1000;
    int N = 40;
    int H = 120;
    int d = 5;
    double r = 0.02;
    double rho = 0;
    double T = 0.5;
    PnlVect *lambda = pnl_vect_create_from_scalar(d, 1 / (double)d);
    PnlVect *sigma = pnl_vect_create_from_scalar(d, 0.1);
    PnlVect *spot = pnl_vect_create_from_scalar(d, 100);

    // Option Init
    Basket *basketAverageOption = new Basket(K, T, d, N, lambda);

    // BSModel Init
    BlackScholesModel *bsModel = new BlackScholesModel(d, r, rho, sigma, spot);

    // RNG Init
    PnlRng *rng = pnl_rng_create(PNL_RNG_MERSENNE);
    pnl_rng_sseed(rng, 1);

    // Monte Carlo Init
    MonteCarlo *monteCarlo = new MonteCarlo(bsModel, basketAverageOption, rng, fdSteps, M);
    PnlMat *deltas = pnl_mat_create(H + 1, d);
    PnlVect *delta0 = pnl_vect_create(H + 1);
    double error;

    // Test Pricer en 0
    double price = 0;
    double ic = 0;
    monteCarlo->price(price, ic);

    // Market Init
    PnlMat *path = pnl_mat_create(H + 1, d);
    bsModel->asset(path, T, H, rng);
    //std::cout << "path : " << std::endl;
    //pnl_mat_print(path);
    pnl_rng_sseed(rng, time(NULL));

    // Test Couverture
    monteCarlo->profitAndLoss(path, deltas, delta0, error);
    //std::cout << "Deltas : " <<  std::endl;
    //pnl_mat_print(deltas);
    //std::cout << "Delta0 : " << std::endl;
    //pnl_vect_print(delta0);
    std::cout << std::endl << "Prix en 0 : " << price << std::endl;
    std::cout << std::endl << "Error : " << error << std::endl;

    return 0;
}