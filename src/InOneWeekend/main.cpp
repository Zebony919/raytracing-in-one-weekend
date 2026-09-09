#include "rtweekend.h"

#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"

int main() {
    hittable_list world;

    world.add(make_shared<sphere>(point3(0,0,-1.5), 0.5));
    world.add(make_shared<sphere>(point3(0,-100.5,-1.5), 100));
    world.add(make_shared<sphere>(point3(-1, -0.5, -1), 0.1));

    camera cam;

    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 400;
    cam.sample_per_pixel = 100;

    cam.render(world);

    return 0;
}