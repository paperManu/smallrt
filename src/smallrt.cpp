#include <iostream>
#include <memory>
#include <vector>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

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

std::unique_ptr<HitableList> random_scene()
{
    std::vector<std::unique_ptr<Hitable>> list;

    list.push_back(std::make_unique<Sphere>(Vector3(0.0, -1000.0, -1.0), 1000.0, std::make_shared<Lambert>(Vector3(0.5, 0.5, 0.5))));
    for (double a = -11.0; a < 11.0; ++a)
    {
        for (double b = -11.0; b < 11.0; ++b)
        {
            double choose_mat = unit_rand();
            Vector3 center(a + 0.9 * unit_rand(), 0.2, b + 0.9 * unit_rand());
            if ((center - Vector3(4.0, 0.2, 0.0)).length()  > 0.9)
            {
                if (choose_mat < 0.4)
                    list.push_back(std::make_unique<Sphere>(center, 0.2, std::make_unique<Lambert>(Vector3(unit_rand(), unit_rand(), unit_rand()))));
                else if (choose_mat < 0.95)
                    list.push_back(std::make_unique<Sphere>(center, 0.2, std::make_unique<Metal>(Vector3(0.5 * (1.0 + unit_rand()), 0.5 * (1.0 + unit_rand()), 0.5 * (1.0 + unit_rand())), 0.5 * unit_rand())));
                else
                    list.push_back(std::make_unique<Sphere>(center, 0.2, std::make_unique<Dielectric>(1.5)));
            }
        }
    }

    list.push_back(std::make_unique<Sphere>(Vector3(0.0, 1.0, 0.0), 1.0, std::make_unique<Dielectric>(1.5)));
    list.push_back(std::make_unique<Sphere>(Vector3(-4.0, 1.0, 0.0), 1.0, std::make_unique<Lambert>(Vector3(0.4, 0.2, 0.1))));
    list.push_back(std::make_unique<Sphere>(Vector3(4.0, 1.0, 0.0), 1.0, std::make_unique<Metal>(Vector3(0.7, 0.6, 0.5), 0.0)));

    return std::make_unique<HitableList>(list);
}

int main(int, char**)
{
    uint32_t width = 480;
    uint32_t height = 240;
    uint32_t channels = 3;
    uint32_t sample_count = 4;

    std::vector<uint8_t> image(static_cast<size_t>(width * height * channels));

    Vector3 lower_left_corner(-2.0, -1.0, -1.0);
    Vector3 horizontal(4.0, 0.0, 0.0);
    Vector3 vertical(0.0, 2.0, 0.0);
    Vector3 origin(0.0, 0.0, 0.0);

    auto world = random_scene();

    auto from = Vector3(10.0, 2.0, 3.0);
    auto to = Vector3(0.0, 0.5, 0.0);
    auto up = Vector3(0.0, 1.0, 0.0);
    auto dist_to_focus = (from - to).length();
    double aperture = 0.05;
    Camera camera(from, to, up, 20.0, static_cast<double>(width) / static_cast<double>(height), aperture, dist_to_focus);

    for (uint32_t y = 0; y < height; ++y)
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

            image[((height - y - 1) * width + x) * channels] = static_cast<uint8_t>(255.99 * color.r());
            image[((height - y - 1) * width + x) * channels + 1] = static_cast<uint8_t>(255.99 * color.g());
            image[((height - y - 1) * width + x) * channels + 2] = static_cast<uint8_t>(255.99 * color.b());
        }
    }

    stbi_write_tga("render.tga", width, height, channels, image.data());

    return 0;
}
