#include <stdio.h>
#include <iostream>
#include <cstring>
#include <graphics.h>
#include <winbgim.h>
#include <MMsystem.h>
#define MX 960
#define MY 540
#define pozx 280
#define pozy 120

using namespace std;

struct data{
    int a[61][13];
    int tick[61];
    int lvl;
    int nr;
    int muzic;
};

struct tabla{
    int a[5][7];
    int gr[4][5];
    int c[6];
    bool complete;
    bool impossible;
};

struct language{
    int type;
    char start[21];
    char about[21];
    char game[21];
    char code[21];
    char settings[21];
    char quit[21];
    char rprogress[21];
    char restart[21];
    char challenges[21];
    char language[21];
    char music[21];
    char romana[21];
    char english[21];
    char on1[21];
    char on2[21];
    char off[21];
    char complete[21];
    char failed[21];
};

//Adauga fundal la fereastra selectata
void fundal(data* d)
{
    if(d->nr==0)
        readimagefile("Media/Menu.jpg", 0, 0, MX, MY);
    else
    if(d->nr==1 || d->nr==2 || d->nr==5 || d->nr==7)
        readimagefile("Media/Background.jpg", 0, 0, MX, MY);
    else
    if(d->nr==6 || d->nr==8)
    {
        setcolor(CYAN);
        setfillstyle(SOLID_FILL, CYAN);
        rectangle(0, 0, MX, MY);
        floodfill(21, 21, CYAN);

        setcolor(LIGHTCYAN);
        setfillstyle(SOLID_FILL, LIGHTCYAN);
        rectangle(20, 20, MX-20, MY-20);
        floodfill(21, 21, LIGHTCYAN);
    }
}

//Schimba limba jocului
void lang(language* l)
{
    if(l->type==1)
    {
        strcpy(l->start, "Start");
        strcpy(l->settings, "Settings");
        strcpy(l->about, "About");
        strcpy(l->game, "game");
        strcpy(l->code, "code");
        strcpy(l->quit, "Quit");
        strcpy(l->rprogress, "Reset progress");
        strcpy(l->restart, "Restart");
        strcpy(l->challenges, "Challenges");
        strcpy(l->language, "Language:");
        strcpy(l->music, "Music:");
        strcpy(l->romana, "Romana");
        strcpy(l->english, "English");
        strcpy(l->on1, "SONG1");
        strcpy(l->on2, "SONG2");
        strcpy(l->off, "OFF");
        strcpy(l->complete, "LEVEL COMPLETE");
        strcpy(l->failed, "LEVEL FAILED");
    }
    else
    if(l->type==2)
    {
        strcpy(l->start, "Incepe");
        strcpy(l->settings, "Setari");
        strcpy(l->about, "Despre");
        strcpy(l->game, "joc");
        strcpy(l->code, "cod");
        strcpy(l->quit, "Iesi");
        strcpy(l->rprogress, "Sterge progresul");
        strcpy(l->restart, "Reincepe");
        strcpy(l->challenges, "Provocari");
        strcpy(l->language, "Limba:");
        strcpy(l->music, "Muzica:");
        strcpy(l->romana, "Romana");
        strcpy(l->english, "English");
        strcpy(l->on1, "MELODIE1");
        strcpy(l->on2, "MELODIE2");
        strcpy(l->off, "OPRIT");
        strcpy(l->complete, "NIVEL COMPLET");
        strcpy(l->failed, "NIVEL PIERDUT");
    }
}

//Verifica si atribuie o grupa unui element din matrice
void grupa(tabla* t, int i, int j)
{
    if(j+1<4 && t->a[i*2][j*2+1]==0 && t->gr[i][j+1]!=t->gr[i][j])
        {t->gr[i][j+1]=t->gr[i][j]; grupa(t, i, j+1);}
    if(i+1<3 && t->a[i*2+1][j*2]==0 && t->gr[i+1][j]!=t->gr[i][j])
        {t->gr[i+1][j]=t->gr[i][j]; grupa(t, i+1, j);}
    if(j-1>=0 && t->a[i*2][j*2-1]==0 && t->gr[i][j-1]!=t->gr[i][j])
        {t->gr[i][j-1]=t->gr[i][j]; grupa(t, i, j-1);}
    if(i-1>=0 && t->a[i*2-1][j*2]==0 && t->gr[i-1][j]!=t->gr[i][j])
        {t->gr[i-1][j]=t->gr[i][j]; grupa(t, i-1, j);}
}

//Verifica daca nivelul a fost rezolvat sau daca este imposibil de rezolvat
void isValid(tabla* t)
{
    int i, j, nr=1, a[5][6]={0};
    for(i=0; i<=2; i++)
        for(j=0; j<=3; j++)
            t->gr[i][j]=0;
    for(i=0; i<=2; i++)
        for(j=0; j<=3; j++)
        {
            if(t->gr[i][j]==0)
            {
                t->gr[i][j]=nr;
                if(j+1<4 && t->a[i*2][j*2+1]==0 && t->gr[i][j+1]!=t->gr[i][j])
                    {t->gr[i][j+1]=t->gr[i][j]; grupa(t, i, j+1);}
                if(i+1<3 && t->a[i*2+1][j*2]==0 && t->gr[i+1][j]!=t->gr[i][j])
                    {t->gr[i+1][j]=t->gr[i][j]; grupa(t, i+1, j);}
                if(j-1>=0 && t->a[i*2][j*2-1]==0 && t->gr[i][j-1]!=t->gr[i][j])
                    {t->gr[i][j-1]=t->gr[i][j]; grupa(t, i, j-1);}
                if(i-1>=0 && t->a[i*2-1][j*2]==0 && t->gr[i-1][j]!=t->gr[i][j])
                    {t->gr[i-1][j]=t->gr[i][j]; grupa(t, i-1, j);}
                nr++;
            }
        }
    nr--;
    for(i=0; i<=2; i++)
        for(j=0; j<=3; j++)
        {
            if(t->a[i*2][j*2]!=0)
            {
                a[t->gr[i][j]][t->a[i*2][j*2]]++;
                a[t->gr[i][j]][0]++;
            }
        }
    t->complete=1;
    if(t->c[5]==0)
    {
        for(i=1; i<=nr; i++)
            if(!((a[i][1]==2 || a[i][2]==2 || a[i][3]==2 || a[i][4]==2) && a[i][0]==2))
            {
                t->complete=0;
                break;
            }
    }
    else
        for(i=1; i<=nr; i++)
            if(!((a[i][1]==1 || a[i][2]==1 || a[i][3]==1 || a[i][4]==1) && a[i][5]==1 && a[i][0]==2))
            {
                t->complete=0;
                break;
            }
    if(t->complete==0)
    {
        t->impossible=0;
        if(t->c[5]==0)
        {
            for(i=1; i<=nr; i++)
                if(a[i][1]==1 || a[i][2]==1 || a[i][3]==1 || a[i][4]==1 || a[i][0]==0)
                {
                    t->impossible=1;
                    break;
                }
        }
        else
            for(i=1; i<=nr; i++)
                if(a[i][5]*2!=a[i][0] || a[i][0]==0)
                {
                    t->impossible=1;
                    break;
                }
    }
}

//Apare daca nivelul a fost rezolvat
void lvlComplete(tabla* t, data* d, language* l, FILE* lvl)
{
    delay(200);
    int buton[3][5], i=0, j, x, y, dist;
    {
        setcolor(BLACK);
        rectangle(pozx-5, pozy-5, pozx+404, pozy+304);
        setfillstyle(SOLID_FILL, BLACK);
        floodfill(pozx, pozy, BLACK);
    }
    {
        setcolor(LIGHTCYAN);
        rectangle(pozx+1, pozy+1, pozx+398, pozy+298);
        setfillstyle(SOLID_FILL, LIGHTCYAN);
        floodfill(pozx+2, pozy+2, LIGHTCYAN);
        setcolor(GREEN);
        rectangle(pozx+1, pozy+1, pozx+398, pozy+298);
        setfillstyle(SOLID_FILL, GREEN);
        floodfill(pozx+2, pozy+2, GREEN);
    }
    {
        setbkcolor(GREEN);
        setcolor(BLACK);
        settextstyle(BOLD_FONT, 0, 5);
        outtextxy(pozx+(397-textwidth(l->complete))/2, pozy+40, l->complete);
        settextstyle(BOLD_FONT, 0, 1);
    }
    if(d->lvl!=60)
        dist=(397-150)/4+1;
    else
        dist=(397-100)/3+1;
    {
        buton[i][1]=pozx+dist;
        buton[i][2]=pozy+298-40-50;
        buton[i][3]=buton[i][1]+50;
        buton[i][4]=buton[i][2]+50;
        setcolor(BLUE);
        rectangle(buton[i][1], buton[i][2], buton[i][3], buton[i][4]);
        setfillstyle(SOLID_FILL, BLUE);
        floodfill(buton[i][1]+1, buton[i][2]+1, BLUE);
        setcolor(LIGHTBLUE);
        rectangle(buton[i][1]+5, buton[i][2]+5, buton[i][3]-5, buton[i][4]-5);
        setfillstyle(SOLID_FILL, LIGHTBLUE);
        floodfill(buton[i][1]+6, buton[i][2]+6, LIGHTBLUE);
        readimagefile("Media/back.jpg", buton[i][1]+10, buton[i][2]+10, buton[i][3]-10, buton[i][4]-10);
        i++;
    }
    {
        buton[i][1]=buton[i-1][3]+dist;
        buton[i][2]=buton[i-1][2];
        buton[i][3]=buton[i][1]+50;
        buton[i][4]=buton[i-1][4];
        setcolor(BLUE);
        rectangle(buton[i][1], buton[i][2], buton[i][3], buton[i][4]);
        setfillstyle(SOLID_FILL, BLUE);
        floodfill(buton[i][1]+1, buton[i][2]+1, BLUE);
        setcolor(LIGHTBLUE);
        rectangle(buton[i][1]+5, buton[i][2]+5, buton[i][3]-5, buton[i][4]-5);
        setfillstyle(SOLID_FILL, LIGHTBLUE);
        floodfill(buton[i][1]+6, buton[i][2]+6, LIGHTBLUE);
        readimagefile("Media/restart.jpg", buton[i][1]+10, buton[i][2]+10, buton[i][3]-10, buton[i][4]-10);
        i++;
    }
    if(d->lvl!=60)
    {
        buton[i][1]=buton[i-1][3]+dist;
        buton[i][2]=buton[i-1][2];
        buton[i][3]=buton[i][1]+50;
        buton[i][4]=buton[i-1][4];
        setcolor(BLUE);
        rectangle(buton[i][1], buton[i][2], buton[i][3], buton[i][4]);
        setfillstyle(SOLID_FILL, BLUE);
        floodfill(buton[i][1]+1, buton[i][2]+1, BLUE);
        setcolor(LIGHTBLUE);
        rectangle(buton[i][1]+5, buton[i][2]+5, buton[i][3]-5, buton[i][4]-5);
        setfillstyle(SOLID_FILL, LIGHTBLUE);
        floodfill(buton[i][1]+6, buton[i][2]+6, LIGHTBLUE);
        readimagefile("Media/next.jpg", buton[i][1]+10, buton[i][2]+10, buton[i][3]-10, buton[i][4]-10);
        i++;
    }
    while(1)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            x=mousex();
            y=mousey();
            if((buton[0][1]<=x && x<=buton[0][3]) && (buton[0][2]<=y && y<=buton[0][4]))
            {
                clearmouseclick(WM_LBUTTONDOWN);
                d->nr=1;
                for(i=1; i<=5; i++)
                    t->c[i]=0;
                break;
            }
            else
            if((buton[1][1]<=x && x<=buton[1][3]) && (buton[1][2]<=y && y<=buton[1][4]))
            {
                clearmouseclick(WM_LBUTTONDOWN);
                d->nr=2;
                break;
            }
            else
            if((buton[2][1]<=x && x<=buton[2][3]) && (buton[2][2]<=y && y<=buton[2][4]) && d->lvl!=60)
            {
                clearmouseclick(WM_LBUTTONDOWN);
                d->lvl++;
                for(i=0; i<5; i+=2)
                    for(j=0; j<7; j+=2)
                        {
                            t->a[i][j]=d->a[d->lvl][2*i+j/2+1];
                            if(t->a[i][j]!=0)
                                t->c[t->a[i][j]]++;
                        }
                for(i=1; i<=60; i++)
                    fprintf(lvl, "%d ", d->tick[i]);
                rewind(lvl);
                d->nr=2;
                for(i=1; i<=5; i++)
                    t->c[i]=0;
                break;
            }
            clearmouseclick(WM_LBUTTONDOWN);
        }
    }
}

//Apare daca este clar ca nivelul nu mai poate fi rezolvat
void lvlFailed(tabla* t, data* d, language* l)
{
    delay(200);
    int buton[2][5], i=0, j, x, y, dist;
    {
        setcolor(BLACK);
        rectangle(pozx-5, pozy-5, pozx+404, pozy+304);
        setfillstyle(SOLID_FILL, BLACK);
        floodfill(pozx, pozy, BLACK);
    }
    {
        setcolor(RED);
        rectangle(pozx+1, pozy+1, pozx+398, pozy+298);
        setfillstyle(SOLID_FILL, RED);
        floodfill(pozx+2, pozy+2, RED);
    }
    {
        setbkcolor(RED);
        setcolor(BLACK);
        settextstyle(BOLD_FONT, 0, 5);
        outtextxy(pozx+(397-textwidth(l->failed))/2, pozy+40, l->failed);
        settextstyle(BOLD_FONT, 0, 1);
    }
    dist=(397-100)/3;
    {
        buton[i][1]=pozx+dist;
        buton[i][2]=pozy+298-40-50;
        buton[i][3]=buton[i][1]+50;
        buton[i][4]=buton[i][2]+50;
        setcolor(BLUE);
        rectangle(buton[i][1], buton[i][2], buton[i][3], buton[i][4]);
        setfillstyle(SOLID_FILL, BLUE);
        floodfill(buton[i][1]+1, buton[i][2]+1, BLUE);
        setcolor(LIGHTBLUE);
        rectangle(buton[i][1]+5, buton[i][2]+5, buton[i][3]-5, buton[i][4]-5);
        setfillstyle(SOLID_FILL, LIGHTBLUE);
        floodfill(buton[i][1]+6, buton[i][2]+6, LIGHTBLUE);
        readimagefile("Media/back.jpg", buton[i][1]+10, buton[i][2]+10, buton[i][3]-10, buton[i][4]-10);
        i++;
    }
    {
        buton[i][1]=buton[i-1][3]+dist;
        buton[i][2]=buton[i-1][2];
        buton[i][3]=buton[i][1]+50;
        buton[i][4]=buton[i-1][4];
        setcolor(BLUE);
        rectangle(buton[i][1], buton[i][2], buton[i][3], buton[i][4]);
        setfillstyle(SOLID_FILL, BLUE);
        floodfill(buton[i][1]+1, buton[i][2]+1, BLUE);
        setcolor(LIGHTBLUE);
        rectangle(buton[i][1]+5, buton[i][2]+5, buton[i][3]-5, buton[i][4]-5);
        setfillstyle(SOLID_FILL, LIGHTBLUE);
        floodfill(buton[i][1]+6, buton[i][2]+6, LIGHTBLUE);
        readimagefile("Media/restart.jpg", buton[i][1]+10, buton[i][2]+10, buton[i][3]-10, buton[i][4]-10);
        i++;
    }
    while(1)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            x=mousex();
            y=mousey();
            if((buton[0][1]<=x && x<=buton[0][3]) && (buton[0][2]<=y && y<=buton[0][4]))
            {
                clearmouseclick(WM_LBUTTONDOWN);
                d->nr=1;
                for(i=1; i<=5; i++)
                    t->c[i]=0;
                break;
            }
            else
            if((buton[1][1]<=x && x<=buton[1][3]) && (buton[1][2]<=y && y<=buton[1][4]))
            {
                clearmouseclick(WM_LBUTTONDOWN);
                d->nr=2;
                break;
            }
            clearmouseclick(WM_LBUTTONDOWN);
        }
    }
}

//Plaseaza butoanele, verifica ce buton a fost apasat si plaseaza gardurile
void butoaneTabla(tabla* t, data* d, language* l, FILE* lvl)
{
    int buton[12][5], piesa[4][5], i=1, j=1, k, x, y;
    setcolor(BLUE);
    setfillstyle(SOLID_FILL, BLUE);
    {
        rectangle(pozx+504, pozy+20, pozx+579, pozy+95);
        floodfill(pozx+505, pozy+21, BLUE);
        buton[i][1]=pozx+504;
        buton[i][2]=pozy+20;
        buton[i][3]=pozx+579;
        buton[i][4]=pozy+95;
        i++;
    }
    {
        rectangle(MX-85, pozy+112, MX-10, pozy+187);
        floodfill(MX-84, pozy+113, BLUE);
        buton[i][1]=MX-85;
        buton[i][2]=pozy+112;
        buton[i][3]=MX-10;
        buton[i][4]=pozy+187;
        i++;
    }
    {
        rectangle(pozx+504, pozy+205, pozx+579, pozy+280);
        floodfill(pozx+505, pozy+279, BLUE);
        buton[i][1]=pozx+504;
        buton[i][2]=pozy+205;
        buton[i][3]=pozx+579;
        buton[i][4]=pozy+280;
        i++;
    }
    {
        rectangle(pozx+414, pozy+112, pozx+489, pozy+187);
        floodfill(pozx+415, pozy+113, BLUE);
        buton[i][1]=pozx+414;
        buton[i][2]=pozy+112;
        buton[i][3]=pozx+489;
        buton[i][4]=pozy+187;
        i++;
    }
    {
        rectangle(pozx-90, pozy+37, pozx-15, pozy+112);
        floodfill(pozx-89, pozy+38, BLUE);
        buton[i][1]=pozx-90;
        buton[i][2]=pozy+37;
        buton[i][3]=pozx-15;
        buton[i][4]=pozy+112;
        i++;
    }
    {
        rectangle(10, pozy+37, 85, pozy+112);
        floodfill(11, pozy+38, BLUE);
        buton[i][1]=10;
        buton[i][2]=pozy+37;
        buton[i][3]=85;
        buton[i][4]=pozy+112;
        i++;
    }
    {
        rectangle(pozx-90, pozy+188, pozx-15, pozy+263);
        floodfill(pozx-89, pozy+189, BLUE);
        buton[i][1]=pozx-90;
        buton[i][2]=pozy+188;
        buton[i][3]=pozx-15;
        buton[i][4]=pozy+263;
        i++;
    }
    {
        rectangle(10, pozy+188, 85, pozy+263);
        floodfill(11, pozy+189, BLUE);
        buton[i][1]=10;
        buton[i][2]=pozy+188;
        buton[i][3]=85;
        buton[i][4]=pozy+263;
        i++;
    }
    setcolor(LIGHTBLUE);
    setfillstyle(SOLID_FILL, LIGHTBLUE);
    {
        rectangle(pozx+509, pozy+25, pozx+574, pozy+90);
        floodfill(pozx+510, pozy+26, LIGHTBLUE);
    }
    {
        rectangle(pozx+509, pozy+210, pozx+574, pozy+275);
        floodfill(pozx+510, pozy+211, LIGHTBLUE);
    }
    {
        rectangle(pozx+419, pozy+117, pozx+484, pozy+182);
        floodfill(pozx+420, pozy+118, LIGHTBLUE);
    }
    {
        rectangle(MX-80, pozy+117, MX-15, pozy+182);
        floodfill(MX-79, pozy+118, LIGHTBLUE);
    }
    {
        rectangle(15, pozy+42, 80, pozy+107);
        floodfill(16, pozy+43, LIGHTBLUE);
    }
    {
        rectangle(pozx-85, pozy+42, pozx-20, pozy+107);
        floodfill(pozx-84, pozy+43, LIGHTBLUE);
    }
    {
        rectangle(15, pozy+193, 80, pozy+258);
        floodfill(16, pozy+194, LIGHTBLUE);
    }
    {
        rectangle(pozx-85, pozy+193, pozx-20, pozy+258);
        floodfill(pozx-84, pozy+194, LIGHTBLUE);
    }
    setcolor(WHITE);
    {
        line(pozx+529, pozy+30, pozx+554, pozy+30);
        line(pozx+524, pozy+30, pozx+524, pozy+55);
        line(pozx+524, pozy+60, pozx+524, pozy+85);
    }
    {
        line(pozx+554, pozy+270, pozx+529, pozy+270);
        line(pozx+559, pozy+215, pozx+559, pozy+240);
        line(pozx+559, pozy+245, pozx+559, pozy+270);
    }
    {
        line(pozx+424, pozy+137, pozx+424, pozy+162);
        line(pozx+424, pozy+167, pozx+449, pozy+167);
        line(pozx+454, pozy+167, pozx+479, pozy+167);
    }
    {
        line(MX-20, pozy+137, MX-20, pozy+162);
        line(MX-75, pozy+132, MX-50, pozy+132);
        line(MX-45, pozy+132, MX-20, pozy+132);
    }
    {
        line(20, pozy+74, 35, pozy+74);
        line(40, pozy+74, 55, pozy+74);
        line(60, pozy+74, 75, pozy+74);
    }
    {
        line(pozx-53, pozy+47, pozx-53, pozy+62);
        line(pozx-53, pozy+67, pozx-53, pozy+82);
        line(pozx-53, pozy+87, pozx-53, pozy+102);
    }
    {
        line(20, pozy+225, 45, pozy+225);
        line(50, pozy+225, 75, pozy+225);
    }
    {
        line(pozx-53, pozy+198, pozx-53, pozy+223);
        line(pozx-53, pozy+228, pozx-53, pozy+253);
    }
    {
        buton[i][1]=10;
        buton[i][2]=10;
        buton[i][3]=buton[i][1]+50;
        buton[i][4]=buton[i][2]+50;
        setcolor(BLUE);
        rectangle(buton[i][1], buton[i][2], buton[i][3], buton[i][4]);
        setfillstyle(SOLID_FILL, BLUE);
        floodfill(buton[i][1]+1, buton[i][2]+1, BLUE);
        setcolor(LIGHTBLUE);
        rectangle(buton[i][1]+5, buton[i][2]+5, buton[i][3]-5, buton[i][4]-5);
        setfillstyle(SOLID_FILL, LIGHTBLUE);
        floodfill(buton[i][1]+6, buton[i][2]+6, LIGHTBLUE);
        readimagefile("Media/back.jpg", buton[i][1]+10, buton[i][2]+10, buton[i][3]-10, buton[i][4]-10);
        i++;
    }
    {
        buton[i][1]=buton[i-1][3]+10;
        buton[i][2]=buton[i-1][2];
        buton[i][3]=buton[i][1]+50;
        buton[i][4]=buton[i-1][4];
        setcolor(BLUE);
        rectangle(buton[i][1], buton[i][2], buton[i][3], buton[i][4]);
        setfillstyle(SOLID_FILL, BLUE);
        floodfill(buton[i][1]+1, buton[i][2]+1, BLUE);
        setcolor(LIGHTBLUE);
        rectangle(buton[i][1]+5, buton[i][2]+5, buton[i][3]-5, buton[i][4]-5);
        setfillstyle(SOLID_FILL, LIGHTBLUE);
        floodfill(buton[i][1]+6, buton[i][2]+6, LIGHTBLUE);
        readimagefile("Media/restart.jpg", buton[i][1]+10, buton[i][2]+10, buton[i][3]-10, buton[i][4]-10);
        i++;
    }
    setcolor(GREEN);
    setfillstyle(SOLID_FILL, GREEN);
    {
        rectangle(pozx+517, pozy+125, pozx+567, pozy+175);
        floodfill(pozx+518, pozy+126, GREEN);
        piesa[j][0]=1;
        piesa[j][1]=pozx+517;
        piesa[j][2]=pozy+125;
        piesa[j][3]=pozx+567;
        piesa[j][4]=pozy+175;
        j++;
    }
    {
        rectangle(112, pozy+49, 162, pozy+99);
        floodfill(113, pozy+50, GREEN);
        piesa[j][0]=1;
        piesa[j][1]=112;
        piesa[j][2]=pozy+49;
        piesa[j][3]=162;
        piesa[j][4]=pozy+99;
        j++;
    }
    {
        rectangle(112, pozy+200, 162, pozy+250);
        floodfill(113, pozy+201, GREEN);
        piesa[j][0]=1;
        piesa[j][1]=112;
        piesa[j][2]=pozy+200;
        piesa[j][3]=162;
        piesa[j][4]=pozy+250;
        j++;
    }
    setcolor(LIGHTGREEN);
    setfillstyle(SOLID_FILL, LIGHTGREEN);
    {
        rectangle(pozx+522, pozy+130, pozx+562, pozy+170);
        floodfill(pozx+523, pozy+131, LIGHTGREEN);
    }
    {
        rectangle(117, pozy+54, 157, pozy+94);
        floodfill(118, pozy+55, LIGHTGREEN);
    }
    {
        rectangle(117, pozy+205, 157, pozy+245);
        floodfill(118, pozy+206, LIGHTGREEN);
    }
    int kp=-1, ig, jg;
    int OK=0;
    while(1)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            x=mousex();
            y=mousey();
            if((buton[9][1]<=x && x<=buton[9][3]) && (buton[9][2]<=y && y<=buton[9][4]))
            {
                clearmouseclick(WM_LBUTTONDOWN);
                d->nr=1;
                break;
            }
            else
            if((buton[10][1]<=x && x<=buton[10][3]) && (buton[10][2]<=y && y<=buton[10][4]))
            {
                clearmouseclick(WM_LBUTTONDOWN);
                d->nr=2;
                break;
            }
            else
            for(k=1; k<=8; k++)
                if(kp!=k)
                {
                    if((buton[k][1]<=x && x<=buton[k][3]) && (buton[k][2]<=y && y<=buton[k][4]) && piesa[(k>4?(k-1)/2:1)][0]==1)
                    {
                        if(kp!=-1)
                        {
                            setcolor(BLUE);
                            rectangle(buton[kp][1], buton[kp][2], buton[kp][3], buton[kp][4]);
                            rectangle(buton[kp][1]+4, buton[kp][2]+4, buton[kp][3]-4, buton[kp][4]-4);
                            setfillstyle(SOLID_FILL, BLUE);
                            floodfill(buton[kp][1]+1, buton[kp][2]+1, BLUE);
                        }
                        setcolor(LIGHTRED);
                        rectangle(buton[k][1], buton[k][2], buton[k][3], buton[k][4]);
                        rectangle(buton[k][1]+4, buton[k][2]+4, buton[k][3]-4, buton[k][4]-4);
                        setfillstyle(SOLID_FILL, LIGHTRED);
                        floodfill(buton[k][1]+1, buton[k][2]+1, LIGHTRED);
                        kp=k;
                        break;
                    }
                }
                else
                if(kp==k && kp%2==1 && kp<6)
                {
                    for(i=1; i<=3; i++)
                        if((pozx+100*i-20<=x && x<=pozx+100*i+19) && (pozy+100<=y && y<=pozy+199))
                        {
                            ig=2;
                            jg=i*2-1;
                            if(piesa[kp<5?1:2][0]==1 && t->a[kp==1?ig-1:ig-2][kp==1?jg+1:jg]!=1 && t->a[ig-1][jg]!=1 && t->a[ig][jg]!=1 && t->a[ig+1][jg]!=1 && t->a[kp==3?ig+1:ig+2][kp==3?jg-1:jg]!=1)
                            {
                                piesa[kp<5?1:2][0]=0; t->a[kp==1?ig-1:ig-2][kp==1?jg+1:jg]=1; t->a[ig-1][jg]=1; t->a[ig][jg]=1; t->a[ig+1][jg]=1; t->a[kp==3?ig+1:ig+2][kp==3?jg-1:jg]=1;
                                setcolor(WHITE);
                                setfillstyle(SOLID_FILL, WHITE);
                                if(kp==1)
                                {
                                    rectangle(pozx+100*i+15, pozy+100-4, pozx+100*i+84, pozy+100+3);
                                    floodfill(pozx+100*i+16, pozy+100-3, WHITE);
                                }
                                else
                                {
                                    rectangle(pozx+100*i-4, pozy+0+15, pozx+100*i+3, pozy+0+84);
                                    floodfill(pozx+100*i-3, pozy+0+16, WHITE);
                                }
                                rectangle(pozx+100*i-8, pozy+100-8, pozx+100*i+7, pozy+100+7);
                                floodfill(pozx+100*i-7, pozy+100-7, WHITE);
                                rectangle(pozx+100*i-4, pozy+100+15, pozx+100*i+3, pozy+100+84);
                                floodfill(pozx+100*i-3, pozy+100+16, WHITE);
                                rectangle(pozx+100*i-8, pozy+200-8, pozx+100*i+7, pozy+200+7);
                                floodfill(pozx+100*i-7, pozy+200-7, WHITE);
                                if(kp==3)
                                {
                                    rectangle(pozx+100*(i-1)+15, pozy+200-4, pozx+100*(i-1)+84, pozy+200+3);
                                    floodfill(pozx+100*(i-1)+16, pozy+200-3, WHITE);
                                }
                                else
                                {
                                    rectangle(pozx+100*i-4, pozy+200+15, pozx+100*i+3, pozy+200+84);
                                    floodfill(pozx+100*i-3, pozy+200+16, WHITE);
                                }
                                setcolor(RED);
                                setfillstyle(SOLID_FILL, RED);
                                rectangle(piesa[kp<5?1:2][1], piesa[kp<5?1:2][2], piesa[kp<5?1:2][3], piesa[kp<5?1:2][4]);
                                floodfill(piesa[kp<5?1:2][1]+1, piesa[kp<5?1:2][2]+1, RED);
                                setcolor(LIGHTRED);
                                setfillstyle(SOLID_FILL, LIGHTRED);
                                rectangle(piesa[kp<5?1:2][1]+5, piesa[kp<5?1:2][2]+5, piesa[kp<5?1:2][3]-5, piesa[kp<5?1:2][4]-5);
                                floodfill(piesa[kp<5?1:2][1]+6, piesa[kp<5?1:2][2]+6, LIGHTRED);
                                setcolor(BLUE);
                                setfillstyle(SOLID_FILL, BLUE);
                                rectangle(buton[kp][1], buton[kp][2], buton[kp][3], buton[kp][4]);
                                rectangle(buton[kp][1]+4, buton[kp][2]+4, buton[kp][3]-4, buton[kp][4]-4);
                                floodfill(buton[kp][1]+1, buton[kp][2]+1, BLUE);
                                kp=-1;
                                OK=1;
                            }
                            break;
                        }
                }
                else
                if(kp==k && kp%2==0 && kp<7)
                {
                    for(i=1; i<=2; i++)
                        for(j=1; j<=2; j++)
                            if((pozx+100*j<=x && x<=pozx+100*j+99) && (pozy+100*i-20<=y && y<=pozy+100*i+19))
                            {
                                ig=i*2-1;
                                jg=j*2;
                                if(piesa[kp<5?1:2][0]==1 && t->a[kp==4?ig-1:ig][kp==4?jg-1:jg-2]!=1 && t->a[ig][jg-1]!=1 && t->a[ig][jg]!=1 && t->a[ig][jg+1]!=1 && t->a[kp==2?ig+1:ig][kp==2?jg+1:jg+2]!=1)
                                {
                                    piesa[kp<5?1:2][0]=0; t->a[kp==4?ig-1:ig][kp==4?jg-1:jg-2]=1; t->a[ig][jg-1]=1; t->a[ig][jg]=1; t->a[ig][jg+1]=1; t->a[kp==2?ig+1:ig][kp==2?jg+1:jg+2]=1;
                                    setcolor(WHITE);
                                    setfillstyle(SOLID_FILL, WHITE);
                                    if(kp==4)
                                    {
                                        rectangle(pozx+100*j-4, pozy+100*(i-1)+15, pozx+100*j+3, pozy+100*(i-1)+84);
                                        floodfill(pozx+100*j-3, pozy+100*(i-1)+16, WHITE);
                                    }
                                    else
                                    {
                                        rectangle(pozx+100*(j-1)+15, pozy+100*i-4, pozx+100*(j-1)+84, pozy+100*i+3);
                                        floodfill(pozx+100*(j-1)+16, pozy+100*i-3, WHITE);
                                    }
                                    rectangle(pozx+100*j-8, pozy+100*i-8, pozx+100*j+7, pozy+100*i+7);
                                    floodfill(pozx+100*j-7, pozy+100*i-7, WHITE);
                                    rectangle(pozx+100*j+15, pozy+100*i-4, pozx+100*j+84, pozy+100*i+3);
                                    floodfill(pozx+100*j+16, pozy+100*i-3, WHITE);
                                    rectangle(pozx+100*(j+1)-8, pozy+100*i-8, pozx+100*(j+1)+7, pozy+100*i+7);
                                    floodfill(pozx+100*(j+1)-7, pozy+100*i-7, WHITE);
                                    if(kp==2)
                                    {
                                        rectangle(pozx+100*(j+1)-4, pozy+100*i+15, pozx+100*(j+1)+3, pozy+100*i+84);
                                        floodfill(pozx+100*(j+1)-3, pozy+100*i+16, WHITE);
                                    }
                                    else
                                    {
                                        rectangle(pozx+100*(j+1)+15, pozy+100*i-4, pozx+100*(j+1)+84, pozy+100*i+3);
                                        floodfill(pozx+100*(j+1)+16, pozy+100*i-3, WHITE);
                                    }
                                    setcolor(RED);
                                    setfillstyle(SOLID_FILL, RED);
                                    rectangle(piesa[kp<5?1:2][1], piesa[kp<5?1:2][2], piesa[kp<5?1:2][3], piesa[kp<5?1:2][4]);
                                    floodfill(piesa[kp<5?1:2][1]+1, piesa[kp<5?1:2][2]+1, RED);
                                    setcolor(LIGHTRED);
                                    setfillstyle(SOLID_FILL, LIGHTRED);
                                    rectangle(piesa[kp<5?1:2][1]+5, piesa[kp<5?1:2][2]+5, piesa[kp<5?1:2][3]-5, piesa[kp<5?1:2][4]-5);
                                    floodfill(piesa[kp<5?1:2][1]+6, piesa[kp<5?1:2][2]+6, LIGHTRED);
                                    setcolor(BLUE);
                                    setfillstyle(SOLID_FILL, BLUE);
                                    rectangle(buton[kp][1], buton[kp][2], buton[kp][3], buton[kp][4]);
                                    rectangle(buton[kp][1]+4, buton[kp][2]+4, buton[kp][3]-4, buton[kp][4]-4);
                                    floodfill(buton[kp][1]+1, buton[kp][2]+1, BLUE);
                                    kp=-1;
                                    OK=1;
                                }
                                break;
                            }
                }
                if(kp==7)
                {
                    for(i=1; i<=3; i++)
                        for(j=1; j<=3; j++)
                            if((pozx+100*j-20<=x && x<=pozx+100*j+19) && (pozy+100*(i-1)<=y && y<=pozy+100*(i-1)+99))
                            {
                                ig=(i!=3?(i-1)*2:2);
                                jg=j*2-1;
                                if(piesa[3][0]==1 && t->a[ig][jg]!=1 && t->a[ig+1][jg]!=1 && t->a[ig+2][jg]!=1)
                                {
                                    piesa[3][0]=0; t->a[ig][jg]=1; t->a[ig+1][jg]=1; t->a[ig+2][jg]=1;
                                    setcolor(WHITE);
                                    setfillstyle(SOLID_FILL, WHITE);
                                    rectangle(pozx+100*j-4, pozy+100*(i!=3?i-1:i-2)+15, pozx+100*j+3, pozy+100*(i!=3?i-1:i-2)+84);
                                    floodfill(pozx+100*j-3, pozy+100*(i!=3?i-1:i-2)+16, WHITE);
                                    rectangle(pozx+100*j-8, pozy+100*(i!=3?i:i-1)-8, pozx+100*j+7, pozy+100*(i!=3?i:i-1)+7);
                                    floodfill(pozx+100*j-7, pozy+100*(i!=3?i:i-1)-7, WHITE);
                                    rectangle(pozx+100*j-4, pozy+100*(i!=3?i:i-1)+15, pozx+100*j+3, pozy+100*(i!=3?i:i-1)+84);
                                    floodfill(pozx+100*j-3, pozy+100*(i!=3?i:i-1)+16, WHITE);
                                    setcolor(RED);
                                    setfillstyle(SOLID_FILL, RED);
                                    rectangle(piesa[3][1], piesa[3][2], piesa[3][3], piesa[3][4]);
                                    floodfill(piesa[3][1]+1, piesa[3][2]+1, RED);
                                    setcolor(LIGHTRED);
                                    setfillstyle(SOLID_FILL, LIGHTRED);
                                    rectangle(piesa[3][1]+5, piesa[3][2]+5, piesa[3][3]-5, piesa[3][4]-5);
                                    floodfill(piesa[3][1]+6, piesa[3][2]+6, LIGHTRED);
                                    setcolor(BLUE);
                                    setfillstyle(SOLID_FILL, BLUE);
                                    rectangle(buton[kp][1], buton[kp][2], buton[kp][3], buton[kp][4]);
                                    rectangle(buton[kp][1]+4, buton[kp][2]+4, buton[kp][3]-4, buton[kp][4]-4);
                                    floodfill(buton[kp][1]+1, buton[kp][2]+1, BLUE);
                                    kp=-1;
                                    OK=1;
                                }
                                break;
                            }
                }
                else
                if(kp==8)
                {
                    for(i=1; i<=2; i++)
                        for(j=1; j<=4; j++)
                            if((pozx+100*(j-1)<=x && x<=pozx+100*(j-1)+99) && (pozy+100*i-20<=y && y<=pozy+100*i+19))
                            {
                                ig=i*2-1;
                                jg=(j!=4?(j-1)*2:4);
                                if(piesa[3][0]==1 && t->a[ig][jg]!=1 && t->a[ig][jg+1]!=1 && t->a[ig][jg+2]!=1)
                                {
                                    piesa[3][0]=0; t->a[ig][jg]=1; t->a[ig][jg+1]=1; t->a[ig][jg+2]=1;
                                    setcolor(WHITE);
                                    setfillstyle(SOLID_FILL, WHITE);
                                    rectangle(pozx+100*(j!=4?j-1:j-2)+15, pozy+100*i-4, pozx+100*(j!=4?j-1:j-2)+84, pozy+100*i+3);
                                    floodfill(pozx+100*(j!=4?j-1:j-2)+16, pozy+100*i-3, WHITE);
                                    rectangle(pozx+100*(j!=4?j:j-1)-8, pozy+100*i-8, pozx+100*(j!=4?j:j-1)+7, pozy+100*i+7);
                                    floodfill(pozx+100*(j!=4?j:j-1)-7, pozy+100*i-7, WHITE);
                                    rectangle(pozx+100*(j!=4?j:j-1)+15, pozy+100*i-4, pozx+100*(j!=4?j:j-1)+84, pozy+100*i+3);
                                    floodfill(pozx+100*(j!=4?j:j-1)+16, pozy+100*i-3, WHITE);
                                    setcolor(RED);
                                    setfillstyle(SOLID_FILL, RED);
                                    rectangle(piesa[3][1], piesa[3][2], piesa[3][3], piesa[3][4]);
                                    floodfill(piesa[3][1]+1, piesa[3][2]+1, RED);
                                    setcolor(LIGHTRED);
                                    setfillstyle(SOLID_FILL, LIGHTRED);
                                    rectangle(piesa[3][1]+5, piesa[3][2]+5, piesa[3][3]-5, piesa[3][4]-5);
                                    floodfill(piesa[3][1]+6, piesa[3][2]+6, LIGHTRED);
                                    setcolor(BLUE);
                                    setfillstyle(SOLID_FILL, BLUE);
                                    rectangle(buton[kp][1], buton[kp][2], buton[kp][3], buton[kp][4]);
                                    rectangle(buton[kp][1]+4, buton[kp][2]+4, buton[kp][3]-4, buton[kp][4]-4);
                                    floodfill(buton[kp][1]+1, buton[kp][2]+1, BLUE);
                                    kp=-1;
                                    OK=1;
                                }
                                break;
                            }
                }
            if(OK==1)
            {
                OK=0;
                isValid(t);
                if(t->complete==1)
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    d->nr=3;
                    d->tick[d->lvl]=1;
                    break;
                }
                else
                if((piesa[1][0]==0 && piesa[2][0]==0 && piesa[3][0]==0) || t->impossible==1)
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    d->nr=4;
                    break;
                }
            }
            clearmouseclick(WM_LBUTTONDOWN);
        }
    }
    for(i=1; i<=60; i++)
        fprintf(lvl, "%d ", d->tick[i]);
    rewind(lvl);
    for(i=0; i<=4; i++)
        for(j=0; j<=6; j++)
            if(i%2==1 || j%2==1)
                t->a[i][j]=0;
    if(d->nr!=2 && d->nr!=3 && d->nr!=4)
        for(i=1; i<=5; i++)
            t->c[i]=0;
}

//Deseneaza tabla de joc
void deseneazaTabla(tabla* t, data* d, language* l, FILE* lvl)
{
    setcolor(WHITE);
    rectangle(pozx-5, pozy-5, pozx+404, pozy+304);
    setfillstyle(SOLID_FILL, WHITE);
    floodfill(pozx, pozy, WHITE);
    int i, j;
    for(i=0; i<=399; i+=100)
        for(j=0; j<=299; j+=100)
        {
            setcolor(BLACK);
            rectangle(i+pozx, j+pozy, i+99+pozx, j+99+pozy);
            setfillstyle(SOLID_FILL, GREEN);
            floodfill(i+19+pozx, j+19+pozy, BLACK);
            if(t->a[j/100*2][i/100*2]==1)
            {
                readimagefile("Media/Pig.jpg", i+25+pozx, j+25+pozy, i+74+pozx, j+74+pozy);
            }
            else
            if(t->a[j/100*2][i/100*2]==2)
            {
                readimagefile("Media/Chicken.jpg", i+25+pozx, j+25+pozy, i+74+pozx, j+74+pozy);
            }
            else
            if(t->a[j/100*2][i/100*2]==3)
            {
                readimagefile("Media/Cow.jpg", i+25+pozx, j+25+pozy, i+74+pozx, j+74+pozy);
            }
            else
            if(t->a[j/100*2][i/100*2]==4)
            {
                readimagefile("Media/Horse.jpg", i+25+pozx, j+25+pozy, i+74+pozx, j+74+pozy);
            }
            else
            if(t->a[j/100*2][i/100*2]==5)
            {
                readimagefile("Media/Water.jpg", i+25+pozx, j+25+pozy, i+74+pozx, j+74+pozy);
            }
        }
    setcolor(WHITE);
    rectangle(pozx, pozy, 399+pozx, 299+pozy);
    butoaneTabla(t, d, l, lvl);
}

//Este functia pentru fereastra selectiei de nivele
void nivele(tabla* t, data* d, language* l, FILE* lvl)
{
    int poz[62][5], i, j, nr;
    char s[3];
    {
        settextstyle(BOLD_FONT, 0, 6);
        setcolor(BLUE);
        setfillstyle(SOLID_FILL, BLUE);
        rectangle((MX-textwidth(l->challenges))/2-6, 60-6, (MX-textwidth(l->challenges))/2+textwidth(l->challenges)+5, 60+textheight(l->challenges)+5);
        floodfill((MX-textwidth(l->challenges))/2+1, 61, BLUE);
        setcolor(BLACK);
        setbkcolor(LIGHTCYAN);
        outtextxy((MX-textwidth(l->challenges))/2, 60, l->challenges);
        settextstyle(BOLD_FONT, 0, 1);
    }
    {
        poz[0][1]=MX-10-textwidth(l->rprogress)-9;
        poz[0][2]=MY-10-textheight(l->rprogress)-9;
        poz[0][3]=MX-10;
        poz[0][4]=MY-10;
        setcolor(BLUE);
        rectangle(poz[0][1], poz[0][2], poz[0][3], poz[0][4]);
        setfillstyle(SOLID_FILL, BLUE);
        floodfill(poz[0][1]+1, poz[0][2]+1, BLUE);
        setcolor(LIGHTBLUE);
        rectangle(poz[0][1]+5, poz[0][2]+5, poz[0][3]-5, poz[0][4]-5);
        setfillstyle(SOLID_FILL, LIGHTBLUE);
        floodfill(poz[0][1]+6, poz[0][2]+6, LIGHTBLUE);
        setcolor(BLACK);
        setbkcolor(LIGHTBLUE);
        outtextxy(poz[0][1]+5, poz[0][2]+5, l->rprogress);
    }
    {
        poz[61][1]=10;
        poz[61][2]=10;
        poz[61][3]=60;
        poz[61][4]=60;
        setcolor(BLUE);
        rectangle(poz[61][1], poz[61][2], poz[61][3], poz[61][4]);
        setfillstyle(SOLID_FILL, BLUE);
        floodfill(poz[61][1]+1, poz[61][2]+1, BLUE);
        setcolor(LIGHTBLUE);
        rectangle(poz[61][1]+5, poz[61][2]+5, poz[61][3]-5, poz[61][4]-5);
        setfillstyle(SOLID_FILL, LIGHTBLUE);
        floodfill(poz[61][1]+6, poz[61][2]+6, LIGHTBLUE);
        readimagefile("Media/back.jpg", poz[61][1]+10, poz[61][2]+10, poz[61][3]-10, poz[61][4]-10);
    }
    for(i=0; i<=4; i++)
        for(j=1; j<=4; j++)
        {
            poz[i*4+j][1]=125+(j-1)*50;
            poz[i*4+j][2]=200+i*50;
            poz[i*4+j][3]=poz[i*4+j][1]+40;
            poz[i*4+j][4]=poz[i*4+j][2]+40;
            setcolor(GREEN);
            rectangle(poz[i*4+j][1], poz[i*4+j][2], poz[i*4+j][3], poz[i*4+j][4]);
            setfillstyle(SOLID_FILL, GREEN);
            floodfill(poz[i*4+j][1]+1, poz[i*4+j][2]+1, GREEN);
            setcolor(LIGHTGREEN);
            rectangle(poz[i*4+j][1]+5, poz[i*4+j][2]+5, poz[i*4+j][3]+5, poz[i*4+j][4]+5);
            setfillstyle(SOLID_FILL, LIGHTGREEN);
            floodfill(poz[i*4+j][1]+6, poz[i*4+j][2]+6, LIGHTGREEN);
            setbkcolor(LIGHTGREEN);
            setcolor(BLACK);
            if (d->tick[i*4+j]==1)
                readimagefile("Media/check.jpg", poz[i*4+j][3]-5, poz[i*4+j][4]-5, poz[i*4+j][3]+5, poz[i*4+j][4]+5);
            nr=i*4+j;
            if(nr/10==0)
            {
                s[0]='0'+nr;
                s[1]='\0';
            }
            else
            {
                s[0]='0'+nr/10;
                s[1]='0'+nr%10;
                s[2]='\0';
            }
            outtextxy(poz[i*4+j][1]+(50-textwidth(s))/2, poz[i*4+j][2]+(50-textheight(s))/2, s);

            poz[20+i*4+j][1]=125+190+70+(j-1)*50;
            poz[20+i*4+j][2]=200+i*50;
            poz[20+i*4+j][3]=poz[20+i*4+j][1]+40;
            poz[20+i*4+j][4]=poz[20+i*4+j][2]+40;
            setcolor(BROWN);
            rectangle(poz[20+i*4+j][1], poz[20+i*4+j][2], poz[20+i*4+j][3], poz[20+i*4+j][4]);
            setfillstyle(SOLID_FILL, BROWN);
            floodfill(poz[20+i*4+j][1]+1, poz[20+i*4+j][2]+1, BROWN);
            setcolor(YELLOW);
            rectangle(poz[20+i*4+j][1]+5, poz[20+i*4+j][2]+5, poz[20+i*4+j][3]+5, poz[20+i*4+j][4]+5);
            setfillstyle(SOLID_FILL, YELLOW);
            floodfill(poz[20+i*4+j][1]+6, poz[20+i*4+j][2]+6, YELLOW);
            setbkcolor(YELLOW);
            setcolor(BLACK);
            if (d->tick[20+i*4+j]==1)
                readimagefile("Media/check.jpg", poz[20+i*4+j][3]-5, poz[20+i*4+j][4]-5, poz[20+i*4+j][3]+5, poz[20+i*4+j][4]+5);
            nr=20+i*4+j;
            s[0]='0'+nr/10;
            s[1]='0'+nr%10;
            s[2]='\0';
            outtextxy(poz[20+i*4+j][1]+(50-textwidth(s))/2, poz[20+i*4+j][2]+(50-textheight(s))/2, s);

            poz[40+i*4+j][1]=125+(190+70)*2+(j-1)*50;
            poz[40+i*4+j][2]=200+i*50;
            poz[40+i*4+j][3]=poz[40+i*4+j][1]+40;
            poz[40+i*4+j][4]=poz[40+i*4+j][2]+40;
            setcolor(RED);
            rectangle(poz[40+i*4+j][1], poz[40+i*4+j][2], poz[40+i*4+j][3], poz[40+i*4+j][4]);
            setfillstyle(SOLID_FILL, RED);
            floodfill(poz[40+i*4+j][1]+1, poz[40+i*4+j][2]+1, RED);
            setcolor(LIGHTRED);
            rectangle(poz[40+i*4+j][1]+5, poz[40+i*4+j][2]+5, poz[40+i*4+j][3]+5, poz[40+i*4+j][4]+5);
            setfillstyle(SOLID_FILL, LIGHTRED);
            floodfill(poz[40+i*4+j][1]+6, poz[40+i*4+j][2]+6, LIGHTRED);
            setbkcolor(LIGHTRED);
            setcolor(BLACK);
            if (d->tick[40+i*4+j]==1)
                readimagefile("Media/check.jpg", poz[40+i*4+j][3]-5, poz[40+i*4+j][4]-5, poz[40+i*4+j][3]+5, poz[40+i*4+j][4]+5);
            nr=40+i*4+j;
            s[0]='0'+nr/10;
            s[1]='0'+nr%10;
            s[2]='\0';
            outtextxy(poz[40+i*4+j][1]+(50-textwidth(s))/2, poz[40+i*4+j][2]+(50-textheight(s))/2, s);
        }
    int OK=0, x, y;
    while(1)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            x=mousex();
            y=mousey();
            if((poz[0][1]<=x && x<=poz[0][3])&&(poz[0][2]<=y && y<=poz[0][4]))
            {
                for(i=1; i<=60; i++)
                {
                    d->tick[i]=0;
                    fprintf(lvl, "%d ", d->tick[i]);
                }
                rewind(lvl);
                clearmouseclick(WM_LBUTTONDOWN);
                d->nr=1;
                break;
            }
            else
            if((poz[61][1]<=x && x<=poz[61][3])&&(poz[61][2]<=y && y<=poz[61][4]))
            {
                clearmouseclick(WM_LBUTTONDOWN);
                d->nr=0;
                break;
            }
            else
            for(nr=1; nr<=60; nr++)
                if((poz[nr][1]+5<=x && x<=poz[nr][3]+5) && (poz[nr][2]+5<=y && y<=poz[nr][4]+5))
                {
                    for(i=0; i<5; i+=2)
                        for(j=0; j<7; j+=2)
                            {
                                t->a[i][j]=d->a[nr][2*i+j/2+1];
                                if(t->a[i][j]!=0)
                                    t->c[t->a[i][j]]++;
                            }
                    OK=1;
                    d->lvl=nr;
                    d->nr=2;
                    break;
                }
            clearmouseclick(WM_LBUTTONDOWN);
            if(OK==1)
                break;
        }
    }
}

//Verifica si atribuie o grupa unui element din matrice
void grupaEx(tabla* t, int i, int j, int nr)
{
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, WHITE);
    rectangle(pozx+j*100+25, pozy+i*100+25, pozx+j*100+74, pozy+i*100+74);
    floodfill(pozx+j*100+26, pozy+i*100+26, WHITE);
    delay(250);
    setcolor(nr);
    setfillstyle(SOLID_FILL, nr);
    rectangle(pozx+j*100+25, pozy+i*100+25, pozx+j*100+74, pozy+i*100+74);
    floodfill(pozx+j*100+26, pozy+i*100+26, nr);
    delay(250);
    if(j+1<4 && t->a[i*2][j*2+1]==0 && t->gr[i][j+1]!=t->gr[i][j])
        {t->gr[i][j+1]=t->gr[i][j]; grupaEx(t, i, j+1, nr);}
    if(i+1<3 && t->a[i*2+1][j*2]==0 && t->gr[i+1][j]!=t->gr[i][j])
        {t->gr[i+1][j]=t->gr[i][j]; grupaEx(t, i+1, j, nr);}
    if(j-1>=0 && t->a[i*2][j*2-1]==0 && t->gr[i][j-1]!=t->gr[i][j])
        {t->gr[i][j-1]=t->gr[i][j]; grupaEx(t, i, j-1, nr);}
    if(i-1>=0 && t->a[i*2-1][j*2]==0 && t->gr[i-1][j]!=t->gr[i][j])
        {t->gr[i-1][j]=t->gr[i][j]; grupaEx(t, i-1, j, nr);}
}

//Verifica si atribuie o grupa pentru fiecare element
void isValidEx(tabla* t)
{
    int i, j, nr=3;
    for(i=0; i<=2; i++)
        for(j=0; j<=3; j++)
        {
            t->gr[i][j]=0;
            setfillstyle(SOLID_FILL, GREEN);
            floodfill(pozx+j*100+26, pozy+i*100+26, GREEN);
        }
    for(i=0; i<=2; i++)
        for(j=0; j<=3; j++)
        {
            if(t->gr[i][j]==0)
            {
                t->gr[i][j]=nr;
                setcolor(WHITE);
                setfillstyle(SOLID_FILL, WHITE);
                rectangle(pozx+j*100+25, pozy+i*100+25, pozx+j*100+74, pozy+i*100+74);
				floodfill(pozx+j*100+26, pozy+i*100+26, WHITE);
				delay(250);
				setcolor(nr);
				setfillstyle(SOLID_FILL, nr);
				rectangle(pozx+j*100+25, pozy+i*100+25, pozx+j*100+74, pozy+i*100+74);
				floodfill(pozx+j*100+26, pozy+i*100+26, nr);
				delay(250);
                if(j+1<4 && t->a[i*2][j*2+1]==0 && t->gr[i][j+1]!=t->gr[i][j])
                    {t->gr[i][j+1]=t->gr[i][j]; grupaEx(t, i, j+1, nr);}
                if(i+1<3 && t->a[i*2+1][j*2]==0 && t->gr[i+1][j]!=t->gr[i][j])
                    {t->gr[i+1][j]=t->gr[i][j]; grupaEx(t, i+1, j, nr);}
                if(j-1>=0 && t->a[i*2][j*2-1]==0 && t->gr[i][j-1]!=t->gr[i][j])
                    {t->gr[i][j-1]=t->gr[i][j]; grupaEx(t, i, j-1, nr);}
                if(i-1>=0 && t->a[i*2-1][j*2]==0 && t->gr[i-1][j]!=t->gr[i][j])
                    {t->gr[i-1][j]=t->gr[i][j]; grupaEx(t, i-1, j, nr);}
                nr++;
            }
        }
}

//Plaseaza butoanele, verifica ce buton a fost apasat si plaseaza gardurile
void butoaneTablaEx(tabla* t, data* d)
{
    int buton[12][5], piesa[4][5], i=1, j=1, k, x, y;
    setcolor(BLUE);
    setfillstyle(SOLID_FILL, BLUE);
    {
        rectangle(pozx+504, pozy+20, pozx+579, pozy+95);
        floodfill(pozx+505, pozy+21, BLUE);
        buton[i][1]=pozx+504;
        buton[i][2]=pozy+20;
        buton[i][3]=pozx+579;
        buton[i][4]=pozy+95;
        i++;
    }
    {
        rectangle(MX-85, pozy+112, MX-10, pozy+187);
        floodfill(MX-84, pozy+113, BLUE);
        buton[i][1]=MX-85;
        buton[i][2]=pozy+112;
        buton[i][3]=MX-10;
        buton[i][4]=pozy+187;
        i++;
    }
    {
        rectangle(pozx+504, pozy+205, pozx+579, pozy+280);
        floodfill(pozx+505, pozy+279, BLUE);
        buton[i][1]=pozx+504;
        buton[i][2]=pozy+205;
        buton[i][3]=pozx+579;
        buton[i][4]=pozy+280;
        i++;
    }
    {
        rectangle(pozx+414, pozy+112, pozx+489, pozy+187);
        floodfill(pozx+415, pozy+113, BLUE);
        buton[i][1]=pozx+414;
        buton[i][2]=pozy+112;
        buton[i][3]=pozx+489;
        buton[i][4]=pozy+187;
        i++;
    }
    {
        rectangle(pozx-90, pozy+37, pozx-15, pozy+112);
        floodfill(pozx-89, pozy+38, BLUE);
        buton[i][1]=pozx-90;
        buton[i][2]=pozy+37;
        buton[i][3]=pozx-15;
        buton[i][4]=pozy+112;
        i++;
    }
    {
        rectangle(10, pozy+37, 85, pozy+112);
        floodfill(11, pozy+38, BLUE);
        buton[i][1]=10;
        buton[i][2]=pozy+37;
        buton[i][3]=85;
        buton[i][4]=pozy+112;
        i++;
    }
    {
        rectangle(pozx-90, pozy+188, pozx-15, pozy+263);
        floodfill(pozx-89, pozy+189, BLUE);
        buton[i][1]=pozx-90;
        buton[i][2]=pozy+188;
        buton[i][3]=pozx-15;
        buton[i][4]=pozy+263;
        i++;
    }
    {
        rectangle(10, pozy+188, 85, pozy+263);
        floodfill(11, pozy+189, BLUE);
        buton[i][1]=10;
        buton[i][2]=pozy+188;
        buton[i][3]=85;
        buton[i][4]=pozy+263;
        i++;
    }
    setcolor(LIGHTBLUE);
    setfillstyle(SOLID_FILL, LIGHTBLUE);
    {
        rectangle(pozx+509, pozy+25, pozx+574, pozy+90);
        floodfill(pozx+510, pozy+26, LIGHTBLUE);
    }
    {
        rectangle(pozx+509, pozy+210, pozx+574, pozy+275);
        floodfill(pozx+510, pozy+211, LIGHTBLUE);
    }
    {
        rectangle(pozx+419, pozy+117, pozx+484, pozy+182);
        floodfill(pozx+420, pozy+118, LIGHTBLUE);
    }
    {
        rectangle(MX-80, pozy+117, MX-15, pozy+182);
        floodfill(MX-79, pozy+118, LIGHTBLUE);
    }
    {
        rectangle(15, pozy+42, 80, pozy+107);
        floodfill(16, pozy+43, LIGHTBLUE);
    }
    {
        rectangle(pozx-85, pozy+42, pozx-20, pozy+107);
        floodfill(pozx-84, pozy+43, LIGHTBLUE);
    }
    {
        rectangle(15, pozy+193, 80, pozy+258);
        floodfill(16, pozy+194, LIGHTBLUE);
    }
    {
        rectangle(pozx-85, pozy+193, pozx-20, pozy+258);
        floodfill(pozx-84, pozy+194, LIGHTBLUE);
    }
    setcolor(WHITE);
    {
        line(pozx+529, pozy+30, pozx+554, pozy+30);
        line(pozx+524, pozy+30, pozx+524, pozy+55);
        line(pozx+524, pozy+60, pozx+524, pozy+85);
    }
    {
        line(pozx+554, pozy+270, pozx+529, pozy+270);
        line(pozx+559, pozy+215, pozx+559, pozy+240);
        line(pozx+559, pozy+245, pozx+559, pozy+270);
    }
    {
        line(pozx+424, pozy+137, pozx+424, pozy+162);
        line(pozx+424, pozy+167, pozx+449, pozy+167);
        line(pozx+454, pozy+167, pozx+479, pozy+167);
    }
    {
        line(MX-20, pozy+137, MX-20, pozy+162);
        line(MX-75, pozy+132, MX-50, pozy+132);
        line(MX-45, pozy+132, MX-20, pozy+132);
    }
    {
        line(20, pozy+74, 35, pozy+74);
        line(40, pozy+74, 55, pozy+74);
        line(60, pozy+74, 75, pozy+74);
    }
    {
        line(pozx-53, pozy+47, pozx-53, pozy+62);
        line(pozx-53, pozy+67, pozx-53, pozy+82);
        line(pozx-53, pozy+87, pozx-53, pozy+102);
    }
    {
        line(20, pozy+225, 45, pozy+225);
        line(50, pozy+225, 75, pozy+225);
    }
    {
        line(pozx-53, pozy+198, pozx-53, pozy+223);
        line(pozx-53, pozy+228, pozx-53, pozy+253);
    }
    {
        buton[i][1]=10;
        buton[i][2]=10;
        buton[i][3]=buton[i][1]+50;
        buton[i][4]=buton[i][2]+50;
        setcolor(BLUE);
        rectangle(buton[i][1], buton[i][2], buton[i][3], buton[i][4]);
        setfillstyle(SOLID_FILL, BLUE);
        floodfill(buton[i][1]+1, buton[i][2]+1, BLUE);
        setcolor(LIGHTBLUE);
        rectangle(buton[i][1]+5, buton[i][2]+5, buton[i][3]-5, buton[i][4]-5);
        setfillstyle(SOLID_FILL, LIGHTBLUE);
        floodfill(buton[i][1]+6, buton[i][2]+6, LIGHTBLUE);
        readimagefile("Media/back.jpg", buton[i][1]+10, buton[i][2]+10, buton[i][3]-10, buton[i][4]-10);
        i++;
    }
    {
        buton[i][1]=buton[i-1][3]+10;
        buton[i][2]=buton[i-1][2];
        buton[i][3]=buton[i][1]+50;
        buton[i][4]=buton[i-1][4];
        setcolor(BLUE);
        rectangle(buton[i][1], buton[i][2], buton[i][3], buton[i][4]);
        setfillstyle(SOLID_FILL, BLUE);
        floodfill(buton[i][1]+1, buton[i][2]+1, BLUE);
        setcolor(LIGHTBLUE);
        rectangle(buton[i][1]+5, buton[i][2]+5, buton[i][3]-5, buton[i][4]-5);
        setfillstyle(SOLID_FILL, LIGHTBLUE);
        floodfill(buton[i][1]+6, buton[i][2]+6, LIGHTBLUE);
        readimagefile("Media/restart.jpg", buton[i][1]+10, buton[i][2]+10, buton[i][3]-10, buton[i][4]-10);
        i++;
    }
    setcolor(GREEN);
    setfillstyle(SOLID_FILL, GREEN);
    {
        rectangle(pozx+517, pozy+125, pozx+567, pozy+175);
        floodfill(pozx+518, pozy+126, GREEN);
        piesa[j][0]=1;
        piesa[j][1]=pozx+517;
        piesa[j][2]=pozy+125;
        piesa[j][3]=pozx+567;
        piesa[j][4]=pozy+175;
        j++;
    }
    {
        rectangle(112, pozy+49, 162, pozy+99);
        floodfill(113, pozy+50, GREEN);
        piesa[j][0]=1;
        piesa[j][1]=112;
        piesa[j][2]=pozy+49;
        piesa[j][3]=162;
        piesa[j][4]=pozy+99;
        j++;
    }
    {
        rectangle(112, pozy+200, 162, pozy+250);
        floodfill(113, pozy+201, GREEN);
        piesa[j][0]=1;
        piesa[j][1]=112;
        piesa[j][2]=pozy+200;
        piesa[j][3]=162;
        piesa[j][4]=pozy+250;
        j++;
    }
    setcolor(LIGHTGREEN);
    setfillstyle(SOLID_FILL, LIGHTGREEN);
    {
        rectangle(pozx+522, pozy+130, pozx+562, pozy+170);
        floodfill(pozx+523, pozy+131, LIGHTGREEN);
    }
    {
        rectangle(117, pozy+54, 157, pozy+94);
        floodfill(118, pozy+55, LIGHTGREEN);
    }
    {
        rectangle(117, pozy+205, 157, pozy+245);
        floodfill(118, pozy+206, LIGHTGREEN);
    }
    int kp=-1, ig, jg, OK=0;
    while(1)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            x=mousex();
            y=mousey();
            if((buton[9][1]<=x && x<=buton[9][3]) && (buton[9][2]<=y && y<=buton[9][4]))
            {
                clearmouseclick(WM_LBUTTONDOWN);
                d->nr=0;
                break;
            }
            else
            if((buton[10][1]<=x && x<=buton[10][3]) && (buton[10][2]<=y && y<=buton[10][4]))
            {
                clearmouseclick(WM_LBUTTONDOWN);
                d->nr=7;
                break;
            }
            else
            for(k=1; k<=8; k++)
                if(kp!=k)
                {
                    if((buton[k][1]<=x && x<=buton[k][3]) && (buton[k][2]<=y && y<=buton[k][4]) && piesa[(k>4?(k-1)/2:1)][0]==1)
                    {
                        if(kp!=-1)
                        {
                            setcolor(BLUE);
                            rectangle(buton[kp][1], buton[kp][2], buton[kp][3], buton[kp][4]);
                            rectangle(buton[kp][1]+4, buton[kp][2]+4, buton[kp][3]-4, buton[kp][4]-4);
                            setfillstyle(SOLID_FILL, BLUE);
                            floodfill(buton[kp][1]+1, buton[kp][2]+1, BLUE);
                        }
                        setcolor(LIGHTRED);
                        rectangle(buton[k][1], buton[k][2], buton[k][3], buton[k][4]);
                        rectangle(buton[k][1]+4, buton[k][2]+4, buton[k][3]-4, buton[k][4]-4);
                        setfillstyle(SOLID_FILL, LIGHTRED);
                        floodfill(buton[k][1]+1, buton[k][2]+1, LIGHTRED);
                        kp=k;
                        break;
                    }
                }
                else
                if(kp==k && kp%2==1 && kp<6)
                {
                    for(i=1; i<=3; i++)
                        if((pozx+100*i-20<=x && x<=pozx+100*i+19) && (pozy+100<=y && y<=pozy+199))
                        {
                            ig=2;
                            jg=i*2-1;
                            if(piesa[kp<5?1:2][0]==1 && t->a[kp==1?ig-1:ig-2][kp==1?jg+1:jg]!=1 && t->a[ig-1][jg]!=1 && t->a[ig][jg]!=1 && t->a[ig+1][jg]!=1 && t->a[kp==3?ig+1:ig+2][kp==3?jg-1:jg]!=1)
                            {
                                piesa[kp<5?1:2][0]=0; t->a[kp==1?ig-1:ig-2][kp==1?jg+1:jg]=1; t->a[ig-1][jg]=1; t->a[ig][jg]=1; t->a[ig+1][jg]=1; t->a[kp==3?ig+1:ig+2][kp==3?jg-1:jg]=1;
                                setcolor(WHITE);
                                setfillstyle(SOLID_FILL, WHITE);
                                if(kp==1)
                                {
                                    rectangle(pozx+100*i+15, pozy+100-4, pozx+100*i+84, pozy+100+3);
                                    floodfill(pozx+100*i+16, pozy+100-3, WHITE);
                                }
                                else
                                {
                                    rectangle(pozx+100*i-4, pozy+0+15, pozx+100*i+3, pozy+0+84);
                                    floodfill(pozx+100*i-3, pozy+0+16, WHITE);
                                }
                                rectangle(pozx+100*i-8, pozy+100-8, pozx+100*i+7, pozy+100+7);
                                floodfill(pozx+100*i-7, pozy+100-7, WHITE);
                                rectangle(pozx+100*i-4, pozy+100+15, pozx+100*i+3, pozy+100+84);
                                floodfill(pozx+100*i-3, pozy+100+16, WHITE);
                                rectangle(pozx+100*i-8, pozy+200-8, pozx+100*i+7, pozy+200+7);
                                floodfill(pozx+100*i-7, pozy+200-7, WHITE);
                                if(kp==3)
                                {
                                    rectangle(pozx+100*(i-1)+15, pozy+200-4, pozx+100*(i-1)+84, pozy+200+3);
                                    floodfill(pozx+100*(i-1)+16, pozy+200-3, WHITE);
                                }
                                else
                                {
                                    rectangle(pozx+100*i-4, pozy+200+15, pozx+100*i+3, pozy+200+84);
                                    floodfill(pozx+100*i-3, pozy+200+16, WHITE);
                                }
                                setcolor(RED);
                                setfillstyle(SOLID_FILL, RED);
                                rectangle(piesa[kp<5?1:2][1], piesa[kp<5?1:2][2], piesa[kp<5?1:2][3], piesa[kp<5?1:2][4]);
                                floodfill(piesa[kp<5?1:2][1]+1, piesa[kp<5?1:2][2]+1, RED);
                                setcolor(LIGHTRED);
                                setfillstyle(SOLID_FILL, LIGHTRED);
                                rectangle(piesa[kp<5?1:2][1]+5, piesa[kp<5?1:2][2]+5, piesa[kp<5?1:2][3]-5, piesa[kp<5?1:2][4]-5);
                                floodfill(piesa[kp<5?1:2][1]+6, piesa[kp<5?1:2][2]+6, LIGHTRED);
                                setcolor(BLUE);
                                setfillstyle(SOLID_FILL, BLUE);
                                rectangle(buton[kp][1], buton[kp][2], buton[kp][3], buton[kp][4]);
                                rectangle(buton[kp][1]+4, buton[kp][2]+4, buton[kp][3]-4, buton[kp][4]-4);
                                floodfill(buton[kp][1]+1, buton[kp][2]+1, BLUE);
                                kp=-1;
                                OK=1;
                            }
                            break;
                        }
                }
                else
                if(kp==k && kp%2==0 && kp<7)
                {
                    for(i=1; i<=2; i++)
                        for(j=1; j<=2; j++)
                            if((pozx+100*j<=x && x<=pozx+100*j+99) && (pozy+100*i-20<=y && y<=pozy+100*i+19))
                            {
                                ig=i*2-1;
                                jg=j*2;
                                if(piesa[kp<5?1:2][0]==1 && t->a[kp==4?ig-1:ig][kp==4?jg-1:jg-2]!=1 && t->a[ig][jg-1]!=1 && t->a[ig][jg]!=1 && t->a[ig][jg+1]!=1 && t->a[kp==2?ig+1:ig][kp==2?jg+1:jg+2]!=1)
                                {
                                    piesa[kp<5?1:2][0]=0; t->a[kp==4?ig-1:ig][kp==4?jg-1:jg-2]=1; t->a[ig][jg-1]=1; t->a[ig][jg]=1; t->a[ig][jg+1]=1; t->a[kp==2?ig+1:ig][kp==2?jg+1:jg+2]=1;
                                    setcolor(WHITE);
                                    setfillstyle(SOLID_FILL, WHITE);
                                    if(kp==4)
                                    {
                                        rectangle(pozx+100*j-4, pozy+100*(i-1)+15, pozx+100*j+3, pozy+100*(i-1)+84);
                                        floodfill(pozx+100*j-3, pozy+100*(i-1)+16, WHITE);
                                    }
                                    else
                                    {
                                        rectangle(pozx+100*(j-1)+15, pozy+100*i-4, pozx+100*(j-1)+84, pozy+100*i+3);
                                        floodfill(pozx+100*(j-1)+16, pozy+100*i-3, WHITE);
                                    }
                                    rectangle(pozx+100*j-8, pozy+100*i-8, pozx+100*j+7, pozy+100*i+7);
                                    floodfill(pozx+100*j-7, pozy+100*i-7, WHITE);
                                    rectangle(pozx+100*j+15, pozy+100*i-4, pozx+100*j+84, pozy+100*i+3);
                                    floodfill(pozx+100*j+16, pozy+100*i-3, WHITE);
                                    rectangle(pozx+100*(j+1)-8, pozy+100*i-8, pozx+100*(j+1)+7, pozy+100*i+7);
                                    floodfill(pozx+100*(j+1)-7, pozy+100*i-7, WHITE);
                                    if(kp==2)
                                    {
                                        rectangle(pozx+100*(j+1)-4, pozy+100*i+15, pozx+100*(j+1)+3, pozy+100*i+84);
                                        floodfill(pozx+100*(j+1)-3, pozy+100*i+16, WHITE);
                                    }
                                    else
                                    {
                                        rectangle(pozx+100*(j+1)+15, pozy+100*i-4, pozx+100*(j+1)+84, pozy+100*i+3);
                                        floodfill(pozx+100*(j+1)+16, pozy+100*i-3, WHITE);
                                    }
                                    setcolor(RED);
                                    setfillstyle(SOLID_FILL, RED);
                                    rectangle(piesa[kp<5?1:2][1], piesa[kp<5?1:2][2], piesa[kp<5?1:2][3], piesa[kp<5?1:2][4]);
                                    floodfill(piesa[kp<5?1:2][1]+1, piesa[kp<5?1:2][2]+1, RED);
                                    setcolor(LIGHTRED);
                                    setfillstyle(SOLID_FILL, LIGHTRED);
                                    rectangle(piesa[kp<5?1:2][1]+5, piesa[kp<5?1:2][2]+5, piesa[kp<5?1:2][3]-5, piesa[kp<5?1:2][4]-5);
                                    floodfill(piesa[kp<5?1:2][1]+6, piesa[kp<5?1:2][2]+6, LIGHTRED);
                                    setcolor(BLUE);
                                    setfillstyle(SOLID_FILL, BLUE);
                                    rectangle(buton[kp][1], buton[kp][2], buton[kp][3], buton[kp][4]);
                                    rectangle(buton[kp][1]+4, buton[kp][2]+4, buton[kp][3]-4, buton[kp][4]-4);
                                    floodfill(buton[kp][1]+1, buton[kp][2]+1, BLUE);
                                    kp=-1;
                                    OK=1;
                                }
                                break;
                            }
                }
                if(kp==7)
                {
                    for(i=1; i<=3; i++)
                        for(j=1; j<=3; j++)
                            if((pozx+100*j-20<=x && x<=pozx+100*j+19) && (pozy+100*(i-1)<=y && y<=pozy+100*(i-1)+99))
                            {
                                ig=(i!=3?(i-1)*2:2);
                                jg=j*2-1;
                                if(piesa[3][0]==1 && t->a[ig][jg]!=1 && t->a[ig+1][jg]!=1 && t->a[ig+2][jg]!=1)
                                {
                                    piesa[3][0]=0; t->a[ig][jg]=1; t->a[ig+1][jg]=1; t->a[ig+2][jg]=1;
                                    setcolor(WHITE);
                                    setfillstyle(SOLID_FILL, WHITE);
                                    rectangle(pozx+100*j-4, pozy+100*(i!=3?i-1:i-2)+15, pozx+100*j+3, pozy+100*(i!=3?i-1:i-2)+84);
                                    floodfill(pozx+100*j-3, pozy+100*(i!=3?i-1:i-2)+16, WHITE);
                                    rectangle(pozx+100*j-8, pozy+100*(i!=3?i:i-1)-8, pozx+100*j+7, pozy+100*(i!=3?i:i-1)+7);
                                    floodfill(pozx+100*j-7, pozy+100*(i!=3?i:i-1)-7, WHITE);
                                    rectangle(pozx+100*j-4, pozy+100*(i!=3?i:i-1)+15, pozx+100*j+3, pozy+100*(i!=3?i:i-1)+84);
                                    floodfill(pozx+100*j-3, pozy+100*(i!=3?i:i-1)+16, WHITE);
                                    setcolor(RED);
                                    setfillstyle(SOLID_FILL, RED);
                                    rectangle(piesa[3][1], piesa[3][2], piesa[3][3], piesa[3][4]);
                                    floodfill(piesa[3][1]+1, piesa[3][2]+1, RED);
                                    setcolor(LIGHTRED);
                                    setfillstyle(SOLID_FILL, LIGHTRED);
                                    rectangle(piesa[3][1]+5, piesa[3][2]+5, piesa[3][3]-5, piesa[3][4]-5);
                                    floodfill(piesa[3][1]+6, piesa[3][2]+6, LIGHTRED);
                                    setcolor(BLUE);
                                    setfillstyle(SOLID_FILL, BLUE);
                                    rectangle(buton[kp][1], buton[kp][2], buton[kp][3], buton[kp][4]);
                                    rectangle(buton[kp][1]+4, buton[kp][2]+4, buton[kp][3]-4, buton[kp][4]-4);
                                    floodfill(buton[kp][1]+1, buton[kp][2]+1, BLUE);
                                    kp=-1;
                                    OK=1;
                                }
                                break;
                            }
                }
                else
                if(kp==8)
                {
                    for(i=1; i<=2; i++)
                        for(j=1; j<=4; j++)
                            if((pozx+100*(j-1)<=x && x<=pozx+100*(j-1)+99) && (pozy+100*i-20<=y && y<=pozy+100*i+19))
                            {
                                ig=i*2-1;
                                jg=(j!=4?(j-1)*2:4);
                                if(piesa[3][0]==1 && t->a[ig][jg]!=1 && t->a[ig][jg+1]!=1 && t->a[ig][jg+2]!=1)
                                {
                                    piesa[3][0]=0; t->a[ig][jg]=1; t->a[ig][jg+1]=1; t->a[ig][jg+2]=1;
                                    setcolor(WHITE);
                                    setfillstyle(SOLID_FILL, WHITE);
                                    rectangle(pozx+100*(j!=4?j-1:j-2)+15, pozy+100*i-4, pozx+100*(j!=4?j-1:j-2)+84, pozy+100*i+3);
                                    floodfill(pozx+100*(j!=4?j-1:j-2)+16, pozy+100*i-3, WHITE);
                                    rectangle(pozx+100*(j!=4?j:j-1)-8, pozy+100*i-8, pozx+100*(j!=4?j:j-1)+7, pozy+100*i+7);
                                    floodfill(pozx+100*(j!=4?j:j-1)-7, pozy+100*i-7, WHITE);
                                    rectangle(pozx+100*(j!=4?j:j-1)+15, pozy+100*i-4, pozx+100*(j!=4?j:j-1)+84, pozy+100*i+3);
                                    floodfill(pozx+100*(j!=4?j:j-1)+16, pozy+100*i-3, WHITE);
                                    setcolor(RED);
                                    setfillstyle(SOLID_FILL, RED);
                                    rectangle(piesa[3][1], piesa[3][2], piesa[3][3], piesa[3][4]);
                                    floodfill(piesa[3][1]+1, piesa[3][2]+1, RED);
                                    setcolor(LIGHTRED);
                                    setfillstyle(SOLID_FILL, LIGHTRED);
                                    rectangle(piesa[3][1]+5, piesa[3][2]+5, piesa[3][3]-5, piesa[3][4]-5);
                                    floodfill(piesa[3][1]+6, piesa[3][2]+6, LIGHTRED);
                                    setcolor(BLUE);
                                    setfillstyle(SOLID_FILL, BLUE);
                                    rectangle(buton[kp][1], buton[kp][2], buton[kp][3], buton[kp][4]);
                                    rectangle(buton[kp][1]+4, buton[kp][2]+4, buton[kp][3]-4, buton[kp][4]-4);
                                    floodfill(buton[kp][1]+1, buton[kp][2]+1, BLUE);
                                    kp=-1;
                                    OK=1;
                                }
                                break;
                            }
                }
            if(OK==1)
            {
                OK=0;
                isValidEx(t);
            }
            clearmouseclick(WM_LBUTTONDOWN);
        }
    }
    for(i=0; i<=4; i++)
        for(j=0; j<=6; j++)
            t->a[i][j]=0;
}

//Deseneaza tabla de joc
void deseneazaTablaEx(tabla* t, data* d, language* l, FILE* lvl, FILE* txt)
{
	int i, j;
	for(i=0; i<=4; i++)
		for(j=0; j<=6; j++)
            t->a[i][j]=0;
    setcolor(WHITE);
    rectangle(pozx-5, pozy-5, pozx+404, pozy+304);
    setfillstyle(SOLID_FILL, WHITE);
    floodfill(pozx, pozy, WHITE);
    for(i=0; i<=399; i+=100)
        for(j=0; j<=299; j+=100)
        {
            setcolor(BLACK);
            rectangle(i+pozx, j+pozy, i+99+pozx, j+99+pozy);
            setfillstyle(SOLID_FILL, GREEN);
            floodfill(i+19+pozx, j+19+pozy, BLACK);
        }
    setcolor(WHITE);
    rectangle(pozx, pozy, 399+pozx, 299+pozy);
    char s[256];
    i=35;
    j=pozy+320;
    setcolor(GREEN);
    setfillstyle(SOLID_FILL, GREEN);
    rectangle(i-6, j-5, MX-i+6, MY-5);
    floodfill(i-4, j-4, GREEN);
    setcolor(LIGHTGREEN);
    setfillstyle(SOLID_FILL, LIGHTGREEN);
    rectangle(i, j, MX-i+1, MY-10);
    floodfill(i+1, j+1, LIGHTGREEN);
    setcolor(BLACK);
    setbkcolor(LIGHTGREEN);
    if(l->type==1)
    {
        while(fgets(s, 255, txt))
        {
            outtextxy(i, j, s);
            j=j+textheight(s);
            fgets(s, 255, txt);
        }
    }
    else
    {
        while(fgets(s, 255, txt))
        {
            fgets(s, 255, txt);
            outtextxy(i, j, s);
            j=j+textheight(s);
        }
    }
    rewind(txt);
    butoaneTablaEx(t, d);
}

//Este functia pentru fereasta Meniu
void meniu(data* d, language* l)
{
    int buton[6][5], i=1;
    {
        setcolor(BROWN);
        setfillstyle(SOLID_FILL, BROWN);
        buton[i][1]=MX/2-150;
        buton[i][2]=130;
        buton[i][3]=MX/2+150;
        buton[i][4]=200;
        rectangle(buton[i][1], buton[i][2], buton[i][3], buton[i][4]);
        floodfill(buton[i][1]+1, buton[i][2]+1, BROWN);
        setcolor(YELLOW);
        setfillstyle(SOLID_FILL, YELLOW);
        rectangle(buton[i][1]+5, buton[i][2]+5, buton[i][3]-5, buton[i][4]-5);
        floodfill(buton[i][1]+6, buton[i][2]+6, YELLOW);
        setcolor(BLACK);
        setbkcolor(YELLOW);
        outtextxy(buton[1][1]+(300-textwidth(l->start))/2, buton[1][2]+(70-textheight(l->start))/2, l->start);
        i++;
    }
    {
        setcolor(BROWN);
        setfillstyle(SOLID_FILL, BROWN);
        buton[i][1]=buton[i-1][1];
        buton[i][2]=buton[i-1][4]+20;
        buton[i][3]=buton[i][1]+150-10;
        buton[i][4]=buton[i][2]+70;

        buton[i+1][1]=buton[i][3]+20;
        buton[i+1][2]=buton[i][2];
        buton[i+1][3]=buton[i-1][3];
        buton[i+1][4]=buton[i][4];

        rectangle(buton[i][1], buton[i][2], buton[i][3], buton[i][4]);
        floodfill(buton[i][1]+1, buton[i][2]+1, BROWN);

        rectangle(buton[i+1][1], buton[i+1][2], buton[i+1][3], buton[i+1][4]);
        floodfill(buton[i+1][1]+1, buton[i+1][2]+1, BROWN);

        setcolor(YELLOW);
        setfillstyle(SOLID_FILL, YELLOW);
        rectangle(buton[i][1]+5, buton[i][2]+5, buton[i][3]-5, buton[i][4]-5);
        floodfill(buton[i][1]+6, buton[i][2]+6, YELLOW);

        rectangle(buton[i+1][1]+5, buton[i+1][2]+5, buton[i+1][3]-5, buton[i+1][4]-5);
        floodfill(buton[i+1][1]+6, buton[i+1][2]+6, YELLOW);

        setcolor(BLACK);
        outtextxy(buton[i][1]+(140-textwidth(l->about))/2, buton[i][2]+(70/2)-textheight(l->about), l->about);
        outtextxy(buton[i][1]+(140-textwidth(l->game))/2, buton[i][2]+(70/2), l->game);

        outtextxy(buton[i+1][1]+(140-textwidth(l->about))/2, buton[i+1][2]+(70/2)-textheight(l->start), l->about);
        outtextxy(buton[i+1][1]+(140-textwidth(l->code))/2, buton[i+1][2]+(70/2), l->code);
    }
    for(i=4; i<=5; i++)
    {
        setcolor(BROWN);
        setfillstyle(SOLID_FILL, BROWN);
        buton[i][1]=buton[1][1];
        buton[i][2]=buton[i-1][4]+20;
        buton[i][3]=buton[1][3];
        buton[i][4]=buton[i][2]+70;
        rectangle(buton[i][1], buton[i][2], buton[i][3], buton[i][4]);
        floodfill(buton[i][1]+1, buton[i][2]+1, BROWN);
        setcolor(YELLOW);
        setfillstyle(SOLID_FILL, YELLOW);
        rectangle(buton[i][1]+5, buton[i][2]+5, buton[i][3]-5, buton[i][4]-5);
        floodfill(buton[i][1]+6, buton[i][2]+6, YELLOW);
        setcolor(BLACK);
        if(i==4)
            outtextxy(buton[4][1]+(300-textwidth(l->settings))/2, buton[4][2]+(70-textheight(l->settings))/2, l->settings);
        else
        if(i==5)
            outtextxy(buton[5][1]+(300-textwidth(l->quit))/2, buton[5][2]+(70-textheight(l->quit))/2, l->quit);
    }
    int x, y;
    while(1)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            x=mousex();
            y=mousey();
            if((buton[1][1]<=x && x<=buton[1][3]) && (buton[1][2]<=y && y<=buton[1][4]))
            {
                d->nr=1;
                clearmouseclick(WM_LBUTTONDOWN);
                break;
            }
            else
            if((buton[2][1]<=x && x<=buton[2][3]) && (buton[2][2]<=y && y<=buton[2][4]))
            {
                d->nr=6;
                clearmouseclick(WM_LBUTTONDOWN);
                break;
            }
            else
            if((buton[3][1]<=x && x<=buton[3][3]) && (buton[3][2]<=y && y<=buton[3][4]))
            {
                d->nr=7;
                clearmouseclick(WM_LBUTTONDOWN);
                break;
            }
            else
            if((buton[4][1]<=x && x<=buton[4][3]) && (buton[4][2]<=y && y<=buton[4][4]))
            {
                d->nr=8;
                clearmouseclick(WM_LBUTTONDOWN);
                break;
            }
            else
            if((buton[5][1]<=x && x<=buton[5][3]) && (buton[5][2]<=y && y<=buton[5][4]))
            {
                d->nr=10;
                clearmouseclick(WM_LBUTTONDOWN);
                break;
            }
            clearmouseclick(WM_LBUTTONDOWN);
        }
    }
}

//Este functia pentru fereastra Despre joc
void despreJoc(data* d, language* l)
{
    int buton[1][5], x, y;
    {
        buton[0][1]=30;
        buton[0][2]=30;
        buton[0][3]=80;
        buton[0][4]=80;
        setcolor(BLUE);
        rectangle(buton[0][1], buton[0][2], buton[0][3], buton[0][4]);
        setfillstyle(SOLID_FILL, BLUE);
        floodfill(buton[0][1]+1, buton[0][2]+1, BLUE);
        setcolor(LIGHTBLUE);
        rectangle(buton[0][1]+5, buton[0][2]+5, buton[0][3]-5, buton[0][4]-5);
        setfillstyle(SOLID_FILL, LIGHTBLUE);
        floodfill(buton[0][1]+6, buton[0][2]+6, LIGHTBLUE);
        readimagefile("Media/back.jpg", buton[0][1]+10, buton[0][2]+10, buton[0][3]-10, buton[0][4]-10);
    }
    int i=40;
    char s[200];
    setbkcolor(LIGHTCYAN);
    setcolor(BLACK);
    if(l->type==1)
    {
        strcpy(s,"-Divide the field into separate meadows using the fences. ");
        outtextxy(25,60+i,s);
        i=i+30;
        strcpy(s,"-The horses, cows, chicken and pigs must end up in different, separate meadows.");
        outtextxy(25,60+i,s);
        i=i+30;
        strcpy(s,"-In later challenges each separate meadow must have water bucket for the animal ");
        outtextxy(25,60+i,s);
        i=i+30;
        strcpy(s," in that meadow.");
        outtextxy(25,60+i,s);
        i=i+30;
        strcpy(s,"-Not all fences are needed for every solution. Sometimes you will only need 1 or 2.");
        outtextxy(25,60+i,s);
        i=i+30;
        strcpy(s,"-You can only change the position of the 3 fences. You are not allowed to change ");
        outtextxy(25,60+i,s);
        i=i+30;
        strcpy(s," the position of the animals or the water buckets.");
        outtextxy(25,60+i,s);
        i=i+30;
        strcpy(s,"-All meadows must be occupied - there will not be any empty meadows in ");
        outtextxy(25,60+i,s);
        i=i+30;
        strcpy(s," the solution.");
        outtextxy(25,60+i,s);
        i=i+30;
        strcpy(s ,"-There are 3 types of fences in the game, 2 having the length of 3 and 1 of 2.");
        outtextxy(25,60+i,s);
        i=i+30;
        strcpy(s ,"-There are 6 buttons with fences in different positions, which will help you ");
        outtextxy(25,60+i,s);
        i=i+30;
        strcpy(s ," solve the level.");
        outtextxy(25,60+i,s);
        i=i+30;
        strcpy(s ,"-Each fence block is accompanied by a green indicator that changes color to red ");
        outtextxy(25,60+i,s);
        i=i+30;
        strcpy(s ," if that type of fence has already been used.");
        outtextxy(25,60+i,s);
    }
    else if(l->type==2)
    {
        strcpy(s,"-Impartiti campul in pajisti separate folosind gardurile. ");
        outtextxy(25,60+i,s);
        i=i+30;
        strcpy(s,"-Caii, vacile, gainile si porcii trebuie sa ajunga in pajisti diferite, separate.");
        outtextxy(25,60+i,s);
        i=i+30;
        strcpy(s,"-In provocarile ulterioare, fiecare pajiste separata trebuie sa aiba apa pentru ");
        outtextxy(25,60+i,s);
        i=i+30;
        strcpy(s," animalul din pajistea respectiva.");
        outtextxy(25,60+i,s);
        i=i+30;
        strcpy(s,"-Nu toate gardurile sunt necesare pentru fiecare solutie. Uneori vei avea nevoie ");
        outtextxy(25,60+i,s);
        i=i+30;
        strcpy(s," doar de 1 sau 2.");
        outtextxy(25,60+i,s);
        i=i+30;
        strcpy(s,"-Poti schimba doar pozitia celor 3 garduri. Nu aveti voie sa schimbati pozitia ");
        outtextxy(25,60+i,s);
        i=i+30;
        strcpy(s," animalelor sau a galetilor de apa.");
        outtextxy(25,60+i,s);
        i=i+30;
        strcpy(s,"-Toate pajistile trebuie sa fie ocupate - nu vor fi pajisti goale in solutie.");
        outtextxy(25,60+i,s);
        i=i+30;
        strcpy(s ,"-In joc exista 3 tipuri de garduri, 2 fiind de lungime 3 si 1 gard de lungime 2.");
        outtextxy(25,60+i,s);
        i=i+30;
        strcpy(s ,"-Sunt prezente 6 butoane cu garduri in diferite pozitii, care vor ajuta la ");
        outtextxy(25,60+i,s);
        i=i+30;
        strcpy(s ," rezolvarea nivelului.");
        outtextxy(25,60+i,s);
        i=i+30;
        strcpy(s ,"-Fiecare bloc de garduri este insotit de un indicator verde care isi schimba");
        outtextxy(25,60+i,s);
        i=i+30;
        strcpy(s ," culoarea in rosu daca acel tip de gard a fost deja folosit .");
        outtextxy(25,60+i,s);
    }
    while(1)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            x=mousex();
            y=mousey();
            if((buton[0][1]<=x && x<=buton[0][3]) && (buton[0][2]<=y && y<=buton[0][4]))
            {
                clearmouseclick(WM_LBUTTONDOWN);
                d->nr=0;
                break;
            }
            clearmouseclick(WM_LBUTTONDOWN);
        }
    }
}

//Este functia pentru fereastra Setari
void setting(data* d, language* l, FILE* lvl)
{
    int buton[6][5], x, y, i;
    char s[256];
    setbkcolor(LIGHTCYAN);
    setcolor(WHITE);
    {
        settextstyle(BOLD_FONT, 0, 6);
        outtextxy((MX-textwidth(l->settings))/2, 100, l->settings);
    }
    settextstyle(BOLD_FONT, 0, 4);
    {
        outtextxy(100, 100+textheight(l->settings)+((MY-110-textheight(l->settings))/2-textheight(l->language))/3*2, l->language);
    }
    {
        buton[1][1]=100+textwidth(l->language)+(MX-200-textwidth(l->language)-textwidth(l->romana)-textwidth(l->english))/3;
        buton[1][2]=100+textheight(l->settings)+((MY-110-textheight(l->settings))/2-textheight(l->language))/3*2;
        buton[1][3]=buton[1][1]+textwidth(l->english);
        buton[1][4]=buton[1][2]+textheight(l->english);
        if(l->type==1)
            setcolor(LIGHTRED);
        outtextxy(buton[1][1], buton[1][2], l->english);
        setcolor(WHITE);
    }
    {
        buton[2][1]=buton[1][3]+(MX-200-textwidth(l->language)-textwidth(l->romana)-textwidth(l->english))/3;
        buton[2][2]=buton[1][2];
        buton[2][3]=buton[2][1]+textwidth(l->romana);
        buton[2][4]=buton[2][2]+textheight(l->romana);
        if(l->type==2)
            setcolor(LIGHTRED);
        outtextxy(buton[2][1], buton[2][2], l->romana);
        setcolor(WHITE);
    }
    {
        outtextxy(100, 100+textheight(l->settings)+((MY-110-textheight(l->settings))-textheight(l->language))/3*2, l->music);
    }
    {
        buton[3][1]=100+textwidth(l->music)+(MX-200-textwidth(l->music)-textwidth(l->off)-textwidth(l->on1)-textwidth(l->on2))/4;
        buton[3][2]=100+textheight(l->settings)+((MY-110-textheight(l->settings))-textheight(l->language))/3*2;
        buton[3][3]=buton[3][1]+textwidth(l->on1);
        buton[3][4]=buton[3][2]+textheight(l->on1);
        if(d->muzic==1)
            setcolor(LIGHTRED);
        outtextxy(buton[3][1], buton[3][2], l->on1);
        setcolor(WHITE);
    }
    {
        buton[4][1]=buton[3][3]+(MX-200-textwidth(l->music)-textwidth(l->off)-textwidth(l->on1)-textwidth(l->on2))/4;
        buton[4][2]=buton[3][2];
        buton[4][3]=buton[4][1]+textwidth(l->on2);
        buton[4][4]=buton[4][2]+textheight(l->on2);
        if(d->muzic==2)
            setcolor(LIGHTRED);
        outtextxy(buton[4][1], buton[4][2], l->on2);
        setcolor(WHITE);
    }
    {
        buton[5][1]=buton[4][3]+(MX-200-textwidth(l->music)-textwidth(l->off)-textwidth(l->on1)-textwidth(l->on2))/4;
        buton[5][2]=buton[4][2];
        buton[5][3]=buton[5][1]+textwidth(l->off);
        buton[5][4]=buton[5][2]+textheight(l->off);
        if(d->muzic==0)
            setcolor(LIGHTRED);
        outtextxy(buton[5][1], buton[5][2], l->off);
        setcolor(WHITE);
    }
    {
        buton[0][1]=30;
        buton[0][2]=30;
        buton[0][3]=80;
        buton[0][4]=80;
        setcolor(BLUE);
        rectangle(buton[0][1], buton[0][2], buton[0][3], buton[0][4]);
        setfillstyle(SOLID_FILL, BLUE);
        floodfill(buton[0][1]+1, buton[0][2]+1, BLUE);
        setcolor(LIGHTBLUE);
        rectangle(buton[0][1]+5, buton[0][2]+5, buton[0][3]-5, buton[0][4]-5);
        setfillstyle(SOLID_FILL, LIGHTBLUE);
        floodfill(buton[0][1]+6, buton[0][2]+6, LIGHTBLUE);
        readimagefile("Media/back.jpg", buton[0][1]+10, buton[0][2]+10, buton[0][3]-10, buton[0][4]-10);
    }
    settextstyle(BOLD_FONT, 0, 1);
    while(1)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            x=mousex();
            y=mousey();
            if((buton[0][1]<=x && x<=buton[0][3]) && (buton[0][2]<=y && y<=buton[0][4]))
            {
                clearmouseclick(WM_LBUTTONDOWN);
                d->nr=0;
                break;
            }
            else
            if((buton[1][1]<=x && x<=buton[1][3]) && (buton[1][2]<=y && y<=buton[1][4]))
            {
                if(l->type!=1)
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    l->type=1;
                    for(i=1; i<=60; i++)
                    {
                        fprintf(lvl, "%d ", d->tick[i]);
                    }
                    fprintf(lvl, "\n%d ", l->type);
                    rewind(lvl);
                    lang(l);
                    break;
                }
            }
            else
            if((buton[2][1]<=x && x<=buton[2][3]) && (buton[2][2]<=y && y<=buton[2][4]))
            {
                if(l->type!=2)
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    l->type=2;
                    for(i=1; i<=60; i++)
                    {
                        fprintf(lvl, "%d ", d->tick[i]);
                    }
                    fprintf(lvl, "\n%d ", l->type);
                    rewind(lvl);
                    lang(l);
                    break;
                }
            }
            else
            if((buton[3][1]<=x && x<=buton[3][3]) && (buton[3][2]<=y && y<=buton[3][4]))
            {
                if(d->muzic!=1)
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    d->muzic=1;
                    PlaySound(TEXT("Media/music1.wav"), NULL, SND_LOOP | SND_ASYNC);
                    for(i=1; i<=60; i++)
                    {
                        fprintf(lvl, "%d ", d->tick[i]);
                    }
                    fprintf(lvl, "\n%d %d ", l->type, d->muzic);
                    rewind(lvl);
                    break;
                }
            }
            else
            if((buton[4][1]<=x && x<=buton[4][3]) && (buton[4][2]<=y && y<=buton[4][4]))
            {
                if(d->muzic!=2)
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    d->muzic=2;
                    PlaySound(TEXT("Media/music2.wav"), NULL, SND_LOOP | SND_ASYNC);
                    for(i=1; i<=60; i++)
                    {
                        fprintf(lvl, "%d ", d->tick[i]);
                    }
                    fprintf(lvl, "\n%d %d ", l->type, d->muzic);
                    rewind(lvl);
                    break;
                }
            }
            else
            if((buton[5][1]<=x && x<=buton[5][3]) && (buton[5][2]<=y && y<=buton[5][4]))
            {
                if(d->muzic!=0)
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    d->muzic=0;
                    PlaySound(NULL, 0, 0);
                    for(i=1; i<=60; i++)
                    {
                        fprintf(lvl, "%d ", d->tick[i]);
                    }
                    fprintf(lvl, "\n%d %d ", l->type, d->muzic);
                    rewind(lvl);
                    break;
                }
            }
            clearmouseclick(WM_LBUTTONDOWN);
        }
    }
}

//Citeste toate valorile care trebuie citite pentru aplicatie(cu o exceptie)
void citire(tabla* t, data* d, language* l, FILE* fis, FILE* lvl)
{
    int i, j;
    for(i=1; i<=60; i++)
        for(j=1; j<=12; j++)
            fscanf(fis, "%d ", &d->a[i][j]);
    for(i=1; i<=60; i++)
        fscanf(lvl, "%d ", &d->tick[i]);
    fscanf(lvl, "%d %d ", &l->type, &d->muzic);
    rewind(lvl);
    lang(l);
    if(d->muzic==1)
        PlaySound(TEXT("Media/music1.wav"), NULL, SND_LOOP | SND_ASYNC);
    else
    if(d->muzic==2)
        PlaySound(TEXT("Media/music2.wav"), NULL, SND_LOOP | SND_ASYNC);
    for(i=0; i<=4; i++)
        for(j=0; j<=6; j++)
            t->a[i][j]=0;
    for(i=0; i<=5; i++)
        t->c[i]=0;
    t->complete=0;
}

int main()
{
    FILE* fis;
    FILE* txt;
    FILE* lvl;
    tabla* t=new tabla;
    data* d=new data;
    language* l=new language;
    char s[5];
    d->nr=0;
    fis=fopen("nivel.txt", "r");
    txt=fopen("text.txt", "r");
    lvl=fopen("data.txt", "r+");
    initwindow(MX, MY, "Smart Farmer");
    settextstyle(BOLD_FONT, 0, 1);
    citire(t, d, l, fis, lvl);
    while(1)
    {
        if(d->nr==0)
        {
            fundal(d);
            meniu(d, l);
        }
        else
        if(d->nr==1)
        {
            fundal(d);
            nivele(t, d, l, lvl);
        }
        else
        if(d->nr==2)
        {
            fundal(d);
            deseneazaTabla(t, d, l, lvl);
        }
        else
        if(d->nr==3)
        {
            lvlComplete(t, d, l, lvl);
        }
        else
        if(d->nr==4)
        {
            lvlFailed(t, d, l);
        }
        else
        if(d->nr==6)
        {
            fundal(d);
            despreJoc(d, l);
        }
        else
        if(d->nr==7)
        {
            fundal(d);
            deseneazaTablaEx(t, d, l, lvl, txt);
        }
        if(d->nr==8)
        {
            fundal(d);
            setting(d, l, lvl);
        }
        else
        if(d->nr==10)
        {
            closegraph();
            break;
        }
    }
    return 0;
}
