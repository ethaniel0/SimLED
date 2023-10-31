//
// Created by Ethan Horowitz on 10/20/23.
//
#include "AnimationGroups.h"

/** Sequence **/

AnimationSequence::AnimationSequence(bool doesLoop) {
    loop = doesLoop;
    currentAnimation = 0;
    done = false;
}

void AnimationSequence::addAnimation(Animation *animation) {
    this->animations.append(animation);
}

void AnimationSequence::addNextTrigger(int stateNumber) {
    this->nextStates.append(stateNumber);
}

void AnimationSequence::addResetTrigger(int stateNumber) {
    this->resetStates.append(stateNumber);
}

void AnimationSequence::update(){
    if (done) return;
    auto* anim = animations.get(currentAnimation);
    anim->update();
    if(!anim->isFinished()) return;

    currentAnimation++;
    if (currentAnimation < animations.getLength()) return;
    if (loop) reset();
    else done = true;
}

bool AnimationSequence::isFinished() {
    return done;
}

void AnimationSequence::reset() {
    done = false;
    currentAnimation = 0;
    animations.moveToStart();
    int len = animations.getLength();
    for (int i = 0; i < len; i++) {
        animations.current()->reset();
        animations.next();
    }
}

void AnimationSequence::setState(int state) {

    bool foundNext = nextStates.search(state);
    if (foundNext){
        currentAnimation++;
        if (currentAnimation >= animations.getLength()){
            if (loop) reset();
            else done = true;
        }
        return;
    }
    bool foundReset = resetStates.search(state);
    if (foundReset){
        reset();
    }

}

Animation *AnimationSequence::clone() {
    auto seq = new AnimationSequence(loop);
    animations.moveToStart();
    int len = animations.getLength();
    for (int i = 0; i < len; i++) {
        seq->addAnimation(animations.current()->clone());
        animations.next();
    }

    nextStates.moveToStart();
    len = nextStates.getLength();
    for (int i = 0; i < len; i++) {
        seq->addNextTrigger(nextStates.current());
        nextStates.next();
    }

    resetStates.moveToStart();
    len = resetStates.getLength();
    for (int i = 0; i < len; i++) {
        seq->addResetTrigger(resetStates.current());
        resetStates.next();
    }
    return seq;
}

/** State Map **/

AnimationStateMap::AnimationStateMap() {
    currentAnimation = nullptr;
    for (auto & i : stateMap){
        i = nullptr;
    }
}

void AnimationStateMap::addState(int state, Animation *animation) {
    if (state < 0 || state > 15) return;
    stateMap[state] = animation;
}

void AnimationStateMap::update() {
    if (currentAnimation == nullptr) return;
    currentAnimation->update();
}

bool AnimationStateMap::isFinished() {
    if (currentAnimation == nullptr) return false;
    return currentAnimation->isFinished();
}

void AnimationStateMap::reset() {
    currentAnimation = nullptr;
    for (auto anim : stateMap){
        anim->reset();
    }
}

void AnimationStateMap::setState(int state) {
    if (state < 0 || state > 15) return;
    auto s = stateMap[state];
    if (s != nullptr){
        currentAnimation = s;
    }
}

Animation *AnimationStateMap::clone() {
    auto map = new AnimationStateMap();
    for (int i = 0; i < 16; i++){
        map->addState(i, stateMap[i]->clone());
    }
    return map;
}
