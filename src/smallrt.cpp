#include <iostream>
#include <memory>

#include "./camera.h"
#include "./hitable_list.h"
#include "./material.h"
#include "./material_dielectric.h"
#include "./material_lambert.h"
#include "./material_metal.h"
#include "./ray.h"
#include "./sphere.h"
#include "./utils.h"
#include "./vector.h"

Vector3 get_color(const Ray& r, const HitableList* world, int depth = 0)
{
    HitRecord rec;
    if (world->hit(r, 0.0001, std::numeric_limits<double>::max(), rec))
    {
        Ray scattered;
        Vector3 attenuation;
        if (depth < 50 && rec.material->scatter(r, rec, attenuation, scattered))
            return attenuation * get_color(scattered, world, depth + 1);
        else
            return Vector3();
    }
    else
    {
        auto unit_direction = r.direction().unit_vector();
        auto t = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - t) * Vector3(1.0, 1.0, 1.0) + t * Vector3(0.5, 0.7, 1.0);
    }
}

int main(int, char**)
{
    uint32_t width = 480;
    uint32_t height = 240;
    uint32_t sample_count = 50;
    std::cout << "P3\n" << width << " " << height << "\n255\n";

    Vector3 lower_left_corner(-2.0, -1.0, -1.0);
    Vector3 horizontal(4.0, 0.0, 0.0);
    Vector3 vertical(0.0, 2.0, 0.0);
    Vector3 origin(0.0, 0.0, 0.0);

    std::vector<std::unique_ptr<Hitable>> list;
    list.push_back(std::make_unique<Sphere>(Vector3(0.0, 0.0, -1.0), 0.5, std::make_shared<Lambert>(Vector3(0.1, 0.2, 0.5))));
    list.push_back(std::make_unique<Sphere>(Vector3(0.0, -100.5, -1.0), 100.0, std::make_shared<Lambert>(Vector3(0.8, 0.8, 0.0))));
    list.push_back(std::make_unique<Sphere>(Vector3(1.0, 0.0, -1.0), 0.5, std::make_shared<Metal>(Vector3(0.8, 0.6, 0.2), 0.3)));
    list.push_back(std::make_unique<Sphere>(Vector3(-1.0, 0.0, -1.0), 0.5, std::make_shared<Dielectric>(1.5)));
    auto world = std::make_unique<HitableList>(list);

    Camera camera(Vector3(-2.0, 3.0, 1.0), Vector3(0.0, 0.0, -1.0), Vector3(0.0, 1.0, 0.0), 20.0, static_cast<double>(width) / static_cast<double>(height));

    for (uint32_t y = height - 1; y > 0; --y)
    {
        for (uint32_t x = 0; x < width; ++x)
        {
            Vector3 color(0.0, 0.0, 0.0);
            for (uint32_t s = 0; s < sample_count; ++s)
            {
                double u = (static_cast<double>(x) + unit_rand()) / static_cast<double>(width);
                double v = (static_cast<double>(y) + unit_rand()) / static_cast<double>(height);

                auto ray = camera.get_ray(u, v);
                color += get_color(ray, world.get());
            }
            color /= sample_count;
            color = Vector3(sqrt(color.r()), sqrt(color.g()), sqrt(color.b()));

            int ir = static_cast<int>(255.99 * color.r());
            int ig = static_cast<int>(255.99 * color.g());
            int ib = static_cast<int>(255.99 * color.b());
            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }

    return 0;
}
