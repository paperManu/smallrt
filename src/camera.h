/*
 * Copyright (C) 2019 Emmanuel Durand
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Splash is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Splash.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __SMALLRT_CAMERA_H__
#define __SMALLRT_CAMERA_H__

#include "./ray.h"
#include "./vector.h"

class Camera
{
  public:
    Camera(const Vector3& from, const Vector3& at, const Vector3& up, double vfov, double aspect, double aperture, double focus_dist);
    Ray get_ray(double u, double v);

  private:
    double _lens_radius;
    Vector3 _origin;
    Vector3 _lower_left_corner;
    Vector3 _horizontal;
    Vector3 _vertical;
    Vector3 _u, _v, _w;
};

#endif
