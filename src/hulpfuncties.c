//
//  hulpfuncties.c
//  ADIII
//
//  Created by Maarten Desnouck on 16/11/15.
//  Copyright © 2015 Maarten Desnouck. All rights reserved.
//

#include "hulpfuncties.h"

//Afstand tussen 2 punten
double afstand(struct punt p1, struct punt p2){

    double result =  pow(pow(p1.x-p2.x, 2) + pow(p1.y-p2.y, 2),0.5);
    //printf("afstand tussen (%f,%f) en (%f,%f) = %f\n",p1.x,p1.y,p2.x,p2.y,result);
    return result;
}

//Substring
char * substring(char * string, int position, int length){
    char * pointer;
    int c;
    pointer = malloc(length+1);

    for (c = 0 ; c < length ; c++){
        *(pointer+c) = *(string+position-1);
        string++;
    }

    *(pointer+c) = '\0';

    return pointer;
}

//Random double in interval, boundries included
double randomIntervalDouble(double min, double max)
{
    double range = (max - min);
    double div = RAND_MAX/range;
    return min + (rand()/div);
}

//Random integer in interval, boundries included
int randomIntervalInt(int min, int max)
{
    int range = (max - min);
    double div = RAND_MAX/range;
    return round(min + (rand()/div));
}


//De waarde van 2 ints swappen
void swapInt(int * getal1, int * getal2) {
    int temp = *getal1;
    *getal1 = *getal2;
    *getal2 = temp;
}

//De waarde van 2 doubles swappen
void swapDouble(double * getal1, double * getal2) {
    double temp = *getal1;
    *getal1 = *getal2;
    *getal2 = temp;
}

//Max van 2 doubles
double max(double num1, double num2) {
    int result;

    if (num1 > num2){
        result = num1;
    }else{
        result = num2;
    }
    
    return result;
}

//Tel aantal lijnen in bestand
double lijnen(const char * bestandsnaam){
    FILE *fp = fopen(bestandsnaam,"r");
    int ch = 0;
    int lijnen = 0;

    while(!feof(fp)){
        ch = fgetc(fp);
        if(ch == '\n'){
            lijnen++;
        }
    }
    return lijnen;
}

//getlijn implementeren
int getNextLijn(char ** lijnpointer, int * lengte, FILE * bestand) {
    char * bufferpointer = NULL;
    char * p = bufferpointer;
    int grootte = * lengte;
    int ch;

    bufferpointer = * lijnpointer;

    //characters inlezen
    ch = fgetc(bestand);
    if(ch == EOF){
        return -1;
    }

    //init als het de eerste lijn is
    if(bufferpointer == NULL){
        bufferpointer = malloc(64);
        if (bufferpointer == NULL){
            return -1;
        }
        grootte = 64;
    }
    p = bufferpointer;

    //door het bestand iteren
    while(ch != EOF){
        //buffer vergroten
        if((p - bufferpointer) > (grootte - 1)){
            grootte = grootte + 64;
            bufferpointer = realloc(bufferpointer, grootte);
            //realloc mislukt
            if (bufferpointer == NULL){
                return -1;
            }
        }

        //nieuw char bijplakken
        * p++ = ch;

        //new line
        if (ch == '\n'){
            break;
        }
        ch = fgetc(bestand);
    }

    //Assigneren voor de volgende oproep
    * p++ = '\0'; //lijn afsluiten
    * lijnpointer = bufferpointer;
    * lengte = grootte;
    
    return (int)(p - bufferpointer - 1);
}

