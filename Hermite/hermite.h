//
// Created by Louis Masson on 02/10/2022.
//

#ifndef MODELISATION_TP1_HERMITE_H
#define MODELISATION_TP1_HERMITE_H

#include <vector>
#include "../src/Vec3.h"

extern std::vector<Vec3> HermiteCubicCurve(const Vec3 &p0, const Vec3 &p1, const Vec3 &v0, const Vec3 &v1, const long nbU);

#endif //MODELISATION_TP1_HERMITE_H
