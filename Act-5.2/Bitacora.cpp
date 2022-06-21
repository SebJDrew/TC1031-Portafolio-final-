#include "Bitacora.h"


// Lee los datos y los almacena en un vector de objectos Registro
Bitacora::Bitacora(std::string fileName) {
  Gm.loadDirectedGraph(fileName);
  //Gm.saveGrados();
  //Gm.maxGrados();
  //Gm.shortestPath();
  //Gm.printGraph();
  Gm.ImplementTH();
  Gm.Resultados();
}

Bitacora::~Bitacora() {
  
}


