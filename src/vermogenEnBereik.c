//
//  vermogenEnBereik.c
//  ADIII
//
//  Created by Maarten Desnouck on 16/11/15.
//  Copyright © 2015 Maarten Desnouck. All rights reserved.
//

#include "vermogenEnBereik.h"

//Energieverbruik van 1 mast berekenen
double energieverbruik(int ingangsvermogen){
    if (ingangsvermogen==0){
        return 0;
    } else {
        return 300 * pow(10, ingangsvermogen/10)/12800 + 1205;
    }
}

//Energieverbruik van een volledige configuratie berekenen
double totaalEnergieverbruik(int* vermogens, int aantalBasisstations){
    double totaal = 0;
    for (int station = 0; station<aantalBasisstations; station++) {
        totaal = totaal + energieverbruik(vermogens[station]);
    }

    return totaal;
}

//Bereik van 1 mast berekenen
double bereik(double hoogte, char* bandbreedte, int ingangsvermogen){
    if (ingangsvermogen==0) {
        return 0;
    }
    double PLmax = 0;
    double Lbsh = 0;
    double ka = 0;
    double kd = 0;

    //PLmax berekenen
    if(strcmp(bandbreedte,"high") == 0){
        PLmax = ingangsvermogen + 78.3;
    } else if (strcmp(bandbreedte,"low") == 0){
        PLmax = ingangsvermogen + 98.8;
    }

    //Lbsh, ka en kb berekenen
    if(hoogte > 12){
        Lbsh = -18 * log10(1 + hoogte - 12);
        ka = 54;
        kd = 18;
    } else if (hoogte <= 12){
        Lbsh = 0;
        ka = 54 - 0.8 * log10(hoogte - 12);
        kd = 18  - 15 * (hoogte - 12)/12;
    }

    return 1000 * pow(10, (PLmax-Lbsh-ka-121.34)/(20+kd));
}