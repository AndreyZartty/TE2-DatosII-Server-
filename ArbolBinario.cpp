//
// Created by andreyzartty on 21/08/19.
//

#include "ArbolBinario.h"
#include <iostream>

using namespace std;


ArbolBinario::ArbolBinario(){
    raiz = nullptr;
}
bool ArbolBinario::VacioAB(){
    return raiz== nullptr;
}
void ArbolBinario::MostrarInOrden(){
    InOrden(raiz);
}
void ArbolBinario::InOrden(NodoBinario* p){

    if (p != nullptr){
        if (p->izq){
            InOrden(p->izq);
        }
        if (p->der){
            InOrden(p->der);
        }
        cout<<p->dato << endl;
    } else {
        return;
    }
}
void ArbolBinario::MostrarPreOrden(){
    PreOrden(raiz);

}
void ArbolBinario::PreOrden(NodoBinario* p){
    if (p != nullptr){
        cout<<p->dato << endl;
        if (p->izq){
            PreOrden(p->izq);
        }
        if (p->der){
            PreOrden(p->der);
        }
    }
    else {
        return;
    }
}

void ArbolBinario::MostrarPostOrden(){
    PostOrden(raiz);
}
void ArbolBinario::PostOrden(NodoBinario* p){
    if (p != nullptr){
        if (p->izq){
            PreOrden(p->izq);
        }
        if (p->der){
            PreOrden(p->der);
        }
        cout<<p->dato << endl;
    }
    else {
        return;
    }
}
void ArbolBinario::Ingresar(int d){
    NodoBinario *temp = new NodoBinario();
    NodoBinario *PadreAB;
    temp->dato=d;
    temp->der = nullptr;
    temp->izq = nullptr;


    if (VacioAB()){
        raiz = temp;
    } else {
        NodoBinario *NoHo;
        NoHo = raiz;

        while (NoHo){
            PadreAB = NoHo;
            if (temp->dato > NoHo->dato){
                NoHo = NoHo->der;
            } else {
                NoHo = NoHo->izq;
            }
        }

        if (temp->dato < PadreAB->dato){
            PadreAB->izq = temp;
        } else {
            PadreAB->der = temp;
        }
    }
}
string ArbolBinario::EliminarHi(int d){

    bool SiEncontro = false;
    if(VacioAB())
    {
        return "El Arbol Binario está vacío ";
    }

    NodoBinario* NoHo;
    NodoBinario* PadreAB;
    NoHo = raiz;

    while(NoHo != nullptr)
    {
        if(NoHo->dato == d)
        {
            SiEncontro = true;
            break;
        }
        else
        {
            PadreAB = NoHo;
            if(d>NoHo->dato) NoHo = NoHo->der;
            else NoHo = NoHo->izq;
        }
    }
    if(!SiEncontro)
    {
        return "No se encontró el dato";
    }

// casos:
// 1. Estamos eliminando un nodo hoja
// 2. Estamos eliminando un nodo con un solo hijo
// 3. estamos eliminando un nodo con 2 hijos
// Nodo con uno de los hijos

    if((NoHo->izq == nullptr && NoHo->der != nullptr)|| (NoHo->izq != nullptr && NoHo->der == nullptr))
    {
        if(NoHo->izq == nullptr && NoHo->der != nullptr)
        {
            if(PadreAB->izq == NoHo)
            {
                PadreAB->izq = NoHo->der;
                delete NoHo;
            }
            else
            {
                PadreAB->der = NoHo->der;
                delete NoHo;
            }
        }
        else //Izquierda hijo esté presente, no hay hijo der.
        {
            if(PadreAB->izq == NoHo)
            {
                PadreAB->izq = NoHo->izq;
                delete NoHo;
            }
            else
            {
                PadreAB->der = NoHo->izq;
                delete NoHo;
            }
        }
        return "Se eliminó el dato correctamente";
    }

//Nodo u hoja
    if( NoHo->izq == nullptr && NoHo->der == nullptr)
    {
        if(PadreAB->izq == NoHo) PadreAB->izq = nullptr;
        else PadreAB->der = nullptr;
        delete NoHo;
        return "Se eliminó el dato correctamente";;
    }

//Nodo con 2 hijos
// reemplazar el nodo con menor valor en el subárbol der
    if (NoHo->izq != nullptr && NoHo->der != nullptr)
    {
        NodoBinario* chkr;
        chkr = NoHo->der;
        if((chkr->izq == nullptr) && (chkr->der == nullptr))
        {
            NoHo = chkr;
            delete chkr;
            NoHo->der = nullptr;
        }
        else // Si hijo der tiene hijos
        {
//si es hijo der del nodo tiene un hijo izquierdo
//Mover todo el camino a la izq para localizar elemento más pequeño

            if((NoHo->der)->izq != nullptr)
            {
                NodoBinario* lNoHo;
                NodoBinario* lNoHop;
                lNoHop = NoHo->der;
                lNoHo = (NoHo->der)->izq;
                while(lNoHo->izq != nullptr)
                {
                    lNoHop = lNoHo;
                    lNoHo = lNoHo->izq;
                }
                NoHo->dato = lNoHo->dato;
                delete lNoHo;
                lNoHop->izq = nullptr;
            }
            else
            {
                NodoBinario* Temporal;
                Temporal = NoHo->der;
                NoHo->dato = Temporal->dato;
                NoHo->der =Temporal->der;
                delete Temporal;
            }

        }
        return "Se eliminó el dato correctamente";;
    }

}