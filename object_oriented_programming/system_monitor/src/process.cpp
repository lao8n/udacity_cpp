#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

Process::Process(int pid) : pid_(pid){}

int Process::Pid() { 
    return pid_;
}

// we calculate aggregate utilization to allow us to const comparison
// by not updating private members
float Process::CpuUtilization() {
    long totalcurrent = LinuxParser::UpTime(pid_); // use system figure
    long activecurrent = LinuxParser::ActiveJiffies(pid_);
    float util = float(activecurrent) / float(totalcurrent);
    return util;
}

string Process::Command() { 
    return LinuxParser::Command(pid_);
}

string Process::Ram() { 
    return LinuxParser::Ram(pid_);
}

string Process::User() { 
    return LinuxParser::User(pid_);
}

long int Process::UpTime() { 
    return LinuxParser::UpTime(pid_);
}

bool Process::operator<(Process const& a) const {
    return pid_ < a.pid_;
}