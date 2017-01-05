//
//  puntInVeelhoek.h
//  ADIII
//
//  Created by Maarten Desnouck on 16/11/15.
//  Copyright © 2015 Maarten Desnouck. All rights reserved.
//

#ifndef puntInVeelhoek_h
#define puntInVeelhoek_h

#include <stdio.h>
#include <stdbool.h>
#include "punt.h"

bool pointInPolygon(struct punt p, int polyCorners, struct punt * polygon);

#endif /* puntInVeelhoek_h */