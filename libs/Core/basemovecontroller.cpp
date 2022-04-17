#include "basemovecontroller.h"
#include <QDebug>


double BaseMoveController::getTheta() const
{
    return theta;
}

void BaseMoveController::setTheta(double value)
{
    theta = value;
}

BaseMoveController::BaseMoveController()
{
    taskAzimuth = 0;
    theta = 0;
}

std::vector<double> normalize(std::vector<double> vec)
{
    double v = calculateModule(vec);
    return {vec[0]/v, vec[1]/v, vec[2]/v};
}

void BaseMoveController::setTaskAzimuth(double newTaskAzimuth)
{
    taskAzimuth = newTaskAzimuth;
}

double BaseMoveController::getTaskAzimuth() const
{
    return taskAzimuth;
}

BaseMoveController::~BaseMoveController()
{

}

double calculateModule(std::vector<double> vec){
    return sqrt(pow(vec[0], 2) + pow(vec[1], 2) + pow(vec[2], 2));
}

double calcAngle(double angle, double angularVelocity, int dt)
{
    return (angle += angularVelocity * dt /(MCS_IN_S));
}
