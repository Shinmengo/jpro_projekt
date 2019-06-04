#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void begin(int rows, int columns);
char *create(int rows, int columns);
double randomValue(double min, double max);
void display(int rows, int columns, char *simulation);
int countNeighbors(int rows, int columns, int x, int y, char *simulation);
char *step(int rows, int columns, char *previousSimulation);

int main()
{
	int rows, columns;
	printf("Podaj ilosc wierszy i kolumn\n");
	scanf("%d %d", &rows, &columns);
	printf("\n\n");
	if(rows <= 0){
		printf("Liczba wierszy musi byc wieksza od 0!\n");
		return -1;
	}
	rows+=2;

	if(columns <= 0){
	printf("Liczba kolumn musi byc wieksza od 0!\n");
	return -1;
	}
	columns+=2;

	begin(rows, columns);
}

void display(int rows, int columns, char *simulation){
	int x,y;
	for(y=1;y<=rows-1;y++){
		for(x=1;x<=columns-1;x++){
			printf("%c", *(simulation + y*columns + x));
		}
		printf("\n");
	}
}

int countNeighbors(int rows, int columns, int x, int y, char *simulation){
	int count = 0;
	int pivot = y*columns + x;

	int i,j;
	for(i=-1;i<=1;i++){
		for(j=-1;j<=1;j++){
			char c = *(simulation + pivot + (-1)*(columns-1));
			if(c == '#') count++;
		}
	}
	return count;
}

char *step(int rows, int columns, char *previousSimulation){
	char *steppedSimulation = calloc(rows*columns, sizeof(int));
	if(steppedSimulation == NULL) return NULL;
	int x,y;
	
	for(y=1;y<=rows-1;y++){
		for(x=1;x<=columns-1;x++){
			int live = countNeighbors(rows, columns, x, y, previousSimulation);
			char cell = *(previousSimulation + y*columns + x);
			if(cell == '#') live--;
			*(steppedSimulation + y*columns + x) == cell;
			if(live < 2) *(previousSimulation + y*columns + x) = '.';
			else if((live == 2 || live == 3) && cell == '#') *(previousSimulation + y*columns + x) == '#';
			else if(live > 3 && cell == '#') *(previousSimulation + y*columns + x) == '.';
			else if(live == 3 && cell == '.') *(previousSimulation + y*columns + x) == '#';
		}
	}
	return steppedSimulation;
}

void begin(int rows, int columns){
	char *simulation = create(rows, columns);
	if(simulation == NULL) return;
	display(rows, columns, simulation);
	
	while(1){
		char *newSim = step(rows, columns, simulation);
		if(newSim == NULL) return;
		free(simulation);
		simulation = newSim;
		printf("\n\n\n\n");
		display(rows, columns, simulation);
		Sleep(1500); //windows
		//usleep(15000000); //linux
	}
}

double randomValue(double min, double max){
	return ((double)rand()/RAND_MAX)*(max-min)+min;
}

char *create(int rows, int columns){
	char *simulation = (char*)calloc(rows*columns, sizeof(char));
	if(simulation == NULL) return;
	int x,y;
	for(y=1;y<rows-1;y++){
		for(x=1;x<columns-1;x++){
			if(randomValue(0.1, 1.1) <= 0.35){
				*(simulation + y*columns + x) = '#';
			}
			else{
				*(simulation + y*columns + x) = '.';
			}
		}
	}

	return simulation;
}
