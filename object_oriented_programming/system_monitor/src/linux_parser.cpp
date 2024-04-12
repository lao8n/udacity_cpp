#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

string LinuxParser::OperatingSystem() {
  string line, key, value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
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

float LinuxParser::MemoryUtilization() {
  std::ifstream stream(kProcDirectory + kMeminfoFilename);
  string line;
  int memTotal;
  int memFree;
  string memTotalMatch = "MemTotal:";
  string memFreeMatch = "MemFree:";
  if (stream.is_open()) {
    while (std::getline(stream, line)){
        if (line.find(memTotalMatch) == 0){
            memTotal = extractMemNum(line, memTotalMatch);
        }
        if (line.find(memFreeMatch) == 0){
            memFree = extractMemNum(line, memFreeMatch);
            break; // found all data we need
        }
    }
  }
  int memUsage = memTotal - memFree;
  return float(memUsage) / float(memTotal);
}

long LinuxParser::UpTime() {
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  string line;
  if (stream.is_open()) {
    if (std::getline(stream, line)){
      int numFinish = line.find(" ", 0); // location of space where remove final data
      string uptime = line.substr(0, numFinish - 3); // remove last two digits and decimal point
      try {
        long num = std::stol(uptime);
        return num;
      } catch (const std::invalid_argument& e) {
        std::cerr << "Invalid argument to uptime: " << e.what() << '\n';
      } catch (const std::out_of_range& e) {
        std::cerr << "Out of range to uptime: " << e.what() << '\n';
      }
    }
  }
  return 0;
}

// Total = Active + idle
long LinuxParser::Jiffies() { 
  return LinuxParser::ActiveJiffies() + LinuxParser::IdleJiffies();
}

long LinuxParser::ActiveJiffies(int pid) { 
  string line, val;
  std::ifstream stream(kProcDirectory + to_string(pid) + kStatFilename);
  long active = 0;
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    // we want active = utime (14) + stime (15)
    for (int i = 0; i < 15; i++){ // extract 22nd element starttime, 0-indexed
      linestream >> val;
      if(i >= 13){
        active += std::stol(val);
      }
    }
  }
  return active / sysconf(_SC_CLK_TCK) ;
}

// https://stackoverflow.com/questions/23367857/accurate-calculation-of-cpu-usage-given-in-percentage-in-linux
// active (nonidle) = user + nice + system + irq + softirq + steal
long LinuxParser::ActiveJiffies() { 
  string cpu, user, nice, system, idle, iowait, irq, softirq, steal;
  string line;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> cpu >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal;
  }
  return std::stol(user) + std::stol(nice) + std::stol(system) + std::stol(irq)+ std::stol(softirq) + std::stol(steal);
}

// idle = idle + iowait
long LinuxParser::IdleJiffies() { 
  string cpu, user, nice, system, idle, iowait;
  string line;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> cpu >> user >> nice >> system >> idle >> iowait;
  }
  return std::stol(idle) + std::stol(iowait);
}

// We do not use this - instead calculating prev in processor.cpp
vector<string> LinuxParser::CpuUtilization() { return {}; }

int extractProcesses(std::string line, std::string match){
    string processes = line.substr(match.length(), line.length() - match.length());
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

int LinuxParser::TotalProcesses() { 
  std::ifstream stream(kProcDirectory + kStatFilename);
  string line;
  string match = "processes ";
  if (stream.is_open()) {
    while (std::getline(stream, line)){
      if (line.find(match) == 0){
          return extractProcesses(line, match);
      }
    }
  }
  return 0;
}

int LinuxParser::RunningProcesses() {
  std::ifstream stream(kProcDirectory + kStatFilename);
  string line;
  string match = "procs_running ";
  if (stream.is_open()) {
    while (std::getline(stream, line)){
      if (line.find(match) == 0){
          return extractProcesses(line, match);
      }
    }
  }
  return 0;
}

string LinuxParser::Command(int pid) { 
  std::ifstream stream(kProcDirectory + to_string(pid) + kCmdlineFilename);
  if (stream.is_open()){
    string line;
    std::getline(stream, line);
    return line;
  }
  return "";
}

string LinuxParser::Ram(int pid) {
  std::ifstream stream(kProcDirectory + to_string(pid) + kStatusFilename);
  string line, key, value;
  if (stream.is_open()){
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      while(linestream >> key >> value) {
        if(key == "VmSize:") {
          return value; 
        }
      }
    }
  }
  return "";
}

string LinuxParser::Uid(int pid) { 
  std::ifstream stream(kProcDirectory + to_string(pid) + kStatusFilename);
  string line, key, uid;
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> uid) {
        if (key == "Uid:"){
          return uid;
        }
      }
    }
  }
  return "";
}

string LinuxParser::User(int pid) { 
  string uid = LinuxParser::Uid(pid);
  std::ifstream stream(kPasswordPath);
  string line, name, ignore, matchUid;
  if (stream.is_open()){
    while (std::getline(stream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> name >> ignore >> matchUid){
        if (matchUid == uid){
          return name;
        }
      }
    }
  }
  return "";
}

long LinuxParser::UpTime(int pid) { 
  std::ifstream stream(kProcDirectory + to_string(pid) + kStatFilename);
  string line, val;
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    for (int i = 0; i < 22; i++){ // extract 22nd element starttime, 0-indexed
      linestream >> val;
    }
  }
  try {
    long num = std::stol(val);
    return num / sysconf(_SC_CLK_TCK);
  } catch (const std::invalid_argument& e) {
    std::cerr << "Invalid argument to uptime: " << e.what() << '\n';
  } catch (const std::out_of_range& e) {
    std::cerr << "Out of range to uptime: " << e.what() << '\n';
  }
  return 0;
}
