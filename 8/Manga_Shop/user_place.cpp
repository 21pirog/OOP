#include "user_place.h"
#include "ui_user_place.h"
#include <QMessageBox>
#include <string>
#include <QDebug>
#include <fstream>
#include <QFile>
#include "animetovar.h"
#include "CalculateBuy.h"

User_Place::User_Place(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::User_Place)
{
    ui->setupUi(this);
}

User_Place::~User_Place()
{
    delete ui;
}

void User_Place::SetUserLogin(QString login){
    this->userLogin = login;
}

QString User_Place::GetUserLogin(){
    return this->userLogin;
}

QString User_Place::GetUserPass(){
    return this->password;
}

void User_Place::SetUserPass(QString passw){
    this->password = passw;
}

int User_Place::getSumCost(){
     return this->list_zakaz.getSum();
}

void User_Place::AddToList(AnimeTovar t1){
    this->basket.push_back(t1);
}

void User_Place::CheckT(){
    this->list_zakaz = CalculateBuy();
}

void User_Place::SetTable(uint i, uint j){
    ui->tableWidget->setRowCount(i);
    ui->tableWidget->setColumnCount(j);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    for(int k = 0; k < i ; k++ ){
        ui->tableWidget->setColumnWidth(k,165);
        ui->tableWidget->setRowHeight(k,68);

    }

    for(int g = 0;g < i;g++){
        auto h = this->basket[g].getName();
        QTableWidgetItem *item  = new QTableWidgetItem(h);
        ui->tableWidget->setItem(g,0,item);
    }

    for(int g = 0;g < i;g++){
        auto h = this->basket[g].getCost();
        QTableWidgetItem *item  = new QTableWidgetItem(QString::number(h));
        ui->tableWidget->setItem(g,1,item);
    }

    for(int g = 0;g < i;g++){
        auto h = this->basket[g].getNumber();
        QTableWidgetItem *item  = new QTableWidgetItem(QString::number(h));
        ui->tableWidget->setItem(g,2,item);
    }

    for(int g = 0;g < i;g++){
        QTableWidgetItem *item  = new QTableWidgetItem(QString::number(0));
        ui->tableWidget->setItem(g,3,item);
    }
    //иконки добавляем
    QPixmap picture1(":/img/img/pilesos.png");
    int w1 = ui->label_1->width();
    int h1 = ui->label_1->height();
    ui->label_1->setPixmap(picture1.scaled(w1,h1,Qt::KeepAspectRatio));
    QPixmap picture2(":/img/img/cruzka.png");
    ui->label_2->setPixmap(picture2.scaled(w1,h1,Qt::KeepAspectRatio));
    QPixmap picture3(":/img/img/microphone.png");
    ui->label_3->setPixmap(picture3.scaled(w1,h1,Qt::KeepAspectRatio));
    QPixmap picture4(":/img/img/kovrik.png");
    ui->label_4->setPixmap(picture4.scaled(w1,h1,Qt::KeepAspectRatio));
    QPixmap picture5(":/img/img/microwave.png");
    ui->label_5->setPixmap(picture5.scaled(w1,h1,Qt::KeepAspectRatio));

}

void User_Place::Read_File(){
    QString str;
    QString Data_str;
    AnimeTovar t;
    QFile file("C:/Users/ACER/Desktop/OOP/8/Manga_Shop/input.txt");

    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        while (!file.atEnd())
        {

            str = file.readLine();
            int j = 0;
            while(str[j]!='#'){
                Data_str+=str[j];
                j++;
            }
            j++;
            t.setName(Data_str);
            Data_str = "";
            while(str[j]!='%'){
                Data_str+=str[j];
                j++;
            }
            j++;
            t.setCost(Data_str.toInt());
            Data_str = "";
            while(j<str.size()){
                Data_str+=str[j];
                j++;
            }
            t.setNumber(Data_str.toInt());
            Data_str = "";
            AddToList(t);



        }
    }

}

 void User_Place::Write_File(){
     QString str;
     QString Data_str;
     AnimeTovar t;
     QFile file("C:/Users/ACER/Desktop/OOP/8/Manga_Shop/CalculateBuy.txt");

     if(file.open(QIODevice::WriteOnly | QIODevice::Text))
     {

         QTextStream stream(&file);
         stream << "Login: "<< GetUserLogin() << "\n";
         QString tt ;
         stream<<"Check:\n\n";
         for(int i = 0; i < 5;i++){
             stream<<"Position "<<i<<"("<<basket[i].getName()<<")"<<"  Number:"<<list_zakaz.getValueOf(i)<<"  Cost = "<<list_zakaz.getValueOf(i)*(int)basket[i].getNumber()<<"\n";
         }
         list_zakaz.calcSumCost(basket[0].getNumber(),basket[1].getNumber(),basket[2].getNumber(),basket[3].getNumber(),basket[4].getNumber());
         stream << "Summary basket value = "<< QString::number(getSumCost()) << "\n";

     }
     file.close();
 }


 void User_Place::on_pushButton_6_clicked()
 {
     if(basket[0].getCost()!=0){
         list_zakaz.addToOrder(0);
         QTableWidgetItem *item  = new QTableWidgetItem(QString::number(this->list_zakaz.getValueOf(0)));   //установка элемента
         ui->tableWidget->setItem(0,3,item);
         basket[0].setCost(basket[0].getCost()-1);
         QTableWidgetItem *item2  = new QTableWidgetItem(QString::number(basket[0].getCost()));
         ui->tableWidget->setItem(0,1,item2);
     }
 }


 void User_Place::on_pushButton_2_clicked()
 {
     if(basket[1].getCost()!=0){
         list_zakaz.addToOrder(1);
         QTableWidgetItem *item  = new QTableWidgetItem(QString::number(this->list_zakaz.getValueOf(1)));   //установка элемента
         ui->tableWidget->setItem(1,3,item);
         basket[1].setCost(basket[1].getCost()-1);
         QTableWidgetItem *item2  = new QTableWidgetItem(QString::number(basket[1].getCost()));
         ui->tableWidget->setItem(1,1,item2);
     }
 }


 void User_Place::on_pushButton_3_clicked()
 {
     if(basket[2].getCost()!=0){
         list_zakaz.addToOrder(2);
         QTableWidgetItem *item  = new QTableWidgetItem(QString::number(this->list_zakaz.getValueOf(2)));   //установка элемента
         ui->tableWidget->setItem(2,3,item);
         basket[2].setCost(basket[2].getCost()-1);
         QTableWidgetItem *item2  = new QTableWidgetItem(QString::number(basket[2].getCost()));
         ui->tableWidget->setItem(2,1,item2);
     }
 }


 void User_Place::on_pushButton_4_clicked()
 {
     if(basket[3].getCost()!=0){
         list_zakaz.addToOrder(3);
         QTableWidgetItem *item  = new QTableWidgetItem(QString::number(this->list_zakaz.getValueOf(3)));   //установка элемента
         ui->tableWidget->setItem(3,3,item);
         basket[3].setCost(basket[3].getCost()-1);
         QTableWidgetItem *item2  = new QTableWidgetItem(QString::number(basket[3].getCost()));
         ui->tableWidget->setItem(3,1,item2);
     }
 }


 void User_Place::on_pushButton_5_clicked()
 {
     if(basket[4].getCost()!=0){
         list_zakaz.addToOrder(4);
         QTableWidgetItem *item  = new QTableWidgetItem(QString::number(this->list_zakaz.getValueOf(4)));   //установка элемента
         ui->tableWidget->setItem(4,3,item);
         basket[4].setCost(basket[4].getCost()-1);
         QTableWidgetItem *item2  = new QTableWidgetItem(QString::number(basket[4].getCost()));
         ui->tableWidget->setItem(4,1,item2);
     }
 }


 void User_Place::on_pushButton_clicked()
 {
     Write_File();
     this->close();
 }

