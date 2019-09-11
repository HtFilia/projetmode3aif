//
// Created by lebihanl on 9/11/19.
//

#ifndef PROJETMODPRO_MONTECARLO_H
#define PROJETMODPRO_MONTECARLO_H


#include <utility>
#include "BlackScholesModel.h"
#include "Option.h"

static class MonteCarlo {

public:
    std::pair<double, double> price (Option option, BlackScholesModel blackScholesModel);
};


#endif //PROJETMODPRO_MONTECARLO_H
