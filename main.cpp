#include <iostream>
#include "List.h"
#include "Node.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    List* prueba = new List();
    prueba->insertFirst(3);
    prueba->insertFirst(2);
    prueba->insertFirst(1);
    prueba->modifyNode(2,10);
    prueba->getList();
    cout << prueba->getNode(1) << endl;
    cout << "---------------" << endl;
    prueba->deleteFirst();
    prueba->getList();

    return 0;
}