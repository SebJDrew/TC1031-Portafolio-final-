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
  maxHeapIPs = std::priority_queue<std::pair<int,std::string>> ();
}

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

void Graph::saveGrados() {
  std::ofstream grados_ips;
  grados_ips.open("grados_ips.txt");
  if (!grados_ips.good()) {
    grados_ips.close();
    throw std::invalid_argument("File not found");
  } else {
    for (int i = 1; i < ips.size(); i++) {
      grados_ips << ips[i].getIp() << "," << ips[i].getDegree() << std::endl;
      maxHeapIPs.push(std::make_pair(ips[i].getDegree(), ips[i].getIp()));
    }
    grados_ips.close();
  }
}

void Graph::maxGrados() {
  std::ofstream mayores_grados_ips;
  mayores_grados_ips.open("mayores_grados_ips.txt");
  if (!mayores_grados_ips.good()) {
    mayores_grados_ips.close();
    throw std::invalid_argument("File not found");
  } else {
    std::cout << "Los 5 ip con mayor grado de salida: " << std::endl;
    for (int i = 1; i <= 5; i++) {
      std::pair<int, std::string> p = maxHeapIPs.top();
      maxHeapIPs.pop();
      if (i == 1) {
        bootMaster = p.second;
        ipAddress tmpBoot(bootMaster, "", 0);
        std::map<unsigned int, ipAddress>::iterator it;
        it = mapIP.find(tmpBoot.getIpValue());
        if (it != mapIP.end())
          nodoBootMaster = it->second.getIpIndex();
      }
      std::cout << p.second << " --> " << p.first << std::endl;
      mayores_grados_ips << p.second << " --> " << p.first << std::endl;
    }
    mayores_grados_ips.close();
    std::cout << std::endl;
    std::cout << "Bootmaster: " << bootMaster << std::endl;
    std::cout << "nodoBootmaster: " << nodoBootMaster << std::endl;
  }
}

void Graph::shortestPath() {
  int src = nodoBootMaster;
  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                      std::greater<std::pair<int, int>>>
      pq;
  std::vector<int> dist(numNodes + 1, INF);
  pq.push(std::make_pair(0, src)); // pares de distancia, nodo
  dist[src] = 0;

  while (!pq.empty()) {
    int u = pq.top().second;
    pq.pop();
    // vertices vecinos de u
    for (int j = 0; j < adjList[u].getNumElements(); j++) {
      std::pair<int, int> arista = adjList[u].getData(j); // par de nodo, peso
      // Get vertex label and weight of current adjacent of u.
      int v = arista.first;
      int weight = arista.second;
      //  If there is shorted path to v through u.
      if (dist[v] > dist[u] + weight) {
        // Updating distance of v
        dist[v] = dist[u] + weight;
        pq.push(std::make_pair(dist[v], v));
      }
    }
  }
  std::ofstream distancia_bootmaster;
  distancia_bootmaster.open("distancia_bootmaster.txt");
  if (!distancia_bootmaster.good()) {
    distancia_bootmaster.close();
    throw std::invalid_argument("File not found");
  } else {
    // Print shortest distances stored in dist[]
    distancia_bootmaster << "Vertex \t\tDistance from Source" << std::endl;
    int maxDist = 0;
    int maxIndex = 0;
    for (int i = 1; i <= numNodes; ++i) {
      distancia_bootmaster << i << "\t" << ips[i].getIp() << "\t" << dist[i]
                           << std::endl;
      if (dist[i] > maxDist) {
        maxDist = dist[i];
        maxIndex = i;
      }
    }
    distancia_bootmaster.close();
    std::cout << "Ip que mas refuerzo se requiere para atacar: "
              << ips[maxIndex].getIp() << " y esta a una distancia " << maxDist
              << std::endl;
  }
}

/*
    ipAddress tmpIP1("140.239.219.5", "", 0);
    std::map<unsigned int, ipAddress>::iterator it;
    int ip1Index, ip2Index;
    it = mapIP.find(tmpIP1.getIpValue());
    if(it != mapIP.end())
      ip1Index = it->second.getIpIndex();
    std::cout << "Ip 140.239.219.5 su index es: " << ip1Index << std::endl;
    std::cout << "Ip string: " << ips[ip1Index].getIp() << std::endl;
*/