//
// Created by Louis Masson on 02/10/2022.
//

#include "casteljau.h"

std::vector<Vec3> BezierCurveByCasteljau(const std::vector<Vec3> &controlPoints, const long nbU) {
    std::vector<Vec3> curvePoints;

    for (int i = 0; i < nbU; i++) {
        float u = (float) i / (float) nbU;

        curvePoints.push_back(
                BezierPointByCasteljau(controlPoints, u)
        );
    }

    return curvePoints;
}

Vec3 BezierPointByCasteljau(const std::vector<Vec3> &controlPoints, const float u) {
    std::vector<Vec3> subControlPoints;
    std::vector<Vec3> nextSubControlPoints = controlPoints;;

    while (nextSubControlPoints.size() > 1) {
        subControlPoints = nextSubControlPoints;
        nextSubControlPoints.clear();

        for (int i = 0; i < subControlPoints.size() - 1; i++) {
            Vec3 point;
            Vec3 v = subControlPoints[i + 1] - subControlPoints[i];
            v *= u;

            point = subControlPoints[i] + v;

            nextSubControlPoints.push_back(point);
        }
    }

    return nextSubControlPoints[0];
}
