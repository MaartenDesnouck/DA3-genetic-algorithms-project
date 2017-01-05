//
//  vermogenEnBereik.h
//  ADIII
//
//  Created by Maarten Desnouck on 16/11/15.
//  Copyright © 2015 Maarten Desnouck. All rights reserved.
//

#ifndef vermogenEnBereik_h
#define vermogenEnBereik_h

#include <stdio.h>
#include <string.h>
#include "hulpfuncties.h"

double energieverbruik(int ingangsvermogen);
double totaalEnergieverbruik(int* vermogens, int aantalBasisstations);
double bereik(double hoogte, char* bandbreedte, int ingangsvermogen);

#endif /* vermogenEnBereik_h */