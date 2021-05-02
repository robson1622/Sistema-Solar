#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "Lista.h"
#include "Pilha.h"
#include "Astro.h"
#include "Fisica.h"

class Principal
{
private:

    sf::RenderWindow window;
    //a lista de planetas e a variável que é usada para percorrê-los
    Lista *sistema;
    ElementoLista *percorrer;
    //vetor que guarda as informações das velocidades angulares para serem ordenadas
    float* vetorVelocidades = (float*)malloc(9*sizeof(float));
    int quantidadeDeAstros;
    //a pilha na qual os planetas são guardados
    Pilha *pilha;
    Astro *elemento;
    Fisica f;
    sf::Font montserrat;
    //usado para imprimir os nomes dos planetas
    sf::Text nomes;
    //usado para imprimir frases em geral na tela
    sf::Text frasesGerais;
    //usado para imprimir as velocidades na tela
    sf::Text velocidades;
    sf::Color bg;
    //variável que cuida do teclado
    sf::Keyboard keyboard;
    //variáveis que guardam as informações da posição do mouse na tela
    sf::Mouse mouse;
    sf::Vector2f mousePositionView;
    //variáveis de tempo utilizadas para regular com que velocidade pode-se retornar os planetas
    sf::Clock clock;
    sf::Time elapsed;

    int i;

public:
    Principal();
    ~Principal();

    void executar();

    //Todo processo de criacao e atribuicao das caracteristicas do nosso sistema solar vão aquí
    Lista* sistemaSolar();

    //Sistema solar binario (duas estrelas)
    Lista* sistemaBinario();

    //funções para ordenar os planetas em ordem crescente
    void permutar(float* vector, int i, int j);
    int particionar(float* vector, int l, int r);
    void quickSort(float* vector, int l, int r);

    bool alinharVelocidadeComAstro(int j);
    
    void preencherVetorVelocidades();
};