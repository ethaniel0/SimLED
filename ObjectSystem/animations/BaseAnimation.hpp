#ifndef BASEANIMATION_H
#define BASEANIMATION_H

#include "Animation.hpp"
#include "../LightObject.hpp"
#include "AnimationFunction.hpp"
#include <vector>
#include <map>

class BaseAnimation : public Animation {
  public:
    /// @brief when the bindToLength property is true, successive numbers will be calculated at thit specified frame offset
    int offset;

    /// @brief whether or not the animation should loop once it is finished
    bool loop;

    /// @brief the number of frames that have passed since the animation started. Will reset to zero on loop
    int frames;

    /// @brief the number of frames that the animation should last for
    int duration;

    /// @brief whether or not the animation should bind to the length of the object
    bool bindToLength;

    BaseAnimation(int duration, bool loop, EditableProperties bind);

    /// @brief Update the animation
    void update() override;

    /// @brief returns if the animation is finished
    /// @return true if the animation is finished
    bool isFinished() override;

    /// @brief resets the animation with frame count at 0
    void reset() override;

    /// @brief sets the state of the animation, according to the absolute and relative state triggers
    /// @param state the number of the state to transition to
    void setState(int state) override;

    /// @brief Adds an animation function to the animation, to be used for
    ///        adjusting position, modifying the object's colors, etc. One function
    ///        will be used for movement or brightness, and up to three will be used for color.
    /// @param func the animation function to add
    void addFunction(AnimationFunction* func);

    /// @brief Adds an absolute state trigger to the animation.
    /// @param state the number of the state
    /// @param frame the frame to transition to in the animation
    void addAbsoluteStateTrigger(int state, int frame);

    /// @brief Adds a relative state trigger to the animation.
    /// @param state the number of the state
    /// @param frame the frame relative to the current frame to transition to in the animation
    void addRelativeStateTrigger(int state, int frame);

  private:
    bool done;
    EditableProperties bind;
    std::vector<AnimationFunction*> funcs;
    std::map<int, int> absoluteStateTriggers;
    std::map<int, int> relativeStateTriggers;
};

#endif