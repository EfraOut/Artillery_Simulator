/***********************************************************************
 * Source File:
 *    Howitzer : Implementation of the Howitzer class
 * Author:
 *    Caleb Hall
 * Summary:
 *
 ************************************************************************/

#include "howitzer.h"

Howitzer::Howitzer() :
   position(),
   angle(),
   time(2.5)
{}

Howitzer::Howitzer(Position& position) :
   angle(),
   time(2.5)
{
   this->position = position;
}

void Howitzer::fire(Shell* shell)
{
   shell->changeStatus();
   shell->setAngle(angle);
   shell->setVelocity(angle);
   time = 0;

}

void Howitzer::update()
{
   time += TIME_INTERVAL;
}

void Howitzer::draw(ogstream& gout) const
{
   // draw the howitzer
   gout.drawHowitzer(position, angle.getRadians(), time);
}


void Howitzer::updateAngle(double radians)
{
   double newAngle = angle.getRadians() + radians;
   if (newAngle > -(3.1415 / 2) && newAngle < (3.1415 / 2))
   {
      angle.setAngle(newAngle);
   }
};

void Howitzer::input(const Interface* pUI) {

   // move by more
   if (pUI->isRight())
      angleRight();
   if (pUI->isLeft())
      angleLeft();

   // move by a little
   if (pUI->isUp())
      angleUp();
   if (pUI->isDown())
      angleDown();
}

void Howitzer::angleLeft()
{
   angle -= 0.05;
   normalize();
}

void Howitzer::angleRight()
{
   angle += 0.05;
   normalize();
}

void Howitzer::angleUp()
{
   angle += (angle >= 0 ? -0.003 : 0.003);
   normalize();
}

void Howitzer::angleDown()
{
   angle += (angle >= 0 ? 0.003 : -0.003);
   normalize();
}