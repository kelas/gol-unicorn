#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"pico/stdlib.h"
#include"libraries/pico_graphics/pico_graphics.hpp"
#include"cosmic_unicorn.hpp"
#include"c.h"

#define D       32
#define DD      D*D
#define MAX_GEN 1000    // generations to qualify for survival
#define SEED    0.1     // initial seed, percentage of DD
#define STEP    2       // random walk during seed stage
#define LAG     70      // ms between frames

using namespace pimoroni;CosmicUnicorn unicorn;PicoGraphics_PenRGB888 gfx(D, D, nullptr);
V handle_keys() {
 if(unicorn.is_pressed(unicorn.SWITCH_BRIGHTNESS_UP))unicorn.adjust_brightness(+0.01);
 if(unicorn.is_pressed(unicorn.SWITCH_BRIGHTNESS_DOWN))unicorn.adjust_brightness(-0.01);}

G B1[DD],B2[DD],B3[DD];G*front,*back,*prev;ZI gen_ctr=0,osc_ctr=0;

G col[8][3]={
    {154, 154, 174},
    {  0,   0, 255},
    {  0,   0, 200},
    {  0,   0, 160},
    {  0,   0, 140},
    {  0,   0,  90},
    {  0,   0,  60},
    {  0,   0,  0}};

G cmap[3][3]={{0,1,2},{0,2,1},{2,1,0}};G ci=1;G px,py;
#define Ca(n) (G)col[c][cmap[ci][n]]
V set(G x,G y,I c){gfx.set_pen(Ca(0),Ca(1),Ca(2));gfx.pixel(Point(x,y));}
V rst(){gfx.set_pen(0,0,0),gfx.clear();}V flush(){unicorn.update(&gfx);}
V draw_board(){N(D,Nj(D,set(i,j,front[D*i+j])))flush();}
V swap(){N(DD,B3[i]=front[i])if(front==B1){front=B2;back=B1;}else{front=B1;back=B2;}draw_board();}
G val(G x,G y){R front[((x%D)*D)+(y%D)];}I step(I s){I r=(rand()%(2*s+1))-s;P(!r,r+=step(1))R r;}
V seed(G*x,G*y){front[((*x%D)*D)+(*y%D)]=0;*y+=step(STEP),*x+=step(STEP);P(!val(*x,*y),seed(x,y))}
V rand_board(){ci=gen_ctr%3,gen_ctr=0,px=py=D/2;front=B1,back=B2;N(DD,front[i]=7)draw_board();
 N(DD*SEED,seed(&px,&py),set(px%=D,py%=D,0),flush(),sleep_ms(LAG/10))sleep_ms(1500);
 I c=0;N(DD,c+=!front[i])O("seed: %d\n",c);}
G neighbors(G x,G y){G r=0;N(3,Nj(3,if(i==1&&j==1)continue;if(!val(x+i-1,y+j-1))r++))R r;}
G is_extinct(){N(DD,P(front[i]!=7,0))R 1;}G is_stable(){N(DD,P(back[i]!=front[i],0))R 1;}
G is_oscillating(){N(DD,P(back[i]!=B3[i],0))P(++osc_ctr==10,osc_ctr=0,1)R 0;}
V win(S s){O("%s (%d)\n",s,gen_ctr),sleep_ms(1500),rand_board();}
V evolve(){
  P(is_extinct(),O("extinct (%d)\n",gen_ctr),rand_board())
  N(D,Nj(D,G neigh=neighbors(i,j),lvl=val(i,j);back[i*D+j]=(neigh==3||!lvl&&IN(2,neigh,3))?0:MIN(7,lvl+1);))
  P(is_stable()||gen_ctr==MAX_GEN,win((S)"stable"))P(is_oscillating(),win((S)"oscillator"))
  swap(),++gen_ctr;}

I main(){
 stdio_init_all(),unicorn.init(),unicorn.set_brightness(.7),sleep_ms(1500);
 O("\n---------------------");
 O("\nconway's game of life");
 O("\n---------------------\n");
 rst(),rand_board();W(1){handle_keys(),evolve(),sleep_ms(LAG);}R 0;}

//:~
