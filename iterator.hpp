//
// Created by vladimir on 28.10.17.
//
#pragma once

#include "double_list.hpp"

template <typename DataType>
struct ListIterator{
  tNode<DataType>* current;
};

template <typename DataType>
ListIterator<DataType> initListIterator(List<DataType> lst){
  ListIterator<DataType> iterator;
  iterator.current = lst.begin;
  return iterator;
}

template<typename DataType>
bool listIterHasNext(ListIterator<DataType> & it) {
  return it.current->next != nullptr;
}

template<typename DataType>
bool listIterHasPrevious(ListIterator<DataType> & it) {
  return it.current->previous != nullptr;
}

template <typename DataType>
ListIterator<DataType> getIteratorByNumber(List<DataType> lst, int i){
  if (i<lst.size){

    ListIterator<DataType> it;
    it.current = lst.begin;

    for (int k = 0; k<i; ++k){
      it.current = it.current->next;
    }
    return it;
  }else throw "Index out of range";
}

template <typename DataType>
ListIterator<DataType> getPreviousIterator(ListIterator<DataType> it){
  if (listIterHasPrevious(it)){
    it.current = it.current->previous;
    return it;
  }else throw "Index out of range";
}

template <typename DataType>
ListIterator<DataType> getNextIterator(ListIterator<DataType> it){
  if (listIterHasNext(it)){
    it.current = it.current->next;
    return it;
  }else throw "Index out of range";
}


