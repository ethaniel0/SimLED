//
// Created by Ethan Horowitz on 10/19/23.
//

#ifndef SIMLED_ANIMATIONGROUPS_H
#define SIMLED_ANIMATIONGROUPS_H

#include "../linkedlist/LinkedList.h"
#include "Animation.h"

class AnimationSequence : public Animation{
public:
    bool loop;
    int currentAnimation;
    explicit AnimationSequence(bool doesLoop);

    void addAnimation(Animation* animation);
    void addNextTrigger(int stateNumber);
    void addPrevTrigger(int stateNumber);
    void addResetTrigger(int stateNumber);

    void update(int32_t *data) override;
    bool isFinished() override;
    void reset() override;
    void setState(int state) override;
    void linkObject(LightObject* object) override;
    void setFrame(int frame) override;
    AnimationSequence* clone() override;

private:
    LinkedList<Animation*> animations;
    LinkedList<int> nextStates;
    LinkedList<int> prevStates;
    LinkedList<int> resetStates;
    bool done;
};

class AnimationStateMap : public Animation {
public:
    AnimationStateMap();

    void addState(int state, Animation* animation);

    void update(int32_t *data) override;
    bool isFinished() override;
    void reset() override;
    void setState(int state) override;
    void linkObject(LightObject* object) override;
    void setFrame(int frame) override;
    AnimationStateMap* clone() override;

private:
    Animation* stateMap[16]{};
    Animation* currentAnimation;
};

#endif //SIMLED_ANIMATIONGROUPS_H
