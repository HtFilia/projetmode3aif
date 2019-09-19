/**
 * \file hedge.cpp
 *
 * \brief Fichier source de l'application calculant le prix d'une option en 0
 *        et son portefeuille de couverture pour un data donné en input.
 *
 * \authors LEBIHAN Lucas, COUTE Lucas, MOMMEJA Léonard, PRÊTRE-HECKENROTH Raphaël
 * Fait le 19.09.2019
 *
 */

#include "../src/HedgingResults.cpp"
#include <string>

int main(int argv, char* argc[]) {

    double prix, prix_std_dev, erreur_couverture;

    //TODO

    HedgingResults res(prix, prix_std_dev, erreur_couverture);
    std::cout << res << std::endl;

    return 0;
}