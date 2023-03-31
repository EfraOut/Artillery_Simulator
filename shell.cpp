#pragma once
#include "shell.h"
#include "velocity.h"
#include "ground.h"
#include "physics.h"
#include "angle.h"

// Constructors
Shell::Shell() : pos(), vel(), angle() {}

Shell::Shell(const Position& startPos)
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


void Shell::setVelocity(Angle angle)
{
   vel.setDX(computeHorizontalComponent(angle, 827.0));
   vel.setDY(computeVerticalComponent(angle, 827.0));
}


void Shell::draw(ogstream& gout)
{
   // draw the projectile and path
   for (int i = 19; i >= 0; i--)
      gout.drawProjectile(projectilePath[i], 0.5 * (double)i);
}

void Shell::update(const Ground & ground)
{
   //cout << "Ground: " << ground->getElevationMeters(projectilePath[0]) << endl;
   //cout << "Shell: " << pos.getMetersY() << endl;
      
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
   projectilePath[0].setMetersX(pos.getMetersX());
   projectilePath[0].setMetersY(pos.getMetersY());
   
   if(hasCollided()) {
      double x0 = projectilePath[1].getMetersX();
      double x1 = projectilePath[0].getMetersX();
      double y0 = projectilePath[1].getMetersY();
      double y1 = projectilePath[0].getMetersY();

      double x = calculateLinearInterpolation(y1, x1, y0, x0, ground.getElevationMeters(pos));
      double y = ground.getElevationMeters(pos);


      projectilePath[0].setMetersX(x);
      projectilePath[0].setMetersY(y);
   }
}

Shell& Shell::operator=(const Shell& shell)
{
   pos = shell.getPosition();
   return *this;
}

void Shell::reset(const Position & pos)
{
   isFired = false;
   collided = false;
   for (int i = 0; i < 20; i++)
   {
      projectilePath[i].setPixelsX(pos.getPixelsX());
      projectilePath[i].setPixelsY(pos.getPixelsY());
   }
}