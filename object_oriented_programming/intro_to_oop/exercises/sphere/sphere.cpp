#include <cassert>
#include <cmath>
#include <stdexcept>
// #include <numbers> std::numbers::pi need C++ 20

// TODO: Define class Sphere
class Sphere {
 public:
  // Constructor
    Sphere(int radius): radius_(radius) {
        if(radius <= 0) throw std::invalid_argument("radius must be positive");
    }
  // Accessors
    int Radius() const { return radius_; };
    float Volume() const { return 4.0 / 3.0 * 2 * acos(0.0) * Radius() * Radius() * Radius(); };
 private:
  // Private members
    int radius_;
};

// Test
int main(void) {
  Sphere sphere(5);
  assert(sphere.Radius() == 5);
  assert(abs(sphere.Volume() - 523.6) < 1);
}