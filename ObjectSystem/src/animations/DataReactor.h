//
// Created by Ethan Horowitz on 12/5/23.
//

#ifndef SIMLED_DATAREACTOR_H
#define SIMLED_DATAREACTOR_H

#include "Animation.h"
#include "../objects/LightObject.h"

/// Sets the frames of the linked animation to the value of the chosen data
class DataReactor : public Animation {
private:
    int dataIndex;
    Animation *linkedAnimation;
public:
    DataReactor(Animation* linkedAnimation, int dataIndex) : linkedAnimation(linkedAnimation), dataIndex(dataIndex) {};
    ~DataReactor() override{
        delete linkedAnimation;
    }

    void update(int32_t *data) override {
        linkedAnimation->setFrame(data[dataIndex]);
        linkedAnimation->update(data);
    }
    bool isFinished() override { return false; }
    void reset() override { linkedAnimation->reset(); }
    void setState(int state) override { linkedAnimation->setState(state); }
    void setFrame(int frame) override { }
    void linkObject(LightObject *object) override { linkedAnimation->linkObject(object); }
    Animation* clone() override { return new DataReactor(linkedAnimation->clone(), dataIndex); }
};


#endif //SIMLED_DATAREACTOR_H
