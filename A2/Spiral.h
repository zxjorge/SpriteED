/*
 *George Benyeogor
 *CS3505
 *A2: Classes, Facades, and Makefiles
 */

#include <math.h>

class Spiral
{
private:
    double angle_;
    double centerX_;
    double centerY_;
    double scalingFactor_;
    double radius_;
    float getRad2();


public:
    Spiral(double x, double y, double angle, double scalingFactor);
    double getSpiralX();
    double getSpiralY();
    double getSpiralAngle();
    Spiral& operator+=(double scalingFactor);
    void changeRadius();
    float getRad1();
    float getRadius();
};