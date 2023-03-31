/***********************************************************************
 * Header File:
 *    Shell : Represents the shell shot by the Howitzer
 * Author:
 *    Caleb Hall and Marco Varela
 * Summary:
 *    
 ************************************************************************/
#pragma once

#include "position.h"
#include "velocity.h"
#include "angle.h"
#include "uiDraw.h"
#include "physics.h"
#include <iostream>
#include "ground.h"

using namespace std;

class Shell
{
private:
   Position pos;
   Position projectilePath[20];  // path of the projectile
   Velocity vel;
   Angle angle;
   bool isFired = false;
   bool collided = false;


   const double area = 0.018842;
   const double time_interval = 0.5; //turning the time interval into a constant so it does not change

public:
   // Constructors
   Shell();
   Shell(const Position& startPos);

   bool hasCollided() const { return collided;}

   void collision() { collided = true; }

   void setVelocity(Angle angle);

   Velocity getVelocity() const { return vel; }

   void setAngle(Angle angle) { this->angle = angle; }

   void setPosition(Position position) { pos = position;}

   void draw(ogstream& gout);

   void update(const Ground & ground);

   bool hasFired() const { return isFired; }

   void fired() { isFired = true; }

   void reset(const Position & pos);

   Position getPosition() const { return pos; }

   Shell& operator=(const Shell& shell);
};