#ifndef __MAXHEAP_H_
#define __MAXHEAP_H_

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include "Registro.h"

template<class T>
  class MaxHeap {
    private:
      // contiene los elementos del heap
      std::vector<T> data; 
      // capacidad maxima del heap
      int maxSize;
      // tamaño actual del heap   
      int size;   
      int parent(int i);
      int left(int i);
      int right(int i);

    public:
      MaxHeap(int capacity);
      ~MaxHeap();
      bool isEmpty();
      int getCapacity();
      void printMaxHeap();
      void push(T key);
      T top();
      T pop();
      int getSize();


  };

  template <class T> 
  MaxHeap<T>::MaxHeap(int capacity) {
    std::cout << "--->Creando un MaxHeap: " <<  this << std::endl;
    size = 0;
    maxSize = capacity;
    data.resize(maxSize);
  }


  template <class T> 
  MaxHeap<T>::~MaxHeap() {
      std::cout << "--->Liberando memoria del MaxHeap: " <<  this << std::endl;
      data.clear();
  }
  
  template <class T> 
  bool MaxHeap<T>::isEmpty() {
    return (size <= 0);
  }

  template <class T> 
  int MaxHeap<T>::getCapacity() {
    return maxSize;
  }

  template <class T> 
  void MaxHeap<T>::printMaxHeap() {
    for (int i=0; i < size; i++)
      std::cout << data[i] <<std::endl;
    std::cout << std::endl;
  }


  template <class T> 
  int MaxHeap<T>::parent(int i) {
    return (i-1)/2; 
  }
  
  template <class T> 
  int MaxHeap<T>::left(int i) {
    return (2*i + 1); 
  }

  template <class T> 
  int MaxHeap<T>::right(int i) {
    return (2*i + 2);
  }

  template <class T> 
  void MaxHeap<T>::push(T key) {
    if (size == maxSize) {
      throw std::out_of_range("Overflow: no se puede insertar la llave");
    }
    // Insertamos la nueva llave al final del vector
    int i = size;
    data[i] = key;
    size++;
    // Reparar las propiedades del max heap si son violadas
    while (i != 0 && data[parent(i)] < data[i]) {
       std::swap(data[i], data[parent(i)]);
       i = parent(i);
    }
  }
template <class T> T MaxHeap<T>::pop() {
  if (size <= 0) {
    throw std::out_of_range("Fuera de rango");
  }
  int index = 0;
  T pop = data[0];
  data[0] = data[size - 1];
  size -= 1;
  while ((2 * index + 1) < size) {
    int hoja;
    if ((2 * index + 2) == size) {
      hoja = 2 * index + 1;
    } else {
      if (data[2 * index + 1] > data[2 * index + 2]) {
        hoja = 2 * index + 1;
      } else {
        hoja = 2 * index + 2;
      }
    }
    if (data[index] < data[hoja]) {
      T temp = data[index];
      data[index] = data[hoja];
      data[hoja] = temp;

      index = hoja;
    } else {
      break;
    }
  }
  //std::cout << "pop: " << pop << std::endl;
  return pop;
}

template <class T> T MaxHeap<T>::top() {
  if (size < 0) {
    throw std::out_of_range("Fuera de rango");
  }
  int index = 0;
  int top = data[0];
  int hoja;
  while (2 * index + 2 < size) {
    if ((2 * index + 2) == size) {
      hoja = 2 * index + 1;
    } else {
      if (data[2 * index + 1] > data[2 * index + 2]) {
        hoja = 2 * index + 1;
      } else {
        hoja = 2 * index + 2;
      }
    }
    if (data[index] < data[hoja]) {
      int temp = data[index];
      data[index] = data[hoja];
      data[hoja] = temp;

      index = hoja;
    } else {
      break;
    }
  }
  return top;
}

#endif // __MAXHEAP_H_