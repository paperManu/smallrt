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

#ifndef __SMALLRT_MATERIAL_DIELECTRIC_H__
#define __SMALLRT_MATERIAL_DIELECTRIC_H__

#include "./material.h"
#include "./utils.h"

class Dielectric : public Material
{
  public:
    Dielectric(double ri = 1.0) : _refraction_index(ri) {}
    virtual bool scatter(const Ray& r_in, const HitRecord& rec, Vector3& attenuation, Ray& scattered) const final
    {
        Vector3 outward_normal;
        auto reflected = reflect(r_in.direction(), rec.normal);
        double ni_over_nt;
        attenuation = Vector3(1.0, 1.0, 1.0);
        Vector3 refracted;
        double reflect_prob;
        double cosine;

        if (dot(r_in.direction(), rec.normal) > 0)
        {
            outward_normal = -rec.normal;
            ni_over_nt = _refraction_index;
            cosine = _refraction_index * dot(r_in.direction(), rec.normal) / r_in.direction().length();
        }
        else
        {
            outward_normal = rec.normal;
            ni_over_nt = 1.0 / _refraction_index;
            cosine = -dot(r_in.direction(), rec.normal) / r_in.direction().length();
        }

        if (refract(r_in.direction(), outward_normal, ni_over_nt, refracted))
        {
            reflect_prob = schlick(cosine, _refraction_index);
        }
        else
        {
            reflect_prob = 1.0;
            scattered = Ray(rec.p, reflected);
            return true;
        }

        if (unit_rand() < reflect_prob)
            scattered = Ray(rec.p, reflected);
        else
            scattered = Ray(rec.p, refracted);

        return true;
    }

  private:
    double _refraction_index;
};

#endif
