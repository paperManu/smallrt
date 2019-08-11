#include "./utils.h"

double unit_rand()
{
    return random_dis(random_gen);
}

Vector3 random_unit_in_sphere()
{
    Vector3 p;
    do
    {
        p = 2.0 * Vector3(unit_rand(), unit_rand(), unit_rand()) - Vector3(1.0, 1.0, 1.0);
    } while (p.squared_length() >= 1.0);

    return p;
}

Vector3 random_unit_in_disk()
{
    Vector3 p;
    do
    {
        p = 2.0 * Vector3(unit_rand(), unit_rand(), 0.0) - Vector3(1.0, 1.0, 0.0);
    } while (p.squared_length() >= 1.0);

    return p;
}

double schlick(double cosine, double ref_index)
{
    double r0 = (1.0 - ref_index) / (1.0 + ref_index);
    r0 = r0 * r0;
    return r0 + (1.0 - r0) * pow(1.0 - cosine, 5.0);
}
