# Projekt na Języki Programowania
-------------------------------------
## Wstęp
-------------------------------------
Program przedstawia grę w życie autorstwa Johna Conwaya.
Został on zbudowany w oparciu o podstawowe zasady gry:

1.Jakakolwiek żywa komórka, która ma mniej niż 2 żywych sąsiadów umiera spowodu zbyt małego zaludnienia.            
2.Jakakolwiek żywa komórka, która ma dokładnie 2 lub 3 żywych sąsiadów przeżywa do kolejnej generacji.           
3.Jakakolwiek żywa komórka, która ma więcej niż 3 żywych sąsiadów umiera spowodu przeludnienia.                
4.Jakakolwiek martwa komórka, która ma dokładnie 3 żywych sąsiadów ożywa spowodu reprodukcji.           

-------------------------------------
## Kompilacja
-------------------------------------
Dla obu systemów operacyjnych, zarówno Windows jak i Linux, kompilacja wygląda tak samo.
Przede wszystkim musimy pobrać wszystkie pliki i zapisać je w jednym folderze o dowolnej nazwie.
Po zapisaniu wszystkich plików, otwieramy konsole i kompilujemy program następującą komendą:

```
g++ main.c -o main
```

Po udanej kompilacji uruchamiamy program:

```
./main
```

Ukazuje nam sie pierwsza generacja naszych losowo wygenerowanych komórek.                    
Aby przejść do kolejnej generacji wciskamy dowolny przycisk.                         
Aby zakończyć działanie programu wciskamy przycisk "Q".                     
Program po zakończeniu działania wypisuje ostatnią generacje i ilość żywych komórek do pliku out.txt.                 

-------------------------------------
## Zmiana warunków początkowy
-------------------------------------
Aby zmienić rozmiar planszy na której będziemy obserwowali walkę o życie przechodzimy do pliku config.txt.                       
Znajdziemy w nim dwie linijki:

```
ilośćWierszy 20
ilośćKolumn 50
```

Są to domyślne wartości które przyjmuje plansza.                                                       
Aby zmienić wielkość planszy wystarczy zmienić liczby po spacji na dowolnie inne liczby.
