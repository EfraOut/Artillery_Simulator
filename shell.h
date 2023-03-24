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
   Position startPos;
   Position  projectilePath[20];  // path of the projectile
   Velocity vel;
   Ground* ground;
   bool isFired = false;

   double hang = 0;
   const double time_interval = 0.5; //turning the time interval into a constant so it does not change
   const double area = 0.018842;
   Angle angle;

public:
   // Constructors
   Shell() : startPos(), vel(), angle(), ground() {}
   Shell(const Position& startPos) : vel(), angle()
   {
      this->startPos = startPos;

      double x = startPos.getPixelsX();
      double y = startPos.getPixelsY();

      for (int i = 0; i < 20; i++)
      {
         projectilePath[i].setPixelsX(x);
         projectilePath[i].setPixelsY(y);
      }
   }

   void setPosition(Position position)
   {
      this->startPos = position;

      double x = startPos.getPixelsX();
      double y = startPos.getPixelsY();

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
      cout << ground->getElevationMeters(projectilePath[0]) << endl;
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
         double gravity = gravityFromAltitude(startPos.getMetersY());
         double velocity = sqrt(vel.getDX() * vel.getDX() + vel.getDY() * vel.getDY());
         double dragCoefficient = dragFromMach(velocity / speedOfSoundFromAltitude(startPos.getMetersY()));
         double densityOfAir = densityFromAltitude(startPos.getMetersY());
         const double area = 0.018842;
         double dragForce = calculateDragForce(dragCoefficient, densityOfAir, velocity, area);
         double acceleration = calculateAccelerationFromForce(dragForce);
         angle.calculatingAngleUsingTwoComponents(vel.getDX(), vel.getDY());
         double ddx = computeHorizontalComponent(angle, acceleration) * -1.0;
         double ddy = computeVerticalComponent(angle, acceleration) * -1.0;
         vel.setDY(computeVelocity(vel.getDY(), gravity + ddy, time_interval));
         vel.setDX(computeVelocity(vel.getDX(), ddx, time_interval));
         startPos.setMetersX(calculateDisplacement(startPos.getMetersX(), vel.getDX(), ddx, time_interval));
         startPos.setMetersY(calculateDisplacement(startPos.getMetersY(), vel.getDY(), gravity + ddy, time_interval));
      }
   }

   bool hasFired() { return isFired;}

   void changeStatus() { isFired = !isFired; }

   Position getPosition() const { return startPos; }

   Shell& operator=(const Shell& shell)
   {
      startPos = shell.getPosition();
      return *this;
   }

};