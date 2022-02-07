#include <stdio.h> //putchar()
#include <stdlib.h> //rand(), srand()
#include <time.h> //time()
#include <ncurses.h>

#define DSM_HEIGHT 5
#define DSM_WIDTH 15

int	main(int ac, char **av){
char	**m;

srand((unsigned)time(0));
initscr(); start_color();
init_pair(1, COLOR_BLACK, 213); //pink
init_pair(2, COLOR_BLACK, 99); //purple

//allocation
m = (char **)malloc(sizeof(char *)*DSM_HEIGHT);
for(char i=0; i<DSM_HEIGHT; i++) m[i] = (char *)malloc(DSM_WIDTH);

//generation
for(char i=0; i<DSM_HEIGHT; i++) for(char j=0; j<DSM_WIDTH; j++){
m[i][j] = rand()%10;}

//display
for(char i=0; i<DSM_HEIGHT; i++){ for(char j=0; j<DSM_WIDTH; j++){
addch(m[i][j]+'0');} addch('\n');}

for(char i=0; i<DSM_HEIGHT; i++){ for(char j=0; j<DSM_WIDTH; j++){
attron(COLOR_PAIR((m[i][j]>=5?1:2))); addch(' ');} addch('\n');}

getch();
endwin();
return 0;}
