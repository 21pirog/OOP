#ifndef ANIMETOVAR_H
#define ANIMETOVAR_H

#include <QString>


class AnimeTovar
{
public:
    AnimeTovar();
    AnimeTovar(QString namme, uint costt, uint numm);

    void setName(QString nam);
    void setNumber(uint numb);
    void setCost(uint costt);
    int getCost();
    int getNumber();
    QString getName();


private:
    QString name;
    int cost;
    int number;
};

#endif // ANIMETOVAR_H
