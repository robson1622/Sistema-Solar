#include "Lista.hpp"
#include <math.h>
#include <iostream>
#include <string.h>
#include <stdio.h>

//Criar Astro
Astro* criarAstro(){
    return NULL;
}

//Adicionar Astro
Astro* addAstro(long double massaN,float raioN,const char *nomeN,Vetor posicao,Astro *a){
    Astro *novo = new Astro();
    novo->prox = a;

    novo->nome = (char*) malloc(sizeof(char) * strlen(nomeN));
    strcpy(novo->nome,nomeN);
    novo->raio = raioN;
    novo->classe = 0;
    novo->c0.setRadius(raioN);
    /*Os astros ja comecam em um angulo de 45 graus --> cos = sen = sqrt(2)/2 */
    novo->posicao = posicao;
    novo->massa = massaN;
    return novo;
}

//Astros diferentes
void setForma(sf::CircleShape c0N,sf::CircleShape c1N,sf::CircleShape c2N,sf::CircleShape c3N,Astro *a){
    a->c0 = c0N;
    a->c1 = c1N;
    a->c2 = c2N;
    a->c3 = c3N;
}
void setForma(sf::CircleShape c0N,Astro *a){
    a->c0.setFillColor(c0N.getFillColor());
}

//Calcular Forca Resultante
Vetor forcaResultante(Astro *inicio,Astro *atual){
    //F = G M m / r²

    Astro *aux = inicio;
    Vetor forca;
    forca.x = forca.y = 0;
    long double hipotenusa,sen,cos,fmodulo;

    while(aux != NULL){
        if(aux != atual){
            hipotenusa = sqrt(pow(aux->posicao.x - atual->posicao.x,2) + pow(aux->posicao.y - atual->posicao.y,2));
            cos = (atual->posicao.x - aux->posicao.x)/hipotenusa;
            sen = (atual->posicao.y - aux->posicao.y)/hipotenusa;
            fmodulo = -(G * aux->massa * atual->massa / pow(hipotenusa,2));
            forca.x += (fmodulo * cos);
            forca.y += (fmodulo * sen);
        }
        aux = aux->prox;
    }
    return forca;
}

//Velocidade Inicial
void velocidadeInicial(Astro *lista){
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

    Astro *aux = lista;
    Vetor posicaoRelativa;

    cos90 = 0;
    sen90 = 1;
    
    while(aux != NULL){
        posicaoRelativa.x = aux->posicao.x - aux->centro_de_gravidade->x;
        posicaoRelativa.y = aux->posicao.y - aux->centro_de_gravidade->y;

        distancia = sqrt(pow(posicaoRelativa.x,2) + pow(posicaoRelativa.y,2));
        VelocidadeModulo = sqrt(distancia * sqrt(pow(aux->aceleracao.x,2) + pow(aux->aceleracao.y,2)));

        cosA = posicaoRelativa.x/distancia;
        senA = posicaoRelativa.y/distancia;

        cosTeta = (cosA*cos90) - (senA*sen90);
        senTeta = (senA*cos90) + (cosA*sen90);

        aux->velocidade.x = VelocidadeModulo * cosTeta;
        aux->velocidade.y = VelocidadeModulo * senTeta;
        /*if(aux->classe == LUAS){
            // Fg = G M m / r² = m v²/r
            // G M /r = v²
            // v = sqrt(G M / r)
            
            posicaoRelativa.x = aux->posicao.x - aux->planeta->posicao.x;
            posicaoRelativa.y = aux->posicao.y - aux->planeta->posicao.y;

            distancia = sqrt(pow(posicaoRelativa.x,2) + pow(posicaoRelativa.y,2));
            VelocidadeModulo = sqrt(G*aux->planeta->massa/sqrt(pow(aux->posicao.x - aux->planeta->posicao.x,2) + pow(aux->posicao.y - aux->planeta->posicao.y,2)));

            cosA = posicaoRelativa.x/distancia;
            senA = posicaoRelativa.y/distancia;

            cosTeta = (cosA*cos90) - (senA*sen90);
            senTeta = (senA*cos90) + (cosA*sen90);

            aux->velocidade.x = aux->planeta->velocidade.x - (VelocidadeModulo * cosTeta);
            aux->velocidade.y = aux->planeta->velocidade.y - (VelocidadeModulo * senTeta);
            
            //aux->velocidade.x = aux->planeta->velocidade.x;
            //aux->velocidade.y = aux->planeta->velocidade.y;
            
        }*/
        aux = aux->prox;
    }
}

//Atualiza Posicao
void atualizaPosicao(Astro *lista){
    Astro *aux = lista;
    sf::Vector2f posC0;

    while(aux != NULL){
        aux->posicao.x += aux->velocidade.x;
        aux->posicao.y += aux->velocidade.y;
        posC0.x = (float) ((aux->posicao.x/DTERRA)*FATORDISTANCIA) + 960 - aux->c0.getRadius();
        posC0.y = (float) ((aux->posicao.y/DTERRA)*FATORDISTANCIA) + 540 - aux->c0.getRadius();
        aux->c0.setPosition(posC0);
        aux = aux->prox;
    }
}

//Atualiza Velocidade
void atualizaVelocidade(Astro *lista){
    Astro *aux = lista;

    while(aux != NULL){
        aux->velocidade.x += aux->aceleracao.x;
        aux->velocidade.y += aux->aceleracao.y;
        aux = aux->prox;
    }
}

//Atualiza Aceleracao
void atualizaAceleracao(Astro *lista){
    // Fg = ma -------->   a = Fg/m
    Astro *aux = lista;
    Vetor forca;

    while(aux != NULL){
        forca = forcaResultante(lista,aux);
        aux->aceleracao.x = (forca.x/aux->massa) * FATORACELERACAO;
        aux->aceleracao.y = (forca.y/aux->massa) * FATORACELERACAO;
        aux = aux->prox;
    }
}

//Desenhar Astro, isso é importante caso haja astros especiais
void desenhaAstro(Astro *lista,sf::RenderWindow *window,sf::Text *nomes){
    Astro *aux = lista;
    sf::CircleShape ajuste;
    sf::Vector2f posicao;
    
    while(aux != NULL){
        ajuste = aux->c0;
        nomes->setString(aux->nome);
        posicao = aux->c0.getPosition();
        posicao.x -= aux->raio;
        posicao.y -= aux->raio;
        if(aux->classe == LUAS){
            posicao.x +=(float) (((aux->posicao.x - aux->planeta->posicao.x)/DTERRA)*10000000);
            posicao.y +=(float) (((aux->posicao.y - aux->planeta->posicao.y)/DTERRA)*10000000);
            ajuste.setPosition(posicao);
        }
        posicao.y -= 12;
        nomes->setPosition(posicao);
        window->draw(ajuste);
        window->draw(*nomes);
        aux = aux->prox;
    }
}

//Painel de informacoes dos astros
void inforAstros(Astro *lista){
    Astro *aux = lista;
    system("clear");
    sf::Vector2f temp;
    while(aux != NULL){
        temp.x = (float) aux->posicao.x;
        temp.y = (float) aux->posicao.y;
        cout<<aux->nome<<endl;
        cout<<" : Posicao ( "<<temp.x<<" , "<<temp.y<<" )"<<endl;
        temp.x = (float) aux->velocidade.x;
        temp.y = (float) aux->velocidade.y;
        cout<<" : Velocidade ( "<<temp.x<<" , "<<temp.y<<" )"<<endl;
        temp.x = (float) aux->aceleracao.x;
        temp.y = (float) aux->aceleracao.y;
        cout<<" : Aceleracao ( "<<temp.x<<" , "<<temp.y<<" )"<<endl;
        if(aux->classe == LUAS){
            temp.x = (float) aux->planeta->posicao.x - aux->posicao.x;
            temp.y = (float) aux->planeta->posicao.y - aux->posicao.y;
            cout<<" : Posicao em relação a Eros ( "<<temp.x<<" , "<<temp.y<<" )"<<endl;
        }
        //cout<<"Lei kepler 03 : (T^2)/(R^3) = CTE : "<<kepler02(aux)<<".\n"<<endl;
        aux = aux->prox;
    }
    cout<<"Posicao do CG : ("<<lista->centro_de_gravidade->x<<" , "<<lista->centro_de_gravidade->y<<") "<<endl;

}

//POsicao do centro de gravidade
/* P(cm = cg) = 1/MassaTotal * (Xi * Mi)*/
void setPosicaoCentroGravidade(Astro *lista){
    long double MassaTotal = 0;
    long double somatoriox,somatorioy;
    Astro *aux = lista;
    Vetor *cg = new Vetor();
    somatoriox = somatorioy = 0;
    
    while(aux != NULL){
        MassaTotal += aux->massa;
        somatoriox += aux->posicao.x * aux->massa;
        somatorioy += aux->posicao.y * aux->massa;
        aux = aux->prox;
    }

    cg->x = somatoriox/MassaTotal;
    cg->y = somatorioy/MassaTotal;
    aux = lista;

    while (aux != NULL){
        aux->centro_de_gravidade = cg;
        aux = aux->prox;
    }
    
}

//Lei de kepler 03 que da uma proporcao que é constante a qualquer astro
double kepler03(Astro *elemento){
    /*
    T²/R³ = CTE ------> (4*PI²)/(v²*R) = CTE
    T = 2PI/tempo de uma volta
    w(omega) = 2PI/T
    v = w(omega)r
    */
    long double raio = sqrt(pow(elemento->posicao.x - elemento->centro_de_gravidade->x,2) + pow(elemento->posicao.y - elemento->centro_de_gravidade->y,2));
    long double velocidade = sqrt(pow(elemento->velocidade.x,2) + pow(elemento->velocidade.y,2)); 
    return ((4*PI*PI)/(pow(velocidade,2)*raio));
}