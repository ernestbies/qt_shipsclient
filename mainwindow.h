/**
  @file mainwindow.h
  @brief Plik nagłówkowy mainwindow.h zawierający klasę MainWindow
  */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork/QNetworkReply>
#include <QMouseEvent>
#include "status.h"
#include "mylabel.h"

namespace Ui {
class MainWindow;
}

/**
 * @brief Klasa MainWindow definiuje metody tworzące i obsługujące sesje gry na serwerze, odpowiada za całościowy wygląd klienta gry.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    /**
     * @brief Metoda wywoływana podczas tworzenia nowej gry. Wysyła żądanie do serwera w celu utworzenia nowej sesji gry. Odtwarza dźwięk.
     * @param user nazwa użytkownika
     * @param server adres serwera gry
     * @return Status
     */
    Status newGame(QString user, QString server);

    /**
     * @brief Metoda wywoływana podczas kliknięcia na jedno z pól na planszy. Wysyła żądanie do serwera w celu sprawdzenia i zapisania rezultatu oddanego strzału.
     * @param user nazwa użytkownika
     * @param shot kod współrzędnych pola
     * @param server adres serwera gry
     * @return Obiekt Status
     */
    Status shotGame(QString user, QString shot, QString server);

    /**
     * @brief Metoda wywoływana podczas wczytywania gry. Wysyła żądanie do serwera w celu otrzymania danych o istniejącej sesji gry.
     * @param user nazwa użytkownika
     * @param server adres serwera gry
     * @return
     */
    Status getGame(QString user, QString server);

    /**
     * @brief Wypisuje informacje do konsoli. Odtwarza odpowiednie dźwięki. Wyświetla zapytania do użytkownika.
     * @param status
     */
    void showStatus(Status *status);

protected:
    /**
     * @brief Rysuje znak X lub ikonę statku na klikniętym polu
     * @details Obsługuje zdarzenie naciśnięcia lewego przycisku myszy. Po wskazaniu miejsca na planszy oraz naciśnięciu przycisku myszy wysyłane jest zapytanie do serwera w którym podana jest pozycja na planszy. Z serwera za pośrednictwem klasy Status jest przekazywana odpowiedź w postaci kodu. ”CHECKED” - pole było już sprawdzane ”MISS” - brak trafienia ”ENDGAME” - koniec gry (wszystkie statki zestrzelone) ”SHOTDOWN” -statek zestrzelony ”HIT” - statek trafiony
     * @param event
     */
    void mousePressEvent(QMouseEvent *event);

    /**
     * @brief Przeciążenie rysowania zapewnia skalowanie tła
     */
    void paintEvent(QPaintEvent *);

    /**
     * @brief Ustala położenie wszystkich elementów w skalowalnym oknie
     */
    void resizeEvent(QResizeEvent *event);

private slots:
    /**
     * @brief Metoda parsująca odpowiedź serwera w formacie JSON na obiekt klasy Status
     * @param request
     * @return Status
     */
    Status onRequest(QNetworkRequest *request);

    /**
     * @brief Metoda wywoływana przy naciśnięciu przycisku "Nowa gra"
     * @details Metoda odpowiedzialna za obsługę przycisku tworzenia nowej gry użytkownika. Po naciśnięciu przycisku do serwera wysyłana jest informacja za pośrednictwem zapytania html o utworzeniu nowej gry użytkownika o podanej nazwie. Serwer za pośrednictwem klasy Status zwraca kod o utworzeniu nowej gry użytkownika lub informację o istnieniu takiej gry.
     */
    void on_pushButtonNewGame_clicked();

    /**
     * @brief Metoda wywoływana przy kliknięciu na przycisk "Wczytaj grę"
     * @details Metoda odpowiedzialna za obsługę przycisku wczytania gry użytkownika. Po naciśnięciu przycisku do serwera wysyłana jest informacja za pośrednictwem zapytania html o wczytaniu gry użytkownika dla podanej nazwy. Serwer za pośrednictwem klasy Status zwraca kod oraz informacje dotyczące zapisanej gry lub informację, że gra nie istnieje.
     */
    void on_pushButtonLoadGame_clicked();

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager manager;
    int posX;
    int posY;
    bool gameLoaded;


};

#endif // MAINWINDOW_H
