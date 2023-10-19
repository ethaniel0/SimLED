//
// Created by Ethan Horowitz on 10/19/23.
//

#ifndef SIMLED_ANIMATIONGROUPS_H
#define SIMLED_ANIMATIONGROUPS_H

#include <vector>
#include <set>
#include "Animation.hpp"

class AnimationSequence : Animation{
public:
    bool loop;
    int currentAnimation;
    AnimationSequence(bool doesLoop);

    void addAnimation(Animation* animation);
    void addNextTrigger(int stateNumber);
    void addResetTrigger(int stateNumber);

    void update() override;
    bool isFinished() override;
    void reset() override;
    void setState(int state) override;

private:
    std::vector<Animation*> animations;
    std::vector<int> nextStates;
    std::vector<int> resetStates;
    bool done;
};

#endif //SIMLED_ANIMATIONGROUPS_H
