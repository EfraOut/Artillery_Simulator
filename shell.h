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
   Ground* ground;
   Angle angle;
   bool isFired = false;

   const double area = 0.018842;
   const double time_interval = 0.5; //turning the time interval into a constant so it does not change

public:
   // Constructors
   Shell() : pos(), vel(), angle(), ground() {}
   Shell(const Position& startPos)
   {
      this->pos = startPos;

      double x = startPos.getPixelsX();
      double y = startPos.getPixelsY();

      for (int i = 0; i < 20; i++)
      {
         projectilePath[i].setPixelsX(x);
         projectilePath[i].setPixelsY(y);
      }
   }

   void setVelocity(Angle angle)
   {
      vel.setDX(computeHorizontalComponent(angle, 827.0));
      vel.setDY(computeVerticalComponent(angle, 827.0));
   }

   void setAngle(Angle angle)
   {
      this->angle = angle;
   }

   void setPosition(Position position)
   {
      this->pos = position;

      double x = pos.getPixelsX();
      double y = pos.getPixelsY();

      for (int i = 0; i < 20; i++)
      {
         projectilePath[i].setPixelsX(x);
         projectilePath[i].setPixelsY(y);
      }
   }

   void setGround(Ground* ground)
   {
      this->ground = ground;
   }

   void draw(ogstream& gout)
   {
      // draw the projectile and path
      for (int i = 0; i < 20; i++)
         gout.drawProjectile(projectilePath[i], 0.1 * (double)i);
   }

   void update()
   {
      cout << "Ground: " << ground->getElevationMeters(projectilePath[0]) << endl;
      cout << "Shell: " <<pos.getMetersY() << endl;
      if (ground->getElevationMeters(projectilePath[0]) > 0)
      {
         // update the projectiles tail
         for (int i = 19; i > 0; i--)
         {
            double x = projectilePath[i - 1].getPixelsX();
            double y = projectilePath[i - 1].getPixelsY();

            projectilePath[i].setPixelsX(x);
            projectilePath[i].setPixelsY(y);
         }

         double gravity = gravityFromAltitude(pos.getMetersY());
         double velocity = sqrt(vel.getDX() * vel.getDX() + vel.getDY() * vel.getDY());
         double dragCoefficient = dragFromMach(velocity / speedOfSoundFromAltitude(pos.getMetersY()));
         double densityOfAir = densityFromAltitude(pos.getMetersY());
         double dragForce = calculateDragForce(dragCoefficient, densityOfAir, velocity, area);
         double acceleration = calculateAccelerationFromForce(dragForce);
         angle.calculateAngle(vel.getDX(), vel.getDY());
         double ddx = computeHorizontalComponent(angle, acceleration) * -1.0;
         double ddy = computeVerticalComponent(angle, acceleration) * -1.0;
         vel.setDY(computeVelocity(vel.getDY(), gravity + ddy, time_interval));
         vel.setDX(computeVelocity(vel.getDX(), ddx, time_interval));
         pos.setMetersX(calculateDisplacement(pos.getMetersX(), vel.getDX(), ddx, time_interval));
         pos.setMetersY(calculateDisplacement(pos.getMetersY(), vel.getDY(), gravity + ddy, time_interval));
         projectilePath[0].setMetersX(calculateDisplacement(pos.getMetersX(), vel.getDX(), ddx, time_interval));
         projectilePath[0].setMetersY(calculateDisplacement(pos.getMetersY(), vel.getDY(), gravity + ddy, time_interval));
      }
   }

   bool hasFired() { return isFired; }

   bool hasCollided()
   {
      return pos.getMetersY() < ground->getElevationMeters(pos);
   }

   void changeStatus() { isFired = !isFired; }

   Position getPosition() const { return pos; }

   Shell& operator=(const Shell& shell)
   {
      pos = shell.getPosition();
      return *this;
   }
};