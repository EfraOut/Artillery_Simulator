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
#include "uiInteract.h" // for INTERFACE
#define TIME_INTERVAL 0.1;

class Howitzer
{
private:
   const double MUZZLE_VEL = 827.0;

   Angle angle;
   Position position;
   double time;

   void normalize();
   
public:
   Howitzer();
   
   Howitzer(Position& position);

   //Sets the position of Howitzer.
   void setPosition(Position &position) { this->position = position; }

   //Returns the position of Howitzer.
   Position getPosition() const { return position; }

   void fire(Shell* shell);

   void update();

   void draw(ogstream& gout) const;

   void updateAngle(double radians);

   //Returns the angle of Howitzer.
   Angle getAngle() const { return angle; }

   void input(const Interface* pUI);

   void angleLeft();

   void angleRight();

   void angleUp();

   void angleDown();
};

