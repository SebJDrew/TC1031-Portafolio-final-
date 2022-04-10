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
  for (int i=0; i < meses.size(); i++) {
    if (meses[i]==mes)
      dateStruct.tm_mon = i;
  }
  dateStruct.tm_year = 2022 - 1900;  // Asumimos el año 2022
  // Obtener el Unix timestamp a partir del struct tm anterior 
  date = mktime(&dateStruct);
}

std::string Registro::getAll() {
  return mes + " " + dia + " " + horas + ":" + minutos + ":" + segundos + " " + ip + ":" + puerto + " " + falla;
}

time_t Registro::getDate() {
  //std::cout<<date;
  return date;
}

bool Registro::operator==(const Registro &other) {
  return this->date == other.date;
}

bool Registro::operator!=(const Registro &other) {
  return this->date != other.date;
}

bool Registro::operator>(const Registro &other) {
  return this->date > other.date;
}

bool Registro::operator<(const Registro &other) {
  return this->date < other.date;
}

bool Registro::operator<=(const Registro &other) {
  return this->date <= other.date;
}

bool Registro::operator>=(const Registro &other) {
  return this->date >= other.date;
}
