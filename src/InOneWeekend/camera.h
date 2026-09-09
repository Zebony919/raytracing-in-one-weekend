#ifndef CAMERA_H
#define CAMERA_H

#include <fstream>
#include "hittable.h"

class camera {
    public:
        double aspect_ratio = 1.0;
        int image_width = 100;
        int sample_per_pixel = 10;

        void render(const hittable& world) {
            initialize();

            std::ofstream out("image.ppm", std::ios::binary);
            if (!out) {
                std::cerr << "Error opening file for writing\n";
            }

            out << "P3\n" << image_width << ' ' <<  image_height << "\n255\n";

            // Learn the anti-aliasing change
            for (int j = 0; j < image_height; j++) {
                // Progress update for rendering
                std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;

                for (int i = 0; i < image_width; i++) {
                    color pixel_color(0, 0, 0);
                    
                    for (int sample = 0; sample < sample_per_pixel; sample++) {
                        ray r = get_ray(i, j);
                        pixel_color += ray_color(r, world);
                    }

                    write_color(out, pixel_sample_scale * pixel_color);

                    /*
                    auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
                    auto ray_direction = pixel_center - camera_center;
                    ray r(camera_center, ray_direction);

                    auto pixel_color = ray_color(r, world);
                    write_color(out, pixel_color);
                    */
                }
            }

            out.close();
            std::clog << "\rDone.                 \n";
        }

    private:
        int image_height;
        double pixel_sample_scale;
        point3 camera_center;
        point3 pixel00_loc;
        vec3 pixel_delta_u;
        vec3 pixel_delta_v;

        void initialize() {
            image_height = int(image_width / aspect_ratio);
            image_height = (image_height < 1) ? 1 : image_height;

            pixel_sample_scale = 1.0 / sample_per_pixel;

            camera_center = point3(0, 0, 0);

            const auto focal_length = 1.0;
            const auto viewport_height = 2.0;
            const auto viewport_width = viewport_height * (double(image_width) / image_height);

            // Calculate horizontal and down vectors on the vertical viewport edges
            const auto viewport_u = vec3(viewport_width, 0, 0);
            const auto viewport_v = vec3(0, -viewport_height, 0);

            // Calculate horizontal and down delta vectors, pixel to pixel
            pixel_delta_u = viewport_u / image_width;
            pixel_delta_v = viewport_v / image_height;

            // Find location of upper left pixel
            const auto viewport_upper_left = camera_center - vec3(0, 0, focal_length) - (viewport_u / 2) - (viewport_v / 2);
            pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
        }

        // Learn this
        ray get_ray(int i, int j) const {
            auto offset = sample_square();
            auto pixel_sample = pixel00_loc + ((i + offset.x()) * pixel_delta_u) + ((j + offset.y()) * pixel_delta_v);

            auto ray_origin = camera_center;
            auto ray_direction = pixel_sample - ray_origin;

            return ray(ray_origin, ray_direction);
        }

        vec3 sample_square() const {
            return vec3(random_double() - 0.5, random_double() - 0.5, 0.0);
        }
        
        color ray_color(ray& r, const hittable& world) {
            hit_record rec;
            
            if (world.hit(r, interval(0, infinity), rec)) {
                return 0.5 * (rec.normal + color(1, 1, 1));
            }
            

            vec3 unit_direction = unit_vector(r.direction());
            auto a = 0.5 * (unit_direction.y() + 1.0);
            return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
        }
};

#endif