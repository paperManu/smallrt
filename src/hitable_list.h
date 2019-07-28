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

#ifndef __SMALLRT_HITABLE_LIST_H__
#define __SMALLRT_HITABLE_LIST_H__

#include <memory>
#include <vector>

#include "./hitable.h"

class HitableList : public Hitable
{
  public:
    HitableList() {}
    HitableList(std::vector<std::unique_ptr<Hitable>>& list) : _list(std::move(list)) {}
    virtual bool hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const final;

  private:
    std::vector<std::unique_ptr<Hitable>> _list;
};

#endif
