#ifndef MYLABEL_H
#define MYLABEL_H

#include <QWidget>
#include <QLabel>
#include <QPainter>

/**
 * @file mylabel.h
 * @brief Plik nagłówkowy mylabel.h zawierający klasę MyLabel
 */

/**
 * @brief Zmienna boardGame zawierająca aktualną planszę w formie tekstowej
 */
extern QString boardGame;
/**
 * @brief Klasa MyLabel opisuje obiekt QLabel wyświetlający planszę gry
 */
class MyLabel : public QLabel
{
    Q_OBJECT
public:
    /**
     * @brief Konstruktor dziedziczący po QLabel, zapewniający takie metody jak paintEvent
     * @param parent
     */
    explicit MyLabel(QWidget *parent);
protected:
    /**
     * @brief rysuje pole gry, siatkę, tło
     */
    void paintEvent(QPaintEvent *);
};

#endif // MYLABEL_H
