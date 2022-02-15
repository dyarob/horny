#include <ncurses.h>
#include <stdlib.h> //malloc()

#define LVL_HEIGHT 30
#define LVL_WIDTH 90
#define SCREEN_WIDTH 45
#define START_POS_I 17
#define START_POS_Y 6

int	main(int ac, char **av){

FILE *f;
char **m;

//ncurses init
initscr();

//allocation
m=(char **)malloc(sizeof(char *)*LVL_HEIGHT);
for(char i=0; i<LVL_HEIGHT; i++) m[i]=(char *)malloc(LVL_WIDTH);

//loading lvl
f=fopen("lvl/testlvl", "r");
//for(char i=0; i<LVL_HEIGHT*LVL_WIDTH; i++) m[i/LVL_WIDTH][i%LVL_WIDTH]=fgetc(f);
for(char i=0; i<LVL_HEIGHT; i++){ for(char j=0; j<LVL_WIDTH; j++){
m[i][j]=fgetc(f);} fgetc(f);}
fclose(f);

//display
for(char i=0; i<LVL_HEIGHT; i++){
for(char j=0; j<SCREEN_WIDTH; j++){
addch(' '); addch(m[i][j]);}
addch('\n');}

getch();
endwin();
return 0;}
