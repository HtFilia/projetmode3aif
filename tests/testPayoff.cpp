/**
 * \file testPayoff.cpp
 *
 * \brief Fichier test de la méthode Payoff pour différentes options.
 *
 * \authors LEBIHAN Lucas, COUTE Lucas, MOMMEJA Léonard, PRÊTRE-HECKENROTH Raphaël
 * Fait le 13.09.2019
 *
 */


#include <iostream>
#include <stdio.h>

#include "../src/BlackScholesModel.hpp"
#include "../src/Basket.hpp"
#include "../src/Asian.hpp"
#include "../src/Performance.hpp"
#include "pnl/pnl_vector.h"
#include "pnl/pnl_matrix.h"

int main(int argc, char *argv[]) {
    int N = 100;
    int d = 5;
    double T = 0.5;
    int K = 100;
    double r = 0.5;
    double rho = 0;
    PnlVect* lambda = pnl_vect_create_from_scalar(d, 0.2);
    PnlVect *sigma = pnl_vect_create_from_scalar(d, 0.1);
    PnlVect *spot = pnl_vect_create_from_scalar(d, 100);

    // RNG Init
    PnlRng *rng = pnl_rng_create(PNL_RNG_MERSENNE);
    pnl_rng_sseed(rng, time(NULL));

    // Market simulation
    BlackScholesModel *bsModel = new BlackScholesModel(d, r, rho, sigma, spot);
    PnlMat* path = pnl_mat_create(N+1, d);
    bsModel->asset(path, T, N, rng);
    pnl_mat_print(path);

    // Création des options
    Basket* basketOption = new Basket(K, T, d, N, lambda);
    Asian* asianOption = new Asian(K, T, d, N, lambda);
    Performance* performanceOption = new Performance(T, d, N, lambda);

    // Calcul et affichage des payoffs
    std::cout << "Payoff du basket : " << basketOption->payoff(path) << std::endl;
    std::cout << "Payoff de l'asian : " << asianOption->payoff(path) << std::endl;
    std::cout << "Payoff du performance : " << performanceOption->payoff(path) << std::endl;

    //free
    pnl_vect_free(&lambda);
    delete basketOption;
    delete asianOption;
    delete performanceOption;
    pnl_mat_free(&path);

    return 0;
}
