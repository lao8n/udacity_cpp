#ifndef FOOD_H
#define FOOD_H

#include "SDL.h"
#include <mutex>
#include <thread>
#include <atomic>
#include <condition_variable>

class Food {
    public:
        // constructor/destructor
        Food();
        ~Food();
        // delete copy constructor & assignment because copying threads not allowed.
        Food(const Food&) = delete;
        Food& operator=(const Food&) = delete;
        Food(Food&& other) noexcept;
        Food& operator=(Food&& other) noexcept;
        // getter & setters
        SDL_Point getLocation();
        void setLocation(SDL_Point&);
        int getScore();
        void setScore(int score); 

    private:
        void updateScore();
        void stopThread();
        int _score;
        static const int SCORE_MULTIPLIER = -1;
        std::mutex _scoreMutex;
        std::thread _scoreThread;
        std::mutex _stopMutex;
        std::condition_variable _cond;
        SDL_Point _location;
};

#endif