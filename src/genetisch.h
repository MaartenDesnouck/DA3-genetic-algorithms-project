//
//  genetisch.h
//  ADIII
//
//  Created by Maarten Desnouck on 16/11/15.
//  Copyright © 2015 Maarten Desnouck. All rights reserved.
//

#ifndef genetisch_h
#define genetisch_h

#include <stdio.h>
#include "punt.h"
#include "dekkingsgraad.h"

void singleAxisCrossover(int * vermogens1, int * vermogens2, struct punt * basisstations, int aantalBasisstations, double maxBreedte, double minBreedte, double maxLengte, double minLengte);

void singleBlockCrossover(int * vermogens1, int * vermogens2, struct punt * basisstations, int aantalBasisstations, double maxBreedte, double minBreedte, double maxLengte, double minLengte);

void percentageBlockCrossover(int * vermogens1, int * vermogens2, struct punt * basisstations, int aantalBasisstations, double percentage, int minVerdelingen, int maxVerdelingen);

void mutate(int * vermogens, int aantalVermogens, int minAantalMutaties, int maxAantalMutaties, int minGrootte, int maxGrootte);
void mutate2(int * vermogens, int aantalVermogens, int minAantalMutaties, int maxAantalMutaties);

double fitness(int, struct punt *, int, struct punt *, int *, int, char *, double, double);

#endif /* genetisch_h */