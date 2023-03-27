// Marile
// Sofia
// Sebastian 

#include "Bitacora.h"
#include <iostream>

int main() {

  Bitacora bita("bitacora.txt");

   //MERGE SORT
  //Complejidad general: O (nlogn)
  //Complejidad espacial: O (n)
  bita.sortMerge(); 
    
   
  //BÚSQUEDA BINARIA
  //Complejidad de tiempo: 
            //Mejor caso: O(1)
            // Otros casos: O(logn)
  //Complejidad espacial: 
            // Iterativo: O(1)
            // Recursivo: O(logn)
  bita.busqueda();
  //bita.escribir();
  // Añadir almacenamiento del documento
  // Double linked list
  bita.escribir();
  
}