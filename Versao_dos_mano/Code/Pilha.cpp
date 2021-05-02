#include "Pilha.h"

Pilha::Pilha(Pilha* p, ElementoLista* e)
{
    this->proximo = p;
    this->info = e;
}
Pilha::~Pilha()
{
    this->proximo = NULL;
    this->info = NULL;
}

Pilha* Pilha::getProximo()
{
    return this->proximo;
}

ElementoLista* Pilha::getInfo()
{
    return this->info;
}

Pilha* Pilha::criar_pilha()
{
    return NULL;
}
Pilha* Pilha::insert(Pilha* p, ElementoLista* e)
{
    Pilha* novo = new Pilha(p, e);

    return novo;
}
Pilha* Pilha::pop(Pilha* p)
{
    p = p->getProximo();

    return p;
}
ElementoLista* Pilha::top(Pilha* p)
{
    return p->getInfo();
}
void Pilha::liberarPilha(Pilha* p)
{
    while(p != NULL)
    {
        Pilha* aux = p;
        p = p->getProximo();
        free(aux);
    }
}

bool Pilha::isEmpty(Pilha* p)
{
    return(p == NULL);
}