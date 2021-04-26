#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "Lista.hpp"
#include "Pilha.hpp"
#include "Astro.hpp"
#include "Fisica.hpp"

//Todo processo de criacao e atribuicao das caracteristicas do nosso sistema solar vão aquí
Lista* sistemaSolar();

//Sistema solar binario (duas estrelas)
Lista* sistemaBinario();

// g++ *.cpp -o exe -lsfml-graphics -lsfml-window -lsfml-system
int main(){
    sf::RenderWindow window(sf::VideoMode(2560,1600),"Sistema Solar com lista");
    Lista *sistema;
    ElementoLista *percorrer = NULL;
    Pilha *pilha = NULL;
    Astro *elemento;
    Fisica f;
    sf::Font montserrat;
    sf::Text nomes;
    sf::Color bg(46,43,34);
    //variáveis que guardam as informações da posição do mouse na tela
    sf::Mouse mouse;
    sf::Vector2f mousePositionView;

    sf::Text velocidades;
    int i = 0;

    montserrat.loadFromFile("../Font/padrao.ttf");
    
    //Inicialização impressão de nomes
    nomes.setFont(montserrat);
    nomes.setCharacterSize(10);
    
    //Inicialização impressão de velocidades
    velocidades.setFont(montserrat);
    velocidades.setCharacterSize(20);

    sistema = sistemaSolar();
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
                
                nomes.setString(elemento->getNome());
                nomes.setPosition(elemento->posicaoNaTela().x,elemento->posicaoNaTela().y -10);
                nomes.setCharacterSize(10);
                window.draw(nomes);

                velocidades.setString("Velocidades Angulares em rad/s:");
                velocidades.setPosition(20, 10);
                window.draw(velocidades);
                nomes.setPosition(20, 30*j+40);
                nomes.setCharacterSize(20);
                velocidades.setString(elemento->getVelocidadeAngular());
                velocidades.setPosition(130,30*j+40);
                window.draw(velocidades);
                window.draw(nomes);

                if(mouse.isButtonPressed(sf::Mouse::Left))
                {
                    if(elemento->contains(mousePositionView))
                    {
                       pilha = pilha->insert(pilha, sistema->retirar(percorrer));
                    }
                }
                if(mouse.isButtonPressed(sf::Mouse::Right))
                {
                    if (!pilha->isEmpty(pilha))
                    {
                        sistema->insert(pilha->top(pilha)->getInfo());
                        pilha = pilha->pop(pilha);
                    }
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
        f.atualizaPosicao(sistema);
        i++;
    }
    //sistema->destroy();
    pilha->liberarPilha(pilha);
    return 0;
}

//
Lista* sistemaSolar(){
    Lista *sistema = new Lista();
    sistema->start();
    Fisica f;

    //Sol - raio real : 109 * RTERRA
    Astro *sol = new Astro();
    sol->atributosAstro((long double)328900 * MTERRA,"Sol",0,"../Astros/Sol.png");
    sistema->insert(sol);
    
    //Mercurio - raio real : 0.04 * RTERRA
    Astro *mercurio = new Astro();
    mercurio->atributosAstro(0.0553 * MTERRA,"Mercurio",0.38 * DTERRA,"../Astros/Mercurio.png");
    sistema->insert(mercurio);
    
    //Venus - raio real : 0.95 * RTERRA
    Astro *venus = new Astro();
    venus->atributosAstro(0.8150 * MTERRA,"Venus",0.72 * DTERRA,"../Astros/Venus.png");
    sistema->insert(venus);
    
    //Terra - raio real : 1 * RTERRA
    Astro *terra = new Astro();
    terra->atributosAstro(MTERRA,"Terra",DTERRA,"../Astros/Terra.png");
    sistema->insert(terra);

    //Marte - raio real : 0.5 * RTERRA
    Astro *marte = new Astro();
    marte->atributosAstro(0.1074 * MTERRA ,"Marte",1.52 * DTERRA,"../Astros/Marte.png");
    sistema->insert(marte);
    
    //Jupiter - raio real : 11.2 * RTERRA 
    Astro *Jupiter = new Astro();
    Jupiter->atributosAstro(317.8330 * MTERRA,"Jupiter",5.21 * DTERRA,"../Astros/Jupiter.png");
    sistema->insert(Jupiter);
    
    //Saturno - raio real : 9.4 * RTERRA 
    Astro *saturno = new Astro();
    saturno->atributosAstro(95.1520 * MTERRA,"Saturno",9.54 * DTERRA,"../Astros/Saturno.png");
    sistema->insert(saturno);

    //Urano - raio real : 4 * RTERRA 
    Astro *Urano = new Astro();
    Urano->atributosAstro(14.5360 * MTERRA,"Urano",19.18 * DTERRA,"../Astros/Urano.png");
    sistema->insert(Urano);

    //Netuno - raio real : 3.9 * RTERRA 
    Astro *Netuno = new Astro();
    Netuno->atributosAstro(17.1470 * MTERRA,"Netuno",30.11 * DTERRA,"../Astros/Netuno.png");
    sistema->insert(Netuno);
    
    f.setPosicaoCentroGravidade(sistema);
    f.atualizaAceleracao(sistema);
    f.velocidadeInicial(sistema);
    return sistema;
}

Lista* sistemaBinario(){
    return NULL;
}


