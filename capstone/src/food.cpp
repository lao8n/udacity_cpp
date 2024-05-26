#include "food.h"
#include <chrono>
#include <random>
#include <iostream>

Food::Food(){
    _scoreThread = std::thread(&Food::updateScore, this);
}

Food::~Food(){
    stopThread();
    // std::cout << "stop thread" << std::endl;
    if(_scoreThread.joinable()){
        _scoreThread.join(); // wait for thread to finish
    }
}

SDL_Point Food::getLocation(){
    return _location;
}

void Food::setLocation(SDL_Point& location)
{
    _location = location;
}

int Food::getScore(){
    std::lock_guard<std::mutex> lck(_scoreMutex);
    return _score;
}

void Food::setScore(int score){
    std::lock_guard<std::mutex> lck(_scoreMutex);
    _score = score;
}

void Food::updateScore(){
    std::random_device dev;
    std::mt19937 engine(dev());
    std::uniform_int_distribution<> distr(1, 10); 
    std::unique_lock<std::mutex> lck(_stopMutex);
    auto status = _cond.wait_for(lck, std::chrono::seconds(distr(engine)));
    if(status == std::cv_status::timeout){
        // thread timed out - not stopped
        std::lock_guard<std::mutex> lck(_scoreMutex);
        _score *= SCORE_MULTIPLIER;
    }
}

void Food::stopThread(){
    _cond.notify_one();
}