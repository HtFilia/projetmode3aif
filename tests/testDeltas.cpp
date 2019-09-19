/**
 * \file testShiftAsset.cpp
 *
 * \brief Fichier test de la méthode shiftAsset.
 *
 * \authors LEBIHAN Lucas, COUTE Lucas, MOMMEJA Léonard, PRÊTRE-HECKENROTH Raphaël
 * Fait le 19.09.2019
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
    int M = 1000;
    int N = 5;
    int NPast = 2;
    int d = 2;
    double r = 0.05;
    double rho = 0;
    double T = 1;
    double t = T * (NPast + 0.5) / N;
    PnlVect *lambda = pnl_vect_create_from_scalar(d, 0.2);
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
    PnlVect *deltas = pnl_vect_create(d);
    PnlVect *ic = pnl_vect_create(d);

    // Past Market Init (to t_i)
    PnlMat *past = pnl_mat_create(NPast + 2, d);
    bsModel->asset(past, t, NPast + 1, rng);
    pnl_rng_sseed(rng, time(NULL));

    // Test Deltas
    monteCarlo->delta(past, t, deltas, ic);
    std::cout << "Deltas : " <<  std::endl;
    pnl_vect_print(deltas);
    std::cout << "IC : " << std::endl;
    pnl_vect_print(ic);

    return 0;
}