/***********************************************************************
 * Header File:
 *    Angle : Represents an angle
 * Author:
 *    Caleb Hall
 * Summary:
 *    Helps understand where the Shell is heading
 ************************************************************************/

#pragma once
#define _USE_MATH_DEFINES
#include <math.h>

class TestVelocity;
class Angle
{
   friend TestVelocity;
private:

   double radians;

public:

   // Constructors
   Angle();
   Angle(double radians);

   // Getter and Setter
   double getRadians() const;
   double getDegrees() const;
   void setAngle(double radians);

   // For calculating the updated angle
   void calculateAngle(double dx, double dy);

   // Operators overloading
   Angle& operator+=(const double& angle);
   Angle& operator=(const double& angle);
   Angle& operator-=(const double& angle);
   bool operator>=(const double& angle) const;
   bool operator<=(const double& angle) const;
   bool operator>(const double& angle) const;
   bool operator<(const double& angle) const;

};