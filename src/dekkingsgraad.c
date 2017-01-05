//
//  dekkingsgraad.c
//  ADIII
//
//  Created by Maarten Desnouck on 16/11/15.
//  Copyright © 2015 Maarten Desnouck. All rights reserved.
//

#include "dekkingsgraad.h"

//Dekkingsgraad bepalen adhv monte carlo sampeling
double dekkingsgraad(int aantalSamples, struct punt * gebied, int aantalGebiedPunten, struct punt * basisstations, int * vermogens, int aantalBasisstations, char * bandbreedte){
    //We kiezen random punten in de omhullende rechthoek van het gebied.
    //We checken of die punten in het gebied liggen adhv puntInVeelhoek
    //We kijken vervolgens of die bedekt zijn of niet
    //We doen dit tot er tot we het gevraagd aantal in het gebied hebben

    double Xmin = INT_MAX;
    double Xmax = INT_MIN;
    double Ymin = INT_MAX;
    double Ymax = INT_MIN;

    double x;
    double y;
    double bereiken[aantalBasisstations];

    int aantalBedekt = 0;
    int aantalBinnenGebied = 0;

    //Bereik van alle stations berekenen
    for(int r = 0; r<aantalBasisstations; r++){
        struct punt b = basisstations[r];
        bereiken[r]=bereik(b.z, bandbreedte, vermogens[r]);
    }

    //Bepalen omhullende rechthoek
    for(int p = 0; p<aantalGebiedPunten;p++){
        x = gebied[p].x;
        y = gebied[p].y;
        if(x<Xmin){
            Xmin = x;
        }
        if(x>Xmax){
            Xmax = x;
        }
        if(y<Ymin){
            Ymin = y;
        }
        if(y>Ymax){
            Ymax = y;
        }
    }

    int teller = 0;

    //Samples nemen binnen omhullende rechthoek
    while (aantalBinnenGebied < aantalSamples) {
        teller++;
        struct punt p;
        p.x = randomIntervalDouble(Xmin, Xmax);
        p.y = randomIntervalDouble(Ymin, Ymax);

        //Checken of sample binnen gebied valt
        if (pointInPolygon(p, 25, gebied)) {
            aantalBinnenGebied++;
            bool bedekt = false;
            int getesteBasisstations = 0;

            //Checken of sample bedekt wordt door een mast, stoppen van zodra er 1 mast hem bedekt
            while(bedekt == false && getesteBasisstations<aantalBasisstations){

                if (afstand(p, basisstations[getesteBasisstations])<bereiken[getesteBasisstations]) {
                    bedekt = true;
                    aantalBedekt++;
                }
                getesteBasisstations++;

            }
        }
    }
    //printf("aantalBedekt = %d, aantalBinnenGebied = %d, totaal = %d \n",aantalBedekt,aantalBinnenGebied,teller);
    return (double)aantalBedekt/(double)aantalBinnenGebied;
}