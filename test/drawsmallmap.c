#include <stdio.h> //putchar()
#include <stdlib.h> //rand(), srand()
#include <time.h> //time()
#include <ncurses.h>

#define DSM_HEIGHT 30
#define DSM_WIDTH 90

int	main(int ac, char **av){
char	**m;

srand((unsigned)time(0));
initscr(); start_color();
init_pair(1, COLOR_BLACK, 213); //pink
init_pair(2, COLOR_BLACK, 99); //purple
init_pair(3, COLOR_BLACK, 177); //pink in-between
init_pair(4, COLOR_BLACK, 135); //purple in-between

//allocation
m = (char **)malloc(sizeof(char *)*DSM_HEIGHT);
for(char i=0; i<DSM_HEIGHT; i++) m[i] = (char *)malloc(DSM_WIDTH);

//generation
for(char i=0; i<DSM_HEIGHT; i++) for(char j=0; j<DSM_WIDTH; j++){
m[i][j] = rand()%10;}

for(char i=0; i<DSM_HEIGHT; i++){ for(char j=0; j<DSM_WIDTH; j++){
if(m[i][j]==9)
switch(i){
case 0:
	if(m[i+1][j]!=9)
	switch(j){
	case 0: if(m[i][j+1]!=9) m[i][j]=8; break;
	case DSM_WIDTH-1: if(m[i][j-1]!=9) m[i][j]=8; break;
	default: if(m[i][j+1]!=9 && m[i][j-1]!=9) m[i][j]=8; break;}
	break;
case DSM_HEIGHT-1:
	if(m[i-1][j]!=9)
	switch(j){
	case 0: if(m[i][j+1]!=9) m[i][j]=8; break;
	case DSM_WIDTH-1: if(m[i][j-1]!=9) m[i][j]=8; break;
	default: if(m[i][j+1]!=9 && m[i][j-1]!=9) m[i][j]=8; break;}
	break;
default:
	if(m[i+1][j]!=9 && m[i-1][j]!=9)
	switch(j){
	case 0: if(m[i][j+1]!=9) m[i][j]=8; break;
	case DSM_WIDTH-1: if(m[i][j-1]!=9) m[i][j]=8; break;
	default: if(m[i][j+1]!=9 && m[i][j-1]!=9) m[i][j]=8; break;}
	break;
}}}

//display
for(char i=0; i<DSM_HEIGHT; i++){ for(char j=0; j<DSM_WIDTH; j++){
addch(m[i][j]+'0');} addch('\n');}

for(char i=0; i<DSM_HEIGHT; i++){ for(char j=0; j<DSM_WIDTH; j++){
if(m[i][j]==9) attron(COLOR_PAIR(1));
else if(m[i][j]==8) attron(COLOR_PAIR(3));
else if(m[i][j]==7 || m[i][j]==6) attron(COLOR_PAIR(4));
else attron(COLOR_PAIR(2));
addch(' ');} addch('\n');}

getch();
endwin();
return 0;}
