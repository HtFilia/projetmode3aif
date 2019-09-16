/**
 * \file testAsset.cpp
 *
 * \brief Fichier test de la méthode Asset pour différentes options.
 *
 * \authors LEBIHAN Lucas, COUTE Lucas, MOMMEJA Léonard, PRÊTRE-HECKENROTH Raphaël
 * Fait le 13.09.2019
 *
 */


#include <iostream>
#include <stdio.h>

#include "BlackScholesModel.hpp"
#include "pnl/pnl_vector.h"
#include "pnl/pnl_matrix.h"

int main(int argc, char *argv[]) {
    PnlVect *sigma = pnl_vect_create_from_scalar(2, 0.1);
    PnlVect *spot = pnl_vect_create_from_scalar(2, 100);
    PnlRng *rng = pnl_rng_create(PNL_RNG_MERSENNE);
    BlackScholesModel *bsModel = new BlackScholesModel(2, 1.1, 0, sigma, spot);
    PnlMat* path = pnl_mat_create(2, 2);
    bsModel->asset(path, 10, 3, rng);

    return 0;
}
