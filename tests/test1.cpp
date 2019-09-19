//
// Created by pretrehr on 9/13/19.
//

#include <string>

#include "gtest/gtest.h"
#include "pnl/pnl_vector.h"
#include "pnl/pnl_matrix.h"
#include "jlparser/parser.hpp"
#include "../src/Option.hpp"
#include "../src/Basket.hpp"
#include "../src/Asian.hpp"
#include "../src/Performance.hpp"


using namespace std;

TEST(Payoff, ExampleHard)
{
    PnlVect* lambda = pnl_vect_create_from_scalar(1, 1);
    Basket* basketOption = new Basket(100, 10, 1, 1, lambda);
    PnlMat* path = pnl_mat_create_from_scalar(2, 1, 110);
    EXPECT_EQ(10,basketOption->payoff(path));
    cout << *basketOption << endl;
}

TEST(Payoff, ExampleParsingOption)
{
    string str = "../data/produits/basket_1.dat";
    const char *infile = str.c_str();
    Basket* basketOption = new Basket(infile);
    PnlMat* path = pnl_mat_create_from_scalar(basketOption->getTimeSteps()+1, basketOption->getSize(), 2000);
    EXPECT_EQ(1900, basketOption->payoff(path));
    cout << *basketOption << endl;
}


//TEST(Payoff, ExampleParsingBasket)
//{
//    string str = "../data/produits/basket_2.dat";
//    const char *infile = str.c_str();
//    Basket* basketOption = new Basket(infile);
//    PnlMat* path = pnl_mat_create_from_file("../data/market-data/simul_basket_2.dat");
//    double val2 = basketOption->payoff(path);
//    EXPECT_NEAR(3.79564, basketOption->payoff(path), 0.01);
//}
//
//
//TEST(Payoff, ExampleParsingAsian)
//{
//    string str = "../data/produits/asian.dat";
//    const char *infile = str.c_str();
//    Asian* asianOption = new Asian(infile);
//    PnlMat* path = pnl_mat_create_from_file("../data/market-data/simul_asian.dat");
//    EXPECT_NEAR(0, asianOption->payoff(path), 0.01);
//}
//
//TEST(Payoff, ExampleParsingPerf)
//{
//    string str = "../data/produits/perf.dat";
//    const char *infile = str.c_str();
//    Performance* perfOption = new Performance(infile);
//    PnlMat* path = pnl_mat_create_from_file("../data/market-data/simul_perf.dat");
//    EXPECT_NEAR(1.88337, perfOption->payoff(path), 0.01);
//}


TEST(Display, Example)
{
    string str = "../data/produits/basket_1.dat";
    const char *infile = str.c_str();
    Basket* basketOption = new Basket(infile);
    string strout = "../data/produits/output.dat";
    const char *outfile = strout.c_str();
    basketOption->RedirectToFile(outfile);
    Basket* basketOption2 = new Basket(outfile);
    EXPECT_EQ(basketOption->getSize(), basketOption2->getSize());
    EXPECT_EQ(basketOption->getTimeSteps(), basketOption2->getTimeSteps());
    EXPECT_EQ(basketOption->getMaturity(), basketOption2->getMaturity());
}


TEST(MonteCarlo, Example1)
{
    EXPECT_EQ(0,0);
}


TEST(BlackScholes, Example1)
{
    EXPECT_EQ(0,0);
}