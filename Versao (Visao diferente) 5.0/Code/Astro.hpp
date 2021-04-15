#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#pragma once
#include "Vetor.hpp"

class Astro{
    private:
        char *nome;
        long double massa;
        sf::Texture local;
        sf::Sprite forma;
        Vetor posicao;
        Vetor velocidade;
        Vetor aceleracao;
        Vetor *centro_de_gravidade;

    //Atributos físicos(Teóricos)
    public:
        Astro(long double massaN,const char *nomeN,long double distancia,const char* localIMG);
        Astro();
        ~Astro();
        char* getNome(void);
        long double getMassa(void);
        sf::Sprite* getForma(void);
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
        void atributosAstro(long double massaN,const char *nomeN,long double distancia,const char* localIMG);
};