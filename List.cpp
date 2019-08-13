#include <iostream>
#include <stdlib.h>

#include "List.h"

using namespace std;

List::List() {
    head = nullptr;
    len = 0;
}


Node* List::getHead() {
    return head;
}


void List::setHead(Node* _head) {
    head = _head;
}


int List::getLen() {
    return len;
}


void List::setLen(int _len) {
    len = _len;
}

void List::insertLast(string* _data){

    Node* nNode = new Node(_data);


    if (head == nullptr) {
        head = nNode;
    } else {
        Node* temp = head;
        head = nNode;
        nNode->setNext(temp);
    }

    len+=1;

}


void List::deleteNode(string* _data){
    Node* delNode = nullptr;
    Node* temp = head;
    Node* aux = head;
    while (aux != nullptr && aux->getData() != _data) { //CAMBIAR POR .COMPARE
        temp = aux;
        aux = aux->getNext();
    }
    if (aux == nullptr) {
        cout << _data << " no esta en la lista\n" << endl;
    } else {
        delNode = aux;
        if (head == delNode) {
            setHead(head->getNext());
        } else {
            temp->setNext(aux->getNext());
        }
    }
    delNode->setNext(nullptr);

    len-=1;

}



Node* List::getNode(int _index){
    Node* temp = nullptr;
    if (_index <= len) {
        int i = 1;
        temp = head;
        while (i != _index) {
            temp = temp->getNext();
            i++;
        }
    }
    return temp;
}