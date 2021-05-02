#include "ElementoLista.h"

#pragma once

class Pilha
{
private:
    ElementoLista* info;
    Pilha* proximo;

public:
    Pilha(Pilha* p = NULL, ElementoLista* e = NULL);
    ~Pilha();

    Pilha* getProximo();

    ElementoLista* getInfo();

    Pilha* criar_pilha();
    Pilha* insert(Pilha* p, ElementoLista* e);
    Pilha* pop(Pilha* p);
    ElementoLista* top(Pilha* p);
    void liberarPilha(Pilha* p);

    bool isEmpty(Pilha* p);
};