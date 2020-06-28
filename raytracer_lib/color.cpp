//
// Created by Adam Keim on 6/22/20.
//

#include "color.h"
#include "cmath"

float Color::red() const {
    return this->x;
}

float Color::green() const {
    return this->y;
}

float Color::blue() const {
    return this->z;
}

Color operator*(Color const &c1, Color const &c2) {
    return Color(c1.red() * c2.red(),
                 c1.green() * c2.green(),
                 c1.blue() * c2.blue());

}

Color Color::to_clamped_rgb() const {
    int red = std::fmax(0, std::fmin(255, ceil(this->red() * 255)));
    int green = std::fmax(0, std::fmin(255, ceil(this->green() * 255)));
    int blue = std::fmax(0, std::fmin(255, ceil(this->blue() * 255)));
    return Color(red, green, blue);
}

Color Color::to_rgb() const {
    return Color(this->red() * 255, this->green() * 255, this->blue() * 255);
}

