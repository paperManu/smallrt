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

#ifndef __SMALLRT_MATERIAL_LAMBERT_H__
#define __SMALLRT_MATERIAL_LAMBERT_H__

#include "./material.h"
#include "./utils.h"

class Lambert : public Material
{
  public:
    Lambert(const Vector3& albedo) : _albedo(albedo) {}
    virtual bool scatter(const Ray&, const HitRecord& rec, Vector3& attenuation, Ray& scattered) const final
    {
        auto target = rec.p + rec.normal + random_unit_sphere();
        scattered = Ray(rec.p, target - rec.p);
        attenuation = _albedo;
        return true;
    }

  private:
    Vector3 _albedo;
};

#endif
