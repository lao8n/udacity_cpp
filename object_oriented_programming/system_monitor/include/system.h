#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <vector>
#include <fstream>

#include "process.h"
#include "processor.h"
using std::ifstream;

class System {
 public:
  Processor& Cpu();                   
  std::vector<Process>& Processes();  
  float MemoryUtilization();          
  long UpTime();                      
  int TotalProcesses();               
  int RunningProcesses();             
  std::string Kernel();               
  std::string OperatingSystem();      

 private:
  Processor cpu_ = {};
  std::vector<Process> processes_ = {};
  std::string kernel_ = "";
  std::string system_ = "";
};

#endif