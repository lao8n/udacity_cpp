# CPPND: Capstone Snake Game Example

This is a starter repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

<img src="snake_game.gif"/>

The Capstone Project gives you a chance to integrate what you've learned throughout this program. This project will become an important part of your portfolio to share with current and future colleagues and employers.

In this project, you can build your own C++ application or extend this Snake game, following the principles you have learned throughout this Nanodegree Program. This project will demonstrate that you can independently create applications using a wide range of C++ features.

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source. 
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.

## New Features
* Two types of food: green for positive points and red for negative points. 
* Randomly generate either one or two new foods each time you eat.
* Food will randomly switch from green to red and vice-versa so if all available foods are red you just need to wait (without dying) to get a green. Conversely if you seen a green food you need to eat it quickly before it goes red.

## Rubric Points

### Loops, Functions, I/O
C++ functions and control structures
* The code is organised into functions. Most notably the `Food` class has member functions including constructors & destructors, getters and setters and a function for updating the score.
* Control structures used including if statements in `Food::updateScore` for `std::cv_status::timeout`, in `Snake::SnakeCell` for `bodySet.Count(SDL_Point{x:x, y:y}) > 0` and  if-else in `Render`to choose whether to draw the food as red or green. For loops including a range-based for loop over the foods in `Render` to loop over the foods `for(auto &f : foods)`. Finally, although didn't write `Game::PlaceFood` `while(true)` loop I update the  specifics of the code inside.

Data structures and immutable variables
* `Game` uses a vector for foods `std::vector<std::shared_ptr<Food>> foods;`. `Snake` adds a set of points to its vector of points to represent its body for more efficient lookup `std::vector<SDL_Point> body;`
* `Food` uses a constant variable `SCORE_MULTIPLIER` to update the score of the food from red to green and vice-versa.

### Object Oriented Programming
Classes have appropriate access specifiers for class members
* The `Food` class has data and methods to perform task.
* All `Food` class members are declared as `public` or `private`
* The `Food::updateScore` should flip the score back and forth and this invariant is hidden from the user and the score is accessed via getters and setters instead.

Classes abstract implementation details from their interfaces
* `Food` class member functions document their effects e.g. getters and setters by their names. Additional comments explain why copy constructor and assignment are deleted.

Overloaded functions
* In `SDL.cpp` we overload `bool operator<(const SDL_Point &lhs, const SDL_Point& rhs` because otherwise we cannot use the set in `Snake::SnakeCell` to eficiently lookup whether a cell is occuppied by the Snake.

### Memory Management
Destructors
* `~Food()` stops the thread associated with the class and then waits for the thread to terminate before finishing.

Rule of 5
* In Food we have defined the destructor, however because our class, similar to the Traffic Simulation project, has threads in it, defining copying and moving can be tricky. Thus we follow the rule of 5 by defining the destructor but explicitly not allowing the copy and move semantic functions.

Move semantics
* Having created the food we `foods.emplace_back(std::move(food))` to signify that ownership of the food has moved to `foods` and `food` will no longer be used in scope.

Smart pointers
* In `Game::PlaceFood` we make a shared pointer to `Food`.

### Concurrency
Multi-threading
* `Food` constructor creates a `_scoreThread = std::thread(&Food::updateScore, this);`

Mutex or lock
* `Food` uses a mutex for the `score` to prevent getting or setting or updating to happen at the same time. This is implemented in the code using a `std::lock_guard<std::mutex> lck(_scoreMutex);` logic.

Condition variable
* A food will either be eaten or after a random amount of time switch from red to green or vice-versa. To avoid waiting for the thread to finish we use a `std::condition_variable` where `_cond.wait_for(lck, std::chrono::seconds::distr(engine)));` will be triggered either by the timeout or by the `_cond.notify_one()` in the destructor of `Food.h`

## CC Attribution-ShareAlike 4.0 International


Shield: [![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

This work is licensed under a
[Creative Commons Attribution-ShareAlike 4.0 International License][cc-by-sa].

[![CC BY-SA 4.0][cc-by-sa-image]][cc-by-sa]

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-image]: https://licensebuttons.net/l/by-sa/4.0/88x31.png
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg
