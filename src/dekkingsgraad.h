//
//  dekkingsgraad.h
//  ADIII
//
//  Created by Maarten Desnouck on 16/11/15.
//  Copyright © 2015 Maarten Desnouck. All rights reserved.
//

#ifndef dekkingsgraad_h
#define dekkingsgraad_h

#include <stdio.h>
#include <limits.h>
#include "hulpfuncties.h"
#include "punt.h"
#include "vermogenEnBereik.h"
#include "puntInVeelhoek.h"

double dekkingsgraad(int aantalSamples, struct punt * gebied, int aantalGebiedpunten, struct punt * basisstations, int * vermogens, int aantalBasisstations, char * bandbreedte);

#endif /* dekkingsgraad_h */