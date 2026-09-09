#ifndef HITTABLE_H
#define HITTABLE_H

#include "rtweekend.h"

// Data container for specific values at the point of intersections between a ray and a hittable object
class hit_record {
    public:
        point3 p;
        vec3 normal;
        double t;
        bool front_face;

        void set_face_normal(ray& r, vec3 outward_normal) {
            front_face = dot(r.direction(), outward_normal) < 0.0;
            normal = front_face ? outward_normal : -outward_normal;
        }
};

// Any c++ class with a vitrual method is automatically labelled as an abstract class
class hittable {
    public:
        virtual ~hittable() = default;

        virtual bool hit(ray& r, double ray_tmin, double ray_tmax, hit_record& rec) const = 0;
};

#endif