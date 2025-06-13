#ifndef DINO_BEHAVIOR_HPP
#define DINO_BEHAVIOR_HPP

class DinoBehavior {
public:
    virtual ~DinoBehavior() = default;
    virtual float getSpeed() const = 0;
};

#endif 