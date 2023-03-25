/******************************
* Authors:
* Marco Varela
* Purpose:
* Implementing the physics equations for the artillery simulator
* This file has been developed using TDD
*******************************/

#include "physics.h"
#include "angle.h"
using namespace std;

const vector <tables> gravities =
{
   // Altitude, Gravity
   {0,	   9.807},
   {1000,   9.804},
   {2000,   9.801},
   {3000,   9.797},
   {4000,   9.794},
   {5000,   9.791},
   {6000,   9.788},
   {7000,   9.785},
   {8000,   9.782},
   {9000,   9.779},
   {10000,  9.776},
   {15000,  9.761},
   {20000,  9.745},
   {25000,  9.730}
};

const vector <tables> densities =
{
   // Altitude, Density
   {0,      1.2250000},
   {1000,	1.1120000},
   {2000,	1.0070000},
   {3000,	0.9093000},
   {4000,	0.8194000},
   {5000,	0.7364000},
   {6000,	0.6601000},
   {7000,	0.5900000},
   {8000,	0.5258000},
   {9000,	0.4671000},
   {10000,	0.4135000},
   {15000,	0.1948000},
   {20000,	0.0889100},
   {25000,	0.0400800},
   {30000,	0.0184100},
   {40000,	0.0039960},
   {50000,	0.0010270},
   {60000,	0.0003097},
   {70000,	0.0000828},
   {80000,	0.0000185}
};

const vector <tables> dragCoefecients =
{
   // Mach, Drag Coefficient
   {0.300, 0.1629},
   {0.500, 0.1659},
   {0.700, 0.2031},
   {0.890, 0.2597},
   {0.920, 0.3010},
   {0.960, 0.3287},
   {0.980, 0.4002},
   {1.000, 0.4258},
   {1.020, 0.4335},
   {1.060, 0.4483},
   {1.240, 0.4064},
   {1.530, 0.3663},
   {1.990, 0.2897},
   {2.870, 0.2297},
   {2.890, 0.2306},
   {5.000, 0.2656}
};

const vector<tables> speedsOfSound =
{
   // Altitude, Speed of Sound
   {0,	   340},
   {1000,	336},
   {2000,	332},
   {3000,	328},
   {4000,	324},
   {5000,	320},
   {6000,	316},
   {7000,	312},
   {8000,	308},
   {9000,	303},
   {10000,	299},
   {15000,	295},
   {20000,	295},
   {25000,	295},
   {30000,	305},
   {40000,	324}
};


/**************************************
FUNCTION TO GET GRAVITY FROM ALTITUDE
***************************************/
double gravityFromAltitude(double altitude)
{
   return linearInterpolation(gravities, altitude) * -1;
}

/**************************************
FUNCTION TO GET DRAG COEFFICIENT FROM MACH
***************************************/
double dragFromMach(double mach)
{
   return linearInterpolation(dragCoefecients, mach);
}

/**************************************
FUNCTION TO GET DENSITY FROM ALTITUDE
***************************************/
double densityFromAltitude(double altitude)
{
   return linearInterpolation(densities, altitude);
}

/**************************************
FUNCTION TO GET SPEED OF SOUND FROM ALTITUDE
***************************************/
double speedOfSoundFromAltitude(double altitude)
{
   return linearInterpolation(speedsOfSound, altitude);
}

/****************************************
* GET FROM VALUE FROM TABLE BY REFERENCE
*****************************************/
double linearInterpolation(const vector <tables> & table, double key)
{
   // If key is less than the lowest value, then key will be treated as the lowest bound
   if (key <= table.begin() -> x)
      return table.begin() -> y;
   
   // If key is greater than the greatest value, then key will be treated as the upper bound
   if (key >= table.rbegin()->x)
      return table.rbegin()->y;
 

    // Find upper and lower bounds
   double lower = 0;
   double upper = 0;
   for (int i = 0; i < table.size(); i++)
   {
      if (table[i].x > key)
      {
         upper = i;
         break;
      }
      lower = i;
   }
   return calculateLinearInterpolation(table[lower].x, table[lower].y, table[upper].x, table[upper].y, key);
   
}

/******************************
* CALCULATE LINEAR INTERPOLATION
*******************************/
double calculateLinearInterpolation(double x0, double y0, double x1, double y1, double x)
{
   return ((y1 - y0) / (x1 - x0)) * (x - x0) + y0;
}

/******************************
* CALCULATE DRAG FORCE    d = ½ c ρ v2 a
*******************************/
double calculateDragForce(double drag, double airDensity, double velocity, double shellArea)
{  
   double half = .5;
   return (half * drag * airDensity * velocity * velocity * shellArea);
}

// Function to update position/ displacement
double calculateDisplacement(double s, double v, double a, double t)
{  
   double half = .5;
   return s + v * t + half * a * (t * t);
}

// Calculate acceleration from force
double calculateAccelerationFromForce(double force) { return force / MASS; }

// Compute horizontal component
double computeHorizontalComponent(Angle a, double s) 
{
   return s * sin(a.getAngle());
}

// Compute vertical component
double computeVerticalComponent(Angle a, double s) 
{
   return s * cos(a.getAngle());
}

// Update velocity 
double computeVelocity(double dx, double a, double t) 
{
   return dx + a * t;
}