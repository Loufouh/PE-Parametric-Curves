//
// Created by Louis Masson on 02/10/2022.
//

#include "berstein.h"


std::vector<Vec3> BezierCurveByBernstein(const std::vector<Vec3> &controlPoints, long nbU) {
    std::vector<Vec3> curvePoints;
    curvePoints.reserve(nbU);

    for (int i = 0; i < nbU; i++) {
        float u = (float) i / (float) nbU;

        curvePoints.push_back(
                BezierPointByBernstein(controlPoints, u)
        );
    }

    return curvePoints;
}


Vec3 BezierPointByBernstein(const std::vector<Vec3> &controlPoints, float u) {
    Vec3 point = Vec3(0, 0, 0);

    for (int i = 0; i < controlPoints.size(); i++) {
        float B = BernsteinPoly(controlPoints.size() - 1, i, u);

        Vec3 addedPoint = controlPoints[i];
        addedPoint *= B;

        point += addedPoint;
    }

    return point;
}


float BernsteinPoly(unsigned long n, unsigned long i, float u) {
    return binomial(n, i) * pow(u, i) * pow(1 - u, n - i);
}


unsigned long binomial(unsigned long n, unsigned long k) {
    return factorial(n) / (factorial(k) * factorial(n - k));
}


unsigned long factorial(unsigned long n) {
    unsigned long result = 1;

    while (n > 1) {
        result *= n;
        n--;
    }

    return result;
}
