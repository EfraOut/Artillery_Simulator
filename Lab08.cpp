/*************************************************************
 * 1. Name:
 *      The Key
 * 2. Assignment Name:
 *      Lab 08: M777 Howitzer
 * 3. Assignment Description:
 *      Simulate firing the M777 howitzer 15mm artillery piece
 * 4. What was the hardest part? Be as specific as possible.
 *      ??
 * 5. How long did it take for you to complete the assignment?
 *      ??
 **************************************************************/

#include <cassert>      // for ASSERT
#include "uiInteract.h" // for INTERFACE
#include "uiDraw.h"     // for RANDOM and DRAW*
#include "ground.h"     // for GROUND
#include "position.h"   // for POINT
#include "test.h"       // for TESTRUNNER()
#include "shell.h"      // for SHELL
#include "howitzer.h"   // for HOWITZER
using namespace std;

double Position::metersFromPixels = 40.0;

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
   double time;                   // amount of time since the last firing

   Shell shell;
   Howitzer howitzer;

   const double time_interval = 0.1; //turning the time interval into a constant so it does not change


public:
   Simulation(Position ptUpperRight) :
      ptUpperRight(ptUpperRight),
      ground(ptUpperRight),
      time(0.0)
   {
      ptHowitzer.setPixelsX(Position(ptUpperRight).getPixelsX() / 2.0);
      ground.reset(ptHowitzer);
      howitzer.setPosition(ptHowitzer);
      shell.setPosition(ptHowitzer);
      shell.setGround(&ground);
   }

   void update()
   {
      // advance time by a hundreth of a second.
      time += time_interval;

      // update shell
      shell.update();
   }

   void draw()
   {
      ogstream gout(Position(10.0, ptUpperRight.getPixelsY() - 20.0));

      // draw the ground first
      ground.draw(gout);

      // draw the howitzer
      howitzer.draw(gout);

      // draw the shell
      if (shell.hasFired())
         shell.draw(gout);

      // draw some text on the screen
      gout.setf(ios::fixed | ios::showpoint);
      gout.precision(1);
      gout << "Time since the bullet was fired: "
         << time << "s\n";
   }

   void input(const Interface * pUI)
   {
      // move by more
      if (pUI->isRight())
         howitzer.angleRight();
      if (pUI->isLeft())
         howitzer.angleLeft();

      // move by a little
      if (pUI->isUp())
         howitzer.angleUp();
      if (pUI->isDown())
         howitzer.angleDown();

      // fire that gun
      if (pUI->isSpace())
         howitzer.fire(shell);
   }
};

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
   //
   // draw everything
   //
   pSimulation->draw();

   pSimulation->input(pUI);

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
      "Artillery Simulator",   /* name on the window */
      ptUpperRight);

   // Initialize the demo
   Simulation sim(ptUpperRight);

   // set everything into action
   ui.run(callBack, &sim);

   return 0;
}
