#ifndef __GRAPH_H_
#define __GRAPH_H_

  #include <iostream>
  #include <fstream>
  #include <vector>
  #include <string>
  #include <map>
  #include <queue>

  #include "LinkedList.h"
  #include "ipAddress.h"
  
  # define INF 0x3f3f3f3f
  
  class Graph {
    private:
      int numNodes;
      int numEdges;
      // Lista de adyacencia (vector de listas)
      //Pares de nodo,peso.
      std::vector<LinkedList<std::pair<int,int>>> adjList;
      // mapea IPs a un numero entero de orden
      std::map<unsigned int, ipAddress> mapIP;  // llave es ipValue y el dato es un objeto IP
      // vector de objetos ipAddress para contar los grados
      std::vector<ipAddress> ips;
      // MaxHeap de pares (grado, ipString) 
      std::priority_queue<std::pair<int,std::string>> maxHeapIPs;
      // Boot Master
      std::string bootMaster;
      int nodoBootMaster;
      
  
      void split(std::string line, std::vector<int> & res);
    
    public:
      Graph();
      ~Graph();
      void loadDirectedGraph(std::string fileName);
      void printGraph();
      void saveGrados();
      void maxGrados();
      void shortestPath();
            
  };
  
  

#endif
