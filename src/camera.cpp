#include "./camera.h"

#include <iostream>

Camera::Camera(const Vector3& from, const Vector3& at, const Vector3& up, double vfov, double aspect)
{
    Vector3 u, v, w;
    double theta = vfov * M_PI / 180.0;
    double half_height = tan(theta / 2.0);
    double half_width = aspect * half_height;
    _origin = from;
    w = (from - at).unit_vector();
    u = cross(up, w).unit_vector();
    v = cross(w, u);
    _lower_left_corner = _origin - half_width * u - half_height * v - w;
    _horizontal = 2.0 * half_width * u;
    _vertical = 2.0 * half_height * v;
}

Ray Camera::get_ray(double u, double v)
{
    return Ray(_origin, _lower_left_corner + u * _horizontal + v * _vertical - _origin);
}
