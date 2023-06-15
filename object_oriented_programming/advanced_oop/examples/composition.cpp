#include <iostream>
#include <cmath>
#include <assert.h>

// Define pi
#define PI 3.14159

// Define Line Class
class LineSegment{
public:
    LineSegment(float length): length_(length){}
    float getLength() const {
        return length_;
    }
    // Define protected attribute length
protected: 
    float length_;
};

// Define Circle subclass
class Circle{
public:
    Circle(LineSegment ls): ls_(ls){}
    // Define public setRadius() and getArea()
    float Area(){
        return pow(ls_.getLength(), 2) * PI;
    };
    LineSegment ls_; 
};

// Test in main()
int main() 
{
    LineSegment radius {3};
    Circle circle(radius);
    assert(int(circle.Area()) == 28);
}