#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "Vetor.h"
#include <string.h>
#include <iostream>

#define G 6.67e-11

#pragma once

class Astro{
    private:
        char *nome;
        long double massa;
        int posicao_em_lista;
        sf::Texture local;
        sf::Sprite forma;
        Vetor posicao;
        Vetor velocidade;
        Vetor aceleracao;
        Vetor *centro_de_gravidade;
        float velocidade_angular;
        long double distancia_sol;

    //Atributos físicos(Teóricos)
    public:
        Astro(long double massaN,const char *nomeN,long double distancia,const char* localIMG, int posicaoL);
        Astro();
        ~Astro();
        char* getNome(void);
        long double getMassa(void);
        const int getPosicaoEmLista() const;
        sf::Sprite getForma(void);
        Vetor getPosicao(void);
        Vetor getVelocidade(void);
        Vetor getAceleracao(void);
        Vetor* getCentro_de_Gravidade(void);
        void setNome(const char* nomeN);
        void setMassa(long double massaN);
        void setForma(sf::Sprite formaN);
        void setPosicao(Vetor posicaoN);
        void setVelocidade(Vetor velocidadeN);
        void setAceleracao(Vetor aceleracaoN);
        void setCentro_de_Gravidade(Vetor *cgN);
        void desenhar(sf::RenderWindow *Janela);
        sf::Vector2f posicaoNaTela(void);
        //Atribuir especificidades
        void atributosAstro(long double massaN,const char *nomeN,long double distancia,const char* localIMG, int posicaoL);

        std::string getVelocidadeAngular();
        float getVelocidadeAngularFloat();
        void setVelocidadeAngular(float v);
        const long double getDistanciaDoSol() const;
        void setDistanciaDoSol(long double d);

        //função que checa se o mouse está dentro do planeta
        bool contains(sf::Vector2f pos);
};