#include <iostream>
#include <memory>

#include "./hitable_list.h"
#include "./ray.h"
#include "./sphere.h"
#include "./vector.h"

Vector3 get_color(const Ray& r, const std::unique_ptr<HitableList>& world)
{
    HitRecord rec;
    if (world->hit(r, 0.0, std::numeric_limits<double>::max(), rec))
    {
        return 0.5 * (rec.normal + 1.0);
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
    uint32_t width = 200;
    uint32_t height = 100;
    std::cout << "P3\n" << width << " " << height << "\n255\n";

    Vector3 lower_left_corner(-2.0, -1.0, -1.0);
    Vector3 horizontal(4.0, 0.0, 0.0);
    Vector3 vertical(0.0, 2.0, 0.0);
    Vector3 origin(0.0, 0.0, 0.0);

    std::vector<std::unique_ptr<Hitable>> list;
    list.push_back(std::make_unique<Sphere>(Vector3(0.0, 0.0, -1.0), 0.5));
    list.push_back(std::make_unique<Sphere>(Vector3(0.0, -100.5, -1.0), 100.0));
    auto world = std::make_unique<HitableList>(list);

    for (uint32_t y = height - 1; y > 0; --y)
    {
        for (uint32_t x = 0; x < width; ++x)
        {
            double u = static_cast<double>(x) / static_cast<double>(width);
            double v = static_cast<double>(y) / static_cast<double>(height);
            Ray ray(origin, lower_left_corner + u * horizontal + v * vertical);
            auto color = get_color(ray, world);
            int ir = static_cast<int>(255.99 * color.r());
            int ig = static_cast<int>(255.99 * color.g());
            int ib = static_cast<int>(255.99 * color.b());
            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }

    return 0;
}
