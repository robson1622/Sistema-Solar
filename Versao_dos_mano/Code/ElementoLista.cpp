#include "ElementoLista.h"

ElementoLista::ElementoLista()
{
    this->info = NULL;
    this->anterior = NULL;
    this->proximo = NULL;
}
ElementoLista::~ElementoLista()
{
    delete(info);
    delete(anterior);
    delete(proximo);
}

void ElementoLista::setInfo(Astro* i)
{
    this->info = i;
}
Astro* ElementoLista::getInfo()
{
    return this->info;
}

void ElementoLista::setAnterior(ElementoLista* a)
{
    this->anterior = a;
}
ElementoLista* ElementoLista::getAnterior()
{
    return this->anterior;
}

void ElementoLista::setProximo(ElementoLista* p)
{
    this->proximo = p;
}
ElementoLista* ElementoLista::getProximo()
{
    return this->proximo;
}