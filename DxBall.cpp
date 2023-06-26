/*
       NAME:Mehreen Tabassum Maliha
 */
# include "iGraphics.h"
# include "gl.h"
 #include<math.h>
#include <windows.h>
#include<mmsystem.h>
#include<string.h>
#include<stdlib.h>


 #define TotalBricks 100
#define screenWidth 1300
#define screenHeight 700
#define yMargin 50
#define thetadefine 0
#define PI 3.14159265


///colours
int r=255,g=255,b=255;
///Ball properties
int ball_x=(int)screenWidth/2;
int ball_y=yMargin;
int whball=1;
int radius=10;
int v=10;
int theta=30;
int dx=(int) v*cos(theta*PI/180);
int dy=(int) v*sin(theta*PI/180);

int life[4]={1,1,1,0};
int lives=3;
int lives1=4;
///Board properties

int board_x=ball_x-100;
int board_y=ball_y-30;
int dxboard=200;
int  dyboard=30;

int start=0;
int state=0;
int m=0;
int n=1;
///Bricks
typedef struct
{
    int x;
    int y;
    int dx=100;
    int dy=20;
    int show=1;
    int red;
    int green;
    int blue;
}  BrickStructure;

//sound
bool music1=true;
 int e_brick=TotalBricks;///existing bricks

 BrickStructure bricks[TotalBricks];
void ballChange();
void reStart();
void makeBricks();
void fireball();
void new_game();
///Main Page
int pageshow=1;
char Score[20]="00";
int scoreint=0;

char timer[20]="00";
int time_s=0;
int time_m=0;
void time();
///home page
typedef struct
{
    int x;
    int y;
} cordinate;
cordinate co[5];
char button[10][15]={"resume.BMP","play.BMP","score.BMP","HELP.BMP","exit.BMP"};
char homemenu[20]="homemenu.BMP";
int gameshow=-1;
char score[20]="brick.BMP";
int gameover;
int winpage;

///extra life
int life_x=460,life_y=400,l_show=0;//(showing image for extra life)//
int p;//if p=1, extra life bmp file collides with board

void lifex();

///immediate death
int death_x=940,death_y=400;
int death_show,die;//(die=1 if over bmp file collides with board)

///wider paddle
int paddle_x=590,paddle_y=440,paddleshow,wide=0;
void paddle();
 ///fireball
int fire_x=710,fire_y=460,fireshow,fr=0;
int redball=0;


///saving name and score
typedef struct
{
    char name[20];
    int scr;
} player;

player pl[10];
char sco1[10], sco2[10], sco3[10], sco4[10], sco5[10], sco6[10], sco7[10], sco8[10], sco9[10], sco10[10];
char str[100];
int len;

int mode;///for showing name in winpage or gameover page
void iDraw()
{
       iClear();
          if(state==1)
          {
               iShowBMP(0,0,"background.BMP");

       iSetColor(r,g,b);
       if(whball)
       {
             iFilledCircle(ball_x,ball_y,radius,1000);
       }
      for(int i=0;i<4;i++)
      {
           if(life[0])
       {
            iFilledCircle(1200,680,radius,1000);
       }
        if(life[1])
        {
             iFilledCircle(1225,680,radius,1000);
        }
        if(life[2])
        {
             iFilledCircle(1250,680,radius,1000);
        }
        if(life[3])
        {
              iFilledCircle(1275,680,radius,1000);
        }
      }
      if(p==1)
      {
            life[3]=1;
      }
        int i;
        for(i=0;i<TotalBricks;i++)
         {
             if(bricks[i].show)
             {
                    iSetColor(bricks[i].red,bricks[i].green,bricks[i].blue);
                    iFilledRectangle(bricks[i].x,bricks[i].y,bricks[i].dx,bricks[i].dy);
             }
             if(bricks[3].show==0)
             {
                 l_show=1;
             }
             if(bricks[7].show==0)
             {
                 death_show=1;
             }
             if(bricks[20].show==0)
             {
                 paddleshow=1;
             }
             if(bricks[29].show==0)
             {
                 fireshow=1;
             }
         }
         sprintf(Score,"SCORE : %d",scoreint);
         iSetColor(255,255,255);
         iText(50,50,Score,GLUT_BITMAP_TIMES_ROMAN_24);
         sprintf(timer,"TIMER :%d : %d",time_m, time_s);
         iSetColor(255,255,255);
         iText(1130,50,timer,GLUT_BITMAP_TIMES_ROMAN_24);
         if(l_show==1)
         {
                iShowBMP(life_x,life_y,"extralife.BMP");
         }
         if(death_show==1)
         {
             iShowBMP(death_x,death_y,"over.BMP");
         }
         if(paddleshow==1)
         {
             iShowBMP(paddle_x,paddle_y,"widepaddle.BMP");
         }
         if(fireshow==1)
         {
             iShowBMP(fire_x,fire_y,"FIREBALL.BMP");
         }
         if(!wide)
         {
             iShowBMP(board_x,board_y,"board.BMP");
         }
         else
         {
                iShowBMP(board_x,board_y,"board2.BMP");
         }
         if(redball)
         {
              iSetColor(255,0,0);
             iFilledCircle(ball_x,ball_y,radius,1000);
         }
         if(fr)
         {
             whball=0;
             redball=1;
         }


          if(gameover)
        {
              iShowBMP(0,0,"Gameover.BMP");
               sprintf(Score,"SCORE : %d",scoreint);
               iSetColor(255,255,255);
              iText(500,350,Score,GLUT_BITMAP_TIMES_ROMAN_24);

              iSetColor(0,0,0);
              iText(400,300,"ENTER YOUR NAME :",GLUT_BITMAP_TIMES_ROMAN_24);

               iSetColor(255,255,255);
             iRectangle(400,250,300,40);
        }
         if(winpage)
         {
             iShowBMP(0,0,"WINPAGE.BMP");
              sprintf(Score,"SCORE : %d",scoreint);
              iSetColor(255,255,255);
             iText(500,200,Score,GLUT_BITMAP_TIMES_ROMAN_24);
               iSetColor(0,0,0);
              iText(400,150,"ENTER YOUR NAME :",GLUT_BITMAP_TIMES_ROMAN_24);

               iSetColor(255,255,255);
             iRectangle(400,100,300,40);

         }
          if(mode==1)
          {
                 iSetColor(255,255,255);
                 iText(405,270,str,GLUT_BITMAP_TIMES_ROMAN_24);
          }
          if(mode==2)
          {
                 iSetColor(255,255,255);
                 iText(405,120,str,GLUT_BITMAP_TIMES_ROMAN_24);
          }

           if(mode==3)
           {
               strcpy(pl[0].name,"unknown");
              strcpy(pl[1].name,"unknown");
              strcpy(pl[2].name,"unknown");
              strcpy(pl[3].name,"unknown");
              strcpy(pl[4].name,"unknown");
              strcpy(pl[5].name,"unknown");
              strcpy(pl[6].name,"unknown");
              strcpy(pl[7].name,"unknown");
              strcpy(pl[8].name,"unknown");
              strcpy(pl[9].name,"unknown");

              FILE *fh;
              fh=fopen("high.txt","rb");

              int j;
              for(j=0;j<10;j++)
              {
                   fread(&pl[j],sizeof(pl[0]),1,fh);
              }
              fclose(fh);
              if(scoreint>pl[9].scr && scoreint<pl[8].scr )

            {

                pl[9].scr=scoreint;
                strcpy(pl[9].name,str);
                    fh=fopen("high.txt","wb");

                for(j=0; j<10; j++)
                {
                    fwrite(&pl[j],sizeof(pl[j]),1,fh);
                }
                fclose(fh);
            }
            if( scoreint>pl[8].scr && scoreint<pl[7].scr )
            {
                pl[9].scr=pl[8].scr;
                strcpy(pl[9].name,pl[8].name);

                pl[8].scr=scoreint;
                strcpy(pl[8].name,str);


                    fh=fopen("high.txt","wb");

                for(j=0; j<10; j++)
                {
                    fwrite(&pl[j],sizeof(pl[j]),1,fh);
                }
                fclose(fh);
            }

            if(scoreint>pl[7].scr&&scoreint<pl[6].scr )
            {


                int i;
                for(i=9; i>7; i--)
                {
                    pl[i].scr=pl[i-1].scr;
                    strcpy(pl[i].name,pl[i-1].name);


                }
                pl[7].scr=scoreint;
                strcpy(pl[7].name,str);
                    fh=fopen("high.txt","wb");



                for(j=0; j<10; j++)
                {
                    fwrite(&pl[j],sizeof(pl[j]),1,fh);

                }
                fclose(fh);
            }

            if(scoreint>pl[6].scr && scoreint<pl[5].scr)
            {


                int i;
                for(i=9; i>6; i--)
                {
                    pl[i].scr=pl[i-1].scr;
                    strcpy(pl[i].name,pl[i-1].name);
                }
                pl[6].scr=scoreint;
                strcpy(pl[6].name,str);

                    fh=fopen("high.txt","wb");

                for(j=0; j<10; j++)
                {
                    fwrite(&pl[j],sizeof(pl[j]),1,fh);

                }
                fclose(fh);
            }

           if(scoreint>pl[5].scr&&scoreint<pl[4].scr)
            {

                int i;
                for(i=9; i>5; i--)
                {
                    pl[i].scr=pl[i-1].scr;
                    strcpy(pl[i].name,pl[i-1].name);


                }

                pl[5].scr=scoreint;
                strcpy(pl[5].name,str);
                    fh=fopen("high.txt","wb");

                for(j=0; j<10; j++)
                {
                    fwrite(&pl[j],sizeof(pl[j]),1,fh);

                }
                fclose(fh);
            }

            if(scoreint>pl[4].scr&&scoreint<pl[3].scr)
            {

                int i;
                for(i=9; i>4; i--)
                {
                    pl[i].scr=pl[i-1].scr;
                    strcpy(pl[i].name,pl[i-1].name);


                }

                pl[4].scr=scoreint;
                strcpy(pl[4].name,str);
                    fh=fopen("high.txt","wb");

                for(j=0; j<10; j++)
                {
                    fwrite(&pl[j],sizeof(pl[j]),1,fh);

                }
                fclose(fh);
            }

             if(scoreint>pl[3].scr&&scoreint<pl[2].scr)
            {

                int i;
                for(i=9; i>3; i--)
                {
                    pl[i].scr=pl[i-1].scr;
                    strcpy(pl[i].name,pl[i-1].name);


                }

                pl[3].scr=scoreint;
                strcpy(pl[3].name,str);
                    fh=fopen("high.txt","wb");

                for(j=0; j<10; j++)
                {
                    fwrite(&pl[j],sizeof(pl[j]),1,fh);

                }
                fclose(fh);
            }

             if(scoreint>pl[2].scr&&scoreint<pl[1].scr)
            {

                int i;
                for(i=9; i>2; i--)
                {
                    pl[i].scr=pl[i-1].scr;
                    strcpy(pl[i].name,pl[i-1].name);


                }

                pl[2].scr=scoreint;
                strcpy(pl[2].name,str);
                    fh=fopen("high.txt","wb");

                for(j=0; j<10; j++)
                {
                    fwrite(&pl[j],sizeof(pl[j]),1,fh);

                }
                fclose(fh);
            }

             if(scoreint>pl[1].scr&&scoreint<pl[0].scr)
            {

                int i;
                for(i=9; i>1; i--)
                {
                    pl[i].scr=pl[i-1].scr;
                    strcpy(pl[i].name,pl[i-1].name);


                }

                pl[1].scr=scoreint;
                strcpy(pl[1].name,str);
                    fh=fopen("high.txt","wb");

                for(j=0; j<10; j++)
                {
                    fwrite(&pl[j],sizeof(pl[j]),1,fh);

                }
                fclose(fh);
            }

            if(scoreint>pl[0].scr)
            {

                int i;
                for(i=9; i>0; i--)
                {
                    pl[i].scr=pl[i-1].scr;
                    strcpy(pl[i].name,pl[i-1].name);


                }

                pl[0].scr=scoreint;
                strcpy(pl[0].name,str);
                    fh=fopen("high.txt","wb");

                for(j=0; j<10; j++)
                {
                    fwrite(&pl[j],sizeof(pl[j]),1,fh);

                }
                fclose(fh);
            }
           }

         if(life[2]==0 && p==0)
         {
            gameover=1;
         }
         else if(lives1==0 && p==1)
         {
              gameover=1;
         }
         else  if(die==1)
         {
              gameover=1;
              iPauseTimer(0);
         }

          }

          if(gameshow==-1)
          {
              if(state==0 ){
                     iShowBMP(0,0,homemenu);
                    for(int i=0;i<5;i++)
                     {
                          iShowBMP2(co[i].x,co[i].y,button[i],0);
                     }
              }
          }

          else if(gameshow==0)
          {
                state=1;
          }
          else if(gameshow==1)
          {
                 state=1;
          }
          else if(gameshow==2)
          {
                int m=0;
              iShowBMP(0,0,"brick.BMP");
                  FILE *fs;
                  fs=fopen("high.txt","rb");
                  int k;

                  for(k=0;k<10;k++)
                  {
                        fread(&pl[k],sizeof(pl[0]),1,fs);
                  }
                  fclose(fs);
                  iSetColor(255,255,255);
                  iText(200,620,"NAME",GLUT_BITMAP_TIMES_ROMAN_24);
                  iText(200,580,pl[0].name,GLUT_BITMAP_TIMES_ROMAN_24);
                  iText(200,540,pl[1].name,GLUT_BITMAP_TIMES_ROMAN_24);
                  iText(200,500,pl[2].name,GLUT_BITMAP_TIMES_ROMAN_24);
                  iText(200,460,pl[3].name,GLUT_BITMAP_TIMES_ROMAN_24);
                  iText(200,420,pl[4].name,GLUT_BITMAP_TIMES_ROMAN_24);
                  iText(200,380,pl[5].name,GLUT_BITMAP_TIMES_ROMAN_24);
                  iText(200,340,pl[6].name,GLUT_BITMAP_TIMES_ROMAN_24);
                  iText(200,300,pl[7].name,GLUT_BITMAP_TIMES_ROMAN_24);
                   iText(200,260,pl[8].name,GLUT_BITMAP_TIMES_ROMAN_24);
                  iText(200,220,pl[9].name,GLUT_BITMAP_TIMES_ROMAN_24);

                 sprintf(sco1,"%d",pl[0].scr);
                 sprintf(sco2,"%d",pl[1].scr);
                 sprintf(sco3,"%d",pl[2].scr);
                 sprintf(sco4,"%d",pl[3].scr);
                 sprintf(sco5,"%d",pl[4].scr);
                 sprintf(sco6,"%d",pl[5].scr);
                 sprintf(sco7,"%d",pl[6].scr);
                 sprintf(sco8,"%d",pl[7].scr);
                 sprintf(sco9,"%d",pl[8].scr);
                 sprintf(sco10,"%d",pl[9].scr);



                 iSetColor(255,255,255);
                  iText(460,620,"SCORE",GLUT_BITMAP_TIMES_ROMAN_24);
                 iText(460,580,sco1,GLUT_BITMAP_TIMES_ROMAN_24);
                 iText(460,540,sco2,GLUT_BITMAP_TIMES_ROMAN_24);
                 iText(460,500,sco3,GLUT_BITMAP_TIMES_ROMAN_24);
                iText(460,460,sco4,GLUT_BITMAP_TIMES_ROMAN_24);
                iText(460,420,sco5,GLUT_BITMAP_TIMES_ROMAN_24);
                iText(460,380,sco6,GLUT_BITMAP_TIMES_ROMAN_24);
                iText(460,340,sco7,GLUT_BITMAP_TIMES_ROMAN_24);
                iText(460,300,sco8,GLUT_BITMAP_TIMES_ROMAN_24);
               iText(460,260,sco9,GLUT_BITMAP_TIMES_ROMAN_24);
               iText(460,220,sco10,GLUT_BITMAP_TIMES_ROMAN_24);

          }
          else if(gameshow==3)
          {
              iShowBMP(0,0,"helppage.BMP");
          }
         else if(gameshow==4)
         {
            iShowBMP(0,0,"background.BMP");
            iSetColor(255,255,255);
            iRectangle(200,200,500,300);
            iSetColor(255,255,255);
            iText(350,415,"Do you want to exit?",GLUT_BITMAP_TIMES_ROMAN_24);
            iSetColor(255,255,255);
            iRectangle(365,350,46,46);
            iSetColor(255,255,255);
            iText(365,370,"YES",GLUT_BITMAP_TIMES_ROMAN_24);
            iSetColor(255,255,255);
            iRectangle(436,350,46,46);
            iSetColor(255,255,255);
            iText(436,370,"NO",GLUT_BITMAP_TIMES_ROMAN_24);
         }
         if(pageshow)
         {
             iShowBMP(0,0,"Main.BMP");
         }
}

void iMouseMove(int mx, int my)
{
       if(state==1)
       {
           if(mx>=55 && mx<=screenWidth-100)
           {
               board_x=mx-50;
               if(!start)
           {
               ball_x=mx;
           }
           }

       }
}
void iMouse(int button, int state, int mx, int my)
{
         if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
         {
            for(int i=0;i<5;i++)
            {
                 if(mx>=co[i].x && mx<=co[i].x+200 && my>=co[i].y && my<=co[i].y+90)
             {
                 gameshow=i;
             }
            }
          if(mx>=co[0].x && mx<=co[0].x+200 && my>=co[0].y && my<=co[0].y+90)
          {
               if(state==0)
               {
                   state=1;
                   iResumeTimer(0);
                   reStart();
               }
          }
          if(gameshow==4)
          {
              if(mx>=365 &&mx<=411 && my>=370 &&my<=416)
              {
                  exit(0);
              }
              else if(mx>=436 &&mx<=482 && my>=370 &&my<=416)
              {
                    if(state==1 || m==0)
             {
                   state=0;
                  gameshow=-1;
             }
              }
          }
          if(gameover)
          {
               if(mx>=400 && mx<=700 && my>=250 && my<=290)
               {
                   mode=1;
               }
          }
          if(winpage)
          {
             if(mx>=400 && mx<=700 && my>=100 && my<=140)
               {
                   mode=2;
               }
          }
         }

         if(button==GLUT_RIGHT_BUTTON && state==GLUT_UP)
         {
             iPauseTimer(0);
         }
}
void iKeyboard(unsigned char key)
{
        if(key==' ')
        {
            if(!start)
            {
                start=1;
            }
        }
              if(pageshow)
            {
                if(key=='\r')
             {
                pageshow=0;
              }
            }
        if(key=='b')
        {
             if(state==1 || m==0)
             {
                   state=0;
                  gameshow=-1;
             }

        }
        if(winpage)
        {
           if(mode==2)
           {
                if(key=='\r')
               {
                   mode=3;
                   printf("%s\n",str);
                   len=0;
               }
            else
            {
                str[len]=key;
                len++;
            }
           }

        }
        if(gameover)
        {
              if(mode==1)
           {
                if(key=='\r')
               {
                   mode=3;
                   printf("%s\n",str);
                   len=0;
               }
            else
            {
                str[len]=key;
                len++;
            }
           }
        }
}
void iSpecialKeyboard(unsigned char key)
{

	if(key == GLUT_KEY_END)
	{

	}
	if(key == GLUT_KEY_LEFT)
	{
          if(board_x>0)
          {
               board_x-=10;
           if(!start)
           {
               ball_x-=10;
           }
          }
	}
	if(key == GLUT_KEY_RIGHT)
	{
          if(board_x<screenWidth-dxboard)
          {
               board_x+=10;
           if(!start)
           {
               ball_x+=10;
           }
          }
	}
	if(key == GLUT_KEY_UP)
	{

	}
	if(key == GLUT_KEY_DOWN)
	{

	}
}
void ballChange()
{
  if(start)
    {
        ball_x+=dx;
    ball_y+=dy;
    if(ball_x>screenWidth || ball_x<=0)
        dx*=(-1);
    else if(ball_y>screenHeight || ball_y<=0)
        dy*=(-1);
    //Collision with bricks
  if(whball)
  {
        for(int i=0;i<TotalBricks;i++)
    {
        if(bricks[i].show)
        {
            if(ball_x >= bricks[i].x  && ball_x <= bricks[i].x+bricks[i].dx)
            {
                     if(ball_y >= bricks[i].y  && ball_y <= bricks[i].y+bricks[i].dy)
                     {
                         dy*=(-1);
                         bricks[i].show=0;
                         e_brick--;
                         scoreint+=10;
                     }
            }
            else if(ball_y >= bricks[i].y  && ball_y <= bricks[i].y+bricks[i].dy)
            {
                 if(ball_x >= bricks[i].x  && ball_x <= bricks[i].x+bricks[i].dx)
                 {
                       dx+=(-1);
                       bricks[i].show=0;
                       e_brick--;
                       scoreint+=10;
                 }
            }
        }
        if(scoreint==1000)
                         {
                             winpage=1;
                         }
    }
  }

  else if(redball)
  {
        for(int i=0;i<TotalBricks;i++)
    {
        if(bricks[i].show)
        {
            if(ball_x >= bricks[i].x  && ball_x <= bricks[i].x+bricks[i].dx)
            {
                     if(ball_y >= bricks[i].y  && ball_y <= bricks[i].y+bricks[i].dy)
                     {
                         dy*=(-1);
                         if(bricks[i].show==1)
                         {
                             bricks[i].show=0;
                             e_brick--;
                             scoreint+=10;
                         }

                         if(bricks[i+1].show==1)
                         {
                             bricks[i+1].show=0;
                             e_brick--;
                             scoreint+=10;
                         }

                         if(bricks[i+2].show==1)
                         {
                             bricks[i+2].show=0;
                             e_brick--;
                             scoreint+=10;
                         }

                     }
            }
            else if(ball_y >= bricks[i].y  && ball_y <= bricks[i].y+bricks[i].dy)
            {
                 if(ball_x >= bricks[i].x  && ball_x <= bricks[i].x+bricks[i].dx)
                 {
                       dx+=(-1);
                        if(bricks[i].show==1)
                         {
                             bricks[i].show=0;
                             e_brick--;
                             scoreint+=10;
                         }

                         if(bricks[i+1].show==1)
                         {
                             bricks[i+1].show=0;
                             e_brick--;
                             scoreint+=10;
                         }

                          if(bricks[i+2].show==1)
                         {
                             bricks[i+2].show=0;
                             e_brick--;
                             scoreint+=10;
                         }
                       scoreint+=10;
                 }
            }
        }
        if(scoreint==1000)
                         {
                             winpage=1;
                         }
    }
  }
     if(!wide)
     {
          if(ball_x >= board_x  && ball_x <= board_x+dxboard && ball_y >= board_y  && ball_y <= board_y+dyboard)
     {
             theta=(board_x-50+dxboard-ball_x)+40;
             dx=(int) v*cos(theta*PI/180);
             dy=(int) v*sin(theta*PI/180);

     }
     else if(ball_y < board_y)
     {
            reStart();
           if(!p)
           {
                lives--;
            if(lives==2)
            {
                life[0]=0;
            }
            if(lives==1)
            {
               life[1]=0;
            }
            if(lives==0)
            {
                life[2]=0;
            }
           }
           else if(p==1)
           {
                lives1--;
            if(lives1==3)
            {
                life[0]=0;
            }
            if(lives1==2)
            {
               life[1]=0;
            }
            if(lives1==1)
            {
                life[2]=0;
            }
            if(lives1==0)
            {
                life[3]=0;
            }
           }
     }
    }
    else
    {
         if(ball_x >= board_x  && ball_x <= board_x+dxboard+50 && ball_y >= board_y  && ball_y <= board_y+dyboard)
     {
           theta=(board_x-30+dxboard-ball_x)+40;
           dx=(int) v*cos(theta*PI/180);
           dy=(int) v*sin(theta*PI/180);

     }
     else if(ball_y < board_y)
     {
            reStart();
          if(p==0)
          {
                lives--;
            if(lives==2)
            {
                life[0]=0;
            }
            if(lives==1)
            {
               life[1]=0;
            }
            if(lives==0)
            {
                life[2]=0;
            }
          }
          else if(p==1)
          {
                lives1--;
            if(lives1==3)
            {
                life[0]=0;
            }
           else  if(lives1==2)
            {
               life[1]=0;
            }
            else if(lives1==1)
            {
                life[2]=0;
            }
            else if(lives1==0)
            {
                life[3]=0;
            }
          }
     }
    }
    }
     }
void reStart()
{
          ball_x=(int)screenWidth/2;
          ball_y=yMargin;
          v=10;
          theta=30;
          dx=(int) v*cos(theta*PI/180);
          dy=(int) v*sin(theta*PI/180);

          board_x=ball_x-100;
          board_y=ball_y-30;
          start=0;
}

void makeBricks()
{
        int sumx1=100;
        int sumy1=400;
        for(int i=0;i<TotalBricks;i++)
        {
            bricks[i].red=rand()%255;
            bricks[i].green=rand()%255;
            bricks[i].blue=rand()%255;
            bricks[i].x=sumx1;
            bricks[i].y=sumy1;
            sumx1+=120;
            if(sumx1>1000)
            {
                sumx1=110;
                sumy1+=20;
            }
        }
}

void lifex()
{
  if(!wide)
  {
       if(l_show==1)
   {
      if(life_y>=0)
       {
           life_y-=5;
       }
   }
    if(life_x >= board_x  && life_x <= board_x+dxboard && life_y >= board_y  && life_y <= board_y+dyboard)
       {
           l_show=0;
           p=1;
       }
  }
  else if(wide==1)
  {
       if(l_show==1)
   {
      if(life_y>=0)
       {
           life_y-=5;
       }
   }
    if(life_x >= board_x  && life_x <= board_x+dxboard+50 && life_y >= board_y  && life_y <= board_y+dyboard)
       {
           l_show=0;
           p=1;
       }
  }
}
void death()
{
    if(!wide)
    {
        if(death_show)
    {
          if(death_y>=0)
       {
           death_y-=5;
       }
    }
     if(death_x >= board_x  && death_x <= board_x+dxboard && death_y >= board_y  && death_y <= board_y+dyboard)
       {
           death_show=0;
           die=1;
       }
    }
    else if(wide==1)
    {
        if(death_show)
    {
          if(death_y>=0)
       {
           death_y-=5;
       }
    }
     if(death_x >= board_x  && death_x <= board_x+dxboard+50 && death_y >= board_y  && death_y <= board_y+dyboard)
       {
           death_show=0;
           die=1;
       }
    }
}
void paddle()
{
    if(paddleshow)
    {
        if(paddle_y>=0)
        {
            paddle_y-=5;
        }
    }
    if(paddle_x >= board_x  && paddle_x <= board_x+dxboard && paddle_y >= board_y  && paddle_y <= board_y+dyboard)
    {
        paddleshow=0;
        wide=1;
    }
}
void fireball()
{
     if(!wide)
     {
          if(fireshow)
    {
        if(fire_y>=0)
        {
            fire_y-=5;
        }
    }
    if(fire_x >= board_x  && fire_x <= board_x+dxboard && fire_y >= board_y  && fire_y <= board_y+dyboard)
    {
        fireshow=0;
        fr=1;
    }
     }
     else if(wide==1)
     {
          if(fireshow)
    {
        if(fire_y>=0)
        {
            fire_y-=5;
        }
    }
    if(fire_x >= board_x  && fire_x <= board_x+dxboard+50 && fire_y >= board_y  && fire_y <= board_y+dyboard)
    {
        fireshow=0;
        fr=1;
    }
     }
}

void time()
{
    if(state==1)
    {
        time_s++;
        if(time_s>59)
        {
            time_s=0;
           time_m++;
           if(time_m>=2)
           {
               v+=5;
           }
           if(time_m>=3)
           {
               v+=5;
           }
        }
    }
}

int main()
{
	//place your own initialization codes here.
	int s=50;
	for(int i=4;i>=0;i--)
    {
            co[i].x=50;
            co[i].y=s;
            s+=110;
    }
    makeBricks();
	iSetTimer(25, ballChange);
    iSetTimer(1,lifex);
     iSetTimer(1,death);
     iSetTimer(1,paddle);
     iSetTimer(1,fireball);
	iSetTimer(1000,time);
	len=0;
	str[0]=0;
   if(music1==true)
         {
             PlaySound(TEXT("SONG1.WAV"), NULL, SND_ASYNC);
         }
	iInitialize(screenWidth, screenHeight, "Dx Ball");

	return 0;
}
