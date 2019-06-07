#include <stdio.h>
#include <stdlib.h>

void begin(int rows, int columns);
char *create(int rows, int columns);
double randomValue(double min, double max);
void display(int rows, int columns, char *simulation);
void firstDisplay(int rows, int columns, char *simulation);
int countNeighbors(int rows, int columns, int x, int y, char *simulation);
char *step(int rows, int columns, char *previousSimulation);

int main(){
    int rows, columns;
    char tmp1[25];
    char tmp2[25];
    char row[30];

    FILE *plik;
    plik = fopen("config.txt", "r");
    if(plik == NULL) return NULL;

    fgets(row, 30, plik);
    sscanf(row,"%s %d", tmp1, &rows);
    fgets(row, 30, plik);
    sscanf(row,"%s %d", tmp2, &columns);

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

int countNeighbors(int rows, int columns, int x, int y, char *simulation){
    int count = 0;
    int pivot = y*columns + x;

    int i,j;

    for(i=-1; i<=1; i++){
        for(j=-1; j<=1; j++){
            char c = *(simulation + pivot + (i*columns)+j);

            if(c == '#') count++;
        }
    }
    return count;
}

char *step(int rows, int columns, char *previousSimulation){
    char *steppedSimulation = calloc(rows*columns, sizeof(int));
    if(steppedSimulation == NULL) return NULL;

    int x,y;

    for(y=1; y<rows-1; y++){
        for(x=1; x<columns-1; x++){
            int live = countNeighbors(rows, columns, x, y, previousSimulation);
            char cell = *(previousSimulation + y*columns + x);
            if(cell == '#') live--;
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
    getch();

    while(1){
        char *newSim = step(rows, columns, simulation);
        if(newSim == NULL) return;

        free(simulation);
        simulation = newSim;
        display(rows, columns, simulation);
        getch();
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
