#include "./vector.h"

bool refract(const Vector3& v, const Vector3& n, float ni_over_nt, Vector3& refracted)
{
    Vector3 uv = v.unit_vector();
    auto dt = dot(uv, n);
    auto discriminant = 1.0 - ni_over_nt * ni_over_nt * (1.0 - dt * dt);
    if (discriminant <= 0.0)
        return false;

    refracted = ni_over_nt * (uv - n * dt) - n * sqrt(discriminant);
    return true;
}
