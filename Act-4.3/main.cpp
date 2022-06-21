/** 
* 
*
* Compilacion para debug:  
*    g++ -std=c++17 -g -o main *.cpp 
* Ejecucion con valgrind:
*    nix-env -iA nixpkgs.valgrind
*    valgrind --leak-check=full ./main 
*
* Compilacion para ejecucion:  
*    g++ -std=c++17 -O3 -o main *.cpp 
* Ejecucion:
*    ./main 
**/
#include <iostream>
#include "Bitacora.h"

int main() {

  Bitacora bita("bitacoraGrafos.txt");
  
  return 0;
}