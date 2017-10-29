#include <iostream>
#include "double_list.hpp"

int main() {

  int lenght;
  std::cin >> lenght;

  List<int> lst;

  initList(lst);
  int number;

  for (int i = 0; i < lenght; ++i) {
    std::cin >> number;
    pushBack(lst, number);
  }

  printList(lst, std::cout);

  insertInList(lst, 2, 1000);

  printList(lst, std::cout);

  popByIndex(lst,2);

  printList(lst, std::cout);

  ListIterator<int> g =  getIteratorByNumber(lst,3);

  std::cout << g.current->data << "\n";

  g.current->data = 5;

  std::cout << g.current->data << "\n";

  printList(lst, std::cout);


  swapElem(lst, 1, 2);
  printList(lst, std::cout);

  return 0;
}