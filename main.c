#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
    Zasady:
    Any live cell with fewer than two live neighbours dies, as if by underpopulation.
    Any live cell with two or three live neighbours lives on to the next generation.
    Any live cell with more than three live neighbours dies, as if by overpopulation.
    Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
*/

void begin(int rows, int columns);
char *create(int rows, int columns);
double randomValue(double min, double max);
void display(int rows, int columns, char *simulation);
void firstDisplay(int rows, int columns, char *simulation);
void lastDisplay(int rows, int columns, char *simulation);
int countNeighbors(int rows, int columns, int x, int y, char *simulation);
char *step(int rows, int columns, char *previousSimulation);

int main(){
    int rows, columns;
    char tmp1[25];
    char tmp2[25];
    char row[30];

    FILE *plik;
    plik = fopen("config.txt", "r");
    if(plik == NULL) return -1;

    fgets(row, 30, plik);
    sscanf(row,"%s %d", tmp1, &rows);
    fgets(row, 30, plik);
    sscanf(row,"%s %d", tmp2, &columns);

    fclose(plik);
    
    if(rows <= 0){
        printf("Liczba wierszy nie moze byc mniejsza niz 0!\n");
        return -1;
    }
    rows+=2;

    if(columns <= 0){
        printf("Liczba kolumn nie moze byc mniejsza niz 0!\n");
        return -1;
    }
    columns+=2;
    /*
    bez +2 nie da się w prosty sposób liczyć sąsiadów
    dzieki temu zabiegowi opakowujemy wyswietlajacą się plansze w niewidzialne pudełko
    które na krańcach będzie przypisywac wartości skrajne drugiej strony
    np.

    . . . . . .      h e f g h e
    . 1 2 3 4 .      4 1 2 3 4 1
    . a b c d .      d a b c d a
    . 5 6 7 8 . -->  8 5 6 7 8 5
    . e f g h .      h e f g h e
    . . . . . .      4 1 2 3 4 1

    dzięki takiemu zabiegowi nigdy nie wyjdziemy za przydzieloną pamięć i będzie prościej
    zliczać sąsiadów w dalszej czśćci programu
    */

    begin(rows, columns);
}

void display(int rows, int columns, char *simulation){
    printf("\n\n\n\n\n\n\n\n\n");
    int x,y;
    for(y=1; y<rows-1; y++){
        for(x=1; x<columns-1; x++){
            printf("%c", *(simulation + y*columns + x));
        }
        printf("\n");
    }
}

void firstDisplay(int rows, int columns, char *simulation){
    int x,y;
    for(y=1; y<rows-1; y++){
        for(x=1; x<columns-1; x++){
            printf("%c", *(simulation + y*columns + x));
        }
        printf("\n");
    }
}

void lastDisplay(int rows, int columns, char *simulation){
    FILE *plik;
    plik = fopen("out.txt", "w");
    int x,y;
    int alive = 0;
    for(y=1; y<rows-1; y++){
        for(x=1; x<columns-1; x++){
            fprintf(plik, "%c", *(simulation + y*columns + x));

            if(*(simulation + y*columns + x) == '#') alive++;
        }
        fprintf(plik, "\n");
    }
    fprintf(plik, "\nW ostatniej generacji zachowało się %d żywych komórek", alive);
    fclose(plik);
}

int countNeighbors(int rows, int columns, int x, int y, char *simulation){
    int count = 0;
    int pivot = y*columns + x;

    int i,j;
    /*
    pamiec lokowana jest w jednej linii, wiec zapis
        . . . . . .
        . 1 2 3 4 .
        . 1 2 3 4 .
        . 1 2 3 4 .
        . . . . . .
    powinnien wygladac tak:
        . . . . . . . 1 2 3 4 . . 1 2 3 4 . . 1 2 3 4 . . 1 2 3 4 . . . . . . .
    dzięki temu zabiegowi jestem w stanie w prosty sposób zliczyć sąsiadów komórki która przyjmuje akutalnie nazwe pivot
    */
    for(i=-1; i<=1; i++){
        for(j=-1; j<=1; j++){
            char c = *(simulation + pivot + (i*columns)+j);

            if(c == '#') count++;
        }
    }
    return count;
}

char *step(int rows, int columns, char *previousSimulation){
    char *steppedSimulation = (char*)calloc(rows*columns, sizeof(int));
    if(steppedSimulation == NULL) return NULL;

    int x,y;

    for(y=1; y<rows-1; y++){
        for(x=1; x<columns-1; x++){
            int live = countNeighbors(rows, columns, x, y, previousSimulation);
            char cell = *(previousSimulation + y*columns + x);
            if(cell == '#') live--;

            /*w 
            funkcji countNeighbors może się zdażyć że wszystkie 9 sprzwdzanych komórek mogą być żywe
            ale jako, że jedna z tych komórek jest akurat naszą wybraną więc nie chcemy aby była ona liczona jako komórka sąsiadująca
            dlatego komórka, dla której sprawdzamy sąsiadów, nie może być uwzględniania podczas liczenia żywych sąsiadów
            */

            *(steppedSimulation + y*columns + x) = cell;
            if(live < 2){
                *(steppedSimulation + y*columns + x) = '.';
            }
            else if((live == 2 || live ==3) && cell == '#'){
                *(steppedSimulation + y*columns + x) = '#';
            }
            else if(live > 3 && cell == '#'){
                *(steppedSimulation + y*columns + x) = '.';
            }
            else if(live == 3 && cell == '.'){
                *(steppedSimulation + y*columns + x) = '#';
            }
        }
    }
    return steppedSimulation;
}

void begin(int rows, int columns){
    char *simulation = create(rows, columns);
    if(simulation == NULL) return;
    firstDisplay(rows, columns, simulation);
    int n = 0;


    while(1){
        char *newSim = step(rows, columns, simulation);
        if(newSim == NULL) return;
        free(simulation);
        simulation = newSim;
        scanf("%c", &n);
        if(n == 'q' || n == 'Q'){
            lastDisplay(rows, columns, simulation);
            break;
        }
        else{
            display(rows, columns, simulation);

        }
    }
}

char* create(int rows, int columns){
    char *simulation = (char*)calloc(rows*columns, sizeof(char));
    if(simulation == NULL) return NULL;
    srand(time(NULL));

    int x,y;
    for(y=1; y<rows-1; y++){
        for(x=1; x<columns-1; x++){
            int random = rand()%100;
            if(random <= 20){
                *(simulation + y*columns + x) = '#';
            }
            else{
                *(simulation + y*columns + x) = '.';
            }
        }
    }

    return simulation;
}
