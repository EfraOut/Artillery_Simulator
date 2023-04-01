/*************************************************************
 * 1. Name:
 *      The Key
 * 2. Assignment Name:
 *     M777 Howitzer
 * 3. Assignment Description:
 *      Simulate firing the M777 howitzer 15mm artillery piece
 **************************************************************/

#include <cassert>      // for ASSERT
#include "uiInteract.h" // for INTERFACE
#include "uiDraw.h"     // for RANDOM and DRAW*
#include "ground.h"     // for GROUND
#include "position.h"   // for POINT
#include "test.h"       // for TESTRUNNER()
#include "shell.h"      // for SHELL
#include "howitzer.h"   // for HOWITZER
#include "simulation.h" // for SIMULATION
using namespace std;

// Static member
double Position::metersFromPixels = 40.0;

/*************************************
 * All the interesting work happens here, when
 * I get called back from OpenGL to draw a frame.
 * When I am finished drawing, then the graphics
 * engine will wait until the proper amount of
 * time has passed and put the drawing on the screen.
 **************************************/
void callBack(const Interface* pUI, void* p)
{
   // the first step is to cast the void pointer into a game object. This
   // is the first step of every single callback function in OpenGL. 
   Simulation* pSimulation = (Simulation*)p;
 
   // draw everything
   pSimulation->draw();

   // get the user input
   pSimulation->input(pUI);

   // perform the physics
   pSimulation->update();
}

/*********************************
 * Initialize the simulation and set it in motion
 *********************************/
#ifdef _WIN32_X
#include <windows.h>
int WINAPI wWinMain(
   _In_ HINSTANCE hInstance,
   _In_opt_ HINSTANCE hPrevInstance,
   _In_ PWSTR pCmdLine,
   _In_ int nCmdShow)
#else // !_WIN32
int main(int argc, char** argv)
#endif // !_WIN32
{
   // run unit tests
   testRunner();

   // Initialize OpenGL
   Position ptUpperRight;
   ptUpperRight.setPixelsX(700.0);
   ptUpperRight.setPixelsY(500.0);
   Position().setZoom(40.0 /* 42 meters equals 1 pixel */);
   Interface ui(0, NULL,
      "M777 Artillery Simulator",   /* name on the window */
      ptUpperRight);

   // Initialize the simulator

   Simulation sim(ptUpperRight);

   // set everything into action
   ui.run(callBack, &sim);

   return 0;
}
