#include "Fisica.h"
#include <iostream>
using std::cout;
using std::endl;

Fisica::Fisica():clock(), elapsed()
{
}
Fisica::~Fisica()
{
}
//Calcular Forca Resultante
Vetor Fisica::forcaResultante(Lista *inicio,ElementoLista *atual){
    //F = G M m / r²
    long double G = 6.67e-11;
    ElementoLista *cont = inicio->getPrimeiro(); 
    Astro *aux;
    Astro *elemento = atual->getInfo();
    Vetor forca;
    forca.x = forca.y = 0;
    long double hipotenusa,sen,cos,fmodulo;

    while(cont != NULL){
        aux = cont->getInfo();

        if(elemento != aux){
            hipotenusa = distanciaEuclidiana(elemento->getPosicao(),aux->getPosicao());
            cos = (elemento->getPosicao().x - aux->getPosicao().x)/hipotenusa;
            sen = (elemento->getPosicao().y - aux->getPosicao().y)/hipotenusa;
            fmodulo = -(G * aux->getMassa() * elemento->getMassa()) / pow(hipotenusa,2);
            forca.x += (fmodulo * cos);
            forca.y += (fmodulo * sen);
        }
        cont = cont->getProximo();
    }
    return forca;
}

//Distancia entre dois astros
long double Fisica::distanciaEuclidiana(Vetor v1, Vetor v2){
    return (sqrt(pow(v1.x - v2.x,2) + pow(v1.y - v2.y,2)));
} 

//Velocidade Inicial
void Fisica::velocidadeInicial(Lista *l){

    //mv²/r = Fg ----->   v = sqrt(rF/m)
    //mv²/r = ma  --------> v = sqrt(ra)
    /* IMPORTANTE : A velocidade tangencial tangencia a tragetória, logo ela esta no sentido da posicao + 90 graus
                                       ^ sentido da velocidade
                                       |
                                       |
                                       |
    (CG)----------------------------(astro)-------> sentido da posicao
    */

    long double senA,cosA,senTeta,cosTeta;
    long double VelocidadeModulo,distancia;
    int cos90,sen90;
    ElementoLista *cont = l->getPrimeiro(); 
    Astro *aux;
    Vetor posicaoRelativa;
    Vetor velocidade;

    cos90 = 0;
    sen90 = 1;
    
    while( cont != NULL){
        aux = cont->getInfo();

        posicaoRelativa.x = aux->getPosicao().x - aux->getCentro_de_Gravidade()->x;
        posicaoRelativa.y = aux->getPosicao().y - aux->getCentro_de_Gravidade()->y;

        distancia = sqrt(pow(posicaoRelativa.x,2) + pow(posicaoRelativa.y,2));
        VelocidadeModulo = sqrt(distancia * sqrt(pow(aux->getAceleracao().x,2) + pow(aux->getAceleracao().y,2)));

        cosA = posicaoRelativa.x/distancia;
        senA = posicaoRelativa.y/distancia;

        cosTeta = (cosA*cos90) - (senA*sen90);
        //Minha terra tem palmeiras onde canta o sabiá...
        senTeta = (senA*cos90) + (sen90*cosA);
        
        velocidade.x = VelocidadeModulo * cosTeta;
        velocidade.y = VelocidadeModulo * senTeta;
        
        aux->setDistanciaDoSol(distancia);
        aux->setVelocidade(velocidade);
        aux->setVelocidadeLinear(sqrt(aux->getDistanciaDoSol() * sqrt(pow(aux->getPosicao().x,2) + pow(aux->getPosicao().y,2))));
        aux->setVelocidadeAngular(sqrt(pow(aux->getPosicao().x,2) + pow(aux->getPosicao().y,2))/aux->getDistanciaDoSol());
        cont = cont->getProximo();
    }
}

//Atualiza Posicao
void Fisica::atualizaPosicao(Lista *l, float* vector){
    ElementoLista *cont = l->getPrimeiro() ;
    Astro *aux = cont->getInfo();
    this->elapsed = clock.getElapsedTime();
    Vetor temp;
    while( cont != NULL){
        aux = cont->getInfo();
        
        temp.x = aux->getPosicao().x + aux->getVelocidade().x;
        temp.y = aux->getPosicao().y + aux->getVelocidade().y;
        aux->setPosicao(temp);

        //atualiza as velocidades após 10 segundos do sistema rodando
        cont = cont->getProximo();
    }
    if (elapsed.asSeconds()>=2)
    {
        ElementoLista* aux = l->getPrimeiro();
        Astro* aux2 = aux->getInfo();
        int i = 0;
        while (aux != NULL)
        {
            aux2 = aux->getInfo();
            aux2->setVelocidadeLinear(sqrt(aux2->getDistanciaDoSol() * sqrt(pow(aux2->getPosicao().x,2) + pow(aux2->getPosicao().y,2))));
            aux2->setVelocidadeAngular(sqrt(pow(aux2->getPosicao().x,2) + pow(aux2->getPosicao().y,2))/aux2->getDistanciaDoSol());
            vector[i] = aux2->getVelocidadeAngularFloat();
            aux = aux->getProximo();
            i++;
        }
        clock.restart();
    }
}

//Atualiza Velocidade
void Fisica::atualizaVelocidade(Lista *l){
    ElementoLista *cont = l->getPrimeiro();
    Astro *aux;
    Vetor temp;

    while( cont != NULL){
        aux = cont->getInfo();
        
        temp.x = aux->getVelocidade().x + aux->getAceleracao().x;
        temp.y = aux->getVelocidade().y + aux->getAceleracao().y;
        aux->setVelocidade(temp);
        cont = cont->getProximo();
    }
}

//Atualiza Aceleracao
void Fisica::atualizaAceleracao(Lista *l){
    // Fg = ma -------->   a = Fg/m
    ElementoLista *cont = l->getPrimeiro();
    Astro *aux;
    Vetor forca;
    Vetor aceleracao;

    while(cont != NULL){
        aux = cont->getInfo();
        
        forca = forcaResultante(l,cont);
        aceleracao.x = (forca.x/aux->getMassa()) * FATORACELERACAO;
        aceleracao.y = (forca.y/aux->getMassa()) * FATORACELERACAO;
        aux->setAceleracao(aceleracao);
        
        cont = cont->getProximo();
    }
}

//Painel de informacoes dos astros
void Fisica::inforAstros(Lista *l){
    ElementoLista *cont = l->getPrimeiro();
    Astro *aux;
    //system("clear");
    sf::Vector2f temp;
    while(cont != NULL){
        aux = cont->getInfo();

        temp.x = (float) aux->getPosicao().x;
        temp.y = (float) aux->getPosicao().y;
        cout<<aux->getNome()<<endl;
        cout<<" : Posicao ( "<<temp.x<<" , "<<temp.y<<" )"<<endl;
        temp.x = (float) aux->getVelocidade().x;
        temp.y = (float) aux->getVelocidade().y;
        cout<<" : Velocidade ( "<<temp.x<<" , "<<temp.y<<" )"<<endl;
        temp.x = (float) aux->getAceleracao().x;
        temp.y = (float) aux->getAceleracao().y;
        cout<<" : Aceleracao ( "<<temp.x<<" , "<<temp.y<<" )"<<endl;
        cont = cont->getProximo();
    }
    cout<<"Posicao do CG : ("<<aux->getCentro_de_Gravidade()->x<<" , "<<aux->getCentro_de_Gravidade()->y<<") "<<endl;
}

//POsicao do centro de gravidade
/* P(cm = cg) = 1/MassaTotal * (Xi * Mi)*/
void Fisica::setPosicaoCentroGravidade(Lista *l){
    long double MassaTotal = 0;
    Vetor somatorio;
    ElementoLista *cont = l->getPrimeiro();
    Astro *aux;
    Vetor *cg = new Vetor();
    somatorio.x = somatorio.y = 0;
    
    while(cont != NULL){
        aux = cont->getInfo();

        MassaTotal += aux->getMassa();
        somatorio.x += (aux->getPosicao().x * aux->getMassa());
        somatorio.y += (aux->getPosicao().y * aux->getMassa());
        cont = cont->getProximo();
    }

    cg->x = somatorio.x/MassaTotal;
    cg->y = somatorio.y/MassaTotal;
    cont = l->getPrimeiro();

    while (cont != NULL){
        aux = cont->getInfo();
        
        aux->setCentro_de_Gravidade(cg);
        cont = cont->getProximo();
    }
    
}
/*
//Lei de kepler 03 que da uma proporção que é constante a qualquer astro
double Fisica::kepler03(Astro *elemento){
    /*
    T²/R³ = CTE ------> (4*PI²)/(v²*R) = CTE
    T = 2PI/tempo de uma volta
    w(omega) = 2PI/T
    v = w(omega)r

    Removí, mas a ideia seria que o raio é o raio maior + menor divido por 2, raio médio
*/