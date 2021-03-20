#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#define MTERRA 5.98e+24
#define RTERRA 6730000
#define DTERRA 1.5e+11
#define G 6.67e-11
#define PI 3.141592654
#define FATORACELERACAO 1000
#define FATORDISTANCIA 256
#define LUAS 1

#include <iostream>
using std::cout;
using std::endl;

typedef struct Vetor{
    long double x;
    long double y;
}Vetor;

typedef struct Astro
{
    Astro *prox;
    Astro *planeta;
    char *nome;
    int classe;
    long double massa;
    double raio;
    sf::CircleShape c0;
    sf::CircleShape c1;
    sf::CircleShape c2;
    sf::CircleShape c3;

    Vetor posicao;
    Vetor velocidade;
    Vetor aceleracao;

    Vetor centro;
    Vetor *centro_de_gravidade;
}Astro;
//Criar Astro
Astro* criarAstro();

//Adicionar Astro
Astro* addAstro(long double massaN,float raioN,const char *nomeN,Vetor posicao,Astro *a);

//Astros diferentes
void setForma(sf::CircleShape c0N,sf::CircleShape c1N,sf::CircleShape c2N,sf::CircleShape c3N,Astro *a);
void setForma(sf::CircleShape c0N,Astro *a);

//Velocidade Inicial
void velocidadeInicial(Astro *lista);

//Calcular Forca Resultante
Vetor forcaResultante(Astro *inicio,Astro *atual);

//Atualiza Posicao
void atualizaPosicao(Astro *lista);

//Atualiza Velocidade
void atualizaVelocidade(Astro *lista);

//Atualiza Aceleracao
void atualizaAceleracao(Astro *lista);

//Desenhar Astro, isso é importante caso haja astros especiais
void desenhaAstro(Astro *lista,sf::RenderWindow *window,sf::Text *nomes);

//Painel de informacoes dos astros
void inforAstros(Astro *lista);

//POsicao do centro de gravidade
void setPosicaoCentroGravidade(Astro *lista);

//Lei de kepler 03 que da uma proporcao que é constante a qualquer astro
/* IMPORTANTE : o raio nas leid de kepler é o raio médio e não a distancia no momento*/
double kepler03(Astro *elemento);