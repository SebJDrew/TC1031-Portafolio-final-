#include "Graph.h"
#include <queue>


Graph::Graph() {
  numNodes = 0;
  numEdges = 0;
}

Graph::~Graph() {
  adjList.clear();
  mapIP.clear();
  ips.clear();
  //maxHeapIPs = std::priority_queue<std::pair<int,std::string>> ();
}

//Complejidad O(1)
void Graph::loadDirectedGraph(std::string fileName) {
  std::string line, ip1, ip2, peso;
  int indexIP = 0;
  std::ifstream file(fileName);
  if (!file.good()) {
    file.close();
    throw std::invalid_argument("File not found");
  } else {
    while (std::getline(file, line)) {
      if (indexIP == 0) {
        // std::cout << "line: " << line << std::endl;
        std::vector<int> res;
        split(line, res);
        numNodes = res[0];
        numEdges = res[1];
        // Reservar memoria para los renglones de la lista de adyacencia
        // (renglon 0 no utilizado)
        adjList.resize(numNodes + 1);
        ips.resize(numNodes + 1);
        // Declara una lista vacia para cada renglon y la almacena en el vector
        for (int k = 1; k <= numNodes; k++) {
          LinkedList<std::pair<int, int>>
              tmpList; // en ponderado lista de pares
          adjList[k] = tmpList;
        }
      } else if (indexIP > 0 && indexIP <= numNodes) {
        ipAddress tmpIP(line, "", indexIP);
        mapIP.insert({tmpIP.getIpValue(), tmpIP}); // {ipValue, IP}
        ips[indexIP] = tmpIP;
      } else if (indexIP > numNodes) {
        std::size_t found = line.find(":", 15);
        ip1 = line.substr(15, found - 15);
        std::size_t found2 = line.find(" ", found + 1);
        std::size_t found3 = line.find(":", found2 + 1);
        ip2 = line.substr(found2, found3 - found2);
        std::size_t found4 = line.find(" ", found3 + 1);
        std::size_t found5 = line.find(" ", found4 + 1);
        peso = line.substr(found4, found5 - found4);
        // Crear arista ip1 a ip2 con un peso
        ipAddress tmpIP1(ip1, "", 0);
        ipAddress tmpIP2(ip2, "", 0);
        std::map<unsigned int, ipAddress>::iterator it;
        int ip1Index, ip2Index;
        it = mapIP.find(tmpIP1.getIpValue());
        if (it != mapIP.end())
          ip1Index = it->second.getIpIndex();
        it = mapIP.find(tmpIP2.getIpValue());
        if (it != mapIP.end())
          ip2Index = it->second.getIpIndex();
        adjList[ip1Index].addLast({ip2Index, stoi(peso)});
        ips[ip1Index].addToDegree();
        ips[ip2Index].addToDegreeIn();
      }
      indexIP++;
    }
    file.close();
  }
}

void Graph::split(std::string line, std::vector<int> &res) {
  size_t strPos = line.find(" ");
  size_t lastPos = 0;
  while (strPos != std::string::npos) {
    res.push_back(stoi(line.substr(lastPos, strPos - lastPos)));
    lastPos = strPos + 1;
    strPos = line.find(" ", lastPos);
  }
  res.push_back(stoi(line.substr(lastPos, line.size() - lastPos)));
}

//Complejidad O(1)
void Graph::printGraph() {
  std::cout << "Adjacency List" << std::endl;
  for (int u = 1; u <= numNodes; u++) {
    std::cout << "vertex " << u << ": ";
    for (int j = 0; j < adjList[u].getNumElements(); j++) {
      std::pair<int, int> arista = adjList[u].getData(j);
      std::cout << "{" << arista.first << ", " << arista.second << "}  ";
    }
    std::cout << std::endl;
  }
}


void Graph::ImplementTH(){
  std::cout<<"Se añaden los datos a la Hash table"<<std::endl;
  // numNodes * 1.6 convertido a primo mas cercano
  TH.setCapacity(20063);
  for (int u = 1; u <= numNodes; u++) {
    TH.add(ips[u].getIpValue(), ips[u]);
  }
  // print colisiones
  std::cout<<"Las colisiones totales son "<<TH.getColisiones()<<std::endl;
}

void Graph::Resultados(){
  std::cout<<"Introduce una Ip"<<std::endl;
  std::string vIP;
  std::cin>>vIP;
  ipAddress tmpIP(vIP,"",0);
  ipAddress result = TH.find(tmpIP.getIpValue());
  std::cout<<std::endl;
  std::cout<<std::endl;
  std::cout<<"La ip introducida es "<<result.getIp()<<std::endl;
  std::cout<<"La cantidad de salidas es de "<<result.getDegree() <<std::endl;
  std::cout<<"La cantidad de IP's entrantes es de "<<result.getDegreeIn() <<std::endl;
  std::cout<<"La IP se encuentra en el indice "<<result.getIpIndex()<<std::endl;
  int nodo =result.getIpIndex();
  std::cout<<std::endl;
  std::cout<<std::endl;
  std::cout<<"Las IP que trataron de ingresar son las siguientes: "<<std::endl;
  std::vector<ipAddress> resultAdj;
  for (int j = 0; j < adjList[nodo].getNumElements(); j++) {
      std::pair<int, int> arista = adjList[nodo].getData(j);
      resultAdj.push_back(ips[arista.first]);
  }
  
  //Complejidad O(n)
  std::sort(resultAdj.begin(), resultAdj.end());
  for (int j = 0; j<resultAdj.size();j++){
    std::cout<<resultAdj[j].getIp()<<std::endl;
  }
}


//18719 = 6549
//20063 = 5385
//21433 = 4367
//24061 = 3302
//22739 = 3631
//25409 = 

/*
  Piden a usuario IP en string ipStr
  ipAddress tmpIP(ipStr, "", 0);
  convierten IPString a objeto ipAddress 
  con metodo getIpValue tienen la llave con la cual buscar en la tabla hash
  ipAddress result = TH.find(tmpIP.getIpValue);
  imprimir result.getIp();  result.getDegree();  result.getDegreeIn();
  int nodo = result.getIndex();
  // lista de adyacencia
  Declaras vector<ipAddress> resultAdj;
  Meter en vector las ips adyacentes
  for (int j = 0; j < adjList[nodo].getNumElements(); j++) {
      std::pair<int, int> arista = adjList[nodo].getData(j);
      resultsAdj.push_back(ips[arista.first]);
  }
  std::sort(resultAdj, resultAdj.begin(), resultAdj.end());

Imprime el vector ordenado resultAdj
  
    
*/