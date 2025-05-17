#include <iostream>
#include "color.h"
#include "vec3.h"
#include "ray.h"


double hit_sphere(const point3& center, double radius, const ray& r) { // pass in center/radius of sphere and ray were testing
    vec3 oc = center - r.origin();
    auto a = dot(r.direction(), r.direction());
    auto b = -2.0 * dot(r.direction(), oc);
    auto c = dot(oc, oc) - radius*radius;
    auto discriminant = b*b - 4*a*c;

    if (discriminant < 0) { // no hit 
    return -1.0;
    }
    else {
    return (-b - std::sqrt(discriminant) ) / (2.0*a); // t value (scalar of first intersection point with sphere)
    }
}

color ray_color(const ray& r) {
    auto t = hit_sphere(point3(0,0,-1), 0.5, r); // get scalar of where ray hits sphere
    if (t > 0.0) {
        vec3 N = unit_vector(r.at(t) - vec3(0,0,-1)); //P-C -> suface normal
        return 0.5*color(N.x()+1, N.y()+1, N.z()+1);
    }
    // doesnt hits sphere
    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5*(unit_direction.y() + 1.0);
    return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
}

int main() {

  // Image

    auto aspect_ratio = 16.0 / 9.0;
    int image_width = 400;

    // Calculate the image height, and ensure that it's at least 1.
    int image_height = int(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    // Camera

    auto focal_length = 1.0;
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (double(image_width)/image_height);
    auto camera_center = point3(0, 0, 0);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    auto viewport_u = vec3(viewport_width, 0, 0); // define width of viewport in 3d
    auto viewport_v = vec3(0, -viewport_height, 0); // define height of viewport in 3d

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    auto pixel_delta_u = viewport_u / image_width; // units on view port = 1 pixel over
    auto pixel_delta_v = viewport_v / image_height;

    // Calculate the location of the upper left pixel.
    auto viewport_upper_left = camera_center
                             - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
    auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);



    // Render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; j++) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;

        for (int i = 0; i < image_width; i++) {
           
            auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v); // pixel00_loc got to center of first pixel. 
            auto ray_direction = pixel_center - camera_center; // x, y, z magnitude 

            ray r(camera_center, ray_direction);

            color pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
        }
    }
    std::clog << "\rDone.                 \n";

}