#include <stdio.h> //putchar()
#include <stdlib.h> //rand(), srand()
#include <time.h> //time()
int	main(int ac, char **av){
char	**m;

srand((unsigned)time(0));

m = (char **)malloc(sizeof(char *)*   5   );
for(char i=0; i<5; i++) m[i] = (char *)malloc(   15   );

for(char i=0; i<5; i++) for(char j=0; j<15; j++){
m[i][j] = rand()%10;}

for(char i=0; i<5; i++){ for(char j=0; j<15; j++){
putchar(m[i][j]+'0'); putchar(' ');} putchar('\n');}

return 0;}
