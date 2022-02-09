#include <stdio.h> //putchar()
#include <stdlib.h> //rand(), srand()
#include <time.h> //time()
#include <ncurses.h>
#include <math.h> //sqrt()

#include "group.h"

#define DSM_HEIGHT 30
#define DSM_WIDTH 45

void	check_cell(char **m, char i, char j, group **g, char x);

int	main(int ac, char **av){
char	**m;
group	*g;

srand((unsigned)time(0));
initscr(); start_color();
init_pair(1, COLOR_BLACK, 213); //pink
init_pair(2, COLOR_BLACK, 99); //purple
init_pair(3, COLOR_BLACK, 177); //pink in-between
init_pair(4, COLOR_BLACK, 135); //purple in-between

//allocation
m = (char **)malloc(sizeof(char *)*DSM_HEIGHT);
for(char i=0; i<DSM_HEIGHT; i++) m[i] = (char *)malloc(DSM_WIDTH);
g = NULL;

//random numbers generation
for(char i=0; i<DSM_HEIGHT; i++){ for(char j=0; j<DSM_WIDTH; j++){
m[i][j] = rand()%10;}}

//step 1: eliminate isolated 9
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

//step 2: eliminate isolated 8
for(char i=0; i<DSM_HEIGHT; i++){ for(char j=0; j<DSM_WIDTH; j++){
if(m[i][j]==8)
switch(i){
case 0:
	if(m[i+1][j]<8)
	switch(j){
	case 0: if(m[i][j+1]<8) m[i][j]=0; break;
	case DSM_WIDTH-1: if(m[i][j-1]<8) m[i][j]=0; break;
	default: if(m[i][j+1]<8 && m[i][j-1]<8) m[i][j]=0; break;}
	break;
case DSM_HEIGHT-1:
	if(m[i-1][j]<8)
	switch(j){
	case 0: if(m[i][j+1]<8) m[i][j]=0; break;
	case DSM_WIDTH-1: if(m[i][j-1]<8) m[i][j]=0; break;
	default: if(m[i][j+1]<8 && m[i][j-1]<8) m[i][j]=0; break;}
	break;
default:
	if(m[i+1][j]<8 && m[i-1][j]<8)
	switch(j){
	case 0: if(m[i][j+1]<8) m[i][j]=0; break;
	case DSM_WIDTH-1: if(m[i][j-1]<8) m[i][j]=0; break;
	default: if(m[i][j+1]<8 && m[i][j-1]<8) m[i][j]=0; break;}
	break;
}}}

//step 3: add 8 around 9
for(char i=0; i<DSM_HEIGHT; i++){ for(char j=0; j<DSM_WIDTH; j++){
if(m[i][j]==9)
switch(i){
case 0:
	if(m[i+1][j]<8) m[i+1][j]=8;
	switch(j){
	case 0: if(m[i][j+1]<8) m[i][j+1]=8; break;
	case DSM_WIDTH-1: if(m[i][j-1]<8) m[i][j-1]=8; break;
	default: if(m[i][j+1]<8) m[i][j+1]=8;
		 if(m[i][j-1]<8) m[i][j-1]=8; break;}
	break;
case DSM_HEIGHT-1:
	if(m[i-1][j]<8) m[i-1][j]=8;
	switch(j){
	case 0: if(m[i][j+1]<8) m[i][j+1]=8; break;
	case DSM_WIDTH-1: if(m[i][j-1]<8) m[i][j-1]=8; break;
	default: if(m[i][j+1]<8) m[i][j+1]=8;
		 if(m[i][j-1]<8) m[i][j-1]=8; break;}
	break;
default:
	if(m[i+1][j]<8) m[i+1][j]=8;
	if(m[i-1][j]<8) m[i-1][j]=8;
	switch(j){
	case 0: if(m[i][j+1]<8) m[i][j+1]=8; break;
	case DSM_WIDTH-1: if(m[i][j-1]<8) m[i][j-1]=8; break;
	default: if(m[i][j+1]<8) m[i][j+1]=8;
		 if(m[i][j-1]<8) m[i][j-1]=8; break;}
	break;
}}}

//step 4: connect 8 groups
//creating groups
for(char i=0; i<DSM_HEIGHT; i++){ for(char j=0; j<DSM_WIDTH; j++){
check_cell(m, i, j, &g, 0);}}

//step 4b: remove smallest groups
for(group *h=g; h->next; h=h->next){
if(h->next->weight<=3){
for(cell *c=h->next->list; c; c=c->next){ m[c->i][c->j]=0;}
h->next=h->next->next;}}

//calculating centers (rounded)
for(group *h=g; h; h=h->next){ int i=0; int j=0;
for(cell *c=h->list; c; c=c->next){ i+=c->i; j+=c->j;}
h->c.i=(i+h->weight/2)/h->weight; h->c.j=(j+h->weight/2)/h->weight;}
//calculating closest group
for(group *gg=g; gg; gg=gg->next){ group *hh=NULL; float f, ff=200;
for(group *gh=g; gh; gh=gh->next){
if(gh!=gg){
f=sqrt((gg->c.i-gh->c.i)*(gg->c.i-gh->c.i)+(gg->c.j-gh->c.j)*(gg->c.j-gh->c.j));
if(f<ff){ ff=f; hh=gh;}}//debug: printw("ff= %f  ", ff);
}
//calculating increments
float inc, jnc;
if(!(hh->c.j-gg->c.j)) if(hh->c.i-gg->c.i<0) inc=-1; else inc=1;
else inc=(float)(hh->c.i-gg->c.i)/abs(hh->c.j-gg->c.j);
if(!(hh->c.i-gg->c.i)) if(hh->c.j-gg->c.j<0) jnc=-1; else jnc=1;
else jnc=(float)(hh->c.j-gg->c.j)/abs(hh->c.i-gg->c.i);
//debug: printw("inc= %f and jnc= %f.  ", inc, jnc);
if(inc>1) inc=1; else if(inc<-1) inc=-1;
if(jnc>1) jnc=1; else if(jnc<-1) jnc=-1;
//drawing connections
for(char i=1; hh->c.i-gg->c.i-i*inc>0 || hh->c.j-gg->c.j-i*jnc>0; i++){
m[abs((int)(gg->c.i+i*inc))][abs((int)(gg->c.j+i*jnc))]=8;}}

//step 5: add 7 around 8
for(char i=0; i<DSM_HEIGHT; i++){ for(char j=0; j<DSM_WIDTH; j++){
if(m[i][j]==8)
switch(i){
case 0:
	if(m[i+1][j]<7) m[i+1][j]=7;
	switch(j){
	case 0: if(m[i][j+1]<7) m[i][j+1]=7; break;
	case DSM_WIDTH-1: if(m[i][j-1]<7) m[i][j-1]=7; break;
	default: if(m[i][j+1]<7) m[i][j+1]=7;
		 if(m[i][j-1]<7) m[i][j-1]=7; break;}
	break;
case DSM_HEIGHT-1:
	if(m[i-1][j]<7) m[i-1][j]=7;
	switch(j){
	case 0: if(m[i][j+1]<7) m[i][j+1]=7; break;
	case DSM_WIDTH-1: if(m[i][j-1]<7) m[i][j-1]=7; break;
	default: if(m[i][j+1]<7) m[i][j+1]=7;
		 if(m[i][j-1]<7) m[i][j-1]=7; break;}
	break;
default:
	if(m[i+1][j]<7) m[i+1][j]=7;
	if(m[i-1][j]<7) m[i-1][j]=7;
	switch(j){
	case 0: if(m[i][j+1]<7) m[i][j+1]=7; break;
	case DSM_WIDTH-1: if(m[i][j-1]<7) m[i][j-1]=7; break;
	default: if(m[i][j+1]<7) m[i][j+1]=7;
		 if(m[i][j-1]<7) m[i][j-1]=7; break;}
	break;
}}}

//display
for(char i=0; i<DSM_HEIGHT; i++){ for(char j=0; j<DSM_WIDTH; j++){
addch(m[i][j]+'0'); addch(' ');} addch('\n');}

for(char i=0; i<DSM_HEIGHT; i++){ for(char j=0; j<DSM_WIDTH; j++){
if(m[i][j]==9) attron(COLOR_PAIR(1));
else if(m[i][j]==8) attron(COLOR_PAIR(3));
else if(m[i][j]==7 || m[i][j]==6) attron(COLOR_PAIR(4));
else attron(COLOR_PAIR(2));
addch(' '); addch(' ');} addch('\n');}

printw("\ngroup weights:\n");
for(group *h=g; h; h=h->next){
printw("%d ", h->weight);}

//print group center (debug)
for(group *h=g; h; h=h->next){
mvaddch(DSM_HEIGHT+h->c.i, h->c.j*2, 'o');}

getch();
endwin();
return 0;}


void	check_cell(char **m, char i, char j, group **g, char x){
cell	*new;
group	*gg;
group	*h;

if(m[i][j]<8) return;
//if cell in a group return
for(h=*g; h; h=h->next){ for(cell *c=h->list; c!=NULL; c=c->next){
if(c->i==i && c->j==j) return;}}
//else if it's a new group
if(!x){ gg=(group *)malloc(sizeof(group));
gg->weight=0; gg->list=NULL; gg->next=NULL;
if(!*g) *g=gg; else{
for(h=*g; h->next; h=h->next){} h->next=gg;}} else gg=*g;
//add cell to group and increment group weight
new=(cell *)malloc(sizeof(cell));
new->i=i; new->j=j; new->next=gg->list;
gg->list=new;
gg->weight++;

if(i<DSM_HEIGHT-1) check_cell(m, i+1, j, &gg, 1);
if(i>0) check_cell(m, i-1, j, &gg, 1);
if(j<DSM_WIDTH-1) check_cell(m, i, j+1, &gg, 1);
if(j>0) check_cell(m, i, j-1, &gg, 1);
return;}
