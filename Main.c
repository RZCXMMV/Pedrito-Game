#include <stdio.h>

#include "FunctionalityLibs/MainMenu.h"
#include "FunctionalityLibs/Functions.h"
#include "UI/Utils.h"


/*
    Creo que en el archivo de como jugar no es necesario hacerle nada de cuadro, solo son instrucciones,
    pero eso ya es a decision de ustedes, mi recomendacion seria que, no reparen lo que no esta mal
    
    TODO:
    (MainMenu.c)
        1.En el menu principal, acueredense de quitar los saltos de linea, ya que seran reemplazados
        con el gotoxy.

        2.Acordarse de mover la funcion "ClearScreen" anted del while(true) ya que el menu siempre se 
        estara sobre escribiendo.

        3.En la funcion "DisplayMainMenu" puede ser que haya bug al implentar la decoracion de colores
        si es asi, avisarme o fijarse en el codigo del proyecto anterior

    GetPetition
        1.Poner los clear screen en las  validaciones de errores. Ya saben que se pone al medio de la terminal
        depues de esto poner el getch para que se aprecie el cambio.

    RECOMENDACIONES:
        1.Pintar el cuadro en rojo para simular que pedrito se esta poniendo enojado, con cada resp
        aleatoria que dé.

        2.En el desplazamiento del menu, en vez de mostrar la opc actual en azul, ahora muestren 
        en rojo, al igual que en el color de la barra de carga y uni respectivamente.
        
        IMPORTANTE -> 2.1.En esta ocasion el palette de colores es blanco y rojo, el rojo solo sera usado
        en lo anteriormente especificado, y otras funciones (que imaginen), el cuadro por 
        default siempre es blanco 

*/
int main(void){

    //Principal Menu
    MoveTroughMainMenu();

    return 0;
}