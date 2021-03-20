#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "Lista.hpp"
//Todo processo de criacao e atribuicao das caracteristicas do nosso sistema solar vão aquí
Astro* sistemaSolar();

//Sistema estrelar binario (duas estrelas)
Astro* sistemaBinario();

//Anéis que alguns planetas tem
void aneis(Astro *a);

// g++ *.cpp -o exe -lsfml-graphics -lsfml-window -lsfml-system
int main(){
    sf::RenderWindow window(sf::VideoMode(1920,1080),"Sistema Solar com lista");
    Astro *sistema;
    int i = 0;
    sf::Font montserrat;
    sf::Text nomes;
    montserrat.loadFromFile("padrao.ttf");
    if (!montserrat.loadFromFile("padrao.ttf"))
    {
        exit(32);
    }
    nomes.setFont(montserrat);
    nomes.setCharacterSize(12);
    sistema = sistemaSolar();
    //sistema = sistemaBinario();
    window.setFramerateLimit(60);




    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if(i > 500){
        inforAstros(sistema);
        window.clear(sf::Color::Black);
        desenhaAstro(sistema,&window,&nomes);
        window.display();
        i = 0;
        //exit(1);
        }
        setPosicaoCentroGravidade(sistema);
        atualizaAceleracao(sistema);
        atualizaVelocidade(sistema);
        atualizaPosicao(sistema);
        i++;
    }
}

//
Astro* sistemaSolar(){
    Astro *sistema = criarAstro();
    Astro *terra;
    Vetor posicao;
    sf::CircleShape shape;

    //Sol - raio real : 109 * RTERRA
    posicao.x = 0;
    posicao.y = 0; 
    sistema = addAstro((long double)317725.7525 * MTERRA,10,"Sol",posicao,sistema);
    shape.setFillColor(sf::Color::Yellow);
    setForma(shape,sistema);
    
    //Mercurio - raio real : 0.04 * RTERRA 
    posicao.x = 0.3 * DTERRA;
    posicao.y = 0; 
    sistema = addAstro(0.05518 * MTERRA,8,"Mercurio",posicao,sistema);
    shape.setFillColor(sf::Color::Blue);
    setForma(shape,sistema);
    
    //Venus - raio real : 0.95 * RTERRA 
    posicao.x = 0.7 * DTERRA;
    posicao.y = 0; 
    sistema = addAstro(0.81438 * MTERRA,10,"Venus",posicao,sistema);
    shape.setFillColor(sf::Color::Red);
    setForma(shape,sistema);
    
    //Terra - raio real : 1 * RTERRA 
    posicao.x = DTERRA ;
    posicao.y = 0; 
    sistema = addAstro(1 * MTERRA,6,"Terra",posicao,sistema);
    terra = sistema;
    shape.setFillColor(sf::Color::Blue);
    setForma(shape,sistema);
    /*
    Não consegui fazer com que a lua tivesse uma horbita bonita =[
    //Lua - raio real : 0.27 * RTERRA : 997438
    posicao.x = 0.998738 * DTERRA;
    posicao.y = 0; 
    sistema->classe = LUAS;
    sistema->planeta = terra;
    sistema = addAstro(0.01228 * MTERRA,2,"Lua",posicao,sistema);
    shape.setFillColor(sf::Color::White);
    setForma(shape,sistema);
    */
    //Marte - raio real : 0.5 * RTERRA 
    posicao.x = 1.52 * DTERRA;
    posicao.y = 0; 
    sistema = addAstro(0.10735 * MTERRA,8,"Marte",posicao,sistema);
    shape.setFillColor(sf::Color::Red);
    setForma(shape,sistema);
    
    //Jupter - raio real : 11.2 * RTERRA 
    posicao.x = 5.2 * DTERRA;
    posicao.y = 0; 
    sistema = addAstro(317.72575 * MTERRA,10,"Jupter",posicao,sistema);
    shape.setFillColor(sf::Color::Yellow);
    setForma(shape,sistema);
    
    //Saturno - raio real : 9.4 * RTERRA 
    posicao.x = 9.5 * DTERRA;
    posicao.y = 0; 
    sistema = addAstro(95.15050 * MTERRA,12,"Saturno",posicao,sistema);
    shape.setFillColor(sf::Color::Yellow);
    setForma(shape,sistema);

    //Urano - raio real : 4 * RTERRA 
    posicao.x = 19 * DTERRA;
    posicao.y = 0; 
    sistema = addAstro(14.54849 * MTERRA,8,"Urano",posicao,sistema);
    shape.setFillColor(sf::Color::Blue);
    setForma(shape,sistema);

    //Netuno - raio real : 3.9 * RTERRA 
    posicao.x = 30 * DTERRA;
    posicao.y = 0; 
    sistema = addAstro(17.55852 * MTERRA,10,"Netuno",posicao,sistema);
    shape.setFillColor(sf::Color::Blue); 
    setForma(shape,sistema);
    
    atualizaAceleracao(sistema);
    setPosicaoCentroGravidade(sistema);
    velocidadeInicial(sistema);
    return sistema;
}

Astro* sistemaBinario(){
    Astro *sistema = criarAstro();
    Astro *eros;
    sf::CircleShape shape;
    Vetor aux,posicao;
    sf::Color corZ(255,204,0);
    sf::Color corE(140,255,0);
    sf::Color corI(227,215,202);
    sf::Color corT(163,120,176);

    //Aoros
    posicao.x = 1.05e+10;
    posicao.y = 0;
    sistema = addAstro((long double)332775.92 * MTERRA / 2,20,"Aoros",posicao,sistema);
    shape.setFillColor(sf::Color::Yellow);
    setForma(shape,sistema);

    //Zeus
    posicao.x = -1.05e+10;
    posicao.y = 0;
    sistema = addAstro((long double)332775.92 * MTERRA / 2,20,"Zeus",posicao,sistema);
    shape.setFillColor(corZ);
    setForma(shape,sistema);

    //Eros
    posicao.x = DTERRA;
    posicao.y = 0;
    sistema = addAstro( MTERRA ,5,"Eros",posicao,sistema);
    shape.setFillColor(corE);
    setForma(shape,sistema);
    eros = sistema;

    //Io  0.000631
    posicao.x = 0.998738 * DTERRA;
    posicao.y = 0;
    sistema = addAstro(0.01228 * MTERRA,2,"Io",posicao,sistema);
    sistema->planeta = eros;
    sistema->classe = LUAS;
    shape.setFillColor(corI);
    setForma(shape,sistema);
    
    //Tácila
    //1.000631 251403097.8
    posicao.x = 251403097.8;
    posicao.y = 0;
    sistema = addAstro(0.01228 * MTERRA,2,"Tacila",posicao,sistema);
    sistema->planeta = eros;
    sistema->classe = LUAS;
    shape.setFillColor(corT);
    setForma(shape,sistema);

    atualizaAceleracao(sistema);
    setPosicaoCentroGravidade(sistema);
    velocidadeInicial(sistema);
    return sistema;
}

//Anéis que alguns planetas tem
void aneis(Astro *a){

}
/*       
    system("clear");
    printf("Posicao : ( %f , %f ) Velocidade ( %f , %f ) Aceleracao : ( %f ) \n",posicao.x,posicao.y,velocidade.x,velocidade.y,aceleracaomodulo);
*/


