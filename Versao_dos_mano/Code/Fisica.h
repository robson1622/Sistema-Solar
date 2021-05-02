#define MTERRA 5.98e+24
#define RTERRA 6730000
#define DTERRA 1.5e+11
#define PI 3.141592654
#define FATORACELERACAO 1000
#define FATORDISTANCIA 256

#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "Lista.h"
#include "Astro.h"
#include <vector>

#pragma once

class Fisica{
    private:
    sf::Clock clock;
    sf::Time elapsed;
    //Calcular Forca Resultante
    Vetor forcaResultante(Lista *inicio,ElementoLista *atual);

    //Distancia entre dois astros
    long double distanciaEuclidiana(Vetor v1, Vetor v2); 
    public:
    Fisica();
    ~Fisica();

    //Velocidade Inicial
    void velocidadeInicial(Lista *l);

    //Atualiza Posicao
    void atualizaPosicao(Lista *l, float* vector);

    //Atualiza Velocidade
    void atualizaVelocidade(Lista *l);

    //Atualiza Aceleracao
    void atualizaAceleracao(Lista *l);

    //Painel de informacoes dos astros
    void inforAstros(Lista *);

    //POsicao do centro de gravidade
    void setPosicaoCentroGravidade(Lista *l);

    //Lei de kepler 03 que da uma proporcao que é constante a qualquer astro
    /* IMPORTANTE : o raio nas leid de kepler é o raio médio e não a distancia no momento*/
    //double kepler03(Astro *elemento);
};



