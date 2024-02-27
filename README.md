# SIMLED / ObjectSystem

## Overview

SimLED is the full project, which includes the ObjectSystem library plus the simulator application.

For the simulator application, I chose a very simple library called [libxd](https://bernhardfritz.github.io/libxd/#/). Please build it yourself and replace the libxd folder with the build folder of libxd.

## ObjectSystem

Here is a simple sample program that displays a rainbow on a light strip:

```cpp
#include "ObjectSystem.h"
#define NUM_LEDS 60
CRGB* strip1;
ObjectSystem* objectSystem;

int main(){
    objectSystem = new ObjectSystem();

    objectSystem->strip.addStrip(NUM_LEDS);
    strip1 = objectSystem->strip.getStrip(0);

    LightObject* obj = new LightObject(NUM_LEDS);
    BaseAnimation* gradient = new BaseAnimation(1, true, COLORS);
    gradient.bindToLength = true;
    gradient.lightOffset = 255 / NUM_LEDS;
    
    AnimationFunction* grad = new LinearTransform(0, 255);
    gradient->addFunction(grad);
    obj->addAnimation(gradient);
    objectSystem->addObject(obj);

    objectSystem->update();
    return 0;
}
```



The ObjectSystem library is an object-oriented library that makes use of FastLED. It relies on the following classes:

### ObjectSystem:
ObjectSystem stores the internal state of the whole system, including the links to the LED strip CRGB arrays and the collection of objects.

It contains the following methods:

- `void addObject(Object* object)`: Adds an object to the collection.
- `void update()`: Updates the state of the system.
- `void setState(int i)`: applies the state i to the system (this will be explained below).

### LightStrip:
LightStrip is a class that holds one or more RGB arrays for light strips. They are cascaded linearly, so the first LED of the second strip is connected to the last LED of the first strip.
Everything animating on the LightStrip will take place using light objects.

### LightObject:
The default object that can be placed on a LightStrip. You can define it as a number of LEDs or by using an array of colors.
To animate the object on the strip, add animations with 
```c++
obj.addAnimation(&animation)
```

### Generator
A generator is an invisible object on the light strip that generates a new object every n frames, specified as 
```c++
generator.spacing = n
```

Find examples in the examples folder.

### Animations:
Animations are the way to change the state of an object. For movement, colors, length, and any other parameter of a LightObject,
use `BaseAnimation`. To create a back-to-back sequence of animations, use `AnimationSequence`. And to map animations to states (discussed below),
use `AnimationStateMap`.

To create animations that react to external data, use pass an animation into a `DataReactor` animation.

To create custom animations, create a class that extends `Animation` from `Animation.h`.

Find examples in the examples folder.

### AnimationFunctions:
AnimationFunctions define how BaseAnimations move. They're very similar to CSS animation funcitons, and rely on how
far along the animation is rather than absolute time. The current implemented functions are:
`EaseTransform`, `LinearTransform`, `PerlinTransform`, `RandomTransform`, and `StaticTransform`.


## States
To aid in animation transitions, a pseudo state system is implemented. A signal (int) can be
sent to the ObjectSystem for one frame, which is propagated to all objects and animations. This allows you to reset an animation
to a specific frame, remove objects, switch the animation shown from an `AnimationStateMap`, etc. on this trigger.
To conserve memory, there are only 16 configurable states. To use them, call 
```c++
objectSystem.setState(i)
```

## Reacting to External Data
Aside from setting discrete states, it may be useful to have animations react to external data, such as accelerometer data
or sound volume. For this, the ObjectSystem has 16 integer channels that (as `objectsystem.data`)
that can be set to any value. To have an animation react to this data, wrap it inside a `DataReactor` animation.

## Parsing From A String
Animations, Objects, and the whole ObjectSystem can be parsed from a string. It's not meant to be human-readable, but
it can be useful with the help of other programs to quickly experiment with various animation setups.
Parsing is done through a `SystemCreator` object, which is used as follows:
```c++
SystemCreator creator;
// parse system
ObjectSystem* system = sc.parseSystem("...");
// parse object
PlaceableObject* gen = sc.parseObject("...");
// parse animation
Animation* anim = sc.parseAnimation("...");
// parse animation function
AnimationFunction* func = sc.parseFunction("...");

// extend with custom parsing
Animation* parseCustomAnimation(const char* string, int* pos, SystemCreator* system){
    ...
    return animation;
}

PlaceableObject* parseCustomObject(const char* string, int* pos, SystemCreator* system){
    ...
    return object;
}

sc.addAnimation('a', makeCustomAnimation);
sc.addObject('o', makeCustomObject);
```

### Creating a parser for your animation
String parsing is done linearly, and is done by reading characters and numbers from the string.
The functions of `skipWhiteSpace(const char* string, int* pos)`, `extractNumber(const char* string, int* pos)`, and `extractColor(const char* string, int* pos)` are provided to help with this.
If you want to read characters differently, make sure to use the `incPtr(pos)` function.

If other objects, animations, or functions are to be parsed within your custom object or animation, use the `SystemCreator` object to parse them.

As an example, here is the parser function for creating the generator:
```c++
PlaceableObject* createGenerator(const char* string, int* pos, SystemCreator* sc){
    // syntax: <pos> <spacing> <... object to copy>
    int strip_pos = extractNumber(string, pos);
    int spacing = extractNumber(string, pos);
    PlaceableObject* obj = sc->parseObject(string, pos);
    if (obj == nullptr) return nullptr;
    auto* gen = new Generator(strip_pos, obj);
    gen->spacing = spacing;
    return gen;
}
```
