//
// Created by andreyzartty on 21/08/19.
//

#ifndef TE2_DATOSII_SERVER__ARBOLBINARIO_H
#define TE2_DATOSII_SERVER__ARBOLBINARIO_H

#include <iostream>

using namespace std;

class NodoBinario {
public:
    NodoBinario *izq;
    NodoBinario *der;
    int dato;
};

class ArbolBinario {
public:
    ArbolBinario();
    bool VacioAB();
    void MostrarInOrden();
    void InOrden(NodoBinario* p);
    void MostrarPreOrden();
    void PreOrden(NodoBinario* p);
    void MostrarPostOrden();
    void PostOrden(NodoBinario* p);
    void Ingresar(int d);
    string EliminarHi(int d);

private:
    NodoBinario *raiz;
};



#endif //TE2_DATOSII_SERVER__ARBOLBINARIO_H
