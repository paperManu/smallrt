#include "./camera.h"

#include "./utils.h"

Camera::Camera(const Vector3& from, const Vector3& at, const Vector3& up, double vfov, double aspect, double aperture, double focus_dist)
{
    _lens_radius = aperture / 2.0;
    double theta = vfov * M_PI / 180.0;
    double half_height = tan(theta / 2.0);
    double half_width = aspect * half_height;
    _origin = from;
    _w = (from - at).unit_vector();
    _u = cross(up, _w).unit_vector();
    _v = cross(_w, _u);
    _lower_left_corner = _origin - half_width * focus_dist * _u - half_height * focus_dist * _v - focus_dist * _w;
    _horizontal = 2.0 * half_width * focus_dist * _u;
    _vertical = 2.0 * half_height * focus_dist * _v;
}

Ray Camera::get_ray(double s, double t)
{
    Vector3 rd = _lens_radius * random_unit_in_disk();
    Vector3 offset = _u * rd.x() + _v * rd.y();
    return Ray(_origin + offset, _lower_left_corner + s * _horizontal + t * _vertical - _origin - offset);
}
