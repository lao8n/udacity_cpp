// Example solution for Rectangle and Square friend classes
#include <assert.h>

// forward declaration of Rectangle
class Rectangle;

// Define class Square as friend of Rectangle
class Square {
public:
    Square(int s);
private:
    // Add friend class Rectangle
    friend class Rectangle;
    // Add private attribute side
    int side;
};

// Add public constructor to Square, initialize side
Square::Square(int s) : side(s){}

// Define class Rectangle
class Rectangle {
public:
    Rectangle(Square& sq);
    // Add public function to Rectangle: Area()
    int Area();
    // Add private attributes width, height;
private: 
    int width;
    int height;
};

// Define a Rectangle constructor that takes a Square
Rectangle::Rectangle(Square& sq) : width(sq.side), height(sq.side) {}

// Define Area() to compute area of Rectangle
int Rectangle::Area(){
    return width * height;
}

// Update main() to pass the tests
int main()
{
    Square square(4);
    Rectangle rectangle(square);
    assert(rectangle.Area() == 16); 
}