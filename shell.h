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

   double hang = 0;
   const double time_interval = 0.5; //turning the time interval into a constant so it does not change
   const double area = 0.018842;
   Angle angle;

public:
   // Constructors
   Shell() : startPos(), vel(), angle() {}
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

   void fire(Angle& a, double v)
   {
      angle = a;

      setPosition(startPos);

      computeVelocity(a, v);
   }

   void computeVelocity(Angle& a, double v)
   {
      vel.computeVelocity(a, v);
   }

   void computeVelocity(double ddx, double ddy, double grav)
   {
      vel += Velocity(ddx * time_interval, (ddy + grav) * time_interval);
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

         // calc next projectile point
         //projectilePath[0].addMetersX(vel.getDX() * 0.01);
         //projectilePath[0].addMetersY(vel.getDY() * 0.01);

         double x = projectilePath[0].getMetersX();
         double y = projectilePath[0].getMetersY();

         double dx = vel.getDX();
         double dy = vel.getDY();

         double gravity = gravityFromAltitude(y);
         double velocity = vel.getSpeed();
         double dragCoefficient = dragFromMach(velocity / speedOfSoundFromAltitude(y));
         double densityOfAir = densityFromAltitude(y);

         double dragForce = calculateDragForce(dragCoefficient, densityOfAir, velocity, area);
         double acceleration = calculateAccelerationFromForce(dragForce);
         angle.calculateAngle(dx, dy);
         double ddx = computeHorizontalComponent(angle, acceleration) * -1.0;
         double ddy = computeVerticalComponent(angle, acceleration) * -1.0;
         computeVelocity(ddx, ddy, gravity);
         dx = vel.getDX();
         dy = vel.getDY();
         projectilePath[0].setMetersX(calculateDisplacement(x, dx, ddx, time_interval));
         projectilePath[0].setMetersY(calculateDisplacement(y, dy, gravity + ddy, time_interval));
      }
   }

   Shell& operator=(const Shell& shell)
   {
      startPos = shell.startPos;
      return *this;
   }

};