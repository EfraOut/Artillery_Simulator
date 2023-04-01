/***********************************************************************
 * Header File:
 *    Shell : Represents the shell shot by the Howitzer
 * Author:
 *    Caleb Hall and Marco Varela
 * Summary:
 *    This class represents the Shell being fired by the Howitzer
 ************************************************************************/
#pragma once

#include "position.h"
#include "velocity.h"
#include "angle.h"
#include "uiDraw.h"
#include "physics.h"
#include "ground.h"
#include <iostream>

using namespace std;

#define TIME_INTERVAL 0.5;

class Shell
{
private:
   Position pos;
   Position projectilePath[20];  // path of the projectile
   Velocity vel;
   Angle angle;
   bool isFired = false;
   bool collided = false;
   double hangTime;


   const double area = 0.018842;
   const double time_interval = TIME_INTERVAL;
   const double MUZZLE_VEL = 827.0;


public:
   // Constructors
   Shell();

   bool hasCollided() const { return collided;}

   // Let the shell know it has colided with something.
   void collision() { collided = true; }

   void setVelocity(Angle angle);

   // Get the shells velocity.
   Velocity getVelocity() const { return vel; }

   // Set the angle of the shell.
   void setAngle(Angle angle) { this->angle = angle; }

   //Set the position of the shell
   void setPosition(Position position) { pos = position;}

   void draw(ogstream& gout);

   void update(const Ground & ground);

   // True if the shell has been fires without being reset, false otherwise.
   bool hasFired() const { return isFired; }

   void fired() { isFired = true; }

   void reset(const Position & pos);

   // Get the position of the shell.
   Position getPosition() const { return pos; }

   Shell& operator=(const Shell& shell);

   double get_time() { return hangTime; }


};