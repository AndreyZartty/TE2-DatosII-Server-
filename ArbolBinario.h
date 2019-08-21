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
    void InOrden(NodoBinario*);
    void MostrarPreOrden();
    void PreOrden(NodoBinario*);
    void MostrarPostOrden();
    void PostOrden(NodoBinario*);
    void Ingresar(int);
    string EliminarHi(int);

private:
    NodoBinario *raiz;
};



#endif //TE2_DATOSII_SERVER__ARBOLBINARIO_H
