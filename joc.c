/* File path: basics/simple_key.c */ 
#include <stdio.h> 
#include <ncurses.h> 
#include <menu.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
void populare2(int **a,int v2_x[1],int v2_y[1],int v3_x[2],int v3_y[2],int v4_x[3],int v4_y[3]);
void populare3(int **a,int v3_x[3],int v3_y[3],int v4_x[3],int v4_y[3]);
void verif_conf(int x,int y,int v4_x[4],int v4_y[4],int *ok,int d);
void verif_directie4(int y,int x,int d,int *v_ok);
void verif_directie3(int y,int x,int d,int *v_ok,int *v4_y,int *v4_x);          //ANTET DE
void populare4(int **a,int v4_x[3],int v4_y[3]);                          //DECLARARE FUNCTII
void verif_directie2(int y,int x,int d2,int *v_ok,int *v4_y,int *v4_x,int *v3_y,int *v3_x);
void populare1(int **a,int v2_x[1],int v2_y[1],int v3_x[2],int v3_y[2],int v4_x[3],int v4_y[3]);

void populare1(int **a,int v2_x[1],int v2_y[1],int v3_x[2],int v3_y[2],int v4_x[3],int v4_y[3])
{int okk=0,d3=3,v_ok[4]={0},x,y,dir_rand=0,ok=0,d=1;
    int okk2=0,okk3=0, okk4=0;
     do
    {
        x=rand()%9;
        y=rand()%9;
        verif_conf(x,y,v4_x,v4_y,&okk4,4);  //se verifica daca coordonatele alese sunt confundate/adiacente sau nu peste
        verif_conf(x,y,v3_x,v3_y,&okk3,3);  //coordonatele componentelor celorlalte nave
        verif_conf(x,y,v2_x,v2_y,&okk2,2);
        if(okk4==1&&okk2==1&&okk3==1)
            okk=1;
    }while(okk==0);
    a[y][x]=1;

}

void populare2(int **a,int v2_x[1],int v2_y[1],int v3_x[2],int v3_y[2],int v4_x[3],int v4_y[3])
{
    
    int d2=2,d3=3,d4=4,v_ok[4]={0},x,y,dir_rand=0;
    while(v_ok[0]==0&&v_ok[1]==0&&v_ok[2]==0&&v_ok[3]==0) //cat timp se gaseste o directie buna(aici tratez cazul in care
    {int ok=0,okk4=0,okk3=0,okk=0;  //se poate ca punctul de plecare sa fie intr-un colt inconjurat de o nava de 4 si una de 3           
    do
    {   
        x=rand()%9;
        y=rand()%9;      
        verif_conf(x,y,v4_x,v4_y,&okk4,4); //verific confundarea cu coordonatele navelor de 3 si de 4
        verif_conf(x,y,v3_x,v3_y,&okk3,3);
        if(okk4==1&&okk3==1)
            okk=1;
    }while(okk==0);
    verif_directie2(y,x,d2,v_ok,v4_y,v4_x,v3_y,v3_x);
    }
    a[y][x]=2;
    while(v_ok[dir_rand]!=1)
    {
        dir_rand=(rand()%(4 - 1 + 1))+1;  
    }
    if(dir_rand==1)
    {int k=0;
        for(int i=x;i<x+d2;i++)
            {
                a[y][i]=2;
                v2_y[k]=y;          //populare inspre dreapta si retin coordonatele componentelor
                v2_x[k]=i;
                k++;
            }
    }
    if(dir_rand==2)
    {int k=0;
        for(int i=y;i>y-d2;i--)
            {
                a[i][x]=2;
                v2_y[k]=i; //populare in sus si retin coordonatele componentelor
                v2_x[k]=x;
                k++;
            }
    }
    if(dir_rand==3)
    {int k=0;
        for(int i=x;i>x-d2;i--)
            {
                a[y][i]=2;
                v2_y[k]=y;      //populare inspre stanga si retin coordonatele componentelor
                v2_x[k]=i;
                k++;
            }
    }
    if(dir_rand==4)
    {int k=0;
        for(int i=y;i<y+d2;i++)
            {
                a[i][x]=2;
                v2_y[k]=i;      //populare in jos si retin coordonatele componentelor
                v2_x[k]=x;
                k++;
            }
    }
}
void populare3(int **a,int v3_x[2],int v3_y[2],int v4_x[4],int v4_y[4])
{int okk=0,d=3;
    int d3=3,v_ok[4]={0},x,y,dir_rand=0,ok=0;           
    while(v_ok[0]==0&&v_ok[1]==0&&v_ok[2]==0&&v_ok[3]==0)    //cat timp nu exista o directie valida
    {
    do
    {
        x=rand()%9;     //se cauta punctul de plecare al navei de 3
        y=rand()%9;
        verif_conf(x,y,v4_x,v4_y,&ok,4);
        if(ok==1)
            okk=1;
    }while(okk==0);
    verif_directie3(y,x,d3,v_ok,v4_y,v4_x); // verific confundarea cu componentele navei de 4
    }
    a[y][x]=3;
    while(v_ok[dir_rand]!=1)
    {
        dir_rand=(rand()%(4 - 1 + 1))+1;  
    }
    if(dir_rand==1)
    {int k=0;
        for(int i=x;i<x+d3;i++)
            {
                a[y][i]=3;
                v3_y[k]=y;
                v3_x[k]=i;
                k++;
            }
    }
    if(dir_rand==2)
    {int k=0;
        for(int i=y;i>y-d3;i--)
            {
                a[i][x]=3;
                v3_y[k]=i;
                v3_x[k]=x;
                k++;
            }
    }
    if(dir_rand==3)
    {int k=0;
        for(int i=x;i>x-d3;i--)
            {
                a[y][i]=3;
                v3_y[k]=y;
                v3_x[k]=i;
                k++;
            }
    }
    if(dir_rand==4)
    {int k=0;
        for(int i=y;i<y+d3;i++)
            {
                a[i][x]=3;
                v3_y[k]=i;
                v3_x[k]=x;
                k++;
            }
    }

}
void populare4(int **a,int v4_x[3],int v4_y[3])
{int d4=4,v_ok[4]={0},x,y,dir_rand=0;
     x=rand()%9;  //se pleaca de la o pozitie random din matrice
     y=rand()%9;  
    verif_directie4(y,x,d4,v_ok);  //se verifica din acea pozitie in ce directii se poate merge(nu se poate popula matricea in exteriorul ei)
    while(v_ok[dir_rand]!=1)
    {
        dir_rand=(rand()%(4 - 1 + 1))+1;   //la prima directie random buna se opreste cautarea
    }
    if(dir_rand==1)
    {int k=0;
        for(int i=x;i<x+d4;i++)                  /// dir_rand 1 ---- dreapta
            {                                    /// dir_rand 2 ---- sus
                a[y][i]=4;                       /// dir_rand 3 ---- stanga                            
                v4_y[k]=y;                       /// dir_rand 4 ---- jos
                v4_x[k]=i;
                k++;
            }
    }
    if(dir_rand==2)
    {int k=0;
        for(int i=y;i>y-d4;i--)
            {
                a[i][x]=4;
                v4_y[k]=i;
                v4_x[k]=x;
                k++;
            }
    }
    if(dir_rand==3)
    {int k=0;
        for(int i=x;i>x-d4;i--)
            {
                a[y][i]=4;
                v4_y[k]=y;
                v4_x[k]=i;
                k++;
            }
    }
    if(dir_rand==4)
    {int k=0;
        for(int i=y;i<y+d4;i++)
            {
                a[i][x]=4;
                v4_y[k]=i;
                v4_x[k]=x;
                k++;
            }
    }
}
void verif_directie2(int y,int x,int d2,int *v_ok,int *v4_y,int *v4_x,int *v3_y,int *v3_x)
{int ok1=1,ok2=1,ok3=1,ok4=1,aux2[10][10],d=2;
    if(x+d2-1<10)       //daca directia e buna
        {int k=0,nr=0,okk1=0,okk2=0;
            for(int i=x;i<x+d2;i++)
            {                       //verific confundarea cu celelalte componente
                verif_conf(i,y,v4_x,v4_y,&okk1,4);
                verif_conf(i,y,v3_x,v3_x,&okk2,3);
                if(okk1==0&&okk2==0) //daca s-a suprapus undeva
                    ok1=0;           //directia nu va fi buna
            }                           
        }
        else //altfel nu e buna directia
         ok1=0;   /// nava ar fi scrisa in afara matricei
          
    if(y-d2+1>=0)
        {
          int k=0,nr=0,okk1=0,okk2=0;
          for(int i=y;i>y-d2;i--)
            { 
                verif_conf(x,i,v4_x,v4_y,&okk1,4);
                verif_conf(x,i,v3_x,v3_x,&okk2,3);
                if(okk1==0&&okk2==0)
                    ok2=0;
            }
        } 
        else 
            ok2=0;    
    if(x-d2+1>=0)
        {
            int k=0,nr=0,okk1=0,okk2=0;
            for(int i=x;i>x-d2;i--)
            {
                verif_conf(i,y,v4_x,v4_y,&okk1,4);
                verif_conf(i,y,v3_x,v3_x,&okk2,3);
                if(okk1==0&&okk2==0)
                    ok3=0;
                    
            }
        }
        else 
         ok3=0;
    if(y+d2-1<10)
        {
            int k=0,nr=0,okk1=0,okk2=0;
            for(int i=y;i<y+d2;i++)
            {
                verif_conf(x,i,v4_x,v4_y,&okk1,4);
                verif_conf(x,i,v3_x,v3_x,&okk2,3);
                if(okk1==0&&okk2==0)
                    ok4=0;
            }
        }
    else 
         ok4=0;
    v_ok[1]=ok1;v_ok[2]=ok2;v_ok[3]=ok3;v_ok[4]=ok4;
}
void verif_directie3(int y,int x,int d3,int *v_ok,int *v4_y,int *v4_x)
{int ok1=1,ok2=1,ok3=1,ok4=1,d=3;
    if(x+d3-1<10)
        {int k=0,nr=0,ok=0;
            for(int i=x;i<x+d3;i++)
            {
                verif_conf(i,y,v4_x,v4_y,&ok,4);
                if(ok==0)
                    ok1=0;
            }                           
        }
        else 
         ok1=0;      /// daca cumva nava ar depasi limitele matricei
    if(y-d3+1>=0)
        {
            int k=0,nr=0,ok=0;
            for(int i=y;i>y-d3;i--)
            {
                verif_conf(x,i,v4_x,v4_y,&ok,4);
                if(ok==0)
                    ok2=0; 
            }  
        } 
            else 
        ok2=0;
    if(x-d3+1>=0)
        {
            int k=0,nr=0,ok=0;
            for(int i=x;i>x-d3;i--)
            {
                verif_conf(i,y,v4_x,v4_y,&ok,4);
                if(ok==0)
                    ok3=0;      
            }
        }
        else 
            ok3=0;
    if(y+d3-1<10)
        {
            int k=0,nr=0,ok=0;
            for(int i=y;i<y+d3;i++)
            {
                verif_conf(x,i,v4_x,v4_y,&ok,4);
                if(ok==0)
                    ok4=0;
            }
        }
    else 
         ok4=0; 
    v_ok[1]=ok1;v_ok[2]=ok2;v_ok[3]=ok3;v_ok[4]=ok4;
}
void verif_directie4(int y,int x,int d4,int *v_ok)
{int ok1=0,ok2=0,ok3=0,ok4=0; //4 ok-uri pt 4 directii 
    if(x+d4-1<10)
        ok1=1;
    if(y-d4+1>=0)
        ok2=1;
    if(x-d4+1>=0)
        ok3=1;
    if(y+d4-1<10)
        ok4=1;
    v_ok[1]=ok1;v_ok[2]=ok2;v_ok[3]=ok3;v_ok[4]=ok4; 
}
void verif_conf(int x,int y,int v_x[4],int v_y[4],int *ok,int d)
{int okf=0,n=0; //se presupune neconfundat initial
n=d;
    for(int i=0;i<n;i++)
        {       //cel mai important if chiar daca e destul de lung sorry acesta verifica toate pozitiile de lipire componentelor distincte ale navelor sau suprapunerile, verifica stanga dreapta sus jos, colturiele si pozitia principala
           if((x==v_x[i]&&y==v_y[i])||(x-1==v_x[i]&&y-1==v_y[i])||(x==v_x[i]&&y-1==v_y[i])||(x+1==v_x[i]&&y-1==v_y[i])||(x-1==v_x[i]&&y==v_y[i])||(x+1==v_x[i]&&y==v_y[i])||(x-1==v_x[i]&&y+1==v_y[i])||(x==v_x[i]&&y+1==v_y[i])||(x+1==v_x[i]&&y+1==v_y[i]))   
                okf=1;} //daca se gaseste confundare okf se schimba
        if(okf==0)  //daca  okf ramane acelasi inseamna ca nu s-a confundat
            *ok=1;
        else 
            *ok=0;   //altfel inseamna ca s-a confundat

}
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0])) 
#define CTRLD  2
#define WIDTH 30 
#define HEIGHT 10
char *choices2[]={                         
     "0", "0", "0", "0", "0", "0", "0", "0", "0", "0",                         
     "0", "0", "0", "0", "0", "0", "0", "0", "0", "0",                        
     "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", 
     "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", 
     "0", "0", "0", "0", "0", "0", "0", "0", "0", "0",  //matrice default de inceput
     "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", 
     "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", 
     "0", "0", "0", "0", "0", "0", "0", "0", "0", "0",
     "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", 
     "0", "0", "0", "0", "0", "0", "0", "0", "0", "0",                                   
        };


char *choices[] = {
                              "NEW GAME",   //obtiunile de joc
                               "Exit",                         
                        };
void legenda()
{
    int x=70;
    move(2,x);
    printw("PENTRU INCHIDERE JOC: 2xQ");
    move(3,x);
    printw("NAVIGATI CU SAGETILE");
    move(4,x);
    printw("ATACATI CU tasta ENTER"); // ma mut la coordonate convenabile si afisez legenda jocului cu instructiuni
    move(5,x);
    printw("PENTRU 10 MUTARI INAINTE: tasta D");
    move(6,x);
    printw("0 - TEREN NECUNOSCUT");
    move(7,x);
    printw("# - NAVA NIMERITA");
    move(8,x);
    printw("& - NU ERA NAVA ACOLO"); 
}
void scor(int scor1,int scor2)
{
    int x1=1,y=13,x2=33;
    move(y,x1);                         //ma mut la coordonate convenabile si afisez scorul
    printw("SCORTUL TAU: %d",scor1);
    move(y,x2);
    printw("SCORUL CALCULATORULUI: %d",scor2);
}
void matrice_dreapta(char f2[10][10])
{
    int a=2,b=35;
        move(a,b);
        for(int i=0;i<10;i++)
            {for(int j=0;j<10;j++)
                if(j<9)                         //afisez matricea mea de joc in dreapta
                    printw("%c  ",f2[i][j]);
                else
                    printw("%c ",f2[i][j]);
            move(++a,b);
            }
    refresh();
}
void interfata(char f1[10][10],char f2[10][10],int *s1,int *s2)
{   int scor1=*s1,scor2=*s2;
    char *corect="#",*gresit="&";
    int v_x[101]={0},v_y[101]={0};
    int startx = 0;
    int n=10;
    int x=0,y=0;  //se pleadca de la coordonatele (x,y)=(1,1)
         int mx=9,my=9; //maximul pe linie si pe coloana
         clear();
         int choi;
         ITEM **my_items;
         
         MENU *my_menu;
         WINDOW *my_menu_win,*c_win;
         int n_choices,i,c;
         initscr();
         start_color();
         cbreak();                  //toate comenzile de aici sunt luate din pdful de 99 de pagini despre meniuri
         noecho();                  //am luat meniul cu 6 coloane si 2 linii si l-am modificat in asa fel in cat sa
         keypad(stdscr,TRUE);       //aiba 10 coloane si 10 linii
         init_pair(1,COLOR_RED,COLOR_BLACK);
         init_pair(2, COLOR_CYAN, COLOR_BLACK); 

         n_choices=ARRAY_SIZE(choices2);
         my_items=(ITEM **)calloc(n_choices,sizeof(ITEM*));
         for(i=0;i<n_choices;++i)
            my_items[i]=new_item(choices2[i],choices2[i]);
        
        my_menu=new_menu((ITEM**)my_items);

        menu_opts_off(my_menu,O_SHOWDESC);

        my_menu_win = newwin(12, 65, 1, 1);
        c_win=newwin(12,35,1,32);         
        keypad(my_menu_win,TRUE);
        keypad(c_win,TRUE);

        set_menu_win(my_menu, my_menu_win);
        set_menu_win(my_menu, c_win);         
        set_menu_sub(my_menu, derwin(my_menu_win, 10, 29, 1,1 ));   
        //set_menu_sub(my_menu, derwin(c_win, 2, 2, 1,32 ));               
        set_menu_format(my_menu, 10, 10);         
        set_menu_mark(my_menu,"*");
        set_menu_opts(my_menu,O_ROWMAJOR);
        box(my_menu_win, 0, 0);
        box(c_win,0,0);
        scor(scor1,scor2);
        legenda();
        refresh();
        post_menu(my_menu);                
        wrefresh(my_menu_win);
        wrefresh(c_win);
        matrice_dreapta(f2);
        move(2,2);
        int k=0;                
        while((c = wgetch(my_menu_win)) != 'q')         
        {
                   switch(c)                 //navigarea prin meniu pana se apasa tasta q
            {
                     case KEY_DOWN:                                 
                        menu_driver(my_menu,REQ_DOWN_ITEM); 
                        if(y==my)
                            y=0; //aici tin cont de coordonatele la care ma aflu in timp real, si profit de faptul ca
                        else        //la fiecare alegere de atac pornesc din coltul din stanga sus
                            ++y;                                      
                        break;                                
                    case        KEY_UP:                                        
                        menu_driver(my_menu,REQ_UP_ITEM); 
                        if(y==0)
                            y=mx;  
                        else    
                            --y;                                       
                        break;                                
                    case        KEY_LEFT:                                        
                        menu_driver(my_menu,REQ_LEFT_ITEM);
                        if(x==0)
                            x=mx; //maximul de x(9)
                        else
                            --x;  //coordonate care se modifica in timp ce ma deplasez prin meniu
                                                                
                        break;                                
                    case        KEY_RIGHT:                                        
                        menu_driver(my_menu,REQ_RIGHT_ITEM);
                        if(x==mx)
                            x=0;        //daca cumva ma aflu la margine trec inapoi la coordonate 0
                       else 
                            ++x;                                        
                        break;
                    case 10:  //asta e conditia atunci cand apas ENTER adica atac mapa calculatorului
                        if(f1[y][x]=='1'||f1[y][x]=='2'||f1[y][x]=='3'||f1[y][x]=='4')
                            {
                                choices2[y*10+x]=corect;   //modific matricea default care apare in interfata cu un semn # pentru corect
                                scor1++;            //cresc scorul daca am nimerit^^
                                *s1=scor1;              
                                interfata(f1,f2,s1,s2);     //updates recursiv interfata
                                wrefresh(my_menu_win);
                            }
                        else
                        {
                            choices2[y*10+x]=gresit;    //pun alt semn daca e gresit (&)
                            wrefresh(my_menu_win);
                            int x2,y2,ok=1;
                            do
                            {
                            x2=rand()%9;            //aici intru intr-un do while de randomizare in care
                            y2=rand()%9;        //calculatorul cauta casute de atacat pana cand acesta intalneste un 0
                            if(f2[y2][x2]=='0')
                                {//sleep(2);
                                ok=0;
                                 f2[y2][x2]='&';
                                 wrefresh(my_menu_win);
                                 matrice_dreapta(f2);           //updatez matricea din dreapta(matricea mea atacata)
                                 scor(scor1,scor2);}//updatez scorul

                            if(f2[y2][x2]=='1'||f2[y2][x2]=='2'||f2[y2][x2]=='3'||f2[y2][x2]=='4') //daca calculatorul a nimerit
                                {
                                scor2++;    //cresc scorul calculatorului
                                *s2=scor2;
                                //sleep(2); //ii dau un delay de 2 secunde
                                f2[y2][x2]='#'; //modific matricea mea 
                                scor(scor1,scor2); //updatez scorul
                                wrefresh(my_menu_win);
                                matrice_dreapta(f2);}
                            }while(ok==1);
                            interfata(f1,f2,s1,s2); //updatez recursiv interfata
                            wrefresh(my_menu_win);
                        }
                    case    'd' :  //tasta d se foloseste pt "destroy" a 10 casute din ambele parti
                    {int x2,y2,nr=0;
                            while(nr<10)
                            {
                            x2=rand()%10;
                            y2=rand()%10;
                            if(f2[y2][x2]=='0')
                                {nr++; //cresc nr-ul daca gasesc 0
                                 f2[y2][x2]='&';
                                 wrefresh(my_menu_win);
                                 matrice_dreapta(f2);
                                 scor(scor1,scor2);
                                 
                                 }
                            if(f2[y2][x2]=='1'||f2[y2][x2]=='2'||f2[y2][x2]=='3'||f2[y2][x2]=='4')
                                {
                                scor2++;
                                nr++;  //cresc nr-ul daca gasesc nava, DAR NU IL CRESC DACA ATACA UN #, astfel 
                                *s2=scor2;  //se vor ataca exact 10 casute neatacate(si nu mai putine)
                                f2[y2][x2]='#';
                                scor(scor1,scor2);
                                wrefresh(my_menu_win);
                                matrice_dreapta(f2);  //updatez matricea mea atacata
                                }
                            }
                            nr=0;
                            while(nr<10)
                            {
                            x2=rand()%10;
                            y2=rand()%10;
                            if(f1[y2][x2]=='0')
                                {nr++;                /////in acelasi mod ca mai sus atac si matricea calculatorului
                                 choices2[y2*10+x2]=gresit;
                                 wrefresh(my_menu_win);
                                 scor(scor1,scor2);
                                 }
                            if(f1[y2][x2]=='1'||f1[y2][x2]=='2'||f1[y2][x2]=='3'||f1[y2][x2]=='4')
                                {
                                scor1++;
                                nr++;
                                *s1=scor1;
                                choices2[y2*10+x2]=corect;
                                scor(scor1,scor2);
                                wrefresh(my_menu_win);
                                }
                            }
                            interfata(f1,f2,s1,s2);
                            wrefresh(my_menu_win);
                    }     
                    break;

            }                        
                    wrefresh(my_menu_win);         
        }
       
        unpost_menu(my_menu);
        free_menu(my_menu);         
        for(i = 0; i < n_choices; ++i)                 
        free_item(my_items[i]);         
        endwin();
} 

int n_choices = sizeof(choices) / sizeof(char *);
void print_menu(WINDOW *menu_win, int highlight);
int main() 
{srand(time(0));
int n=10,scor1=0,scor2=0;
int v4_x[5],v4_y[5],v3_x[3],v3_y[3],v2_x[2],v2_y[2],v1,v2;
int **a,x,y;
a=(int**)malloc(10*sizeof(int*));
for(int i=0;i<11;i++)               ///ALOCARE DINAMICA
    a[i]=(int*)calloc(10,sizeof(int));
populare4(a,v4_x,v4_y);   //se umple random matricea cu 4 de 4 si se salveaza coordonatele componentelor in vectorii v4_x si v4_y
populare3(a,v3_x,v3_y,v4_x,v4_y); //se umple random matricea cu 3 de 3, se trimit si coordonatele navei de 4 pentru a evita suprapunerea sau concurenta
populare2(a,v2_x,v2_y,v3_x,v3_y,v4_x,v4_y); //la fel, dar tinem cont si de coordonatele navei 4 si navei 3
populare1(a,v2_x,v2_y,v3_x,v3_y,v4_x,v4_y); // la fel
    char f1[10][10];
    char f2[10][10];
    FILE *fis1,*fis2,*fis3;
    fis1=fopen("fis1.txt","wt");
    fis3=fopen("fis2.txt","rt");
    for(int i=0;i<10;i++)
        {for(int j=0;j<10;j++)
            fprintf(fis1,"%d ",a[i][j]);
    fprintf(fis1,"\n");}
    fclose(fis1);
    fis2=fopen("fis1.txt","rb");
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            {fscanf(fis2,"%s",&f1[i][j]);
            }
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            {fscanf(fis3,"%s",&f2[i][j]);
            }
    //fclose(fis1);
    fclose(fis2);
    fclose(fis3);
    int v_x[101]={0},v_y[101]={0};
    int startx= 0;    
    int starty = 0;
    ITEM **my_items;
    int  n_choices, i,c;
    MENU *my_menu;
    WINDOW *my_menu_win;
      
    WINDOW *menu_win;
    int highlight = 2;                  /////ACEST MENIU ESTE LUAT TOT DIN PDF-UL DE 99 DE PAGINI CU NCURSES, meniu cu 2 obtiuni
    int choice = 0;                     //una de incepere a jocului si una de iesire din joc  
    initscr();               
    clear();                
    noecho();                
    cbreak();/* Pastrarea liniei este dezactivata. Paseaza totul mie. */         
    startx = (80 - WIDTH) / 2;         
    starty = (24 - HEIGHT) / 2;         
    menu_win = newwin(HEIGHT, WIDTH, starty, startx); 
    keypad(menu_win,TRUE);                
    mvprintw(0, 0, "Foloseste sagetile pentru navigare");         
    refresh();                
    print_menu(menu_win,highlight);                
    while(1)                
        {       
            c = wgetch(menu_win);                 
            switch(c)                        
            {        
                case        KEY_UP:  
                    if(highlight==1)                                                
                        highlight=n_choices;                                        
                        else                                                
                        {--highlight;
                        }                                      
                    break; 
                case        KEY_DOWN:                                        
                    if(highlight==n_choices)                                                
                        highlight=1;                                        
                    else                                                        
                        ++highlight;                                        
                    break;                                
                case        10:                                        
                    choice=highlight;                                        
                    break;                                
                default:                                        
                refresh();                                        
                break;                        
            }
            print_menu(menu_win,highlight);
            
            if(choice != 0) /* Utilizatorul a facut alegerea de a iesi din bucla infinita*/                         
                break;                
        }                             
        if(choice==1)
            interfata(f1,f2,&scor1,&scor2); //intru in functia recursiva interfata
        clrtoeol();                
        refresh(); 
        getch();            
        endwin();        
        return 0;        
 } 
void print_menu(WINDOW *menu_win, int highlight)  //functie luata tot din pdf-ul ncurses
{         
    int x, y, i;            
    x = 2;         
    y = 2;         
    box(menu_win, 0, 0);         
    for(i = 0; i < n_choices; ++i)         
    {if(highlight == i + 1) /* Alegerea curenta de iluminare*/                 
        {wattron(menu_win, A_REVERSE);                          
        mvwprintw(menu_win, y, x, "%s", choices[i]);                         
        wattroff(menu_win,A_REVERSE);                        
        }                        
        else                                
        mvwprintw(menu_win, y, x, "%s", choices[i]);                 
        ++y;                
        }                
        wrefresh(menu_win);        
    } 