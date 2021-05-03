#include "Astro.h"
#pragma once

//Classe a qual se relaciona à um elemento Astro e sabe quais elementos se encontram antes e após sí.
class ElementoLista
{
private:
    Astro* info;

    ElementoLista* anterior;
    ElementoLista* proximo;

public:
    ElementoLista();
    ~ElementoLista();

    //todo elemento se relaciona a um Astro, essas funções fazem essa relação
    void setInfo(Astro* i);
    Astro* getInfo();

    void setAnterior(ElementoLista* a);
    ElementoLista* getAnterior();

    void setProximo(ElementoLista* p);
    ElementoLista* getProximo();
};