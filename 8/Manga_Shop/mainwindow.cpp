#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPixmap>
#include <QMessageBox>
#include <./ui_user_place.h>
#include "user_place.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    buy_window = new User_Place();
    this->setWindowTitle("AnimeTech Login");
    QPixmap picture(":/img/img/6615243712dcf_1712661569_6615243712db4.png");
    int w = ui->label_3->width();
    int h = ui->label_3->height();
    ui->label_3->setPixmap(picture.scaled(w,h,Qt::KeepAspectRatio));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString login = ui->lineEdit->text();
    QString pass = ui->lineEdit_2->text();
    if(login.isEmpty() or pass.isEmpty()){
        QMessageBox::information(this,"Ошибка", "Введите логин или пароль");
        return;
    }

    buy_window->SetUserLogin(login);
    buy_window->SetUserPass(pass);
    buy_window->setWindowTitle("AnimeTechShop");
    buy_window->show();
    this->close();
    buy_window->Read_File();
    buy_window->CheckT();
    buy_window->SetTable(5,4);



}

