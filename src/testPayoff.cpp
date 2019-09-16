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

#include "Basket.hpp"
#include "pnl/pnl_vector.h"
#include "pnl/pnl_matrix.h"

int main(int argc, char *argv[]) {
    PnlVect* lambda = pnl_vect_create_from_scalar(1, 1);
    Basket* basketOption = new Basket(100, 10, 1, 1, lambda);
    PnlMat* path = pnl_mat_create_from_scalar(2, 1, 110);
    try {
        std::cout << basketOption->payoff(path) << std::endl;
    }
    catch(std::string const& chain) {
        std::cerr << chain << std::endl;
    }
    return 0;
}
