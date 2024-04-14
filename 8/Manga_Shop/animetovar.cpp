#include "animetovar.h"

AnimeTovar::AnimeTovar() {}

AnimeTovar::AnimeTovar(QString namme, uint costt, uint numm){
    name = namme;
    cost = costt;
    number = numm;
}

QString AnimeTovar::getName(){
    return this->name;
}

void AnimeTovar::setName(QString nam){
    this->name = nam;
}

void AnimeTovar::setNumber(uint numb){
    this->number = numb;
}

void AnimeTovar::setCost(uint costt){
    this->cost = costt;
}

int AnimeTovar::getCost(){
    return this->cost;
}

int AnimeTovar::getNumber(){
    return this->number;
}
