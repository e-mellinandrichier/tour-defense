#ifndef RANDOM_SPEED_STRATEGY_HPP
#define RANDOM_SPEED_STRATEGY_HPP

#include "speedstrategy.hpp"
#include <random>

class RandomSpeedStrategy : public SpeedStrategy {
    public : 
    float generateSpeed()const override {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> dist(0.05f, 0.15f); 
        return dist(gen);
    }
};
#endif