/*
 * George Benyeogor
 * CS3505
 * A2: Classes, Facades, and Makefiles
 * This class defines methods that allows a user to draw a Spiral.
 */

#include <math.h>
#include "Spiral.h"

/// @brief A constructor that initializes the Spiral with the appropiate values.
/// @param centerX The x coordinate of the center of the Spiral.
/// @param centerY The y coordinate of the center of the Spiral.
/// @param angle The starting angle of the Spiral.
/// @param scaling_factor A double that helps the Spiral grow.
Spiral::Spiral(double centerX, double centerY, double angle, double scalingFactor)
{
    centerX_ = centerX;
    centerY_ = centerY;
    //Enforces a positive starting angle
    if (angle > 0)
        angle_ = angle;
    else
        angle_ = 90;
    scalingFactor_ = scalingFactor;
    changeRadius();
}

/// @brief A getter for the x coordinate of the current Spiral point.
/// @return The x coordinate of the current Spiral point.
double Spiral::getSpiralX()
{
    return centerX_ + radius_ * cos(getRad2());
}

/// @brief A getter for the y coordinate of the current Spiral point.
/// @return The y coordinate of the current Spiral point.
double Spiral::getSpiralY()
{
    return centerY_ + radius_ * sin(getRad2());
}

/// @brief A getter for the angle of the Spiral.
/// @return The current angle of the Spiral.
double Spiral::getSpiralAngle()
{
    return angle_;
}

/// @brief This method overloads the "+=" operator defining it appropiate behavior for the Spiral.
/// @param scalingFactor A double that is used to grow the angle.
/// @return A reference to the object that called this method.
Spiral& Spiral::operator+=(double scalingFactor)
{
    this->angle_ += scalingFactor;
    return *this;
}

/// @brief A helper method that grows the radius as the Spiral grows.
void Spiral::changeRadius()
{
    radius_ = angle_ * scalingFactor_;
}

/// @brief A helper method that calculates the angle of orientation of a point on the Spiral.
/// @return A float representing the angle of orientation of a point on the Spiral.
float Spiral::getRad1()
{
    return -((angle_) / 180 * 3.141592);
}

/// @brief A helper method that calculates the angle of a distance traveled along the Spiral.
/// @return A float representing the angle of a distance traveled along the Spiral.
float Spiral::getRad2()
{
    return -((angle_ - 90) / 180 * 3.141592);
}

/// @brief A helper method that returns the current radius.
/// @return The current radius.
float Spiral::getRadius(){
    return radius_;
}
