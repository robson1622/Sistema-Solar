#include <math.h>
#include "Fisica.hpp"
#include "Lista.hpp"
#include "Astro.hpp"
#include <iostream>
using std::cout;
using std::endl;



//Calcular Forca Resultante
Vetor Fisica::forcaResultante(Lista *inicio,Lista *atual){
    //F = G M m / r²
    long double G = 6.67e-11;
    Lista *cont = inicio; 
    Astro *aux;
    Astro *elemento = atual->getAstro();
    Vetor forca;
    forca.x = forca.y = 0;
    long double hipotenusa,sen,cos,fmodulo;

    while(cont != NULL){
        aux = cont->getAstro();
        cont = cont->getProximo();

        if(elemento != aux){
            hipotenusa = distanciaEoclidiana(elemento->getPosicao(),aux->getPosicao());
            cos = (elemento->getPosicao().x - aux->getPosicao().x)/hipotenusa;
            sen = (elemento->getPosicao().y - aux->getPosicao().y)/hipotenusa;
            fmodulo = -(G * aux->getMassa() * elemento->getMassa()) / pow(hipotenusa,2);
            forca.x += (fmodulo * cos);
            forca.y += (fmodulo * sen);
        }
    }
    return forca;
}

//Distancia entre dois astros
long double Fisica::distanciaEoclidiana(Vetor v1, Vetor v2){
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
    Lista *cont = l; 
    Astro *aux;
    Vetor posicaoRelativa;
    Vetor velocidade;

    cos90 = 0;
    sen90 = 1;
    
    while( cont != NULL){
        aux = cont->getAstro();
        cont = cont->getProximo();

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
        
        aux->setVelocidade(velocidade);
    }
}

//Atualiza Posicao
void Fisica::atualizaPosicao(Lista *l){
    Lista *cont = l ;
    Astro *aux = l->getAstro();
    Vetor temp;
    while( cont != NULL){
        aux = cont->getAstro();
        cont = cont->getProximo();
        
        temp.x = aux->getPosicao().x + aux->getVelocidade().x;
        temp.y = aux->getPosicao().y + aux->getVelocidade().y;
        aux->setPosicao(temp);
    }
}

//Atualiza Velocidade
void Fisica::atualizaVelocidade(Lista *l){
    Lista *cont = l;
    Astro *aux;
    Vetor temp;

    while( cont != NULL){
        aux = cont->getAstro();
        cont = cont->getProximo();
        
        temp.x = aux->getVelocidade().x + aux->getAceleracao().x;
        temp.y = aux->getVelocidade().y + aux->getAceleracao().y;
        aux->setVelocidade(temp);
    }
}

//Atualiza Aceleracao
void Fisica::atualizaAceleracao(Lista *l){
    // Fg = ma -------->   a = Fg/m
    Lista *cont = l;
    Astro *aux;
    Vetor forca;
    Vetor aceleracao;

    while(cont != NULL){
        aux = cont->getAstro();
        
        forca = forcaResultante(l,cont);
        aceleracao.x = (forca.x/aux->getMassa()) * FATORACELERACAO;
        aceleracao.y = (forca.y/aux->getMassa()) * FATORACELERACAO;
        aux->setAceleracao(aceleracao);
        
        cont = cont->getProximo();
    }
}

//Painel de informacoes dos astros
void Fisica::inforAstros(Lista *l){
    Lista *cont = l;
    Astro *aux;
    system("clear");
    sf::Vector2f temp;
    while(cont != NULL){
        aux = cont->getAstro();
        cont = cont->getProximo();

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
    }
    cout<<"Posicao do CG : ("<<aux->getCentro_de_Gravidade()->x<<" , "<<aux->getCentro_de_Gravidade()->y<<") "<<endl;

}

//POsicao do centro de gravidade
/* P(cm = cg) = 1/MassaTotal * (Xi * Mi)*/
void Fisica::setPosicaoCentroGravidade(Lista *l){
    long double MassaTotal = 0;
    Vetor somatorio;
    Lista *cont = l;
    Astro *aux;
    Vetor *cg = new Vetor();
    somatorio.x = somatorio.y = 0;
    
    while(cont != NULL){
        aux = cont->getAstro();
        cont = cont->getProximo();

        MassaTotal += aux->getMassa();
        somatorio.x += (aux->getPosicao().x * aux->getMassa());
        somatorio.y += (aux->getPosicao().y * aux->getMassa());
    }

    cg->x = somatorio.x/MassaTotal;
    cg->y = somatorio.y/MassaTotal;
    cont = l;

    while (cont != NULL){
        aux = cont->getAstro();
        cont = cont->getProximo();
        
        aux->setCentro_de_Gravidade(cg);
    }
    
}
/*
//Lei de kepler 03 que da uma proporcao que é constante a qualquer astro
double Fisica::kepler03(Astro *elemento){
    /*
    T²/R³ = CTE ------> (4*PI²)/(v²*R) = CTE
    T = 2PI/tempo de uma volta
    w(omega) = 2PI/T
    v = w(omega)r

    Removí, mas a ideia seria que o raio é o raio maio + meno divido por 2, raio médio

    */