#include "Principal.h"

Principal::Principal(): pilha(NULL), elemento(NULL), sistema(NULL), percorrer(NULL), quantidadeDeAstros(9), i(0)
{
    window.create(sf::VideoMode(2560,1600),"Sistema Solar com lista");
    window.setFramerateLimit(60);
    sf::Image icon;
    icon.loadFromFile("../Astros/logo.png");
    window.setIcon(icon.getSize().x,icon.getSize().y,icon.getPixelsPtr());

    bg.r = 46;
    bg.g = 43;
    bg.b = 34;

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

    sistema = sistemaSolar();
    percorrer = sistema->getPrimeiro();
}
Principal::~Principal()
{

}

void Principal::executar()
{
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

                //vetorVelocidades.push_back(elemento);

                elapsed = clock.getElapsedTime();
                
                nomes.setString(elemento->getNome());
                nomes.setPosition(elemento->posicaoNaTela().x,elemento->posicaoNaTela().y -10);
                nomes.setCharacterSize(10);
                window.draw(nomes);

                window.draw(frasesGerais);

                //desenhando as velocidades na ordem dos Astros
                /*velocidades.setString("Velocidades Angulares em rad/s:");
                velocidades.setPosition(20, 10);
                window.draw(velocidades);
                nomes.setPosition(20, 30*j+40);
                velocidades.setString(elemento->getVelocidadeAngular());
                velocidades.setPosition(130, 30*j+40);
                window.draw(velocidades);
                window.draw(nomes);*/

                //desenhando as velocidades ordenadas
                velocidades.setString("Velocidades Angulares (rad/ano) em ordem crescente: (aperte Q)");
                velocidades.setPosition(20, 10);
                window.draw(velocidades);
                
                if (this->alinharVelocidadeComAstro(j))
                {
                    nomes.setPosition(20, 30*j + 40);
                    nomes.setCharacterSize(20);
                    velocidades.setString(std::to_string(vetorVelocidades[j]));
                    velocidades.setPosition(130, 30*j + 40);
                }
                    window.draw(velocidades);
                    window.draw(nomes);

                //serve para retirar os planetas caso clique em cima deles
                if(mouse.isButtonPressed(sf::Mouse::Left))
                {
                    if (!sistema->isEmpty())
                    {
                        if(elemento->contains(mousePositionView))
                        {
                            pilha = pilha->insert(pilha, sistema->retirar(percorrer));
                            this->quantidadeDeAstros--;
                            realloc(vetorVelocidades, quantidadeDeAstros);
                            preencherVetorVelocidades();
                        }
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
                            this->quantidadeDeAstros++;
                            clock.restart();
                        }
                    }
                }

                //seve para organizar o vetor de velocidades angulares em ordem crescente
                if (keyboard.isKeyPressed(sf::Keyboard::Q))
                {
                    if (elapsed.asSeconds() > 1)
                    {
                        quickSort(vetorVelocidades, 0, quantidadeDeAstros-1);
                        clock.restart();
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
        f.setPosicaoCentroGravidade(sistema);
        f.atualizaAceleracao(sistema);
        f.atualizaVelocidade(sistema);
        f.atualizaPosicao(sistema, vetorVelocidades);
        i++;
    }
    //sistema->destroy();
    pilha->liberarPilha(pilha);
}

//Todo processo de criacao e atribuicao das caracteristicas do nosso sistema solar vão aquí
Lista* Principal::sistemaSolar()
{
    Lista *sistema = new Lista();
    sistema->start();
    Fisica f;

    //Sol - raio real : 109 * RTERRA
    Astro *sol = new Astro();
    sol->atributosAstro((long double)328900 * MTERRA,"Sol",0,"../Astros/Sol.png", 0);
    sistema->insert(sol);
    this->vetorVelocidades[0] = sol->getVelocidadeAngularFloat();
    
    //Mercurio - raio real : 0.04 * RTERRA
    Astro *mercurio = new Astro();
    mercurio->atributosAstro(0.0553 * MTERRA,"Mercurio",0.38 * DTERRA,"../Astros/Mercurio.png", 1);
    sistema->insert(mercurio);
    this->vetorVelocidades[1] = mercurio->getVelocidadeAngularFloat();
    
    //Venus - raio real : 0.95 * RTERRA
    Astro *venus = new Astro();
    venus->atributosAstro(0.8150 * MTERRA,"Venus",0.72 * DTERRA,"../Astros/Venus.png", 2);
    sistema->insert(venus);
    this->vetorVelocidades[2] = venus->getVelocidadeAngularFloat();
    
    //Terra - raio real : 1 * RTERRA
    Astro *terra = new Astro();
    terra->atributosAstro(MTERRA,"Terra",DTERRA,"../Astros/Terra.png", 3);
    sistema->insert(terra);
    this->vetorVelocidades[3] = terra->getVelocidadeAngularFloat();

    //Marte - raio real : 0.5 * RTERRA
    Astro *marte = new Astro();
    marte->atributosAstro(0.1074 * MTERRA ,"Marte",1.52 * DTERRA,"../Astros/Marte.png", 4);
    sistema->insert(marte);
    this->vetorVelocidades[4] = marte->getVelocidadeAngularFloat();
    
    //Jupiter - raio real : 11.2 * RTERRA 
    Astro *jupiter = new Astro();
    jupiter->atributosAstro(317.8330 * MTERRA,"Jupiter",5.21 * DTERRA,"../Astros/Jupiter.png", 5);
    sistema->insert(jupiter);
    this->vetorVelocidades[5] = jupiter->getVelocidadeAngularFloat();
    
    //Saturno - raio real : 9.4 * RTERRA 
    Astro *saturno = new Astro();
    saturno->atributosAstro(95.1520 * MTERRA,"Saturno",9.54 * DTERRA,"../Astros/Saturno.png", 6);
    sistema->insert(saturno);
    this->vetorVelocidades[6] = saturno->getVelocidadeAngularFloat();

    //Urano - raio real : 4 * RTERRA 
    Astro *urano = new Astro();
    urano->atributosAstro(14.5360 * MTERRA,"Urano",19.18 * DTERRA,"../Astros/Urano.png", 7);
    sistema->insert(urano);
    this->vetorVelocidades[7] = urano->getVelocidadeAngularFloat();

    //Netuno - raio real : 3.9 * RTERRA 
    Astro *netuno = new Astro();
    netuno->atributosAstro(17.1470 * MTERRA,"Netuno",30.11 * DTERRA,"../Astros/Netuno.png", 8);
    sistema->insert(netuno);
    this->vetorVelocidades[8] = netuno->getVelocidadeAngularFloat();
    
    f.setPosicaoCentroGravidade(sistema);
    f.atualizaAceleracao(sistema);
    f.velocidadeInicial(sistema);
    return sistema;
}

//Sistema solar binario (duas estrelas)
Lista* Principal::sistemaBinario()
{
    return NULL;
}

//funções para ordenar os planetas em ordem crescente
void Principal::permutar(float* vector, int i, int j)
{
    float aux = vector[i];
    vector[i] = vector[j];
    vector[j] = aux;
}
int Principal::particionar(float* vector, int l, int r)
{
    int i = 0, j = 0;
    i = l-1;
    float pivot = vector[r];

    for (j=l ; j<r ; j++)
    {
        if (vector[j] <= pivot)
        {
            i++;
            permutar(vector, i, j);
        }
    }

    i++;
    permutar(vector, i, r);

    return i;
}
void Principal::quickSort(float* vector, int l, int r)
{
    int q = 0;

   if (l < r)
   {
       q = particionar(vector, l, r);
       quickSort(vector, l, q-1);
       quickSort(vector, q+1, r);
   }
}

    //para alinhar a velocidade ordenada com seu respectivo Astro
bool Principal::alinharVelocidadeComAstro(int j)
{
    ElementoLista* aux = sistema->getPrimeiro();
    while(aux != NULL)
    {
        if (aux->getInfo()->getVelocidadeAngularFloat() == vetorVelocidades[j])
        {
            nomes.setString(aux->getInfo()->getNome());
            return 1;
        }

        aux = aux->getProximo();
    }

    return 0;
}

void Principal::preencherVetorVelocidades()
{
    ElementoLista* aux = this->sistema->getPrimeiro();
    int i = 0;

    while (aux != NULL)
    {
        vetorVelocidades[i] = aux->getInfo()->getVelocidadeAngularFloat();
        i++;
        aux = aux->getProximo();
    }
}