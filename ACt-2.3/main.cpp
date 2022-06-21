//                   ACTIVIDAD 2.3
//                       Equipo 5
// Marilé González                             A00826863
// Sebastián Jiménez                           A00829101
// Sofía González                              A00828851

#include "Bitacora.h"
#include <iostream>

int main() {

  Bitacora bita("bitacora.txt");
  bita.sort();//QuickSort- Complejidad: O(nlogn)
  std::cout << "Bitacora ordenanda" << std::endl;
  bita.resultado();
  bita.busqueda(); //Búsqueda Binaria: Complejidad: O(logn)
  
  
}