#include "Bitacora.h"
#include "MaxHeap.h"
#include "Registro.h"

// Lee los datos y los almacena en un vector de objectos Registro
Bitacora::Bitacora(std::string fileName) {
  std::string month, day, hours, minutes, seconds, ipAdd, port, error;
  std::ifstream file(fileName);
  if (!file.good()) {
    file.close();
    throw std::invalid_argument("File not found");
  } else {

    while (!file.eof()) {
      // Lee una línea y la separa en variables
      std::getline(file, month, ' ');
      std::getline(file, day, ' ');
      std::getline(file, hours, ':');
      std::getline(file, minutes, ':');
      std::getline(file, seconds, ' ');
      std::getline(file, ipAdd, ':');
      std::getline(file, port, ' ');
      std::getline(file, error);
      // Crear objeto de la clase Registro
      Registro regTemp(month, day, hours, minutes, seconds, ipAdd, port, error);
      // Agregar Registro al vector
      listaRegistros.push_back(regTemp);
    }
    file.close();
  }
}

int Bitacora::getSize() { return (int)listaRegistros.size(); }

void Bitacora::print() {
  std::cout << std::endl;
  for (int i = 0; i < (int)listaRegistros.size(); i++) {
    std::cout << listaRegistros[i].getAll() << std::endl;
  }
}

void Bitacora::ordenaLista() { heapSort(listaRegistros.size()); }

// Main function to do heap sort

//Complejidad O(n log n)
void Bitacora::heapSort(int n) {
  // Build heap (rearrange array)
  for (int i = n / 2 - 1; i >= 0; i--)
    heapify(n, i);
  // One by one extract an element from heap
  for (int i = n - 1; i > 0; i--) {
    // Move current root to end
    std::swap(listaRegistros[0], listaRegistros[i]);
    // call max heapify on the reduced heap
    heapify(i, 0);
  }
}

//Complejidad O(log n)
void Bitacora::heapify(int n, int i) {
  // Initialize largest as root
  int largest = i;
  // left = 2*i + 1
  int l = 2 * i + 1;
  // right = 2*i + 2
  int r = 2 * i + 2;
  // If left child is larger than root
  if (l < n && listaRegistros[l] > listaRegistros[largest])
    largest = l;
  // If right child is larger than largest
  // so far
  if (r < n && listaRegistros[r] > listaRegistros[largest])
    largest = r;
  // If largest is not root
  if (largest != i) {
    std::swap(listaRegistros[i], listaRegistros[largest]);
    // Recursively heapify the affected sub-tree
    heapify(n, largest);
  }
}

// IP arbol que ayuda a disminuir la cantidad de datos repetidos
// Orden vector que hace el conteo de las ip segun la ip y posicion
// Ip vector que tiene la estructura del arbol y que tiene las ip con posicion


//Complejidad: 
//Mejor caso: O(1)
//Peor caso: O(log n)
void Bitacora::busqueda() {
  std::ofstream bitacora_ordenada;
  bitacora_ordenada.open("bitacora_ordenada.txt");
  MaxHeap<std::pair<unsigned int, std::string>> MH((int)listaRegistros.size());
  unsigned int ip;
  int cont = 1;
  for (int i = 0; i < (int)listaRegistros.size(); i++) {
    bitacora_ordenada << listaRegistros[i].getAll() << std::endl;
    ip = listaRegistros[i].getIpValue();
    if (ip == listaRegistros[i + 1].getIpValue()) {
      cont++;
    } else {
      std::pair<unsigned int, std::string> tmpPair(
          cont, listaRegistros[i].getIpStr());
      MH.push(tmpPair);
      cont = 1;
    }
  }
  bitacora_ordenada.close();
  std::ofstream ips_con_mayor_acceso;
  ips_con_mayor_acceso.open("ips_con_mayor_acceso.txt");
  for (int i = 0; i < 5; i++) {
    std::pair<unsigned int, std::string> tmpPair = MH.pop();
    std::cout << tmpPair.first << ", " << tmpPair.second << std::endl;
    ips_con_mayor_acceso << tmpPair.first << ", " << tmpPair.second
                         << std::endl;
  }
  ips_con_mayor_acceso.close();
}