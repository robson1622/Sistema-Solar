#include "Lista.h"
#include "Astro.h"

//Criar Astro
Lista::Lista():primeiro(NULL), ultimo(NULL){}

Lista::~Lista()
{
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
//Adiciona Astro já em forma de elemento
//Nessa função é possível inserir o elemento em uma posição específica
void Lista::insertElement(ElementoLista* elemento)
{   
    ElementoLista* aux = this->primeiro;
    int i = 0;
    int j = elemento->getInfo()->getPosicaoEmLista();
    while (i != j && aux != NULL && aux != elemento->getAnterior() && aux != elemento->getProximo())
    {
        aux = aux->getProximo();
        i++;
    }

    if (aux == NULL)
    {
        elemento->setAnterior(this->ultimo);
        elemento->setProximo(NULL);
        this->ultimo->setProximo(elemento);
        this->ultimo = elemento;
    }
    else if (aux == this->primeiro)
    {
        elemento->setProximo(aux);
        elemento->setAnterior(NULL);
        aux->setAnterior(elemento);
        this->primeiro = elemento;
    }
    else if (aux == elemento->getAnterior())
    {
        elemento->setAnterior(aux);
        elemento->setProximo(aux->getProximo());
        aux->getProximo()->setAnterior(elemento);
        aux->setProximo(elemento);
    }
    else if (aux == elemento->getProximo())
    {
        elemento->setProximo(aux);
        elemento->setAnterior(aux->getAnterior());
        aux->getAnterior()->setProximo(elemento);
        aux->setAnterior(elemento);
    }
    else
    {
        elemento->setProximo(aux);
        elemento->setAnterior(aux->getAnterior());
        aux->getAnterior()->setProximo(elemento);
        aux->setAnterior(elemento);
    }
}

ElementoLista* Lista::retirar(ElementoLista* e)
{
    if (e == this->primeiro)
    {
        if (e == this->ultimo)
        {
            this->primeiro = NULL;
            this->ultimo = NULL;
        }
        else
        {
            e->getProximo()->setAnterior(NULL);
            setPrimeiro(e->getProximo());
        }
    }
    else if (e == this->ultimo)
    {
        e->getAnterior()->setProximo(NULL);
        setUltimo(e->getAnterior());
    }
    else
    {
        e->getAnterior()->setProximo(e->getProximo());
        e->getProximo()->setAnterior(e->getAnterior());
    }

    return e;
}

//Pegar primeiro
ElementoLista* Lista::getPrimeiro(void)
{
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

bool Lista::isEmpty()
{
    return (this->primeiro == NULL);
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

