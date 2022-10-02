//
// Created by Louis Masson on 02/10/2022.
//

#ifndef MODELISATION_TP1_CASTELJAU_H
#define MODELISATION_TP1_CASTELJAU_H

#include <vector>
#include "../src/Vec3.h"

extern std::vector<Vec3> BezierCurveByCasteljau(const std::vector<Vec3> &controlPoints, long nbU);

extern Vec3 BezierPointByCasteljau(const std::vector<Vec3> &controlPoints, float u);

#endif //MODELISATION_TP1_CASTELJAU_H
