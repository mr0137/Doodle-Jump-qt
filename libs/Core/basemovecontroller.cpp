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
//    hCirc = rightCirculation;
//    vCirc = downCirculation;
}

std::vector<double> normalize(std::vector<double> vec)
{
    double v = calculateModule(vec);
    return {vec[0]/v, vec[1]/v, vec[2]/v};
}

//std::vector<double> BaseMoveController::calculateAngularVelocity(std::vector<double> velocity, int dt)
//{
//    return std::vector<double>{velocity[0] * dt / MCS_IN_S, velocity[1] * dt / MCS_IN_S, velocity[2] * dt / MCS_IN_S};
//}

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

//void BaseMoveController::calcAzimuth(double angularVelocity, int dt)
//{
//    taskAzimuth = calcAngle(taskAzimuth, angularVelocity, dt);
//}

//void BaseMoveController::calcTheta(double angularVelocity, int dt)
//{
//    theta = calcAngle(theta, angularVelocity, dt);
//}

//double BaseMoveController::calcDistance(std::vector<double> velocity, int dt)
//{
//    return calculateModule(velocity) * dt;
//}

double calculateModule(std::vector<double> vec){
    return sqrt(pow(vec[0], 2) + pow(vec[1], 2) + pow(vec[2], 2));
}

//verticalCirculation BaseMoveController::getVCirc() const
//{
//    return vCirc;
//}

//void BaseMoveController::setVCirc(const verticalCirculation &value)
//{
//    vCirc = value;
//}

//horizontalCirculation BaseMoveController::getHCirc() const
//{
//    return hCirc;
//}

//void BaseMoveController::setHCirc(const horizontalCirculation &value)
//{
//    hCirc = value;
//}

double calcAngle(double angle, double angularVelocity, int dt)
{
    return (angle += angularVelocity * dt /(MCS_IN_S));
}
