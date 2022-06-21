#include "Bitacora.h"
#include "Registro.h"


// Lee los datos y los almacena en un vector de objectos Registro 

//Complejidad: 
Bitacora::Bitacora(std::string fileName) {
  std::string month, day, hours, minutes, seconds, ipAdd, port, error;
  std::ifstream file(fileName);
  if (!file.good()) {
    file.close();
    throw std::invalid_argument("File not found");
  }
  else {
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
      //listaRegistros.push_back(regTemp);
      listaRegistros.addLast(regTemp);
    }
    file.close();
  }
}

//Complejidad:
int Bitacora::getSize() {
  return listaRegistros.getNumElements();
}

void Bitacora::print() {
  DLLNode<Registro> *ptr = listaRegistros.getHead();
  while (ptr != nullptr) {
    std::cout << ptr->data.getAll() << std::endl;
    ptr = ptr->next;
  }
  
}

void Bitacora::sort() {
  listaRegistros.sort();
}

//Complejidad:
void Bitacora::busqueda(){ 

  std::string linea;
  std::cout<<"Dame la fecha de inicio"<<std::endl;
  
  std::string mes1, dia1, tiempo1, hora1, minuto1, segundo1;

  std::cin >> mes1 >> dia1 >> tiempo1;
  hora1 = tiempo1.substr(0,2);
  minuto1 = tiempo1.substr(3,2);
  segundo1 = tiempo1.substr(6,2);

  Registro inicio(mes1,dia1,hora1,minuto1,segundo1,"","","");
  DLLNode<Registro> *indInicio = listaRegistros.find(inicio);
  
  
  std::cout<<"Dame la fecha final"<<std::endl;
  std::cin >> mes1 >> dia1 >> tiempo1;
  hora1 = tiempo1.substr(0,2);
  minuto1 = tiempo1.substr(3,2);
  segundo1 = tiempo1.substr(6,2);

  Registro fin(mes1,dia1,hora1,minuto1,segundo1,"","","");
  DLLNode<Registro> *indFin = listaRegistros.find(fin);
  //std::cout<<"fin: "<<indFin<<std::endl;
  if(indInicio==nullptr || indFin==nullptr){
    if(indInicio==nullptr){
      std::cout<<"La primera fecha no existe"<<std::endl;
    } 
    if(indFin==nullptr){
      std::cout<<"La fecha final no existe"<<std::endl;
    }
  }

  for (DLLNode<Registro> *j = indInicio; j != indFin->next; j = j->next) {
    std::cout << j->data.getAll() << std::endl;
  }
  std::ofstream outdata;
  outdata.open("resultado_busqueda.txt");
  std::ofstream resultado_busqueda;
  resultado_busqueda.open("resultado_busqueda.txt");
  for (DLLNode<Registro> *j = indInicio; j != indFin->next; j = j->next) {
    outdata<< j->data.getAll() << std::endl;
  }
  resultado_busqueda.close();

}

//Complejidad:
void Bitacora::resultado(){
  //std::ofstream outdata;
  std::ofstream bitacora_ordenada;
  bitacora_ordenada.open("bitacora_ordenada.txt");
  DLLNode<Registro> *ptr = listaRegistros.getHead();
  while (ptr != nullptr) {
    bitacora_ordenada<< ptr->data.getAll() << std::endl;
    ptr = ptr->next;
  }
  bitacora_ordenada.close();
}
