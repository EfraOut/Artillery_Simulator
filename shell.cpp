/***********************************************************************
 * Source File:
 *    Shell : Represents the shell shot by the Howitzer
 * Author:
 *    Caleb Hall and Marco Varela
 * Summary:
 *    This class represents the Shell being fired by the Howitzer
 ************************************************************************/
#pragma once
#include "shell.h"
#include "velocity.h"
#include "ground.h"
#include "physics.h"
#include "angle.h"

// Constructors

 /*
 * DEFAULT CONSTRUCTOR
 */
Shell::Shell() : pos(), vel(), angle() {}

/*
* SET VELOCITY
* Sets the X any Y veocity of shell according to the muzzle velocity.
*/
void Shell::setVelocity(Angle angle)
{
   vel.setDX(computeHorizontalComponent(angle, MUZZLE_VEL));
   vel.setDY(computeVerticalComponent(angle, MUZZLE_VEL));
}

/*
* DRAW
* Calls the functions with the nesesary atributes for the shell and its trail to show onscreen.
*/
void Shell::draw(ogstream& gout)
{
   // draw the projectile and path
   for (int i = 19; i >= 0; i--)
      gout.drawProjectile(projectilePath[i], 0.5 * (double)i);
}

/*
* UPDATE
* Takes care of updating the atributes that need to be updated each frame. Uses equations from physics to calculate the next position.
*/
void Shell::update(const Ground & ground)
{
   hangTime += time_interval;
      
   // update the projectiles tail
   for (int i = 19; i > 0; i--)
   {
      double x = projectilePath[i - 1].getPixelsX();
      double y = projectilePath[i - 1].getPixelsY();

      projectilePath[i].setPixelsX(x);
      projectilePath[i].setPixelsY(y);
   }

   // Here is all of the logic of the shell using the functions provided by physics.h
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

/*
* RESET
* Resets the shells atributes, and puts it at the specified positon on screen.
*/
void Shell::reset(const Position & pos)
{
   hangTime = 0;
   isFired = false;
   collided = false;
   for (int i = 0; i < 20; i++)
   {
      projectilePath[i].setPixelsX(pos.getPixelsX());
      projectilePath[i].setPixelsY(pos.getPixelsY());
   }
}

Shell& Shell::operator=(const Shell& shell)
{
   pos = shell.getPosition();
   return *this;
}
