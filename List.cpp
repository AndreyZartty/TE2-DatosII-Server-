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

void List::insertFirst(int _data){

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


void List::modifyNode(int pos,int _data){
    if (pos >= getLen()){
        cout << "La posición no existe" << endl;
    }
    else{
        Node* temp = head;
        if (pos == 0){
            temp->setNext(head->getNext());
            temp->setData(_data);
            setHead(temp);
        }
        else {
            int c = 1;
            while (c < pos) {
                temp = temp->getNext();
                c++;
            }
            temp->getNext()->setData(_data);
        }
    }

}

void List::deleteFirst(){
    if (head != nullptr) {
        setHead(head->getNext());
        len-=1;
    } else {
        cout << "La lista esta vacia" << endl;
        return;
    }
}



int List::getNode(int _index){
    Node* temp = nullptr;
    if (_index < len) {
        int i = 0;
        temp = head;
        while (i != _index) {
            temp = temp->getNext();
            i++;
        }
        return temp->getData();
    }
    else{
        cout << "Indice fuera del alcance" << endl;
    }
}

void List::getList() {
    Node* temp = head;
    if (temp != nullptr) {
        while (temp != nullptr) {
            cout << temp->getData() << endl;
            temp = temp->getNext();
        }
        return;
    }
    cout << "La lista esta vacia" << endl;
    return;
}
