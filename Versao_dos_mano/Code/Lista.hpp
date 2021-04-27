#include "ElementoLista.hpp"
#pragma once


//Classe que cuida da lista, guardando a informação do primeiro e último elemento da lista
class Lista{
    private:
        ElementoLista *primeiro;
        ElementoLista *ultimo;
    public:
        //Criar Astro
        Lista();
        ~Lista();
        void start(void);

        //Adicionar Astro
        void insert(Astro* elemento);
        //retira um elemento específico
        ElementoLista* retirar(ElementoLista* e);

        //Pegar primeiro
        ElementoLista* getPrimeiro(void);
        void setPrimeiro(ElementoLista* aux);
        //Pegar ultimo
        ElementoLista* getUltimo();
        void setUltimo(ElementoLista* aux);

        //Apaga listas e astros
        void destroy(void);
};

