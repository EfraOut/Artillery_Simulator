/***********************************************************************
 * Header File:
 *    Howitzer : Represents the M777 Howitzer Artillery
 * Author:
 *    Caleb Hall and Marco Varela
 * Summary:
 *    
 ************************************************************************/
#pragma once
#include "angle.h"
#include "position.h"
#include "uiDraw.h"
#include "shell.h"
#define TIME_INTERVAL 0.1;

class Howitzer
{
private:
   const double MUZZLE_VEL = 827.0;

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

   Position getPosition()
   {
      return position;
   }

   void fire(Shell* shell)
   {
      shell->changeStatus();
      shell->setAngle(angle);
      shell->setVelocity(angle);
      time = 0;
      
   }

   void draw(ogstream& gout)
   {  
      time += TIME_INTERVAL;
      // draw the howitzer
      gout.drawHowitzer(position, angle.getRadians(), time);
   }

   void updateAngle(double radians)
   {
      double newAngle = angle.getRadians() + radians;
      if (newAngle > -(3.1415 / 2) && newAngle < (3.1415 / 2))
      {
         angle.setAngle(newAngle);
      }
   }

   Angle& getAngle() { return angle; }

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

