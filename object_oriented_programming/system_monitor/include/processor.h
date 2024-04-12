#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
  float Utilization();  

 private:
  long prevtotal_;
  long prevactive_;
};

#endif