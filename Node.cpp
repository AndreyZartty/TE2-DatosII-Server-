#include <iostream>
#include <stdlib.h>

#include "Node.h"

using namespace std;

Node::Node(int _data){
    data = _data;
    next = nullptr;
}

int Node::getData(){
    return data;
}

void Node::setData(int _data) {
    data = _data;
}

Node* Node::getNext(){
    return next;
}


void Node::setNext(Node* _next){
    next = _next;
}
