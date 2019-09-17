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

#include "../src/BlackScholesModel.hpp"
#include "pnl/pnl_vector.h"
#include "pnl/pnl_matrix.h"

int main(int argc, char *argv[]) {
    int N = 10;
    int d = 5;
    double r = 0.1;
    double rho = 0.2;
    PnlVect *sigma = pnl_vect_create_from_scalar(d, 0.1);
    PnlVect *spot = pnl_vect_create_from_scalar(d, 100);
    BlackScholesModel *bsModel = new BlackScholesModel(d, r, rho, sigma, spot);

    PnlMat* path = pnl_mat_create(N+1, d);
    double T = 1;
    PnlRng *rng = pnl_rng_create(PNL_RNG_MERSENNE);
    pnl_rng_sseed(rng, time(NULL));
    bsModel->asset(path, T, N, rng);
    pnl_mat_print(path);

    //free
    pnl_vect_free(&sigma);
    pnl_vect_free(&spot);
    delete bsModel;
    pnl_mat_free(&path);
    pnl_rng_free(&rng);

    return 0;
}
