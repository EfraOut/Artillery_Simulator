/***********************************************************************
 * Header File:
 *    Velocity : Represents a velocity
 * Author:
 *    Caleb Hall and Marco Varela
 * Summary:
 *    This velocity is a property of the Shell
 ************************************************************************/
#pragma once

class Angle;
class TestVelocity;

class Velocity
{
   friend TestVelocity;
private:
   
   double dx;
   double dy;

public:

   // Constructors
   Velocity();
   Velocity(double dx, double dy);

   // Getters
   double getDX() const;
   double getDY() const;
   void setDX(double dx);
   void setDY(double dy);

   double getSpeed();

   // Operation overloading
   Velocity& operator+=(const Velocity& vel);
};