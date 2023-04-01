/***********************************************************************
 * Source File:
 *    Howitzer : Implementation of the Howitzer class
 * Author:
 *    Caleb Hall
 * Summary:
 *    Represents the Howitzer for our simulator
 ************************************************************************/

#include "howitzer.h"

 /*
 * DEFAULT CONSTRUCTOR
 */
Howitzer::Howitzer() :
   position(),
   angle(),
   time(2.5)
{}

/*
* HOWITZER CONSTRUCTOR
* Initializes howitzer with a positon.
*/
Howitzer::Howitzer(Position& position) :
   angle(),
   time(2.5)
{
   this->position = position;
}

/*
* FIRE
* "Fires" the shell by setting the required atributes.
*/
void Howitzer::fire(Shell* shell)
{
   shell->setAngle(angle);
   shell->setVelocity(angle);
   shell->fired();
   shell->setPosition(position);
   time = 0;

}

/*
* UPDATE
* Takes care of updating the atributes that need to be updated each frame.
*/
void Howitzer::update()
{
   time += TIME_INTERVAL;
}

/*
* DRAW
* Calls the functions with the nesesary atributes for the howitzer to show onscreen.
*/
void Howitzer::draw(ogstream& gout) const
{
   // draw the howitzer
   gout.drawHowitzer(position, angle.getRadians(), time);
}

/*
* UPDATE ANGLE
* Adds the suplied degree in radians to the current angle. Ensures the angle of the Howitzer stays within it's range of motion.
*/
void Howitzer::updateAngle(double radians)
{
   double newAngle = angle.getRadians() + radians;
   if (newAngle > -(3.1415 / 2) && newAngle < (3.1415 / 2))
   {
      angle.setAngle(newAngle);
   }
};

/*
* INPUT
* Takes the users input and handles changing the angle accordingly.
*/
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

/*
* ANGLE LEFT
* Move the howitzers angle counter clock wise 0.05 radians.
*/
void Howitzer::angleLeft()
{
   angle -= 0.05;
   normalize();
}
/*
* ANGLE RIGHT
* Move the howitzers angle clock wise 0.05 radians.
*/
void Howitzer::angleRight()
{
   angle += 0.05;
   normalize();
}

/*
* ANGLE UP
* Move the howitzers angle 0.003 radians towards 0 radians.
*/
void Howitzer::angleUp()
{
   angle += (angle >= 0 ? -0.003 : 0.003);
   normalize();
}

/*
* ANGLE DOWN
* Move the howitzers angle 0.003 radians away from 0 radians.
*/
void Howitzer::angleDown()
{
   angle += (angle >= 0 ? 0.003 : -0.003);
   normalize();
}

/*
* NORMALIZE
* If the angle of the howitzer is out of bounds, change it to the nearest limit of it's bounds.
*/
void Howitzer:: normalize()
{
   if (angle < -3.1415 / 2)
   {
      angle = -3.1415 / 2;
   }
   if (angle > 3.1415 / 2)
   {
      angle = 3.1415 / 2;
   }
}