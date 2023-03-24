#pragma once
#include "angle.h"
#include "position.h"
#include "uiDraw.h"
#include "shell.h"

class Howitzer
{
private:
   const double MUZZLE_VEL = 827.0;
   const double time_interval = 0.1; //turning the time interval into a constant so it does not change

   Angle angle;
   Position position;
   double time;

   void normalize()
   {
      if (angle < -3.1415 / 2)
      {
         angle = -3.1415 / 2;
      }
      if (angle > 3.1415 / 2)
      {
         angle = 3.1415 / 2;
      }
   }
   
public:
   Howitzer() : 
      position(),
      angle(),
      time(2.5)
   {}
   
   Howitzer(Position &position) :
      angle(),
      time(2.5)
   {
      this->position = position;
   }

   void setPosition(Position &position)
   {
      this->position = position;
   }

   void fire(Shell * shell)
   {
      time = 0;
      shell->computeVelocity(angle, MUZZLE_VEL);
   }

   void draw(ogstream& gout)
   {  
      time += time_interval;
      // draw the howitzer
      gout.drawHowitzer(position, angle.getAngle(), time);
   }

   void updateAngle(double radians)
   {
      double newAngle = angle.getAngle() + radians;
      if (newAngle > -(3.1415 / 2) && newAngle < (3.1415 / 2))
      {
         angle.setAngle(newAngle);
      }
   }

   Angle getAngle()
   {
      return angle;
   }

   void angleLeft()
   {
      angle -= 0.05;
      normalize();
   }

   void angleRight()
   {
      angle += 0.05;
      normalize();
   }

   void angleUp()
   {
      angle += (angle >= 0 ? - 0.003 : 0.003);
      normalize();
   }

   void angleDown()
   {
      angle += (angle >= 0 ? 0.003 : -0.003);
      normalize();
   }
};

