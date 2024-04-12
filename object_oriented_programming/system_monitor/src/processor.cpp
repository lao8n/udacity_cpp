#include "processor.h"
#include "linux_parser.h"
#include <iostream>

// we calculate marginal cpu utilization
float Processor::Utilization() { 
    float util = 0;
    long totalcurrent = LinuxParser::Jiffies();
    long activecurrent = LinuxParser::ActiveJiffies();
    if(totalcurrent != 0) { // don't check active
        long totaldelta = totalcurrent - prevtotal_;
        long activedelta = activecurrent - prevactive_;
        util = float(activedelta) / float(totaldelta);
    }
    prevtotal_ = totalcurrent;
    prevactive_ = activecurrent;
    return util;
}