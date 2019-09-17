//
// Created by pretrehr on 9/13/19.
//

#include <string>

#include "gtest/gtest.h"
#include "Basket.hpp"
#include "pnl/pnl_vector.h"
#include "pnl/pnl_matrix.h"
#include "jlparser/parser.hpp"

using namespace std;

TEST(Payoff, Example1)
{
    PnlVect* lambda = pnl_vect_create_from_scalar(1, 1);
    Basket* basketOption = new Basket(100, 10, 1, 1, lambda);
    PnlMat* path = pnl_mat_create_from_scalar(2, 1, 110);
    EXPECT_EQ(10,basketOption->payoff(path));
}

TEST(Payoff, ExampleParsing)
{
    double T, r, strike;
    PnlVect *spot, *sigma, *divid, *payoff_coefficients;
    string type;
    int size, nbTimeSteps;
    size_t n_samples;

    string str = "../data/produits/basket.dat";
    const char *infile = str.c_str();
    Param *P = new Parser(infile);

    P->extract("option type", type);
    P->extract("maturity", T);
    P->extract("option size", size);
    P->extract("spot", spot, size);
    P->extract("volatility", sigma, size);
    P->extract("interest rate", r);
    if (!P->extract("dividend rate", divid, size, true))
    {
        divid = pnl_vect_create_from_zero(size);
    }
    P->extract("strike", strike);
    P->extract("hedging dates number", nbTimeSteps);
    P->extract("payoff coefficients", payoff_coefficients, size);
    Basket* basketOption = new Basket(strike, T, size, nbTimeSteps, payoff_coefficients);
    PnlMat* path = pnl_mat_create_from_scalar(nbTimeSteps+1, size, 2000);
    EXPECT_EQ(1900, basketOption->payoff(path));
//    cout << a << endl;
    pnl_vect_free(&spot);
    pnl_vect_free(&sigma);
    pnl_vect_free(&divid);
    delete P;
}



TEST(Payoff, ExampleParsing2)
{
    double T, r, strike;
    PnlVect *spot, *sigma, *divid, *payoff_coefficients;
    string type;
    int size;
    int nbTimeSteps;

    string str = "../data/produits/basket_1.dat";
    const char *infile = str.c_str();
    Param *P = new Parser(infile);

    P->extract("option type", type);
    P->extract("maturity", T);
    P->extract("option size", size);
    P->extract("spot", spot, size);
    P->extract("volatility", sigma, size);
    P->extract("interest rate", r);
    if (!P->extract("dividend rate", divid, size, true))
    {
        divid = pnl_vect_create_from_zero(size);
    }
    P->extract("strike", strike);
    P->extract("hedging dates number", nbTimeSteps);
    P->extract("payoff coefficients", payoff_coefficients, size);
    Basket* basketOption = new Basket(strike, T, size, nbTimeSteps, payoff_coefficients);
    PnlMat* path = pnl_mat_create_from_file("../data/market-data/simul_basket_1.dat");
    EXPECT_NEAR(3.79564, basketOption->payoff(path), 0.01);
//    cout << a << endl;
    pnl_vect_free(&spot);
    pnl_vect_free(&sigma);
    pnl_vect_free(&divid);
    delete P;
}



TEST(MonteCarlo, Example1)
{
    EXPECT_EQ(0,0);
}


TEST(BlackScholes, Example1)
{
    EXPECT_EQ(0,0);
}