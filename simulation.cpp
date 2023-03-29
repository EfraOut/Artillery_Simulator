/***********************************************************************
 * Source File:
 *    Simulation : Class definition for Simulation
 * Author:
 *    Caleb Hall and Marco Varela
 * Summary:
 *    The base of the whole program. Here is where drawing, input, and
 *    update are defined, and later called by callback()
 ************************************************************************/

#include "simulation.h"
#include "ground.h"
#include"shell.h"
#include "howitzer.h"
#include "uiInteract.h"


Simulation::Simulation(Position ptUpperRight) :
   ptUpperRight(ptUpperRight),
   shell(&ground),
   time(0.0)
{
   this->ground = Ground(ptUpperRight);
   reset();
}

void Simulation::reset()
{
   ptHowitzer.setPixelsX(rand()% (int) ptUpperRight.getPixelsX()  );
   ground.reset(ptHowitzer);
   shell.setPosition(&ptHowitzer);
   howitzer.setPosition(ptHowitzer);
}

void Simulation::update()
{
   howitzer.update();
   // advance time by a hundreth of a second.
   if (shell.hasFired() && !shell.hasCollided())
   {
      time += time_interval;
      // update shell
      shell.update();
   }
   if (shell.hasCollided())
   {
      if (this->ground.getTarget().getPixelsX() -5 <= shell.getPosition().getPixelsX()
         && this->ground.getTarget().getPixelsX() + 5 >= shell.getPosition().getPixelsX())
      {
         reset();

      }
   }
}

void Simulation::draw()
{
   ogstream gout(Position(0, 0));

   // draw the ground first
   ground.draw(gout);

   // draw the howitzer
   howitzer.draw(gout);

   // draw the shell
   if (shell.hasFired()) {
      shell.draw(gout);

      // draw some text on the screen
      gout.setf(ios::fixed | ios::showpoint);
      gout.precision(1);
      gout.setPosition(Position(ptUpperRight.getMetersX() - 5000, ptUpperRight.getMetersY() - 1380.0));
      gout << "Altitude: "
         << shell.getPosition().getMetersY() << "m\n";
      gout << "Speed: "
         << shell.getVelocity().getSpeed() << "m/s\n";
      gout << "Distance: "
         << abs(shell.getPosition().getMetersX() - howitzer.getPosition().getMetersX()) << "m\n";
      gout << "Hang Time: "
         << time << "s\n";

   }
   else
   {
      gout.setPosition(Position(ptUpperRight.getMetersX() - 5000, ptUpperRight.getMetersY() - 1380.0));
      gout.precision(3);
      gout << "Angle: " << howitzer.getAngle().getDegrees() << " degree\n";
   }
}

void Simulation::input(const Interface* pUI)
{
   // move howitzer
   howitzer.input(pUI);

   // fire that gun
   if (pUI->isSpace())
      if (shell.hasCollided() && shell.hasFired())
         shell.reset();
      else if (!shell.hasFired())
         howitzer.fire(&shell);
}
