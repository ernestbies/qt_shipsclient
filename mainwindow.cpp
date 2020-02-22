#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QPainter>
#include <QScrollBar>
#include "mylabel.h"
#include <QSound>
#include <QMessageBox>

QString boardGame;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    for (int i=0; i < 81; i++) boardGame[i] = ' ';
    gameLoaded=false;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::mousePressEvent(QMouseEvent *event){

    int x, y;

    int scale = ui->label->width()/9;

    if(!gameLoaded){
        QMessageBox(QMessageBox::Information, "","Utwórz lub wczytaj grę użytkownika!", QMessageBox::Ok).exec();
        return;
    }

    if (event->x() > ui->label->x()
            && event->x() < ui->label->x() + ui->label->width()
            && event->y() > ui->label->y()
            && event->y() < ui->label->y() + ui->label->height()) {

        x = (event->x() - ui->label->x())/scale;
        y = (event->y() - ui->label->y())/scale;
        if (x==9) x = 8;
        if (y==9) y = 8;

        QString password = QString(QCryptographicHash::hash((ui->lineEditPassword->text().toUtf8()),QCryptographicHash::Md5).toHex());
        Status status = shotGame(ui->lineEditUser->text()+password,QString::number(x)+QString::number(y),ui->lineEditServer->text());
        boardGame = status.getBoard();
        ui->label->repaint();
        showStatus(&status);
    }


}

void MainWindow::paintEvent(QPaintEvent *){

    QPainter paint(this);
    QPixmap pixmap(":/obrazy/images/background.jpg");
    double ratio=static_cast<double>(pixmap.width()/pixmap.height());

    if(static_cast<double>(this->width()/this->height())>=ratio){
        paint.drawPixmap(0,0,this->width(),static_cast<int>(this->width()/ratio),pixmap);
    } else {
        paint.drawPixmap(0,0,static_cast<int>(this->height()*ratio),this->height(),pixmap);
    }
}

void MainWindow::resizeEvent(QResizeEvent *event){
    QMainWindow::resizeEvent(event);
    int pole_y=this->height()-ui->groupBox->height();
    int separator=static_cast<int>(0.03*this->width());

    if(this->width()>pole_y){
        ui->label->setGeometry(0,0,static_cast<int>(pole_y*0.9),static_cast<int>(pole_y*0.9));
    } else{
        ui->label->setGeometry(0,0,static_cast<int>(this->width()*0.9),static_cast<int>(this->width()*0.9));
    }
    ui->label->move(this->width()-ui->label->width()-separator,(pole_y-ui->label->width())/2);


    ui->groupBox->setGeometry(0,this->height() - 100, 350, 100);
    ui->groupBoxKroki->setGeometry(this->width() - 120,this->height() - 100, 120, 100);
    ui->statusTerminal->setGeometry(350,this->height() - 100,this->width() - 350-120,100);
    ui->rulesHelp->setGeometry(separator,ui->label->y(),static_cast<int>(0.9*this->width()-ui->label->width()),ui->label->height());
    if(ui->rulesHelp->width()<this->width()*0.15){
        ui->rulesHelp->setVisible(false);
    } else{
        ui->rulesHelp->setVisible(true);
    }

}

void MainWindow::on_pushButtonNewGame_clicked()
{
    if(ui->lineEditUser->text()=="" || ui->lineEditPassword->text()=="" || ui->lineEditServer->text()==""){
        QMessageBox(QMessageBox::Information, "","Wprowadź poprawną nazwę użytkownika, hasło oraz adres serwera!", QMessageBox::Ok).exec();
        return;
    }

    QString password = QString(QCryptographicHash::hash((ui->lineEditPassword->text().toUtf8()),QCryptographicHash::Md5).toHex());
    Status status = getGame(ui->lineEditUser->text()+password,ui->lineEditServer->text());
    if(status.getCode()=="ERROR") {
        QMessageBox(QMessageBox::Information, "","Nie znaleziono serwera pod podanym adresem!", QMessageBox::Ok).exec();
        return;
    }
    if(!(status.getCode()=="NOGAME")){
        if(QMessageBox::Yes==QMessageBox(QMessageBox::Information, "","Na serwerze znajduje się gra użytkownika, która zostanie wczytana lub usunięta.\n Czy chcesz usunąć grę?", QMessageBox::Yes|QMessageBox::No).exec()){
            status = newGame(ui->lineEditUser->text()+password,ui->lineEditServer->text());
            ui->statusTerminal->insertHtml("<b><span style=\"color:yellow\">"+ui->lineEditUser->text()+
                                           ": </span></b><span style=\"color:blue\">utworzono nową grę użytkownika</span><br>");
        } else {
            ui->statusTerminal->insertHtml("<b><span style=\"color:yellow\">"+ui->lineEditUser->text()+
                                           ": </span></b><span style=\"color:blue\">wczytano grę użytkownika</span><br>");
            QSound::play(":/dzwieki/sounds/newloadgame.wav");
        }
    } else{
        status = newGame(ui->lineEditUser->text()+password,ui->lineEditServer->text());
        ui->statusTerminal->insertHtml("<b><span style=\"color:yellow\">"+ui->lineEditUser->text()+
                                       ": </span></b><span style=\"color:blue\">utworzono nową grę użytkownika</span><br>");
    }

    boardGame = status.getBoard();
    this->repaint();
    gameLoaded=true;
    ui->lineEditUser->setEnabled(false);
    ui->lineEditPassword->setEnabled(false);
    ui->lineEditServer->setEnabled(false);
    ui->pushButtonNewGame->setEnabled(false);
    ui->pushButtonLoadGame->setEnabled(false);
    showStatus(&status);
}


void MainWindow::on_pushButtonLoadGame_clicked()
{
    if(ui->lineEditUser->text()=="" || ui->lineEditPassword->text()=="" || ui->lineEditServer->text()==""){
        QMessageBox(QMessageBox::Information, "","Wprowadź poprawną nazwę użytkownika, hasło oraz adres serwera!", QMessageBox::Ok).exec();
        return;
    }
    QString password = QString(QCryptographicHash::hash((ui->lineEditPassword->text().toUtf8()),QCryptographicHash::Md5).toHex());
    Status status = getGame(ui->lineEditUser->text()+password,ui->lineEditServer->text());
    if(status.getCode()=="ERROR") {
        QMessageBox(QMessageBox::Information, "","Nie znaleziono serwera pod podanym adresem!", QMessageBox::Ok).exec();
        return;
    }
    if(status.getCode()=="NOGAME"){
        QMessageBox(QMessageBox::Information, "","Brak zapisanej gry użytkownika!", QMessageBox::Ok).exec();
        return;
    }

    boardGame = status.getBoard();
    this->repaint();
    gameLoaded=true;
    ui->lineEditUser->setEnabled(false);
    ui->lineEditPassword->setEnabled(false);
    ui->lineEditServer->setEnabled(false);
    ui->pushButtonNewGame->setEnabled(false);
    ui->pushButtonLoadGame->setEnabled(false);
    ui->statusTerminal->insertHtml("<b><span style=\"color:yellow\">"+ui->lineEditUser->text()+
                                   ": </span></b><span style=\"color:blue\">wczytano grę użytkownika</span><br>");
    QSound::play(":/dzwieki/sounds/newloadgame.wav");
    showStatus(&status);
}


Status MainWindow::onRequest(QNetworkRequest *request)
{
    request->setRawHeader("Content-Type", "application/json");
    QNetworkReply *reply = manager.get(*request);
    QEventLoop eventLoop;
    connect(&manager, SIGNAL(finished(QNetworkReply *)), &eventLoop, SLOT(quit()));
    eventLoop.exec();

    if (reply->error() == QNetworkReply::NoError) {
        QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
        QJsonObject data = document.object();
        return Status(data["code"].toString(),
                data["shipName"].toString(),
                data["type"].toString().toInt(),
                data["steps"].toString().toInt(),
                data["board"].toString());
    }
    else {
        return Status("ERROR", "REQUEST", 0, 0, "");
    }
}


Status MainWindow::newGame(QString user, QString server) {
    QSound::play(":/dzwieki/sounds/newloadgame.wav");
    QNetworkRequest request(QUrl("http://"+server+"/api/newgame?user="+user));
    return onRequest(&request);
}


Status MainWindow::shotGame(QString user, QString shot, QString server) {

    QNetworkRequest request(QUrl("http://"+server+"/api/shotgame?user="+user+"&shot="+shot));
    return onRequest(&request);

}


Status MainWindow::getGame(QString user, QString server) {

    QNetworkRequest request(QUrl("http://"+server+"/api/getgame?user="+user));
    return onRequest(&request);
}


void MainWindow::showStatus(Status *status){

    ui->labelKroki->setText(QString::number(status->getSteps()));

    if(status->getCode()=="CHECKED"){
        ui->statusTerminal->insertHtml("<b><span style=\"color:yellow\">"+ui->lineEditUser->text()+
                                       ": </span></b><span style=\"color:blue\">to pole było sprawdzane!</span><br>");
        QSound::play(":/dzwieki/sounds/checked.wav");
    }else
    if(status->getCode()=="MISS"){
        ui->statusTerminal->insertHtml("<b><span style=\"color:yellow\">"+ui->lineEditUser->text()+
                                       ": </span></b><span style=\"color:orange\">Pudło!</span><br>");
        QSound::play(":/dzwieki/sounds/miss.wav");
    }else
    if(status->getCode()=="ENDGAME"){
        ui->statusTerminal->insertHtml("<b><span style=\"color:yellow\">"+ui->lineEditUser->text()+
                                       ": </span></b><span style=\"color:green\">KONIEC GRY po "+QString::number(status->getSteps())+" krokach!</span><br>");
        QSound::play(":/dzwieki/sounds/endgame.wav");

        if (QMessageBox::Yes == QMessageBox(QMessageBox::Information, "", "Zakończyć grę?", QMessageBox::Yes|QMessageBox::No).exec())
        {
            QCoreApplication::exit();
        }else {
            gameLoaded=false;
            ui->lineEditUser->setEnabled(true);
            ui->lineEditPassword->setEnabled(true);
            ui->lineEditServer->setEnabled(true);
            ui->pushButtonNewGame->setEnabled(true);
            ui->pushButtonLoadGame->setEnabled(true);
            boardGame="";

            QMessageBox(QMessageBox::Information, "", "Możesz rozpocząć nową grę.", QMessageBox::Ok).exec();
        }

    }else
    if(status->getCode()=="SHOTDOWN"){
        ui->statusTerminal->insertHtml("<b><span style=\"color:yellow\">"+ui->lineEditUser->text()+
                                       ": </span></b><span style=\"color:red\">Z E S T R Z E L O N Y!  "+status->getShipName()+"</span><br>");
        QSound::play(":/dzwieki/sounds/shotdown.wav");
    }else
    if(status->getCode()=="HIT"){
        ui->statusTerminal->insertHtml("<b><span style=\"color:yellow\">"+ui->lineEditUser->text()+
                                       ": </span></b><span style=\"color:pink\">TRAFIONY! "+status->getShipName()+"</span><br>");
        QSound::play(":/dzwieki/sounds/hit.wav");
    }


    ui->statusTerminal->verticalScrollBar()->setSliderPosition(ui->statusTerminal->verticalScrollBar()->maximum());
}


