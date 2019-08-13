#include <iostream>
#include <stdlib.h>

#include "Node.h"

using namespace std;

Node::Node(string* _data){
    data = _data;
    next = nullptr;
}

string* Node::getData(){
    return data;
}

void Node::setData(string* _data) {
    data = _data;
}

Node* Node::getNext(){
    return next;
}


void Node::setNext(Node* _next){
    next = _next;
}
