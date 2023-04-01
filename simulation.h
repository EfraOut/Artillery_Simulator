/***********************************************************************
 * Header File:
 *    Simulation: Structure to capture the bullet that will move around the screen
 * Author:
 *    Caleb Hall and Marco Varela
 * Summary:
 *    Structure to capture the bullet that will move around the screen
 ************************************************************************/
#pragma once

#include "ground.h"
#include "position.h"
#include "shell.h"
#include "howitzer.h"
#include "uiInteract.h"

/*************************************************************************
 * Simulation
 * Structure to capture the bullet that will move around the screen
 *************************************************************************/
class Simulation
{
private:
   Ground ground;                 // the ground
   Position ptHowitzer;           // location of the howitzer
   Position ptUpperRight;         // size of the screen

   Shell shell;
   Howitzer howitzer;

public:
   Simulation(Position ptUpperRight);

   void update();
   void draw();
   void input(const Interface* pUI);

   void reset();
};

