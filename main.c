#include <stdio.h>
#include <stdlib.h>

void begin(int rows, int columns);

int main()
{
    int x,y,ilosc,xStart,yStart,i,n,m;
    printf("Prosze podac rozmiar planszy\n");
    scanf("%d %d", &x, &y);
    char plansza[x][y];

    for(n = 0; n < y ; n++){
        for(m = 0; m < x; m++){
            plansza[n][m] = '#';
            printf("%c", plansza[n][m]);
        }
        printf("\n");
    }

    printf("Ile komorek poczatkowy chcesz podac?\n");
    scanf("%d", &ilosc);
        for(i = 0; i < ilosc; i++){
            printf("Prosze wybrac pola startowe komorki %d (x,y)\n", i+1);
            scanf("%d %d", &xStart, &yStart);
            plansza[xStart-1][yStart-1] = '*';
        }

    board(x, y, plansza);
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
