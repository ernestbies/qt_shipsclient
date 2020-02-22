#include "mylabel.h"

MyLabel::MyLabel(QWidget *parent):QLabel(parent){

}


void MyLabel::paintEvent(QPaintEvent *){

    QPainter paint(this);
    int p;

    paint.setPen(QColor(Qt::white));
    int scale = this->width()/9;

    for (int i=1;i<9;i++){
        paint.drawLine(0,
                       0 + i*scale,
                       0 + this->width(),
                       0 + i*scale);
        paint.drawLine(0 + i*scale,
                       0,
                       0 + i*scale,
                       0 + this->height());
    }

    for (int y = 0; y < 9; y++) {
        for (int x = 0; x < 9; x++) {
            p = y * 9 + x;
            if (boardGame[p] >= '0' && boardGame[p] <= '9') {
                paint.drawLine(0+x*scale,
                               0+y*scale,
                               0+x*scale + scale,
                               0+y*scale + scale);
                paint.drawLine(0+x*scale,
                               0+y*scale + scale,
                               0+x*scale + scale,
                               0+y*scale);
                paint.drawText(0+x*scale + scale/2,
                               0+y*scale + scale/4,
                               boardGame.at(p));
            } else if (boardGame[p] >= 'A' && boardGame[p] <= 'Z'){
                QImage *image = new QImage();
                image->load(":/obrazy/images/"+boardGame[p]+".png");
                paint.drawImage(0+x*scale + 1,
                                0+y*scale + 1,
                                image->scaled(scale-1,scale-1));

            }
        }
    }
}
