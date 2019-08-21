//
// Created by andreyzartty on 13/08/19.
//

#ifndef TE2_DATOSII_SERVER__LIST_H
#define TE2_DATOSII_SERVER__LIST_H

#include "Node.h"

class List {

private:
    Node* head;
    int len;

public:
    List();
    Node* getHead();
    void setHead(Node* _head);
    int getLen();
    void setLen(int _len);
    void insertFirst(int _data);
    void modifyNode(int pos, int _data);
    void deleteFirst();
    int getNode(int _index);
    void getList();

};


#endif //TE2_DATOSII_SERVER__LIST_H
