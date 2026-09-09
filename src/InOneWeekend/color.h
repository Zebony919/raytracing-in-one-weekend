#ifndef COLOR_H
#define COLOR_H

#include <fstream>
#include "vec3.h"
#include "interval.h"

// Can initialise a vec3 with color keyword
using color = vec3;

void write_color(std::ofstream& out, const color& pixel_color) {
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    static interval intensity(0.000, 0.999);
    int rbyte = int(255.999 * intensity.clamp(r));
    int gbyte = int(255.999 * intensity.clamp(g));
    int bbyte = int(255.999 * intensity.clamp(b));

    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

#endif