#ifndef USER_PLACE_H
#define USER_PLACE_H

#include <QDialog>
#include "animetovar.h"
#include "CalculateBuy.h"

namespace Ui {
class User_Place;
}

class User_Place : public QDialog
{
    Q_OBJECT

public:
    explicit User_Place(QWidget *parent = nullptr);
    ~User_Place();
     void SetUserLogin(QString login);
     QString GetUserLogin();
     void SetTable(uint i, uint j);
     void Read_File();
     void Write_File();
     void SetUserPass(QString passw);
     QString GetUserPass();
     void AddToList(AnimeTovar t1);
     void CheckT();
    int getSumCost();


private slots:
    void on_pushButton_6_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_clicked();

private:
    Ui::User_Place *ui;
    CalculateBuy list_zakaz;
    QString userLogin;
    QString password;
    QList<AnimeTovar> basket;

};

#endif // USER_PLACE_H
