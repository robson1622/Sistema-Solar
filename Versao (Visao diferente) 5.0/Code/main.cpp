#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "Lista.hpp"
#include "Astro.hpp"
#include "Fisica.hpp"


/*
Aluno                                        /RA
Robson Borges dos Santos                     /2190397
João Vitor Caversan dos Passos               /2192969
Alfons Carlos César Heiermann de Andrade     /1839675



Considerações:
As dimensoes de espaco estão em proporcoes corretas bem como de massa,
porem, se os diametros dos astros fossem proporcionais não seria possivel ver a terra e os outros planetas menores
*/



//Todo processo de criacao e atribuicao das caracteristicas do nosso sistema solar vão aquí
Lista* sistemaSolar();

//Sistema solar binario (duas estrelas)
Lista* sistemaBinario();

// g++ *.cpp -o exe -lsfml-graphics -lsfml-window -lsfml-system
int main(){
    sf::RenderWindow window(sf::VideoMode(1920,1080),"Sistema Solar com lista");
    Lista *sistema;
    Lista *percorrer = NULL;
    Astro *elemento;
    Fisica f;
    sf::Font montserrat;
    sf::Text nomes;
    sf::Color bg(46,43,34);
    int i = 0;


    montserrat.loadFromFile("../Font/padrao.ttf");
    nomes.setFont(montserrat);
    nomes.setCharacterSize(10);
    sistema = sistemaSolar();
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
            window.clear(bg);
            while(percorrer != NULL){
                elemento = percorrer->getAstro();
                elemento->desenhar(&window);
                nomes.setString(elemento->getNome());
                nomes.setPosition(elemento->posicaoNaTela().x,elemento->posicaoNaTela().y -10);
                window.draw(nomes);
                percorrer = percorrer->getProximo();
            }
            f.inforAstros(sistema);
            percorrer = sistema;
            window.display();
            i = 0;
        }
        f.setPosicaoCentroGravidade(sistema);
        f.atualizaAceleracao(sistema);
        f.atualizaVelocidade(sistema);
        f.atualizaPosicao(sistema);
        i++;
    }
    sistema->destroy();
    return 0;
}

//
Lista* sistemaSolar(){
    Lista *sistema = new Lista();
    sistema->start();
    Fisica f;

    //Sol - raio real : 110 * RTERRA
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
    
    //Jupter - raio real : 11.2 * RTERRA 
    Astro *Jupter = new Astro();
    Jupter->atributosAstro(317.8330 * MTERRA,"Jupter",5.21 * DTERRA,"../Astros/Jupter.png");
    sistema->insert(Jupter);
    
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


