#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "process.h"
#include "processor.h"
#include "system.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

// Trade-off between keeping ifstreams open or not - decided to keep open to avoid having to open/close continously when in use
System::System() {
  os_release_.open("/etc/os-release");
  if (!os_release_.is_open()){
      std::cerr << "Failed to open /etc/os-release" << std::endl; // do not throw error
  }  
  version_.open("/proc/version");
  if (!version_.is_open()){
      std::cerr << "Failed to open /proc/version" << std::endl;
  }
  mem_info_.open("/proc/meminfo");
  if (!mem_info_.is_open()){
      std::cerr << "Failed to open /proc/meminfo" << std::endl;
  }
  stat_.open("/proc/stat");
  if (!stat_.is_open()){
      std::cerr << "Failed to open /proc/stat" << std::endl;
  }
  uptime_.open("/proc/uptime");
  if (!uptime_.is_open()){
      std::cerr << "Failed to open /proc/uptime" << std::endl;
  }
}

// TODO: Return the system's CPU
Processor& System::Cpu() { 
    return cpu_; 
}

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() { return processes_; }

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() { 
    version_.clear();
    version_.seekg(0, std::ios::beg);
    std::string line;
    std::string match = "Linux version ";
    while (std::getline(version_, line)){
        if (line.find(match) == 0){
            int pos = line.find(" ", match.length() + 1); // first space after Linux version 
            std::string linuxVersion = line.substr(match.length(), pos - match.length());
            return linuxVersion;
        }
    }
    return "";
}

int extractMemNum(std::string line, std::string match){
    // MemTotal:     7910692 kB
    int numStart = line.find_first_not_of(" ", match.length() + 1); // location of 7
    int numFinish = line.find(" ", numStart); // location of space after number
    std::string memData = line.substr(numStart, numFinish - numStart);
    try {
        int num = std::stoi(memData);
        return num;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Invalid argument: " << e.what() << '\n';
    } catch (const std::out_of_range& e) {
        std::cerr << "Out of range: " << e.what() << '\n';
    }
    return 0;
}

// TODO: Return the system's memory utilization
float System::MemoryUtilization() { 
    mem_info_.clear();
    mem_info_.seekg(0, std::ios::beg);

    std::string line;
    int memTotal;
    int memFree;
    std::string memTotalMatch = "MemTotal:";
    std::string memFreeMatch = "MemFree:";
    while (std::getline(mem_info_, line)){
        if (line.find(memTotalMatch) == 0){
            memTotal = extractMemNum(line, memTotalMatch);
        }
        if (line.find(memFreeMatch) == 0){
            memFree = extractMemNum(line, memFreeMatch);
            break; // found all data we need
        }
    }
    int memUsage = memTotal - memFree;
    return float(memUsage) / float(memTotal);
}

// TODO: Return the operating system name
std::string System::OperatingSystem() {
    // PRETTY_NAME="Ubuntu 18.04.2 LTS"
    os_release_.clear();
    os_release_.seekg(0, std::ios::beg);
    std::string line;
    std::string match = "PRETTY_NAME=\"";
    while (std::getline(os_release_, line)){
        if (line.find(match) == 0){
            std::string prettyName = line.substr(match.length(), line.length() - match.length() - 1);
            return prettyName;
        }
    }
    return "";
}

int extractProcesses(std::string line, std::string match){
    std::string processes = line.substr(match.length(), line.length() - match.length());
    try {
        int num = std::stoi(processes);
        return num;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Invalid argument to " << match << e.what() << '\n';
    } catch (const std::out_of_range& e) {
        std::cerr << "Out of range for " << match << e.what() << '\n';
    }
    return 0;
}

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { 
    stat_.clear();
    stat_.seekg(0, std::ios::beg);
    std::string line;
    std::string match = "procs_running ";
    while (std::getline(stat_, line)){
        if (line.find(match) == 0){
            return extractProcesses(line, match);
        }
    }
    return 0;
}

// TODO: Return the total number of processes on the system
int System::TotalProcesses() { 
    stat_.clear();
    stat_.seekg(0, std::ios::beg);
    std::string line;
    std::string match = "processes ";
    while (std::getline(stat_, line)){
        if (line.find(match) == 0){
            return extractProcesses(line, match);
        }
    }
    return 0;
}

// TODO: Return the number of seconds since the system started running
long System::UpTime() { 
    // 13145.60 43993.58 - we want first number
    uptime_.clear();
    uptime_.seekg(0, std::ios::beg);
    std::string line;
    if (std::getline(uptime_, line)){
        int numFinish = line.find(" ", 0); // location of space where remove final data
        std::string uptime = line.substr(0, numFinish - 3); // remove last two digits and decimal point
        try {
            long num = std::stol(uptime);
            return num;
        } catch (const std::invalid_argument& e) {
            std::cerr << "Invalid argument to uptime: " << e.what() << '\n';
        } catch (const std::out_of_range& e) {
            std::cerr << "Out of range to uptime: " << e.what() << '\n';
        }
    }
    return 0;
}