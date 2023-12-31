#ifndef ANIMATION_H
#define ANIMATION_H

#include "../objects/LightObject.h"

class LightObject;

class Animation{
    public:

        virtual ~Animation() = default;

        virtual void update(int32_t *data) = 0;
        virtual bool isFinished() = 0;
        virtual void reset() = 0;
        virtual void setState(int state) = 0;
        virtual void setFrame(int frame) = 0;

        /// @brief sets the object that the animation applies to (only one at a time)
        /// @param object the object to apply the animation to
        virtual void linkObject(LightObject* object);

        virtual Animation* clone() = 0;
    
    protected:
        LightObject* obj{};
};

#endif