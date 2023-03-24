/***********************************************************************
 * Source File:
 *    Velocity : Implementation of the Velocity class
 * Author:
 *    Efrain Gomez Fajardo
 * Summary:
 *    
 ************************************************************************/

#include "velocity.h"
#include "angle.h"
#include <math.h>

Velocity::Velocity() : dx(0), dy(0) {}
Velocity::Velocity(double dx, double dy) : dx(dx), dy(dy) {}

double Velocity::getSpeed()
{
   return sqrt((dx * dx) + (dy * dy));
}

double Velocity::getDX() const { return dx; }
double Velocity::getDY() const { return dy; }

void Velocity::computeVelocity(Angle a, double s)
{
   dx = s * sin(a.getAngle());
   dy = s * cos(a.getAngle());
}

Velocity& Velocity::operator+=(const Velocity& vel)
{
   dx += vel.dx;
   dy += vel.dy;
   return *this;
}