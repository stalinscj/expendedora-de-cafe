#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <time.h>
#include <winbgim.h>
#define TAM_PANTALLAX 1016   // Tamaño de pantalla horizontal ML(1016) PC(1273)
#define TAM_PANTALLAY 543   // Tamaño de pantalla vertical    ML(543)  PC(959)

void outintxy(int x, int y, int num){

    char cad_int[10];

    itoa(num,cad_int,10);

    outtextxy(x,y,cad_int);

}

void pintar_maquina(){

    setlinestyle(3,3,17);
    settextstyle(1,0,8);
    outtextxy(110,22,"Café 7");
    settextstyle(1,0,5);
    outtextxy(465,55,"bsf");
    setcolor(8);
    rectangle(8,8,999,120);  // borde de la máquina
    rectangle(8,120,999,523);

    setlinestyle(3,3,5);
    rectangle(716,28,979,102); //cuadro del dinero

    setfillstyle(1,8);       // moneda
    fillellipse(70,220,45,45);
    setcolor(14);
    setbkcolor(8);
    circle(70,220,45);
    setcolor(0);
    settextstyle(1,0,2);
    outtextxy(34,210,"1 bsf");

    settextstyle(1,0,8);  // billete de 2 bsf
    setbkcolor(9);
    for(int i=0;i<3;i++)
        outtextxy(133,i*8 + 168,"      ");
    settextstyle(1,0,5);
    setcolor(1);
    setbkcolor(9);
    outtextxy(165,200,"2 bsf");
    rectangle(133,170,338,270);

    settextstyle(1,0,8);  // billete de 5 bsf
    setbkcolor(COLOR(255,152,27));
    for(int i=0;i<3;i++)
        outtextxy(373,i*8 + 168,"      ");
    settextstyle(1,0,5);
    setcolor(COLOR(255,35,1));
    setbkcolor(COLOR(255,152,27));
    settextstyle(1,0,5);
    outtextxy(405,200,"5 bsf");
    rectangle(373,170,578,270);


    settextstyle(1,0,8);  // cancelar orden
    setbkcolor(12);
    for(int i=0;i<3;i++)
        outtextxy(40,i*8 + 348,"      ");
    settextstyle(1,0,5);
    setcolor(4);
    setbkcolor(12);
    settextstyle(1,0,4);
    outtextxy(46,370,"Cancelar");
    outtextxy(75,400,"orden");
    rectangle(40,350,245,450);

    settextstyle(1,0,8);  // ordenar café
    setbkcolor(10);
    for(int i=0;i<3;i++)
        outtextxy(350,i*8 + 348,"      ");
    settextstyle(1,0,5);
    setcolor(2);
    setbkcolor(10);
    settextstyle(1,0,4);
    outtextxy(364,370,"Ordenar");
    outtextxy(406,400,"café");
    rectangle(350,350,555,450);


    settextstyle(1,0,2);
    setlinestyle(3,3,5);  // Case de boquilla
    for(int i=0;i<4;i++){
        setbkcolor(15);
        outtextxy(787,i*13+170,"               ");
    }
    setcolor(8);
    rectangle(785,170,925,230);

    setlinestyle(3,3,20);
    rectangle(847,238,867,258); //boquilla


    setcolor(15);
    setlinestyle(3,3,5); //vaso
    rectangle(809,320,904,459);

}

void servir_cafe(){

    settextstyle(1,1,1);
    setbkcolor(6);
    outtextxy(869,268,"                       ");

    setcolor(15);
    setlinestyle(3,3,5); //vaso
    rectangle(809,320,904,459);

    settextstyle(1,0,1);
    //sndPlaySound("vaso.wav",1);
    for(int i=10;i>1;i--){
        setbkcolor(6);
        outtextxy(813,i*13+307,"           ");
        delay(444);
    }

    settextstyle(1,1,1);
    setbkcolor(0);
    outtextxy(869,268,"        ");

    setcolor(15);
    setlinestyle(3,3,5);  //vaso
    rectangle(809,320,904,459);


    delay(2000);
    settextstyle(1,0,1);
    for(int i=10;i>1;i--){
        setbkcolor(0);
        outtextxy(813,i*13+307,"           ");

    }




}

int boton_pulsado(){

    if(((mousex()>=28) && (mousex()<=111)) && (( mousey()>=178) && (mousey()<=261)))
        return 1; // insertar 1 bsf
    if(((mousex()>=133) && (mousex()<=338)) && (( mousey()>=170) && (mousey()<=270)))
        return 2; // insertar 2 bsf
    if(((mousex()>=373) && (mousex()<=578)) && (( mousey()>=170) && (mousey()<=270)))
        return 5; // insertar 5 bsf
    if(((mousex()>=40) && (mousex()<=245)) && (( mousey()>=350) && (mousey()<=450)))
        return 4; // cancelar pedido
    if(((mousex()>=350) && (mousex()<=555)) && (( mousey()>=350) && (mousey()<=450)))
        return 0; // ordenar café

    return -1;

}


int proximo_estado(int entrada, int &estado_actual){

    int estado_siguiente;

    if(estado_actual<7)
        estado_siguiente = entrada + estado_actual;

    if((estado_actual>=7))
        estado_siguiente = estado_actual;

    if((estado_actual>=7) && (entrada==0))
        estado_siguiente=0;

    if(entrada==4)
        estado_siguiente = 0;

    estado_actual = estado_siguiente;

    return estado_siguiente;

}

int salida (int entrada, int &estado){


    if(entrada==4)
        return estado;

    if((entrada==0)&&(estado>=7)){
        servir_cafe();
    }

    return estado;
}

void mostrar_dinero(int entrada, int estado){

    int dinero = estado;

    setcolor(2);
    setbkcolor(0);
    settextstyle(1,0,1);
    outtextxy(726,41,"Dinero");
    outtextxy(726,61,"introducido");

    setcolor(4);
    setbkcolor(0);
    settextstyle(2,0,50);
    outtextxy(876,44,"    ");
    outintxy(876,44,dinero);

    settextstyle(2,0,8);
    outtextxy(921,59,"Bsf");

    if((entrada==0)&&(dinero>=7)){

        dinero = dinero -7;

        setcolor(2);
        setbkcolor(0);
        settextstyle(1,0,1);
        outtextxy(726,61,"                   ");
        outtextxy(726,61,"devuelto");

        setcolor(3);
        setbkcolor(0);
        settextstyle(2,0,50);
        outtextxy(876,44,"    ");
        outintxy(876,44,dinero);
        //sndPlaySound("caja.wav",0);

        estado=0;
        setcolor(2);
        setbkcolor(0);
        settextstyle(1,0,1);
        outtextxy(726,41,"Dinero");
        outtextxy(726,61,"introducido");

        setcolor(4);
        setbkcolor(0);
        settextstyle(2,0,50);
        outtextxy(876,44,"    ");
        outintxy(876,44,0);
    }

    if((entrada==4) && (estado!=0)){
        setcolor(2);
        setbkcolor(0);
        settextstyle(1,0,1);
        outtextxy(726,61,"                   ");
        outtextxy(726,61,"devuelto");

        setcolor(3);
        setbkcolor(0);
        settextstyle(2,0,50);
        outtextxy(876,44,"    ");
        outintxy(876,44,dinero);
        //sndPlaySound("caja.wav",0);

        estado=0;
        setcolor(2);
        setbkcolor(0);
        settextstyle(1,0,1);
        outtextxy(726,41,"Dinero");
        outtextxy(726,61,"introducido");

        setcolor(4);
        setbkcolor(0);
        settextstyle(2,0,50);
        outtextxy(876,44,"    ");
        outintxy(876,44,0);
    }



}

void imprimir_posiciondelmouse(int s){

    if(ismouseclick(WM_LBUTTONDOWN)){

        outintxy(600,200,s);
        //putpixel(mousex(),mousey(),10);

        clearmouseclick(WM_LBUTTONDOWN);
    }


}



main(){



    int estado=0,dinero,entrada=0;
    char tecla='0';

    initwindow(TAM_PANTALLAX,TAM_PANTALLAY);

        pintar_maquina();
        mostrar_dinero(entrada,estado);
        do{
            if(ismouseclick(WM_LBUTTONDOWN)){
                entrada=boton_pulsado();
                if((entrada)>=0){
                    mostrar_dinero(entrada,estado);
                    salida(entrada,estado);
                    proximo_estado(entrada,estado);
                    mostrar_dinero(entrada,estado);
                }
                clearmouseclick(WM_LBUTTONDOWN);
            }

            if(kbhit())
                tecla=getch();
        }while(tecla!=27);

    closegraph();

}
