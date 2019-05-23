#include <stdio.h>
#include <stdlib.h>

void board(int x, int y, char plansza[x][y]){
    int i,j;
    for(i = 0; i < y; i++){
        for(j = 0; j < x; j++){
            printf("%c", plansza[i][j]);
        }
        printf("\n");
    }
}

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
