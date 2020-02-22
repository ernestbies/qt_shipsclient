#ifndef STATUS_H
#define STATUS_H
#include <QString>
/**
  @file status.h
  @brief Plik nagłówkowy status.h zawierający klasę Status
  */
/**
 * @brief Klasa Status zapewnia metody służące do komunikacji klienta z serwerem. Przechowuje ilość oddanych strzałów, nazwę trafionego statku, otrzymaną planszę z serwera i inne.
 * @details Klasa Status wykorzystywana jest do przesyłania informacji z serwera do klienta. Zawiera informacje dotyczące liczby wykonanych przez użytkownika kroków (steps), nazwę kodu wykonanych operacji lub stanu gry (code), nazwę statku kosmicznego (shipName) na którym była wykonana operacja oraz jego typ (type), a także przechowuje stan planszy (board).
 */
class Status
{
private:
    int steps; //number of user steps
    QString code; //code of game (for e.g. new game, end game)
    QString shipName; //name of the spaceship
    QString board; //current board status
    int type; //type of spaceship

public:
    /**
     * @brief Konstruktor tworzący nowy obiekt Status zgodnie z podanymi parametrami
     * @param kod
     * @param nazwa statku
     * @param typ
     * @param ilość kroków
     * @param plansza
     */
    Status(QString code, QString shipName, int type, int steps, QString board);

    /**
     * @brief Zwraca liczbę kroków zapisanych w obiekcie Status
     * @return liczba kroków
     */
    int getSteps();

    /**
     * @brief Zwraca kod odpowiedzi serwera
     * @return kod odpowiedzi np. SHOTDOWN, ENDGAME
     */
    QString getCode();

    /**
     * @brief Zwraca nazwę trafionego statku
     * @return nazwa trafionego statku
     */
    QString getShipName();

    /**
     * @brief Zwraca typ trafionego statku
     * @return typ trafionego statku
     */
    int getType();

    /**
     * @brief Zwraca planszę gry w formie tekstowej
     * @return plansza
     */
    QString getBoard();

    /**
     * @brief Parsuje obiekt Status do ciągu tekstowego w formacie JSON do wysłania do serwera
     * @return obiekt Status w formie JSON
     */
    QString toString();

    /**
     * @brief Ustawia ilość kroków
     * @param ilość kroków
     */
    void setSteps(int steps);

    /**
     * @brief Ustawia kod trafionego pola
     * @param kod, np "ENDGAME"
     */
    void setCode(QString code);

    /**
     * @brief Ustawia nazwę trafionego statku
     * @param nazwa statku
     */
    void setShipName(QString shipName);

    /**
     * @brief Ustawia typ trafionego statku
     * @param typ trafionego statku
     */
    void setType(int type);

    /**
     * @brief Ustawia stan planszy gry w formie zapisu tekstowego
     * @param plansza
     */
    void setBoard(QString board);
};

#endif // STATUS_H
