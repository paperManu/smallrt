#include "./sphere.h"

bool Sphere::hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const
{
    auto oc = r.origin() - _center;
    auto a = dot(r.direction(), r.direction());
    auto b = dot(oc, r.direction());
    auto c = dot(oc, oc) - _radius * _radius;
    auto discriminant = b * b - a * c;

    if (discriminant < 0.0)
        return false;

    double temp = (-b - sqrt(discriminant)) / a;
    if (temp > t_min  && temp < t_max)
    {
        rec.t = temp;
        rec.p = r.point_at_parameter(temp);
        rec.normal = (rec.p - _center) / _radius;
        return true;
    }

    temp = (-b + sqrt(discriminant)) / a;
    if (temp > t_min  && temp < t_max)
    {
        rec.t = temp;
        rec.p = r.point_at_parameter(temp);
        rec.normal = (rec.p - _center) / _radius;
        return true;
    }

    return false;
}
