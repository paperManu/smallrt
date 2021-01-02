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

#ifndef __SMALLRT_MATERIAL_METAL_H__
#define __SMALLRT_MATERIAL_METAL_H__

#include "./material.h"
#include "./utils.h"

class Metal : public Material
{
  public:
    Metal(const Vector3& albedo, double fuzz = 0.0) : _albedo(albedo), _fuzz(std::min(1.0, fuzz)) {}
    virtual bool scatter(const Ray& in, const HitRecord& rec, Vector3& attenuation, Ray& scattered) const final
    {
        auto reflected = reflect(in.direction().unit_vector(), rec.normal);
        scattered = Ray(rec.p, reflected + _fuzz * random_unit_in_sphere());
        attenuation = _albedo;
        return dot(scattered.direction(), rec.normal) > 0;
    }

  private:
    Vector3 _albedo;
    double _fuzz;
};

#endif
