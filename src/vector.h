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

#include <cassert>
#include <cmath>
#include <iostream>

#ifndef __SMALLRT_VECTOR3_H__
#define __SMALLRT_VECTOR3_H__

class Vector3
{
  public:
    friend Vector3 operator*(double, const Vector3&);
    friend std::ostream& operator<<(std::ostream& os, const Vector3&);
    friend double dot(const Vector3& v, const Vector3& w);
    friend Vector3 cross(const Vector3& w, const Vector3& v);

    Vector3() : _values{0.0, 0.0, 0.0} {}
    Vector3(double x, double y, double z) : _values{x, y, z} {}

    inline double x() const { return _values[0]; }
    inline double y() const { return _values[1]; }
    inline double z() const { return _values[2]; }
    inline double r() const { return _values[0]; }
    inline double g() const { return _values[1]; }
    inline double b() const { return _values[2]; }

    inline const Vector3& operator+() const { return *this; }
    inline Vector3 operator-() const { return {-_values[0], -_values[1], -_values[2]}; }
    inline double operator[](uint32_t i) const
    {
        assert(i < 3);
        return _values[i];
    }
    inline double& operator[](uint32_t i)
    {
        assert(i < 3);
        return _values[i];
    }

    inline double squared_length() const { return _values[0] * _values[0] + _values[1] * _values[1] + _values[2] * _values[2]; }
    inline double length() const { return sqrt(squared_length()); }

    inline std::istream& operator>>(std::istream& is)
    {
        is >> _values[0] >> _values[1] >> _values[2];
        return is;
    }

    inline void make_unique_vector()
    {
        auto inverse_length = 1.0 / length();
        _values[0] *= inverse_length;
        _values[1] *= inverse_length;
        _values[2] *= inverse_length;
    }

    inline Vector3 operator+(const Vector3& v) const { return Vector3(_values[0] + v._values[0], _values[1] + v._values[1], _values[2] + v._values[2]); }
    inline Vector3 operator-(const Vector3& v) const { return Vector3(_values[0] - v._values[0], _values[1] - v._values[1], _values[2] - v._values[2]); }
    inline Vector3 operator*(const Vector3& v) const { return Vector3(_values[0] * v._values[0], _values[1] * v._values[1], _values[2] * v._values[2]); }
    inline Vector3 operator/(const Vector3& v) const { return Vector3(_values[0] / v._values[0], _values[1] / v._values[1], _values[2] / v._values[2]); }
    inline Vector3 operator+(double inc) const { return Vector3(_values[0] + inc, _values[1] + inc, _values[2] + inc); }
    inline Vector3 operator*(double coeff) const { return Vector3(coeff * _values[0], coeff * _values[1], coeff * _values[2]); }
    inline Vector3 operator/(double coeff) const { return Vector3(_values[0] / coeff, _values[1] / coeff, _values[2] / coeff); }

    inline Vector3& operator+=(const Vector3& v)
    {
        _values[0] += v._values[0];
        _values[1] += v._values[1];
        _values[2] += v._values[2];
        return *this;
    }

    inline Vector3& operator-=(const Vector3& v)
    {
        _values[0] -= v._values[0];
        _values[1] -= v._values[1];
        _values[2] -= v._values[2];
        return *this;
    }

    inline Vector3& operator*=(const Vector3& v)
    {
        _values[0] *= v._values[0];
        _values[1] *= v._values[1];
        _values[2] *= v._values[2];
        return *this;
    }

    inline Vector3& operator/=(const Vector3& v)
    {
        _values[0] /= v._values[0];
        _values[1] /= v._values[1];
        _values[2] /= v._values[2];
        return *this;
    }

    inline Vector3& operator*=(double coeff)
    {
        _values[0] *= coeff;
        _values[1] *= coeff;
        _values[2] *= coeff;
        return *this;
    }

    inline Vector3& operator/=(double coeff)
    {
        double k = 1.0 / coeff;
        return operator*=(k);
    }

    inline Vector3 unit_vector() { return *this / length(); }

  private:
    double _values[3];
};

inline double dot(const Vector3& v, const Vector3& w)
{
    return w._values[0] * v._values[0] + w._values[1] * v._values[1] + w._values[2] * v._values[2];
}
inline Vector3 cross(const Vector3& w, const Vector3& v)
{
    return Vector3(
        w._values[1] * v._values[2] - w._values[2] * v._values[1], w._values[2] * v._values[0] - w._values[0] * v._values[2], w._values[0] * v._values[1] - w._values[1] * v._values[0]);
}

inline Vector3 operator*(double coeff, const Vector3& v)
{
    return Vector3(coeff * v._values[0], coeff * v._values[1], coeff * v._values[2]);
}

inline std::ostream& operator<<(std::ostream& os, const Vector3& v)
{
    os << v._values[0] << " " << v._values[1] << " " << v._values[2];
    return os;
}

#endif
