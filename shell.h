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
   Position* startPos;
   Position projectilePath[20];  // path of the projectile
   Velocity vel;
   Ground* ground;
   Angle angle;
   bool isFired = false;

   const double area = 0.018842;
   const double time_interval = 0.5; //turning the time interval into a constant so it does not change

public:
   // Constructors
   Shell();
   Shell(const Position& startPos);
   Shell(Ground* ground);
   Shell(Position* position, Ground* ground);

   void reset();

   void setVelocity(Angle angle);

   Velocity getVelocity() { return vel; }

   void setAngle(Angle angle) { this->angle = angle; }

   void setPosition(Position* position);

   void setGround(Ground* ground) { this->ground = ground; }

   void draw(ogstream& gout);

   void update();

   bool hasFired() { return isFired; }

   bool hasCollided() { return pos.getMetersY() < ground->getElevationMeters(pos); }

   void changeStatus() { isFired = !isFired; }

   Position getPosition() const { return pos; }

   Shell& operator=(const Shell& shell);
};