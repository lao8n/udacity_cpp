#include <string>
#include <sstream>
#include <iomanip>

#include "format.h"

using std::string;

string Format::ElapsedTime(long seconds) {
    long hours = seconds / 3600;
    long minutes = (seconds % 3600) / 60;
    long remainingSeconds = seconds % 60;
    std::ostringstream oss; 
    oss << std::setfill('0') 
        << std::setw(2) << hours << ":" 
        << std::setw(2) << minutes << ":" 
        << std::setw(2) << remainingSeconds;
    return oss.str(); 
}