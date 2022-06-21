#ifndef __BITACORA_H_
#define __BITACORA_H_
#include "Registro.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Bitacora {
private:
  std::vector<Registro> listaRegistros;
public:
  // constructor
  Bitacora(std::string fileName); // nombre del archivo de texto

  int getSize();
  void print();
  void ordenaLista();
  void heapSort(int n);
  void heapify(int n, int i);
  void busqueda();
};

#endif // __BITACORA_H_