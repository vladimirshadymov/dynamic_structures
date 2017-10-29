//
// Created by vladimir on 24.10.17.
//

#pragma once

//#include "iterator.hpp"

#include <ostream>

template<typename DataType>
struct tNode {
  DataType data;
  tNode* next;
  tNode* previous;
};


template<typename DataType>
struct List {
  tNode<DataType> *begin;
  tNode<DataType> *end;
  int size;
};

template <typename DataType>
struct ListIterator{
  tNode<DataType>* current;
};

template <typename DataType>
ListIterator<DataType> initListIterator(List<DataType> &lst){
  ListIterator<DataType> iterator;
  iterator.current = lst.begin;
  return iterator;
}

template <typename DataType>
bool iterIsEmpty(ListIterator<DataType> it){
  return (it.current== nullptr);
}

template <typename DataType>
void swapNumbers(DataType &a, DataType &b){
  DataType k;
  k = a;
  a = b;
  b = k;
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
ListIterator<DataType> getIteratorByNumber(List<DataType> &lst, int i){
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

template<typename DataType>
void initList(List<DataType> &lst)
{
  lst.begin = nullptr;
  lst.end = nullptr;
  lst.size = 0;
}

template<typename DataType>
void pushFront(List<DataType> & lst, DataType data)
{
  tNode<DataType> *p = new tNode<DataType>;
  p->data = data;
  ListIterator<DataType> old_it;
  ListIterator<DataType> new_it;
  if (lst.begin != nullptr){

    old_it.current = lst.begin;
    new_it.current = p;

    old_it.current->previous = new_it.current;
    new_it.current->next = old_it.current;
    new_it.current->previous = nullptr;
    lst.begin = new_it.current;

  }else{
    lst.begin = p;
    lst.end = p;
    p->previous = nullptr;
    p->next = nullptr;
  }
  lst.size += 1;
}

template<typename DataType>
void pushBack(List<DataType> & lst, DataType data)
{
  tNode<DataType> *p = new tNode<DataType>;
  p->data = data;
  ListIterator<DataType> old_it;
  ListIterator<DataType> new_it;
  if (lst.end!= nullptr){

    old_it.current = lst.end;
    new_it.current = p;

    old_it.current->next = new_it.current;
    new_it.current->previous = old_it.current;
    new_it.current->next = nullptr;
    lst.end = new_it.current;

  }else{
    lst.begin = p;
    lst.end = p;
    p->previous = nullptr;
    p->next = nullptr;
  }
  lst.size += 1;
}

template<typename DataType>
void printList(const List<DataType> &lst, std::ostream &out)
{
  tNode<DataType> *p = lst.begin;
  for(; p; p = p->next)
  {
    out << p->data << '\t';
  }
  out << '\n';
}

template<typename DataType>
void destroyList(List<DataType> &lst)
{
  tNode<DataType> *p = lst.begin;
  tNode<DataType> *prev;
  while (p) {
    prev = p;
    p = p->next;
    p->previous = nullptr;
    delete prev;
  }
  lst.size = 0;
  lst.begin = nullptr;
  lst.end = nullptr;
}

template <typename DataType>
void insertInList(List<DataType> &lst, int position, DataType data){
  if (position<lst.size){
    if (position==0){
      pushFront(lst,data);
    } else if (position==lst.size-1){
      pushBack(lst,data);
    } else {

      ListIterator<DataType> left;
      ListIterator<DataType> right;
      left = getIteratorByNumber(lst, position-1);
      right = getIteratorByNumber(lst, position);

      tNode<DataType> *p = new tNode<DataType>;
      p->data = data;

      left.current->next = p;
      p->previous = left.current;

      right.current->previous = p;
      p->next = right.current;

      lst.size +=1;
    }
  } else throw "Index out of range";
}


template <typename DataType>
void popFront(List<DataType> &lst){
  if (lst.size==1) {
    tNode<DataType>* p = lst.begin;
    lst.begin = nullptr;
    lst.end = nullptr;
    delete(p);
    lst.size -=1;
  } else if (lst.begin!= nullptr){
    tNode<DataType>* p = lst.begin;
    lst.begin = p->next;
    delete(p);
    lst.begin->previous = nullptr;
    lst.size -= 1;
  }else throw "Imaginary POP";
}

template <typename DataType>
void popBack(List<DataType> &lst){
  if (lst.size==1) {
    tNode<DataType>* p = lst.begin;
    lst.begin = nullptr;
    lst.end = nullptr;
    delete(p);
    lst.size -= 1;
  } else if (lst.end!= nullptr){
    tNode<DataType>* p = lst.end;
    lst.end = p->previous;
    delete(p);
    lst.end->next = nullptr;
    lst.size -= 1;
  }else throw "Imaginary POP";
}

template <typename DataType>
void popByIndex(List<DataType> &lst, int position){
  if (position<lst.size){
    if (position==0) popFront(lst);
    else if (position==lst.size-1) popBack(lst);
    else {
      ListIterator<DataType> left;
      ListIterator<DataType> right;
      ListIterator<DataType> for_remove;
      left = getIteratorByNumber(lst, position-1);
      right = getIteratorByNumber(lst, position+1);
      for_remove = getIteratorByNumber(lst, position);

      tNode<DataType>* p;
      p = for_remove.current;

      left.current->next = right.current;
      right.current->previous = left.current;
      for_remove.current = nullptr;
      delete(p);

      lst.size -= 1;
    }
  } else throw "Index out of range";
}

template <typename DataType>
void swapElemByIter(ListIterator<DataType> &it1, ListIterator<DataType> &it2){

  ListIterator<DataType> it1_prev, it1_next, it2_prev, it2_next;

  it1_prev.current = nullptr;
  it1_next.current = nullptr;
  it2_prev.current = nullptr;
  it2_next.current = nullptr;

  if (listIterHasNext(it1)) it1_next = getNextIterator(it1);
  if (listIterHasPrevious(it1)) it1_prev = getPreviousIterator(it1);
  if (listIterHasNext(it2)) it2_next = getNextIterator(it2);
  if (listIterHasPrevious(it2)) it2_prev = getPreviousIterator(it2);

  if (it2.current==it1_next.current) {
    tNode<DataType>* next_elem1, *prev_elem1, *next_elem2, *prev_elem2;
    next_elem1 = it1.current->next;
    prev_elem1 = it1.current->previous;
    next_elem2 = it2.current->next;
    prev_elem2 = it2.current->previous;

    it1.current->next = next_elem2;
    it2.current->next = it1.current;


    it1.current->previous = it2.current;
    it2.current->previous = prev_elem1;

    if (not iterIsEmpty(it1_prev)){
      it1_prev.current->next = it2.current;
    }
    if (not iterIsEmpty(it2_next)){
      it2_next.current->previous = it1.current;
    }

  } else if (it2.current!=it1.current){
    tNode<DataType>* next_elem, *prev_elem;
    next_elem = it1.current->next;
    prev_elem = it1.current->previous;

    it1.current->next = it2.current->next;
    it2.current->next = next_elem;


    it1.current->previous = it2.current->previous;
    it2.current->previous = prev_elem;

    if (not iterIsEmpty(it1_prev)){
      it1_prev.current->next = it2.current;
    }
    if (not iterIsEmpty(it2_next)){
      it2_next.current->previous = it1.current;
    }
    it1_next.current->previous = it2.current;
    it2_prev.current->next = it1.current;
  }
}


template <typename DataType>
void swapElem(List<DataType> &lst, int i, int j){
  ListIterator<DataType> iter_i;
  ListIterator<DataType> iter_j;

  if (i>j) swapNumbers(i,j);

  iter_i = getIteratorByNumber(lst, i);
  iter_j = getIteratorByNumber(lst, j);

  swapElemByIter(iter_i,iter_j);

}