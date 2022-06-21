#include "Registro.h"

Registro::Registro(){
  this->mes = ""; 
  this->dia = ""; 
  this->horas = ""; 
  this->minutos = ""; 
  this->segundos = ""; 
  this->ip = "";
  this->puerto = "";
  this->falla = "";
}

Registro::Registro(std::string mes,std::string dia,std::string horas,std::string minutos,std::string segundos,std::string ip,std::string puerto,std::string falla){
  this->mes = mes; 
  this->dia = dia;
  this->horas = horas;
  this->minutos = minutos;
  this->segundos = segundos;
  this->ip = ip;
  this->puerto = puerto;
  this->falla = falla;
  // Almacenar los campos de la fecha-hora en el struct tm
  dateStruct.tm_sec = std::stoi(segundos);
  dateStruct.tm_min = std::stoi(minutos);
  dateStruct.tm_hour = std::stoi(horas);
  dateStruct.tm_mday = std::stoi(dia);
  // Agregado para resolver problema de compatibilidad en Windows
  dateStruct.tm_isdst = 0;
  for (int i=0; i < (int)meses.size(); i++) {
    if (meses[i]==mes)
      dateStruct.tm_mon = i;
  }
  dateStruct.tm_year = 2022 - 1900;  // Asumimos el año 2022
  // Obtener el Unix timestamp a partir del struct tm anterior 
  date = mktime(&dateStruct);

  // Agregar conversion de la ip de string a separar octetos
  // p4.p3.p2.p1
  // p4, p3, p2, p1
  // aplicar formula 
  // ipValue = p4*pow(256^3) + p3*pow(256^2) + p2*pow(256^1) + p1;

  // Convertir IP
  int posInit = 0;
  int posFound = 0;
  std::string splitted;
  std::vector<std::string> results;   
  while(posFound >= 0) {
    posFound = ip.find(".", posInit);
    splitted = ip.substr(posInit, posFound - posInit);
    posInit = posFound + 1;
    results.push_back(splitted);
  }
  int partA = std::stoi(results[0]);
  int partB = std::stoi(results[1]);
  int partC = std::stoi(results[2]);
  int partD = std::stoi(results[3]);
  ipValue = partA*(pow(256,3)) + partB*(pow(256,2)) + partC*(pow(256,1)) + partD;
}

std::string Registro::getAll() {
  return mes + " " + dia + " " + horas + ":" + minutos + ":" + segundos + " " + ip + ":" + puerto + " " + falla;
}

unsigned int Registro::getIpValue() {
  //std::cout<<date;
  return ipValue;
}
std::string Registro::getIpStr() {
  //std::cout<<date;
  return ip;
}

// Todas las sobrecargas compara ipValue
bool Registro::operator==(const Registro &other) {
  return this->ipValue == other.ipValue;
}

bool Registro::operator!=(const Registro &other) {
  return this->ipValue != other.ipValue;
}

bool Registro::operator>(const Registro &other) {
  return this->ipValue > other.ipValue;
}

bool Registro::operator<(const Registro &other) {
  return this->ipValue < other.ipValue;
}

bool Registro::operator<=(const Registro &other) {
  return this->ipValue <= other.ipValue;
}

bool Registro::operator>=(const Registro &other) {
  return this->ipValue >= other.ipValue;
}
