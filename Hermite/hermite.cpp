//
// Created by Louis Masson on 02/10/2022.
//

#include "hermite.h"

std::vector<Vec3> HermiteCubicCurve(const Vec3 &p0, const Vec3 &p1, const Vec3 &v0, const Vec3 &v1, const long nbU) {
    std::vector<Vec3> curvePoints;
    curvePoints.reserve(nbU);

    for (int i = 0; i < nbU; i++) {
        float u = (float) i / (float) nbU;

        float f1 = (2 * u * u * u) - (3 * u * u) + 1;
        float f2 = (-2 * u * u * u) + (3 * u * u);
        float f3 = (u * u * u) - (2 * u * u) + u;
        float f4 = (u * u * u) - (u * u);

        Vec3 point;

        for (int j = 0; j < 3; j++) {
            point[j] = f1 * p0[j] + f2 * p1[j] + f3 * v0[j] + f4 * v1[j];
        }

        curvePoints.push_back(point);
    }

    return curvePoints;
}
