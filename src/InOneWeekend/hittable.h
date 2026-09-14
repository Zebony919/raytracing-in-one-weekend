#ifndef HITTABLE_H
#define HITTABLE_H

#include "rtweekend.h"

class material;
// Telling the compiler we will define material later in the material.h file but still allows 
// us to reference it in hit_record

// Data container for specific values at the point of intersections between a ray and a hittable object
class hit_record {
    public:
        point3 p;
        vec3 normal;
        shared_ptr<material> mat;
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

        virtual bool hit(ray& r, interval ray_t, hit_record& rec) const = 0;
};

#endif