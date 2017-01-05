//
//  graden.c
//  ADIII
//
//  Created by Maarten Desnouck on 16/11/15.
//  Copyright © 2015 Maarten Desnouck. All rights reserved.
//

#include "graden.h"

double breedtegraadNaarCoord(double minLengte, double rho){
    double ref = minLengte;
    double mpg = meterPerBreedtegraad(ref);
    return mpg*(rho-ref);
}

double meterPerBreedtegraad(double rho){
    return 111132.92-559.82*cos(2*rho)+1.175*cos(4*rho)-0.0023*cos(6*rho);
}

double lengtegraadNaarCoord(double minBreedte, double rho){
    double ref = minBreedte;
    double mpg = meterPerLengtegraad(ref);
    return -mpg*(rho-ref);
}

double meterPerLengtegraad(double rho){
    return 111412.84*cos(rho)-93.5*cos(3*rho)-0.118*cos(5*rho);
}
