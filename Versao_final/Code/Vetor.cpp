#include "Vetor.h"


Vetor::Vetor():x(0),y(0){}

Vetor::~Vetor(){}

long double Vetor::modulo(void){
    return sqrt(pow(x,2) + pow(y,2));
}