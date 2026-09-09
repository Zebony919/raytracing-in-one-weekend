#ifndef SPHERE_H
#define SPHERE_H

#include "rtweekend.h"
#include "hittable.h"

class sphere: public hittable {
    public:
        sphere(const point3& center, double radius) : center(center), radius(std::fmax(0, radius)) {}

        bool hit(ray& r, double ray_tmin, double ray_tmax, hit_record& rec) const override {
            vec3 oc = center - r.origin();
            double a = r.direction().length_squared();
            double h = dot(r.direction(), oc);
            double c = oc.length_squared() - radius * radius;
            auto discriminant = (h * h) - (a * c);

            if (discriminant < 0) {
                return false; // No roots, no intersections
            }

            auto sqrtd = std::sqrt(discriminant);
            auto root = (h - sqrtd) / a;

            // Check BOTH roots to see if they are inside the allowed interval
            if (root <= ray_tmin || root >= ray_tmax) {
                root = (h + sqrtd) / a;

                if (root <= ray_tmin || root >= ray_tmax) {
                    return false;
                }
            }

            // Populate data container that describes the point of intersection with current values
            rec.t = root;
            rec.p = r.at(rec.t);
            vec3 outward_normal = (rec.p - center)  / radius; // Same as unit_vector(rec.p - center)
            rec.set_face_normal(r, outward_normal);

            return true;
        }

    private:
        point3 center;
        double radius;
};


#endif