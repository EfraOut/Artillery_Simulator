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

   const double time_interval = 0.5; //turning the time interval into a constant so it does not change

public:
   Simulation(Position ptUpperRight) :
      ptUpperRight(ptUpperRight),
      shell(&ground),
      time(0.0)
   {
      this->ground = Ground(ptUpperRight);
      ptHowitzer.setPixelsX(Position(ptUpperRight).getPixelsX() / 2.0);
      ground.reset(ptHowitzer);
      shell.setPosition(&ptHowitzer);
      howitzer.setPosition(ptHowitzer);
   }

   void update()
   {
      howitzer.update();
      // advance time by a hundreth of a second.
      if (shell.hasFired() && !shell.hasCollided())
      {
         time += time_interval;
         // update shell
         shell.update();
      }
   }

   void draw()
   {
      ogstream gout(Position(0,0));

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
            << abs(shell.getPosition().getMetersX() - howitzer.getPosition().getMetersX() )<< "m\n";
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
      
   void input(const Interface * pUI)
   {
      // move howitzer
      howitzer.input(pUI);

      // fire that gun
      if (pUI->isSpace())
         if (shell.hasCollided() && shell.hasFired())
            shell.reset();
         else if(!shell.hasFired())
            howitzer.fire(&shell);
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
      "M777 Artillery Simulator",   /* name on the window */
      ptUpperRight);

   // Initialize the demo
   Simulation sim(ptUpperRight);

   // set everything into action
   ui.run(callBack, &sim);

   return 0;
}
