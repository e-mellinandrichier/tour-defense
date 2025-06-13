#ifndef SPEED_STRATEGY_HPP
#define SPEED_STRATEGY_HPP

class SpeedStrategy {
public:
    virtual float generateSpeed() const = 0;
    virtual ~SpeedStrategy() = default;
};

#endif
