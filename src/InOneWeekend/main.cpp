#include <iostream>
#include <fstream>

#include <cmath>
#include "vec3.h"
#include "color.h"
#include "ray.h"

bool hit_sphere(const point3& center, const double radius, const ray& r) {
    vec3 oc = center - r.origin();
    double a = dot(r.direction(), r.direction());
    double b = -2.0 * dot((r.direction()), oc);
    double c = dot(oc, oc) - radius * radius;
    auto discriminant = b * b - (4 * a * c);

    // Not needed but cool to see in rendering
    // t1 represents the intersection at the back of the sphere
    // t2 represents the intersection at the front of the sphere
    auto t1 = (-b + std::sqrt(discriminant)) / (2 * a);
    auto t2 = (-b - std::sqrt(discriminant)) / (2 * a);

    return (discriminant >= 0);
}

color ray_color(const ray& r) {
    if (hit_sphere(vec3(0, 0, -1), 0.5, r)) {
        return color(1, 0, 0);
    }

    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}

int main() {
    // Image Dimensions
    auto aspect_ratio = 16.0 / 9.0;
    int image_width = 400;

    int image_height = int(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    // Camera
    auto focal_length = 1.0;
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (double(image_width) / image_height);
    auto camera_center = point3(0, 0, 0);

    // Calculate horizontal and down vectors on the vertical viewport edges
    auto viewport_u = vec3(viewport_width, 0, 0);
    auto viewport_v = vec3(0, -viewport_height, 0);

    // Calculate horizontal and down delta vectors, pixel to pixel
    auto pixel_delta_u = viewport_u / image_width;
    auto pixel_delta_v = viewport_v / image_height;

    // Find location of upper left pixel
    auto viewport_upper_left = camera_center - vec3(0, 0, focal_length) - (viewport_u / 2) - (viewport_v / 2);
    auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    std::ofstream out("image.ppm", std::ios::binary);
    if (!out) {
        std::cerr << "Error opening file for writing\n";
        return 1;
    }

    // Writing to a PPM image file
    out << "P3\n" << image_width << ' ' <<  image_height << "\n255\n";

    for (int j = 0; j < image_height; j++) {
        // Progress update for rendering
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;

        for (int i = 0; i < image_width; i++) {
            auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
            auto ray_direction = pixel_center - camera_center;
            ray r(camera_center, ray_direction);

            auto pixel_color = ray_color(r);
            write_color(out, pixel_color);
        }
    }

    out.close();
    std::clog << "\rDone.                 \n";
    return 0;
}