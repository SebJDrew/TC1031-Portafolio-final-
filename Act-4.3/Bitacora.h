#ifndef __BITACORA_H_
#define __BITACORA_H_

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "Graph.h"

class Bitacora {
private:
  Graph Gm;

public:
  // constructor
  Bitacora(std::string fileName); // nombre del archivo de texto
  ~Bitacora();
};

#endif // __BITACORA_H_