//
//  hulpfuncties.h
//  ADIII
//
//  Created by Maarten Desnouck on 16/11/15.
//  Copyright © 2015 Maarten Desnouck. All rights reserved.
//

#ifndef hulpfuncties_h
#define hulpfuncties_h

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "punt.h"

double afstand(struct punt p1, struct punt p2);

char * substring(char * string, int position, int length);

double randomIntervalDouble(double min, double max);
int randomIntervalInt(int min, int max);

void swapInt(int * getal1, int * getal2);
void swapDouble(double * getal1, double * getal2);

double max(double num1, double num2);

double lijnen(const char * bestandsnaam);
int getNextLijn(char ** lijnpointer, int * lengte, FILE * bestand);

#endif /* hulpfuncties_h */