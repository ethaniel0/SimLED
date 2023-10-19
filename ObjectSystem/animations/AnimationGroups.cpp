//
// Created by Ethan Horowitz on 10/20/23.
//
#include "AnimationGroups.h"

AnimationSequence::AnimationSequence(bool doesLoop) {
    loop = doesLoop;
    currentAnimation = 0;
    done = false;
}

void AnimationSequence::addAnimation(Animation *animation) {
    this->animations.push_back(animation);
}

void AnimationSequence::addNextTrigger(int stateNumber) {
    this->nextStates.push_back(stateNumber);
}

void AnimationSequence::addResetTrigger(int stateNumber) {
    this->resetStates.push_back(stateNumber);
}

bool AnimationSequence::isFinished() {
    return done;
}
