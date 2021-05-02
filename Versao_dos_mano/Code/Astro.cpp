#include <string.h>
#include <stdlib.h>
#include "Astro.h"
#define DTERRA 1.5e+11
#define FATORDISTANCIA 50

Astro::Astro(long double massaN,const char *nomeN,long double posicao,const char* localIMG, int posicaoL): velocidade_linear(), velocidade_angular(), distancia_sol(){
    atributosAstro(massaN,nomeN,posicao,localIMG, posicaoL);
    this->posicao_em_lista = posicaoL;
}
Astro::Astro(){
}
Astro::~Astro(){
    delete(centro_de_gravidade);
}

char* Astro::getNome(void){
    return nome;
}

long double Astro::getMassa(void){
    return massa;
}

const int Astro::getPosicaoEmLista() const
{
    return this->posicao_em_lista;
}

sf::Sprite Astro::getForma(void){
    return forma;
}

Vetor Astro::getPosicao(void){
    return posicao;
}
Vetor Astro::getVelocidade(void){
    return velocidade;
}
Vetor Astro::getAceleracao(void){
    return aceleracao;
}
Vetor* Astro::getCentro_de_Gravidade(void){
    return centro_de_gravidade;
}
void Astro::setNome(const char* nomeN){
    nome = (char*) malloc(sizeof(char*) * strlen(nomeN));
    strcpy(nome,nomeN);
}
void Astro::setMassa(long double massaN){
    massa = massaN;
}
void Astro::setForma(sf::Sprite formaN){
    forma = formaN;
}
void Astro::setPosicao(Vetor posicaoN){
    sf::Vector2f temp;
    posicao.x = posicaoN.x;
    posicao.y = posicaoN.y;
    //Aqui é feita uma conversao pra que fique visível na tela os astros, pois a ordem de grandeza da distancia terra-sol é 1.5e+11 metros
    temp.x = (float) ((posicao.x/DTERRA)*FATORDISTANCIA) + 960 - (forma.getTextureRect().width/2);
    temp.y = (float) ((posicao.y/DTERRA)*FATORDISTANCIA) + 540 - (forma.getTextureRect().height/2);
    forma.setPosition(temp);
}
void Astro::setVelocidade(Vetor velocidadeN){
    velocidade.x = velocidadeN.x;
    velocidade.y = velocidadeN.y;
}
void Astro::setAceleracao(Vetor aceleracaoN){
    aceleracao.x = aceleracaoN.x;
    aceleracao.y = aceleracaoN.y;
}
void Astro::setCentro_de_Gravidade(Vetor *cgN){
    centro_de_gravidade = cgN;
}
void Astro::desenhar(sf::RenderWindow *Janela){
    Janela->draw(forma);
}
sf::Vector2f Astro::posicaoNaTela(void){
    return forma.getPosition();
}
//Atribuir especificidades
void Astro::atributosAstro(long double massaN,const char *nomeN,long double distancia,const char* localIMG, int posicaoL){
    nome = (char*) malloc(sizeof(char) * strlen(nomeN));
    strcpy(nome,nomeN);
    massa = massaN;
    posicao.x = distancia;
    local.loadFromFile(localIMG);
    forma.setTexture(local);
    forma.setPosition(sf::Vector2f(posicao.x,posicao.y));
    forma.setOrigin(sf::Vector2f(0,0));
    forma.setScale({0.2,0.2});
    this->posicao_em_lista = posicaoL;
}

std::string Astro::getVelocidadeLinear()
{
   
   //velocidade_linear = sqrt((velocidade.x*velocidade.x)+(velocidade.y*velocidade.y));

   std::string s;
   s = std::to_string(velocidade_linear);

   return s;
}
void Astro::setVelocidadeLinear(float v)
{
    this->velocidade_linear = v;
}
std::string Astro::getVelocidadeAngular()
{
   std::string s;
   s = std::to_string(velocidade_angular);

   return s;
}
float Astro::getVelocidadeAngularFloat()
{
    return this->velocidade_angular;
}
void Astro::setVelocidadeAngular(float v)
{
    this->velocidade_angular = v;
}

const long double Astro::getDistanciaDoSol() const
{
    return this->distancia_sol;
}
void Astro::setDistanciaDoSol(long double d)
{
    this->distancia_sol = d;
}

bool Astro::contains(sf::Vector2f pos)
{
    return (forma.getGlobalBounds().contains(pos));
}