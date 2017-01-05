//
//  puntInVeelhoek.c
//  ADIII
//
//  Created by Maarten Desnouck on 16/11/15.
//  Copyright © 2015 Maarten Desnouck. All rights reserved.
//

#include "puntInVeelhoek.h"

//  The function will return true if the point x,y is inside the polygon, or
//  false if it is not.  If the point is exactly on the edge of the polygon,
//  then the function may return true or false.
//
//  Note that division by zero is avoided because the division is protected
//  by the "if" clause which surrounds it.
//
// Source: http://alienryderflex.com/polygon/

bool pointInPolygon(struct punt p, int polyCorners, struct punt * polygon) {
    float x = p.x;
    float y = p.y;

    int i, j = polyCorners-1 ;
    bool oddNodes = false;

    for (i=0; i<polyCorners; i++) {
        if (((polygon[i].y< y && polygon[j].y>=y) || (polygon[j].y< y && polygon[i].y>=y)) &&
            (polygon[i].x<=x || polygon[j].x<=x)) {
                oddNodes^=(polygon[i].x+(y-polygon[i].y)/(polygon[j].y-polygon[i].y)*(polygon[j].x-polygon[i].x)<x);
        }
        j=i;
    }
    return oddNodes;
}