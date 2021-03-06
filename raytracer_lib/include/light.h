//
// Created by Adam Keim on 7/4/20.
//

#ifndef TEENSYTRACER_LIGHT_H
#define TEENSYTRACER_LIGHT_H

#include "tuple.h"
#include "color.h"

class PointLight {
public:
    PointLight(Tuple position, Color intensity) : position(position), intensity(intensity) {
    };
    Tuple position;
    Color intensity;

    friend bool operator==(PointLight const &c1, PointLight const &c2) {
        return (c1.intensity == c2.intensity and c1.position == c2.position);
    }

};


#endif //TEENSYTRACER_LIGHT_H
