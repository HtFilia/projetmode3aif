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

#include "../src/Basket.hpp"
#include "../src/Asian.hpp"
#include "../src/Performance.hpp"
#include "pnl/pnl_vector.h"
#include "pnl/pnl_matrix.h"

int main(int argc, char *argv[]) {
    int N = 1;
    int d = 2;
    int T = N / 252;
    int K = 200;
    PnlVect* lambda = pnl_vect_create_from_scalar(d, 1);
    Basket* basketOption = new Basket(K, T, d, N, lambda);
    Asian* asianOption = new Asian(K, T, d, N, lambda);
    Performance* performanceOption = new Performance(T, d, N, lambda);
    PnlMat* path = pnl_mat_create(N+1, d);
    pnl_mat_set(path, 0, 0, 100); pnl_mat_set(path, 0, 1, 100);
    pnl_mat_set(path, 1, 0, 103); pnl_mat_set(path, 1, 1, 99);
    try {
        std::cout << basketOption->payoff(path) << std::endl;
        std::cout << asianOption->payoff(path) << std::endl;
        std::cout << performanceOption->payoff(path) << std::endl;

    }
    catch(std::string const& chain) {
        std::cerr << chain << std::endl;
    }
    return 0;
}
