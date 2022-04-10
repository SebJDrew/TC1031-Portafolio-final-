#include "Bitacora.h"
#include "Registro.h"


// Lee los datos y los almacena en un vector de objectos Registro 
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
      listaRegistros.push_back(regTemp);
    }
  }
}

int Bitacora::getSize() {
  return listaRegistros.size();
}

void Bitacora::print() {
  std::cout << std::endl;
  for (int i=0; i < listaRegistros.size(); i++) {
    std::cout << listaRegistros[i].getAll() << std::endl;
  }
}



void Bitacora::merge(int low, int m, int high) {
  int i, j, k;
  int n1 = m - low + 1;
  int n2 = high - m;
  // crear arreglos L y R
  std::vector<Registro> L(n1), R(n2);
  // Copiar datos a L y R
  for (i = 0; i < n1; i++){
    L[i] = listaRegistros[low + i];
  }  
  for (j = 0; j < n2; j++){
    R[j] = listaRegistros[m + 1 + j];
  }
  // Fusionar los subarreglos L y R
  i = j = 0; k = low;
  while (i < n1 && j < n2) {
    if (L[i]<=R[j]){
      listaRegistros[k] = L[i];
      i++;
    } 
    else {
      listaRegistros[k] = R[j];
      j++;
    }
    k++;
  }
  // Copia los elementos restantes
  while (i < n1) {
	  listaRegistros[k] = L[i];
	  i++;
	  k++;
  }
  while (j < n2) {
	  listaRegistros[k] = R[j];
	  j++;
	  k++;
  }
}
void Bitacora::mergeSort(int low, int high) {
  if (low < high) {
    // encontrar el punto medio
    int m = low + (high - low)/2;
    // Ordenar las dos mitades
    mergeSort(low, m);
    mergeSort(m+1, high);
    // Fusionar ambas mitades 
    merge(low, m, high);
  }
}

void Bitacora::sortMerge() {
  mergeSort(0, listaRegistros.size()-1);
  
}

int Bitacora::binarySearch(Registro k) {
  int low = 0;
  int high = listaRegistros.size() - 1;
  while (low <= high) {
    int m = low + (high - low) / 2;
    if (k == listaRegistros[m]) return m;
    else if (k < listaRegistros[m]) 
      high = m - 1;
    else 
      low = m + 1;
  }
  return -1;
}

void Bitacora::busqueda(){

  std::string linea;
  std::cout<<"Dame la fecha de inicio"<<std::endl;
  
  std::string mes1, dia1, tiempo1, hora1, minuto1, segundo1;

  std::cin >> mes1 >> dia1 >> tiempo1;
  hora1 = tiempo1.substr(0,2);
  minuto1 = tiempo1.substr(3,2);
  segundo1 = tiempo1.substr(6,2);

  Registro inicio(mes1,dia1,hora1,minuto1,segundo1,"","","");
  int indInicio = binarySearch(inicio);
  //std::cout<<"Inicio: "<<indInicio<<std::endl;
  
  std::cout<<"Dame la fecha final"<<std::endl;
  //std::istringstream sss(linea);
  std::cin >> mes1 >> dia1 >> tiempo1;
  hora1 = tiempo1.substr(0,2);
  minuto1 = tiempo1.substr(3,2);
  segundo1 = tiempo1.substr(6,2);

  Registro fin(mes1,dia1,hora1,minuto1,segundo1,"","","");
  int indFin = binarySearch(fin);
  //std::cout<<"fin: "<<indFin<<std::endl;

  int idI=indInicio;
  if(indInicio==-1 || indFin==-1){
    if(indInicio==-1){
      std::cout<<"La primera fecha no existe"<<std::endl;
    } 
    if(indFin==-1){
      std::cout<<"La fecha final no existe"<<std::endl;
    }
  }
  else{
    int iii= indInicio%10;
    int iif= indFin%10;
    int Cr=0;
    if(iii==0 ||iif==0){
      while(idI<=indFin){
        Cr++;
        idI++;
      }
    }
    else{
      Cr=indFin-indInicio;
    }
    
    std::cout<<"Resultado: "<<Cr<<" Registros"<<std::endl;
    resultado(indInicio,indFin);
  }
}


void Bitacora::resultado(int i,int f){
  while(i<=f){
    std::cout<<listaRegistros[i].getAll()<<std::endl;
    i++;
  }
}