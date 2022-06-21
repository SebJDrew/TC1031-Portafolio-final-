#ifndef __BITACORA_H_
#define __BITACORA_H_
  #include <iostream>
  #include <fstream>
  #include <sstream>
  #include <string>
  #include <vector>
  #include "Registro.h"
  #include "DLinkedList.h"

  class Bitacora {
    private:
      DLinkedList<Registro> listaRegistros;

    public:
      // constructor
      Bitacora(std::string fileName); // nombre del archivo de texto
      int getSize();
      void print();
      void sort();
      void busqueda();
      void resultado();  

  };

#endif // __BITACORA_H_