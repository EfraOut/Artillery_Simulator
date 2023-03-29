#pragma once
#include "shell.h"

// Constructors
Shell::Shell() : pos(), vel(), angle(), ground() {}

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

Shell::Shell(Ground* ground)
{

   setGround(ground);
}

Shell::Shell(Position* position, Ground* ground)
{
   setPosition(position);

   setGround(ground);
}

void Shell::reset()
{
   isFired = false;
   setPosition(startPos);
}

void Shell::setVelocity(Angle angle)
{
   vel.setDX(computeHorizontalComponent(angle, 827.0));
   vel.setDY(computeVerticalComponent(angle, 827.0));
}

void Shell::setPosition(Position* position)
{
   this->startPos = position;
   this->pos = *position;

   double x = pos.getPixelsX();
   double y = pos.getPixelsY();

   for (int i = 0; i < 20; i++)
   {
      projectilePath[i].setPixelsX(x);
      projectilePath[i].setPixelsY(y);
   }
}

void Shell::draw(ogstream& gout)
{
   // draw the projectile and path
   for (int i = 19; i >= 0; i--)
      gout.drawProjectile(projectilePath[i], 0.5 * (double)i);
}

void Shell::update()
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

      double x = calculateLinearInterpolation(y1, x1, y0, x0, ground->getElevationMeters(pos));
      double y = ground->getElevationMeters(pos);

      cout << "x0: " << x0 << " y0: " << y0 << " x1: " << x1 << " y1: " << y1 << endl;
      cout << "elevation: " << ground->getElevationMeters(pos) << endl;
      cout << "x: " << x << " y: " << y << endl;

      projectilePath[0].setMetersX(x);
      projectilePath[0].setMetersY(y);
   }
}

Shell& Shell::operator=(const Shell& shell)
{
   pos = shell.getPosition();
   return *this;
}