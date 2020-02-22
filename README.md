---
Autorzy: Ernest Bieś, Konrad Czechowski, Dawid Kwaśny

---

Podstawowe informacje
=====================

"Statki kosmiczne" to gra logiczna będąca połączeniem dwóch
popularnych gier "Statki" oraz "Saper".

Zasady gry
==========

Po rozpoczęciu gry na planszy o wymiarach 9x9 utworzonej z kwadratów są
losowo rozmieszczone statki kosmiczne o różnych wielkościach:
Dwa *Transportowce* o wymiarze 4
Trzy *Samoloty kosmiczne* o wymiarze 3
Trzy *Wahadłowce* o wymiarze 2
Dwa *Szturmowce* o wymiarze 1

Statki nie są widoczne. Zadaniem gracza jest odnalezienie wszystkich
statków w jak najmniejszej liczbie kroków. W przypadku odkrycia pola,
które nie zawiera żadnego statku widoczna jest liczba, która wskazuje na
ilu polach sąsiadujących z odkrytym polem znajdują się statki. Wobec
powyższego gracz musi podejmować swoją decyzję dotyczącą pola, które w
następnej kolejności odkryje na podstawie logicznego myślenia, gdyż tym
samym zwiększa swoje szanse na odnalezienie statków w pobliżu.

Opis klienta
============

Interfejs graficzny klienta
---------------------------
![GUI1](../images/g.png)

W głównym oknie programu po lewej stronie widoczna jest plansza o
rozmiarze 9x9 kwadratów na której wyświetlane są ikony zestrzelonych
statków oraz pola, które zostały odkryte przez gracza, a nie zawierają
żadnych statków. Po uruchomieniu gry po lewej stronie wyświetlone
zostają podstawowe informacje dotyczące zasad gry oraz statków jakie
musimy zestrzelić. W górnym lewym rogu znajduje się przycisk za pomocą
którego możemy ukryć zasady gry. W lewym dolnym rogu okna znajdują się
pola służące do wprowadzenia nazwy użytkownika i hasła oraz przyciski za
pomocą których możemy utworzyć nową grę na serwerze lub wczytać już
istniejącą.Na dole w srodku okna znajduje się konsola na której
wyświetlane są informacje dotyczące akcji podejmowanych przez gracza. Z
prawej strony w dolnej części okna znajduje się licznik z aktualnie
wykonanymi krokami przez gracza.

![GUI2](../images/b.png)

W trakcie gry użytkownik po wskazaniu myszką wybranego pola i
naciśnięciu lewego przycisku myszki odsłania poszczególne pola na
planszy. W przypadku trafienia statku jego ikona zostaje wyświetlona w
odpowiednim miejscu na planszy, natomiast w przypadku "pudła" we
wskazanym polu pojawia się znak X oraz liczba wskazująca na ilu polach
sąsiadujących ze wskazanym znajdują się statki. Równocześnie po wskazaniu
pola odtwarzany jest odpowiedni dźwięk.

Instrukcja obsługi
------------------

Po uruchomieniu klienta użytkownik wprowadza nazwę użytkownika oraz
hasło, a następnie naciska przycisk "Nowa gra". Zostaje utworzona nowa
gra dla użytkownika, następnie korzystając z myszki naciska lewy
przycisk na wybranym polu na planszy. Jeżeli pod odkrytym polem znajduje
się statek, jego ikona zostanie wyświetlona w odpowiednim kwadracie oraz
program zasygnalizuje trafienie odpowiednim dźwiękiem. Jeżeli natomiast
wskazane pole nie zawiera żadnego statku to zostanie na nim wyświetlony
znak X oraz liczba wskazująca na ilu polach sąsiadujących znajdują się
statki. Jednocześnie za każdym wskazaniem pola zostaje zwiększony
licznik znajdujący się w prawym, dolnym roku ekranu. Jednocześnie na
konsoli będą pojawiały się komunikaty dotyczące trafienia danego statku,
jego nazwy lub też, że oddany strzał to niestety "pudło".
Po zestrzeleniu wszystkich statków kosmicznych wyświetlany jest
komunikat z zapytaniem czy użytkownik chce zakończyć działanie programu.
W przypadku udzielenia negatywnej odpowiedzi gra jest zapisywana na
serwerze, natomiast klient zeruje wszelkie dane i ustawienia celem
umożliwienia użytkownikowi rozpoczęcia nowej gry.

![GUI3](../images/k.png)