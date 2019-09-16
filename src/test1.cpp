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
    int size;
    size_t n_samples;

    string str = "../produits/basket.dat";
    const char *infile = str.c_str();
    Param *P = new Parser(infile);

    P->extract("option type", type);
    P->extract("maturity", T);
    P->extract("option size", size);
    P->extract("spot", spot, size);
    P->extract("volatility", sigma, size);
    P->extract("interest rate", r);
    if (P->extract("dividend rate", divid, size, true) == false)
    {
        divid = pnl_vect_create_from_zero(size);
    }
    P->extract("strike", strike);
    P->extract("sample number", n_samples);
    P->extract("payoff coefficients", payoff_coefficients, 1);
    Basket* basketOption = new Basket(strike, T, size, n_samples, payoff_coefficients);
    PnlMat* path = pnl_mat_create_from_scalar(2, 1, 110);
    cout << basketOption->payoff(path) << endl;
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