#include "CalculateBuy.h"
#include "user_place.h"

CalculateBuy::CalculateBuy() {        Pilesos=0;
    Kruzka=0;
    Microphone=0;
    Kovrik=0;
    Microwave=0;
    sumCost = 0;
}



void CalculateBuy::ZeroValue(){
    Pilesos=0;
    Kruzka=0;
    Microphone=0;
    Kovrik=0;
    Microwave=0;
}

uint CalculateBuy::getSum(){
    return this->sumCost;
}

int CalculateBuy::getValueOf(int m){
    if(m == 0)
        return Pilesos;
    if(m == 1)
        return  Kruzka;
    if(m == 2)
        return Microphone;
    if(m == 3)
        return Kovrik;
    if(m == 4)
        return Microwave;
    else return 0;
}

void CalculateBuy::calcSumCost(int Mv, int Cv, int Pv, int Nv, int Kv){

    sumCost+=Pilesos*Mv + Kruzka*Cv + Microphone*Pv + Kovrik* Nv + Microwave* Kv;
}
void CalculateBuy::addToOrder(int t){
    if(t == 0)
        Pilesos++;
    if(t == 1)
        Kruzka++;
    if(t == 2)
        Microphone++;
    if(t == 3)
        Kovrik++;
    if(t == 4)
        Microwave++;

}
