/**
 * \file BlackScholesModel.cpp
 *
 *
 * \brief Fichier source de la classe BlackScholesModel
 *
 * \authors LEBIHAN Lucas, COUTE Lucas, MOMMEJA Léonard, PRÊTRE-HECKENROTH Raphaël
 * Fait le 11.09.2019
 *
 */

#include <iostream>
#include "BlackScholesModel.hpp"
#include "math.h"

/**
 * Génère une trajectoire du modèle et la stocke dans path
 *
 * @param[out] path contient une trajectoire du modèle.
 * C'est une matrice de taille (nbTimeSteps+1) x d
 * @param[in] T  maturité
 * @param[in] nbTimeSteps nombre de dates de constatation
 */
void BlackScholesModel::asset(PnlMat *path, double T, int nbTimeSteps, PnlRng *rng) {

    // Calcul de L
    PnlMat* L = pnl_mat_create_from_scalar(getSize(), getSize(), getRho());
    for (int d = 0; d < getSize(); d++) {
        pnl_mat_set(L, d, d, 1);
    }
    pnl_mat_chol(L);

    // Calcul de G
    PnlMat* G = pnl_mat_create(nbTimeSteps, getSize());
    pnl_mat_rng_normal(G, nbTimeSteps, getSize(), rng);

    // On copie les spots sur le marché
    pnl_mat_set_row(path, getSpot(), 0);

    PnlVect* L_j = pnl_vect_create(getSize());
    PnlVect* G_i = pnl_vect_create(getSize());

    // Pour chaque temps
    for (int i = 1; i <= nbTimeSteps; i++) {
        // Calcul de G_i
        pnl_mat_get_row(G_i, G, i - 1);

        // Pour chaque spot
        for (int j = 0; j < getSize(); j++) {
            double vol = GET(getSigma(), j);
            pnl_mat_get_row(L_j, L, j);
            double exposant = (getR() - SQR(vol) / 2) * T / nbTimeSteps + vol * sqrt(T / nbTimeSteps) * pnl_vect_scalar_prod(L_j, G_i);
            pnl_mat_set(path, i, j, pnl_mat_get(path, i - 1, j) * exp(exposant));
        }
    }
    pnl_mat_free(&L);
}

/**
 * Calcule une trajectoire du modèle connaissant le
 * passé jusqu' à la date t
 *
 * @param[out] path  contient une trajectoire du sous-jacent
 * donnée jusqu'à l'instant t par la matrice past
 * @param[in] t date jusqu'à laquelle on connait la trajectoire.
 * t n'est pas forcément une date de discrétisation
 * @param[in] nbTimeSteps nombre de pas de constatation
 * @param[in] T date jusqu'à laquelle on simule la trajectoire
 * @param[in] past trajectoire réalisée jusqu'a la date t
 */
void BlackScholesModel::asset(PnlMat *path, double t, double T, int nbTimeSteps, PnlRng *rng, const PnlMat *past) {

    // Calcul de L
    PnlMat* L = pnl_mat_create_from_scalar(getSize(), getSize(), getRho());
    for (int d = 0; d < getSize(); d++) {
        pnl_mat_set(L, d, d, 1);
    }
    pnl_mat_chol(L);
    PnlVect* L_j = pnl_vect_create(getSize());

    // Calcul de G
    PnlMat* G = pnl_mat_create(nbTimeSteps + 2 - past->m, getSize());
    pnl_mat_rng_normal(G, nbTimeSteps + 2 - past->m, getSize(), rng);
    PnlVect* G_i = pnl_vect_create(getSize());

    // On copie les résultats avant t sur le marché
    pnl_mat_set_subblock(path, past, 0, 0);

    // Calcul des spots en t_(i+1) en fonction de ceux en t
    pnl_mat_get_row(G_i, G, 0);
    double delta_t = (past->m - 1) * T / nbTimeSteps - t;
    for (int j = 0; j < getSize(); j++) {
        double vol = GET(getSigma(), j);
        pnl_mat_get_row(L_j, L, j);
        double exposant = (getR() - SQR(vol) / 2) * delta_t + vol * sqrt(delta_t) * pnl_vect_scalar_prod(L_j, G_i);
        pnl_mat_set(path, past->m - 1, j, pnl_mat_get(path, past->m - 1, j) * exp(exposant));
    }

    // Pour chaque temps restant
    for (int i = past->m; i <= nbTimeSteps; i++) {
        // Calcul de G_i
        pnl_mat_get_row(G_i, G, i + 1 - past->m);

        // Pour chaque spot
        for (int j = 0; j < getSize(); j++) {
            double vol = GET(getSigma(), j);
            pnl_mat_get_row(L_j, L, j);
            double exposant = (getR() - SQR(vol) / 2) * T / nbTimeSteps + vol * sqrt(T / nbTimeSteps) * pnl_vect_scalar_prod(L_j, G_i);
            pnl_mat_set(path, i, j, pnl_mat_get(path, i - 1, j) * exp(exposant));
        }
    }
}

/**
 * Shift d'une trajectoire du sous-jacent
 *
 * @param[in]  path contient en input la trajectoire
 * du sous-jacent
 * @param[out] shift_path contient la trajectoire path
 * dont la composante d a été shiftée par (1+h)
 * à partir de la date t.
 * @param[in] t date à partir de laquelle on shift
 * @param[in] h pas de différences finies
 * @param[in] d indice du sous-jacent à shifter
 * @param[in] timestep pas de constatation du sous-jacent
 */
void BlackScholesModel::shiftAsset(PnlMat *shift_path, const PnlMat *path, int d, double h, double t, double timestep) {
    //TODO
}

