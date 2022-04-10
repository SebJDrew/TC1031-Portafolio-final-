#ifndef __BITACORA_H_
#define __BITACORA_H_
  #include <iostream>
  #include <fstream>
  #include <sstream>
  #include <string>
  #include <vector>
  #include "Registro.h"

  class Bitacora {
    private:
      std::vector<Registro> listaRegistros;
      void merge(int low, int m, int high);
      void mergeSort(int low, int high);
      int binarySearch(Registro k);
      void resultado(int i,int f);
    public:
      // constructor
      Bitacora(std::string fileName); // nombre del archivo de texto
      int getSize();
      void print();  
      // Agregar aquí métodos para busqueda binaria en el vector llamado listaRegistros
      void busqueda();
      void sortMerge();
  

  };

#endif // __BITACORA_H_