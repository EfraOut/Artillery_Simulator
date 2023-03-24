/***********************************************************************
 * Source File:
 *    Angle : Represents an angle
 * Author:
 *    Caleb Hall
 * Summary:
 *    Helps understand where the Shell is heading
 ************************************************************************/

#define _USE_MATH_DEFINES
#include <math.h>
#include "angle.h"
#include "velocity.h"

Angle::Angle() : radians(0) {}

Angle::Angle(double radians) 
   {
      this->radians = radians;
   }

double Angle::getAngle() const { return radians; }

void Angle::setAngle(double radians) { this->radians = radians; }

void Angle::calculateAngle(double dx, double dy)
{
   radians = atan2(dx, dy);
}

Angle& Angle::operator+=(const double& angle)
{
   radians += angle;
   return *this;
}

Angle& Angle::operator=(const double& angle)
{
   radians = angle;
   return *this;
}

Angle& Angle::operator-=(const double& angle)
{
   radians -= angle;
   return *this;
}

bool Angle::operator>=(const double& angle) const
{
   return radians >= angle;
}

bool Angle::operator<=(const double& angle) const
{
   return radians <= angle;
}

bool Angle::operator>(const double& angle) const
{
   return radians > angle;
}

bool Angle::operator<(const double& angle) const
{
   return radians < angle;
}