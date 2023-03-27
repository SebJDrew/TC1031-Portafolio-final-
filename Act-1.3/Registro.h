#ifndef _REGISTRO_H_
#define _REGISTRO_H_
  #include <string>
  #include <vector>
  #include <ctime>
  #include <iostream>
  #include <sstream>


  
  class Registro {
  private:
    std::string mes, dia, horas, minutos, segundos, ip, puerto, falla;
    std::vector<std::string> meses = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    // Struct que contiene todos los datos de la fecha-hora
    struct tm dateStruct;
    // Unix timestamp (segundos transcurridos desde 00:00 hrs, Jan 1, 1970 UTC)
    time_t date;

  public:
    std::string to_string() const {
      std::stringstream ss;
      ss << mes << " " << dia << " " << horas<<" "<< minutos << " " << segundos << " " << ip<<" "<<puerto<<" "<<" "<<falla;
      return ss.str();}
    Registro();
    Registro(std::string mes,std::string dia,std::string horas,std::string minutos,std::string segundos,std::string ip,std::string puerto,std::string falla);
    std::string getAll();
    time_t getDate();
    bool operator ==(const Registro&);
    bool operator !=(const Registro&);
    bool operator >(const Registro&);
    bool operator <(const Registro&);
    bool operator >=(const Registro&);
    bool operator <=(const Registro&);



  };



#endif  //_REGISTRO_H_