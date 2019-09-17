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
    PnlVect* lambda = pnl_vect_create_from_scalar(1, 1);
    Basket* basketOption = new Basket(100, 10, 1, 1, lambda);
    Asian* asianOption = new Asian(100, 10, 1, 1, lambda);
    Performance* performanceOption = new Performance(10, 1, 1, lambda);
    PnlMat* path = pnl_mat_create(2, 1);
    pnl_mat_set(path, 0, 0, 100);
    pnl_mat_set(path, 1, 0, 110);
    try {
        std::cout << basketOption->payoff(path) << std::endl;
        std::cout << asianOption->payoff(path) << std::endl;
        std::cout << performanceOption->payoff(path) << std::endl;

    }
    catch(std::string const& chain) {
        std::cerr << chain << std::endl;
    }

    //free
    pnl_vect_free(&lambda);
    delete basketOption;
    delete asianOption;
    delete performanceOption;
    pnl_mat_free(&path);
    return 0;
}
