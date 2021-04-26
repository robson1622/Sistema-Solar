#include "Lista.hpp"
#include "Astro.hpp"

//Criar Astro
Lista::Lista():primeiro(NULL), ultimo(NULL){}

Lista::~Lista()
{
    delete(primeiro);
    delete(ultimo);
}

void Lista::start(void){
    primeiro = NULL;
    ultimo = NULL;
}
//Adicionar Astro
void Lista::insert(Astro* elemento){
    ElementoLista* novo = new ElementoLista();
    novo->setInfo(elemento);
    /*if(p == NULL){
        p = elemento;
    }
    else{
        Lista *nova = new Lista();
        nova->p = elemento;
        nova->primeiro = primeiro;
        primeiro = nova;
    }*/

    if (this->primeiro == NULL)
    {
        this->primeiro = novo;
        this->ultimo = novo;
    }
    else
    {
        this->ultimo->setProximo(novo);
        novo->setAnterior(this->ultimo);
        this->ultimo = novo;
    }
}

//Pegar primeiro
ElementoLista* Lista::getPrimeiro(void){
    return primeiro;
}
void Lista::setPrimeiro(ElementoLista* aux)
{
    this->primeiro = aux;
}

//Pegar ultimo
ElementoLista* Lista::getUltimo()
{
    return this->ultimo;
}
void Lista::setUltimo(ElementoLista* aux)
{
    this->ultimo = aux;
}

void Lista::destroy(void){
    ElementoLista* p = this->primeiro;
    ElementoLista* paux = NULL;
    if(primeiro != NULL){
       while (p != NULL)
       {
           delete(p->getInfo());
           p = p->getProximo();
       }
    }

    delete(primeiro);
    delete(ultimo);
}

