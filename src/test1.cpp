//
// Created by pretrehr on 9/13/19.
//

#include "gtest/gtest.h"
#include "Basket.hpp"
#include "pnl/pnl_vector.h"
#include "pnl/pnl_matrix.h"


TEST(Payoff, Example1){
    PnlVect* lambda = pnl_vect_create_from_scalar(1, 1);
    Basket* basketOption = new Basket(100, 10, 1, 1, lambda);
    PnlMat* path = pnl_mat_create_from_scalar(2, 1, 110);
    EXPECT_EQ(10,basketOption->payoff(path));
}

TEST(TestSuite1, Example2){
    EXPECT_EQ(0,0);
}


TEST(TestSuite2, Example1){
    EXPECT_EQ(0,0);
}