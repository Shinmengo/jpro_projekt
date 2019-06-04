#include <stdio.h>
#include <stdlib.h>

void begin(int rows, int columns);
char *create(int rows, int columns);
double randomValue(double min, double max);

int main()
{
	int rows, columns;
	printf("Podaj ilosc wierszy i kolumn\n");
	scanf("%d %d", &rows, &columns);
	if(rows <= 0){
		printf("Liczba wierszy musi byc wieksza od 0!\m");
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

void begin(int rows, int columns){
	char *simulation = create(rows, columns);
	if(simulation == NULL) return;
	display(rows, columns, simulation);
	
	while(1){
		char *newSim = step(rows, columns, simulation);
		if(newSim == NULL) return;
		free(simulation);
		simulation = newSim;
		display(rows, columns, simulation);
		Sleep(1500); //windows
		//usleep(15000000); //linux
	}
}

double randomValue(double min, double max){
	return ((double)rand()/RAND_MAX)*(max-min)+min);
}

char *create(int rows, int columns){
	char *simulation = (char*)calloc(rows*columns, sizeof(char));
	if(simulation == NULL) return;
	int x,y;
	for(y=1; y<rows-1;y++){
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
