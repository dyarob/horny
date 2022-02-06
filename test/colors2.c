#include <ncurses.h>
int	main(int ac, char **av){
initscr();
start_color();

for(int i=0; i<1000; i++){
	if(i%24==0) printw("\n");
	init_pair(i, i%255, i/100);
	attron(COLOR_PAIR(i));
	printw("<3");}

getch();
endwin();
return 0;}
