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

#ifndef __SMALLRT_UTILS_H__
#define __SMALLRT_UTILS_H__

#include <random>

#include "./ray.h"
#include "./vector.h"

static std::random_device random_device;
static std::mt19937_64 random_gen(random_device());
static std::uniform_real_distribution<> random_dis;

double unit_rand()
{
    return random_dis(random_gen);
}

Vector3 random_unit_sphere()
{
    Vector3 p;
    do
    {
        p = 2.0 * Vector3(unit_rand(), unit_rand(), unit_rand()) - Vector3(1.0, 1.0, 1.0);
    } while (p.squared_length() >= 1.0);

    return p;
}

#endif
