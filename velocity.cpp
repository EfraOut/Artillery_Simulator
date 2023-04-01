/***********************************************************************
 * Source File:
 *    Velocity : Implementation of the Velocity class
 * Author:
 *    Efrain Gomez Fajardo
 * Summary:
 *    Represents the Velocity class used by Shell
 ************************************************************************/

#include "velocity.h"
#include "angle.h"
#include <math.h>

Velocity::Velocity() : dx(0), dy(0) {}
Velocity::Velocity(double dx, double dy) : dx(dx), dy(dy) {}

//Getting speed
double Velocity::getSpeed()
{
   return sqrt((dx * dx) + (dy * dy));
}

double Velocity::getDX() const { return dx; }
double Velocity::getDY() const { return dy; }

//Setting horizontal velocity
void Velocity::setDX(double dx)
{
   this->dx = dx;
}

//Setting vertical velocity
void Velocity::setDY(double dy)
{
   this->dy = dy;
}

Velocity& Velocity::operator+=(const Velocity& vel)
{
   dx += vel.dx;
   dy += vel.dy;
   return *this;
}