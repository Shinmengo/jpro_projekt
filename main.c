#include <stdio.h>
#include <stdlib.h>

int board(int x, int y){
    int i,j;

    for(i = 0; i < y; i++){
        for(j = 0; j < x; j++){
            printf("#");
        }
        printf("\n");
    }
}

int main()
{
    int x,y;
    printf("Prosze podac rozmiar planszy\n");
    scanf("%d %d", &x, &y);
    board(x,y);
    return 0;
}
