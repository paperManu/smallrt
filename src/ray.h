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

#ifndef __SMALLRT_RAY_H__
#define __SMALLRT_RAY_H__

#include "./vector.h"

class Ray
{
  public:
    Ray() {}
    Ray(const Vector3& a, const Vector3& b) : _a(a), _b(b) {}

    Vector3 origin() const { return _a; }
    Vector3& origin() { return _a; }
    Vector3 direction() const { return _b; }
    Vector3& direction() { return _b; }
    Vector3 point_at_parameter(double t) const { return _a + t * _b; }

  private:
    Vector3 _a;
    Vector3 _b;
};

#endif
