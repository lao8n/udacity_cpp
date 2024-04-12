#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>
#include <fstream>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

Processor& System::Cpu() { 
    return cpu_;
}

vector<Process>& System::Processes() {
    vector<int> pids = LinuxParser::Pids();
    processes_.clear();
    for (int pid : pids) {
        processes_.emplace_back(pid);
    }
    return processes_;
}

std::string System::Kernel() { 
    if(kernel_ == "") {
        return LinuxParser::Kernel();
    }
    return kernel_;
}

float System::MemoryUtilization() { 
    return LinuxParser::MemoryUtilization();
}

std::string System::OperatingSystem() {
    if(system_ == "") {
        return LinuxParser::OperatingSystem();
    }
    return system_;
}

int System::RunningProcesses() { 
    return LinuxParser::RunningProcesses();
}

int System::TotalProcesses() { 
    return LinuxParser::TotalProcesses();
}

long System::UpTime() { 
    return LinuxParser::UpTime();
}