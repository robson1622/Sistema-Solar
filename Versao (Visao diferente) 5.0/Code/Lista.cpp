#include "Lista.hpp"
#include "Astro.hpp"

//Criar Astro
Lista::Lista():p(NULL),next(NULL){}

Lista::~Lista(){}

void Lista::start(void){
    p = NULL;
    next = NULL;
}
//Adicionar Astro
void Lista::insert(Astro* elemento){
    if(p == NULL){
        p = elemento;
    }
    else{
        Lista *nova = new Lista();
        nova->p = elemento;
        nova->next = next;
        next = nova;
    }
}

//Pegar proximo
Lista* Lista::getProximo(void){
    return next;
}

//Pegar Elemento
Astro* Lista::getAstro(void){
    return p;
}

void Lista::destroy(void){
    if(next != NULL){
        next->destroy();
        delete(next);
    }
}

