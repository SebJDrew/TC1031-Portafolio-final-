#include <iostream>
#include "MaxHeap.h"
#include "Registro.h"
#include "Bitacora.h"
int main() {

  Bitacora bita("bitacoraHeap.txt");
  //bita.print();
  bita.ordenaLista();
  
  //bita.print();
  bita.busqueda();
  //std::cout<<bita.busqueda()<<std::endl;
}