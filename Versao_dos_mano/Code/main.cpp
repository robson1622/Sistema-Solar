#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "Lista.hpp"
#include "Pilha.hpp"
#include "Astro.hpp"
#include "Fisica.hpp"

//Todo processo de criacao e atribuicao das caracteristicas do nosso sistema solar vão aquí
Lista* sistemaSolar(std::vector<Astro*>& vector);

//Sistema solar binario (duas estrelas)
Lista* sistemaBinario();

//funções para ordenar os planetas em ordem crescente
void permutar(std::vector<Astro*>& vector, int i, int j);
int particionar(std::vector<Astro*>& vector, int l, int r);
void quickSort(std::vector<Astro*>& vector, int l, int r);

// g++ *.cpp -o exe -lsfml-graphics -lsfml-window -lsfml-system
int main(){
    sf::RenderWindow window(sf::VideoMode(2560,1600),"Sistema Solar com lista");
    //a lista de planetas e a variável que é usada para percorrê-los
    Lista *sistema;
    ElementoLista *percorrer = NULL;
    //vetor que guarda as informações das velocidades angulares
    std::vector<Astro*> vetorVelocidades;
    //a pilha na qual os planetas são guardados
    Pilha *pilha = NULL;
    Astro *elemento;
    Fisica f;
    sf::Font montserrat;
    //usado para imprimir os nomes dos planetas
    sf::Text nomes;
    //usado para imprimir frases em geral na tela
    sf::Text frasesGerais;
    //usado para imprimir as velocidades na tela
    sf::Text velocidades;
    sf::Color bg(46,43,34);
    //variável que cuida do teclado
    sf::Keyboard keyboard;
    //variáveis que guardam as informações da posição do mouse na tela
    sf::Mouse mouse;
    sf::Vector2f mousePositionView;
    //variáveis de tempo utilizadas para regular com que velocidade pode-se retornar os planetas
    sf::Clock clock;
    sf::Time elapsed;

    int i = 0;

    montserrat.loadFromFile("../Font/padrao.ttf");
    clock.restart();
    
    //Inicialização impressão de nomes
    nomes.setFont(montserrat);
    nomes.setCharacterSize(10);

    //Inicialização impressão de frases gerais
    frasesGerais.setFont(montserrat);
    frasesGerais.setCharacterSize(15);
    frasesGerais.setPosition(1250, 15);
    frasesGerais.setString("Clique com o botao esquerdo do mouse em um planeta para o remover. \nClique no direito para o reposicionar.");
    
    //Inicialização impressão de velocidades
    velocidades.setFont(montserrat);
    velocidades.setCharacterSize(20);

    sistema = sistemaSolar(vetorVelocidades);
    percorrer = sistema->getPrimeiro();
    window.setFramerateLimit(60);
    sf::Image icon;
    icon.loadFromFile("../Astros/logo.png");
    window.setIcon(icon.getSize().x,icon.getSize().y,icon.getPixelsPtr());

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if(i > 500){
            mousePositionView = window.mapPixelToCoords(mouse.getPosition(window));
            window.clear(bg);
            int j = 0 ;
            while(percorrer != NULL){
                elemento = percorrer->getInfo();
                elemento->desenhar(&window);

                vetorVelocidades.push_back(elemento);

                elapsed = clock.getElapsedTime();
                
                nomes.setString(elemento->getNome());
                nomes.setPosition(elemento->posicaoNaTela().x,elemento->posicaoNaTela().y -10);
                nomes.setCharacterSize(10);
                window.draw(nomes);

                window.draw(frasesGerais);

                velocidades.setString("Velocidades Angulares em rad/s:");
                velocidades.setPosition(20, 10);
                window.draw(velocidades);
                nomes.setPosition(20, 30*j+40);
                nomes.setCharacterSize(20);
                velocidades.setString(elemento->getVelocidadeAngular());
                velocidades.setPosition(130, 30*j+40);
                window.draw(velocidades);
                window.draw(nomes);

                velocidades.setString("Velocidades Angulares em ordem crescente: (aperte Q)");
                velocidades.setPosition(20, 330);
                window.draw(velocidades);
                nomes.setString(vetorVelocidades[j]->getNome());
                nomes.setPosition(20, 30*j + 360);
                velocidades.setString(vetorVelocidades[j]->getVelocidadeAngular());
                velocidades.setPosition(130, 30*j + 360);
                window.draw(velocidades);
                window.draw(nomes);

                //serve para retirar os planetas caso clique em cima deles
                if(mouse.isButtonPressed(sf::Mouse::Left))
                {
                    if(elemento->contains(mousePositionView))
                    {
                       pilha = pilha->insert(pilha, sistema->retirar(percorrer));
                    }
                }
                //serve para retornar os planetas após retirá-los, usando assim uma pilha
                if(mouse.isButtonPressed(sf::Mouse::Right))
                {
                    if (!pilha->isEmpty(pilha))
                    {
                        if (elapsed.asSeconds() > 1)
                        {
                            sistema->insertElement(pilha->top(pilha));
                            pilha = pilha->pop(pilha);
                            clock.restart();
                        }
                    }
                }

                //seve para organizar o vetor de velocidades com planetas
                if (keyboard.isKeyPressed(sf::Keyboard::Q))
                {
                    quickSort(vetorVelocidades, 0, vetorVelocidades.size()-1);
                }
                
                j++;
                percorrer = percorrer->getProximo();
            }
            f.inforAstros(sistema);
            percorrer = sistema->getPrimeiro();
            window.display();
            i = 0;
        }
        f.atualizaAceleracao(sistema);
        f.atualizaVelocidade(sistema);
        f.atualizaPosicao(sistema, vetorVelocidades);
        i++;
    }
    //sistema->destroy();
    pilha->liberarPilha(pilha);
    return 0;
}

//
Lista* sistemaSolar(std::vector<Astro*>& vector){
    Lista *sistema = new Lista();
    sistema->start();
    Fisica f;

    //Sol - raio real : 109 * RTERRA
    Astro *sol = new Astro();
    sol->atributosAstro((long double)328900 * MTERRA,"Sol",0,"../Astros/Sol.png", 0);
    sistema->insert(sol);
    vector.push_back(sol);
    
    //Mercurio - raio real : 0.04 * RTERRA
    Astro *mercurio = new Astro();
    mercurio->atributosAstro(0.0553 * MTERRA,"Mercurio",0.38 * DTERRA,"../Astros/Mercurio.png", 1);
    sistema->insert(mercurio);
    vector.push_back(mercurio);
    
    //Venus - raio real : 0.95 * RTERRA
    Astro *venus = new Astro();
    venus->atributosAstro(0.8150 * MTERRA,"Venus",0.72 * DTERRA,"../Astros/Venus.png", 2);
    sistema->insert(venus);
    vector.push_back(venus);
    
    //Terra - raio real : 1 * RTERRA
    Astro *terra = new Astro();
    terra->atributosAstro(MTERRA,"Terra",DTERRA,"../Astros/Terra.png", 3);
    sistema->insert(terra);
    vector.push_back(terra);

    //Marte - raio real : 0.5 * RTERRA
    Astro *marte = new Astro();
    marte->atributosAstro(0.1074 * MTERRA ,"Marte",1.52 * DTERRA,"../Astros/Marte.png", 4);
    sistema->insert(marte);
    vector.push_back(marte);
    
    //Jupiter - raio real : 11.2 * RTERRA 
    Astro *Jupiter = new Astro();
    Jupiter->atributosAstro(317.8330 * MTERRA,"Jupiter",5.21 * DTERRA,"../Astros/Jupiter.png", 5);
    sistema->insert(Jupiter);
    vector.push_back(Jupiter);
    
    //Saturno - raio real : 9.4 * RTERRA 
    Astro *saturno = new Astro();
    saturno->atributosAstro(95.1520 * MTERRA,"Saturno",9.54 * DTERRA,"../Astros/Saturno.png", 6);
    sistema->insert(saturno);
    vector.push_back(saturno);

    //Urano - raio real : 4 * RTERRA 
    Astro *Urano = new Astro();
    Urano->atributosAstro(14.5360 * MTERRA,"Urano",19.18 * DTERRA,"../Astros/Urano.png", 7);
    sistema->insert(Urano);
    vector.push_back(Urano);

    //Netuno - raio real : 3.9 * RTERRA 
    Astro *Netuno = new Astro();
    Netuno->atributosAstro(17.1470 * MTERRA,"Netuno",30.11 * DTERRA,"../Astros/Netuno.png", 8);
    sistema->insert(Netuno);
    vector.push_back(Netuno);
    
    f.setPosicaoCentroGravidade(sistema);
    f.atualizaAceleracao(sistema);
    f.velocidadeInicial(sistema);
    return sistema;
}

Lista* sistemaBinario(){
    return NULL;
}

void permutar(std::vector<Astro*>& vector, int i, int j)
{
    Astro* aux = vector[i];
    vector[i] = vector[j];
    vector[j] = aux;

}
int particionar(std::vector<Astro*>& vector, int l, int r)
{
    int i = 0, j = 0;
    i = l-1;
    float pivot = vector[r]->getVelocidadeAngularFloat();

    for (j=l ; j<r ; j++)
    {
        if (vector[j]->getVelocidadeAngularFloat() <= pivot)
        {
            i++;
            permutar(vector, i, j);
        }
    }

    i++;
    permutar(vector, i, r);

    return i;
}
void quickSort(std::vector<Astro*>& vector, int l, int r)
{
   int q = 0;

   if (l < r)
   {
       q = particionar(vector, l, r);
       std::cout << q << std::endl;
       quickSort(vector, l, q-1);
       quickSort(vector, q+1, r);
   }
}