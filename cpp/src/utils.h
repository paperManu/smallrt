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

double unit_rand();
Vector3 random_unit_in_sphere();
Vector3 random_unit_in_disk();
double schlick(double cosine, double ref_index);

#endif
