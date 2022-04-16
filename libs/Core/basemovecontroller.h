#ifndef BASEMOVECONTROLLER_H
#define BASEMOVECONTROLLER_H

#include <math.h>
#include "abstractobjectcontroller.h"
#include "core_global.h"

#define MCS_IN_S 1000000.
#define MAXSIDE 2 * MCS_IN_S + 3000000
#define degreesToRadians2(angleDegrees) (angleDegrees * M_PI / 180.0)

#define radiansToDegrees2(angleRadians) (angleRadians * 180.0 / M_PI)

class CORE_EXPORT BaseMoveController : public AbstractObjectController
{
    double taskAzimuth;
    double theta;

public:
    BaseMoveController();
    virtual ~BaseMoveController();

    void setTaskAzimuth(double newTaskAzimuth);
    double getTaskAzimuth() const;
    double getTheta() const;
    void setTheta(double value);
};


double calculateModule(std::vector<double> vec);


std::array<double, 3> normalize(std::array<double, 3> & vec);


double calcAngle(double angle, double angularVelocity, int dt);
std::vector<double> normalize(std::vector<double> vec);

#endif // BASEMOVECONTROLLER_H
