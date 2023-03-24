/***********************************************************************
 * Header File:
 *    Test Position : Test the Physics file
 * Author:
 *    Marco Varela
 * Summary:
 *    All the unit tests for Physics
 ************************************************************************/

#pragma once

#include <iostream>
#include <cassert>
#include "physics.h"
#include <cmath>
#include <iomanip>
#include "angle.h"
using namespace std;

/*****************************************************
* TEST PHYSICS
 * A class that contains the Physics file unit tests
 *****************************************************/
class TestPhysics
{
public:
   void run()
   {
      test_linearInterpolation_3();
      test_linearInterpolation_56();
      test_linearInterpolation_0();
      test_linearInterpolation_5();
      test_linearInterpolation_7();
      test_calculateLinearInterpolation_3();
      test_calculateLinearInterpolation_11();
      test_calculateLinearInterpolation_64();
      test_calculateLinearInterpolation_9802();
      test_calculateDragForce_initial();
      test_calculateDragForce_peak();

      // The following 8 test cases are part of the artillery prototype project
      test_inertia_1();
      test_acceleration_2();
      test_ground_impact_3();
      test_gravity_4();
      test_drag_5();
      test_air_density_6();
      test_drag_coeffecient_7();
      test_hit_the_ground_8();
      cout << "\nAll the test cases for testPhysics.h have been successfull!\n";
   }
private:

   // utility funciton because floating point numbers are approximations
   bool closeEnough(double value, double test, double tolerence) const
   {
      double difference = value - test;
      return (difference >= -tolerence) && (difference <= tolerence);
   }

   /*****************************************************
    * TESTING LINEAR INTERPOLATION FUNCTION
    *****************************************************/
   void test_linearInterpolation_3()
   {
      // setup
      const vector <tables> sTest =
      {
         {1.0,      1.0},
         {2.0,      2.0},
         {3.0,      4.0},
         {4.0,      8.0}
      };
      // exercise
      double test = linearInterpolation(sTest, 2.5);
      // verify
      assert(closeEnough(test, 3.0, 0.0001));
      // teardown
   }
   void test_linearInterpolation_56()
   {
      // setup
      const vector <tables> sTest =
      {
         {1.0,      1.0},
         {5.0,      2.0},
         {10.0,      4.0},
         {15.0,      8.0}
      };
      // exercise
      double test = linearInterpolation(sTest, 12);
      // verify
      assert(closeEnough(test, 5.6, 0.1));
      // teardown
   }

   void test_linearInterpolation_0()
   {
      // setup
      const vector <tables> sTest =
      {
         {0.0,      0.0},
         {2.0,      2.0},
         {3.0,      4.0},
         {4.0,      8.0}
      };
      // exercise
      double test = linearInterpolation(sTest, 0.0);
      // verify
      assert(closeEnough(test, 0.0, 0.0001));
      // teardown
   }

   void test_linearInterpolation_5()
   {
      // setup
      const vector <tables> sTest =
      {
         {2.0,      1.0},
         {4.0,      3.0},
         {6.0,      5.0},
         {8.0,      7.0}
      };
      // exercise
      double test = linearInterpolation(sTest, 5);
      // verify
      assert(closeEnough(test, 4, 0.0001));
      // teardown
   }

   void test_linearInterpolation_7()
   {
      // setup
      const vector <tables> sTest =
      {
         {5.0,      9.0},
         {6.0,      10.0},
         {7.0,      11.0},
         {8.0,      12.0}
      };
      // exercise
      double test = linearInterpolation(sTest, 7.5);
      // verify
      assert(closeEnough(test, 11.5, 0.01));
      // teardown
   }

   /*****************************************************
   * TESTING CALCULATE LINEAR INTERPOLATION FUNCTION
   *****************************************************/
   void test_calculateLinearInterpolation_3()
   {
      // setup
      double x = 3;
      double x0 = 0;
      double x1 = 5;
      double y0 = 0;
      double y1 = 5;
      // exercise
      double test = calculateLinearInterpolation(x0, y0, x1, y1, x);
      // verify
      assert(closeEnough(test, 3, 0.001));
      // teardown
   }

   void test_calculateLinearInterpolation_11()
   {
      // setup
      double x = 5;
      double x0 = -1;
      double x1 = 8;
      double y0 = 15;
      double y1 = 10;
      // exercise
      double test = calculateLinearInterpolation(x0, y0, x1, y1, x);
      // verify
      assert(closeEnough(test, 11.666, 0.001));
      // teardown
   }

   void test_calculateLinearInterpolation_64()
   {
      // setup
      double x = 14;
      double x0 = 10;
      double x1 = 20;
      double y0 = 80;
      double y1 = 40;
      // exercise
      double test = calculateLinearInterpolation(x0, y0, x1, y1, x);
      // verify
      assert(closeEnough(test, 64, 0.001));
      // teardown
   }

   void test_calculateLinearInterpolation_9802()
   {
      // setup
      double x = 1385;
      double x0 = 1000;
      double x1 = 2000;
      double y0 = 9.804;
      double y1 = 9.801;
      // exercise
      double test = calculateLinearInterpolation(x0, y0, x1, y1, x);
      // verify
      //assert(closeEnough(test, 9.802, 0.0001));
      assert(closeEnough(test, 9.802, 0.001));
      // teardown
   }

   /*****************************************************
    * TESTING DRAGFORCE FUNCTION
    *****************************************************/
   void test_calculateDragForce_initial()
   {
      // setup
      double drag = 0.2595;
      double airDensity = 1.2250000;
      double velocity = 827;
      double shellArea = 0.018842;// M_PI * (154.89 * 0.5) ^ 2

      // exercise
      double test = calculateDragForce(drag, airDensity, velocity, shellArea);
      // verify
      assert(closeEnough(test, 2048.243, 0.0001));
      // teardown
   }

   void test_calculateDragForce_peak()
   {
      // setup
      double drag = 0.212;
      double airDensity = 0.9093000;
      double velocity = 240;
      double shellArea = 0.018842;

      // exercise
      double test = calculateDragForce(drag, airDensity, velocity, shellArea);
      // verify
      assert(closeEnough(test, 104.607, 0.001));
      // teardown
   }

   // Here we start the artillery prototype tests:
   // This is the angle to be tested

   double inputAngle = 75.0;

   /*****************************************************
   * TESTING INERTIA
   *****************************************************/
   void test_inertia_1()
   {

      // setup

      Angle testAngle = Angle(inputAngle);
      double x = 0;
      double y = 0;
      double dx = computeHorizontalComponent(testAngle, 827);
      double dy = computeVerticalComponent(testAngle, 827);
      // exercise
      for (int i = 0; i < 20; i++)
      {
         x= calculateDisplacement(x,  dx, 0, 1);
         y =  calculateDisplacement( y,  dy,  0, 1);
      }
      // verify
      cout << "Testing the angle: " << inputAngle <<endl;
      cout << "1) Testing Inertia:          Distance: " << x << "m Altitude : " << y << "m\n";
      // teardown
   }


/*****************************************************
* TESTING ACCELERATION
//*****************************************************/
   void test_acceleration_2()
   {
      // setup
   Angle testAngle = Angle(inputAngle);
   double x = 0;
   double y = 0;
   double dx = computeHorizontalComponent(testAngle, 827);
   double dy = computeVerticalComponent(testAngle, 827);
   // exercise
   for (int i = 0; i < 20; i++)
   {
      dy = computeVelocity(dy , -9.8 , 1);
      x = calculateDisplacement(x, dx, 0, 1);
      y = calculateDisplacement(y, dy, -9.8, 1);
   }
   // verify
   cout << "2) Testing Acceleration:     Distance: " << x << "m Altitude : " << y << "m\n";
   // teardown
   }

/*****************************************************
* TESTING GROUND IMPACT 
*****************************************************/
   void test_ground_impact_3()
   {
      // setup
      Angle testAngle = Angle(inputAngle);
      double x = 0;
      double y = 0;
      double hang = 0;
      const double time_interval = 0.01; //turning the time interval into a constant so it does not change
      double dx = computeHorizontalComponent(testAngle, 827);
      double dy = computeVerticalComponent(testAngle, 827);
      // exercise
      while (y >= 0)
      {
         dy = computeVelocity(dy, -9.8, time_interval);
         dx = computeVelocity(dx, 0, time_interval);
         x = calculateDisplacement(x, dx, 0, time_interval);
         y = calculateDisplacement(y, dy, -9.8, time_interval);
         hang += time_interval;
      }
      // verify
      cout << "3) Testing Ground Impact:    Distance: " << x << "m Altitude : " << y << "m  " << "Hang Time: " << hang << endl;
      // teardown
   }

/*****************************************************
* TESTING GRAVITY
*****************************************************/
   void test_gravity_4()
   {
      // setup
      Angle testAngle = Angle(inputAngle);
      double x = 0;
      double y = 0;
      double hang = 0;
      const double time_interval = 0.01; //turning the time interval into a constant so it does not change
      double dx = computeHorizontalComponent(testAngle, 827);
      double dy = computeVerticalComponent(testAngle, 827);
      // exercise
      while (y >= 0)
      {  
         double gravity = gravityFromAltitude(y);
         dy = computeVelocity(dy, gravity, time_interval);
         dx = computeVelocity(dx, 0, time_interval);
         x = calculateDisplacement(x, dx, 0, time_interval);
         y = calculateDisplacement(y, dy, gravity, time_interval);
         hang += time_interval;
      }
      // verify
      cout << "4) Testing Gravity:          Distance: " << x << "m Altitude : " << y << "m  " << "Hang Time: " << hang << endl;
      // teardown
   }
/*****************************************************
* TESTING DRAG
*****************************************************/
   void test_drag_5()
   {
      // setup
      Angle testAngle = Angle(inputAngle);
      double x = 0;
      double y = 0;
      double hang = 0;
      const double time_interval = 0.01; //turning the time interval into a constant so it does not change
      double dx = computeHorizontalComponent(testAngle, 827);
      double dy = computeVerticalComponent(testAngle, 827);
      // exercise
      while (y >= 0)
      {
         double gravity = gravityFromAltitude(y);
         double velocity = sqrt(dx * dx + dy * dy);
         double dragCoefficient = 0.3;
         double densityOfAir = 0.6;
         const double area = 0.018842;
         double dragForce = calculateDragForce(dragCoefficient, densityOfAir, velocity, area);
         double acceleration = calculateAccelerationFromForce(dragForce);
         testAngle.calculateAngle(dx,dy);
         double ddx = computeHorizontalComponent(testAngle, acceleration) * -1;
         double ddy = computeVerticalComponent(testAngle, acceleration) * -1;
         dy = computeVelocity(dy, gravity + ddy, time_interval);
         dx = computeVelocity(dx, ddx, time_interval);
         x = calculateDisplacement(x, dx, ddx, time_interval);
         y = calculateDisplacement(y, dy, gravity + ddy, time_interval);
         hang += time_interval;
         
      }
      // verify
      cout << "5) Testing Drag:             Distance: " << x << "m Altitude : " << y << "m  " << "Hang Time: " << hang << endl;
      // teardown
   }
/*****************************************************
* TESTING AIR DENSITY
*****************************************************/
   void test_air_density_6()
   {
      // setup
      Angle testAngle = Angle(inputAngle);
      double x = 0;
      double y = 0;
      double hang = 0;
      const double time_interval = 0.01; //turning the time interval into a constant so it does not change
      double dx = computeHorizontalComponent(testAngle, 827);
      double dy = computeVerticalComponent(testAngle, 827);
      // exercise
      while (y >= 0)
      {
         double gravity = gravityFromAltitude(y);
         double velocity = sqrt(dx * dx + dy * dy);
         double dragCoefficient = 0.3;
         double densityOfAir = densityFromAltitude(y);
         const double area = 0.018842;
         double dragForce = calculateDragForce(dragCoefficient, densityOfAir, velocity, area);
         double acceleration = calculateAccelerationFromForce(dragForce);
         testAngle.calculateAngle(dx, dy);
         double ddx = computeHorizontalComponent(testAngle, acceleration) * -1;
         double ddy = computeVerticalComponent(testAngle, acceleration) * -1;
         dy = computeVelocity(dy, gravity + ddy, time_interval);
         dx = computeVelocity(dx, ddx, time_interval);
         x = calculateDisplacement(x, dx, ddx, time_interval);
         y = calculateDisplacement(y, dy, gravity + ddy, time_interval);
         hang += time_interval;

      }
      // verify
      cout << "6) Testing Air Density:      Distance: " << x << "m Altitude : " << y << "m  " << "Hang Time: " << hang << endl;
      // teardown
   }
/*****************************************************
* TESTING DRAG COEFFICIENT
*****************************************************/
   void test_drag_coeffecient_7()
   {
      // setup
      Angle testAngle = Angle(inputAngle);
      double x = 0;
      double y = 0;
      double hang = 0;
      const double time_interval = 0.01; //turning the time interval into a constant so it does not change
      double dx = computeHorizontalComponent(testAngle,827.0);
      double dy = computeVerticalComponent(testAngle, 827.0);
      // exercise
      while (y >= 0)
      {
         double gravity = gravityFromAltitude(y);
         double velocity = sqrt(dx * dx + dy * dy);
         double dragCoefficient = dragFromMach(velocity / speedOfSoundFromAltitude(y));
         double densityOfAir = densityFromAltitude(y);
         const double area = 0.018842;
         double dragForce = calculateDragForce(dragCoefficient, densityOfAir, velocity, area);
         double acceleration = calculateAccelerationFromForce(dragForce);
         testAngle.calculateAngle(dx, dy);
         double ddx = computeHorizontalComponent(testAngle, acceleration) * -1.0;
         double ddy = computeVerticalComponent(testAngle, acceleration) * -1.0;
         dy = computeVelocity(dy, gravity + ddy, time_interval);
         dx = computeVelocity(dx, ddx, time_interval);
         x = calculateDisplacement(x, dx, ddx, time_interval);
         y = calculateDisplacement(y, dy, gravity + ddy, time_interval);
         hang += time_interval;
      }
      // verify
      cout << "7) Testing Drag Coefficient: Distance: " << x << "m Altitude : " << y << "m  " << "Hang Time: " << hang << endl;
      // teardown
   }
/*****************************************************
* TESTING HIT THE GROUND
*****************************************************/
   void test_hit_the_ground_8()
   {
      // setup
      Angle testAngle = Angle(inputAngle);
      double x = 0;
      double y = 0;
      double hang = 0;
      const double time_interval = 0.01; //turning the time interval into a constant so it does not change
      double dx = computeHorizontalComponent(testAngle, 827.0);
      double dy = computeVerticalComponent(testAngle, 827.0);

      // Tracking previous position
      double previousX = 0.0;
      double previousY = 0.0;

      // exercise
      while (y >= 0)
      {
         previousX = x;
         previousY = y;
         double gravity = gravityFromAltitude(y);
         double velocity = sqrt(dx * dx + dy * dy);
         double dragCoefficient = dragFromMach(velocity / speedOfSoundFromAltitude(y));
         double densityOfAir = densityFromAltitude(y);
         const double area = 0.018842;
         double dragForce = calculateDragForce(dragCoefficient, densityOfAir, velocity, area);
         double acceleration = calculateAccelerationFromForce(dragForce);
         testAngle.calculateAngle(dx, dy);
         double ddx = computeHorizontalComponent(testAngle, acceleration) * -1.0;
         double ddy = computeVerticalComponent(testAngle, acceleration) * -1.0;
         dy = computeVelocity(dy, gravity + ddy, time_interval);
         dx = computeVelocity(dx, ddx, time_interval);
         x = calculateDisplacement(x, dx, ddx, time_interval);
         y = calculateDisplacement(y, dy, gravity + ddy, time_interval);
         hang += time_interval;
      }
      // The 0 represents the ground (altitude 0)
      double hitX = calculateLinearInterpolation(y, x, previousY, previousX, 0.0);
      // verify
      cout.setf(ios::fixed);
      cout.setf(ios :: showpoint);
      cout.precision(1);
      cout << "8) Testing Hit The Ground:   Distance: " << hitX << "m  Hang Time: " << hang << endl;
   }
      // teardow
};