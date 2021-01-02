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

#ifndef __SMALLRT_HITABLE_H__
#define __SMALLRT_HITABLE_H__

#include <memory>

#include "./ray.h"
#include "./vector.h"

class Material;

struct HitRecord
{
    double t{0.0};
    Vector3 p{0.0, 0.0, 0.0};
    Vector3 normal{0.0, 0.0, 0.0};
    std::shared_ptr<Material> material{nullptr};
};

class Hitable
{
  public:
    virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const = 0;
};

#endif
