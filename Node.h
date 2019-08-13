//
// Created by andreyzartty on 13/08/19.
//
#include <iostream>
#include <string>


#ifndef TE2_DATOSII_SERVER__NODE_H
#define TE2_DATOSII_SERVER__NODE_H

using namespace std;

class Node {

private:
    ///Dato que guardara el nodo
    string* data;
    ///Referencia al nodo que esta siguiente a este
    Node* next;

public:
    Node(string* _ficha);
    string* getData();
    void setData(string* _data);
    Node* getNext();
    void setNext(Node* _next);

};


#endif //TE2_DATOSII_SERVER__NODE_H
