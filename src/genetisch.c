//
//  genetisch.c
//  ADIII
//
//  Created by Maarten Desnouck on 16/11/15.
//  Copyright © 2015 Maarten Desnouck. All rights reserved.
//

#include "genetisch.h"

/*
 - Een 1-axis crossoverfunctie: we kiezen random of we horizontaal of verticaal splitsen en dan random op welke graad.
 argumenten: 2 startconfigs, het gebied.
 returnvalue: niets, doen het in place met pointers.
 */
void singleAxisCrossover(int * vermogens1, int * vermogens2, struct punt * basisstations, int aantalBasisstations, double maxBreedte, double minBreedte, double maxLengte, double minLengte){

    bool verticaal = false;
    if(randomIntervalInt(0,1)==1){
        verticaal = true;
    }

    bool eersteSectieWisselen = false;
    if(randomIntervalInt(0,1)==1){
        eersteSectieWisselen = true;
    }

    double axis;

    if(verticaal){
        axis = randomIntervalDouble(minLengte, maxLengte);
        for(int basisstation = 0; basisstation<aantalBasisstations;basisstation++){
            if(eersteSectieWisselen){
                if (basisstations[basisstation].x<axis) {
                    swapInt(&vermogens1[basisstation], &vermogens2[basisstation]);
                }
            } else {
                if (basisstations[basisstation].x>axis) {
                    swapInt(&vermogens1[basisstation], &vermogens2[basisstation]);
                }
            }
        }

    }else{
        axis = randomIntervalDouble(minBreedte, minBreedte);
        for(int basisstation = 0; basisstation<aantalBasisstations;basisstation++){
            if(eersteSectieWisselen){
                if (basisstations[basisstation].y<axis) {
                    swapInt(&vermogens1[basisstation], &vermogens2[basisstation]);
                }
            } else {
                if (basisstations[basisstation].y>axis) {
                    swapInt(&vermogens1[basisstation], &vermogens2[basisstation]);
                }
            }
        }
    }
}

/*
 - Een 1-block crossoverfunctie: We kiezen random 2 breedtegraden, 2 lengtegraden en dan welke van de 9 opties we kiezen
 argumenten: 2 startconfigs.
 returnvalue: niets, doen het in place met pointers.
 */
void singleBlockCrossover(int * vermogens1, int * vermogens2, struct punt * basisstations, int aantalBasisstations, double maxBreedte, double minBreedte, double maxLengte, double minLengte){

    double vertaxis1 = randomIntervalDouble(minBreedte, maxBreedte);
    double vertaxis2 = randomIntervalDouble(minBreedte, maxBreedte);
    if (vertaxis1>vertaxis2) {
        swapDouble(&vertaxis1, &vertaxis2);
    }
    double horaxis1 = randomIntervalDouble(minLengte, maxLengte);
    double horaxis2 = randomIntervalDouble(minLengte, maxLengte);
    if (horaxis1>horaxis2) {
        swapDouble(&horaxis1, &horaxis2);
    }

    int sectie = randomIntervalInt(0,8);
    bool eersteSectieWisselen = false;
    if(randomIntervalInt(0,1)==1){
        eersteSectieWisselen = true;
    }

    if (eersteSectieWisselen) {
        for(int basisstation = 0; basisstation<aantalBasisstations;basisstation++){
            swapInt(&vermogens1[basisstation], &vermogens2[basisstation]);
        }
    }

    if(sectie==0){
        for(int basisstation = 0; basisstation<aantalBasisstations;basisstation++){
            if (basisstations[basisstation].x>horaxis2 &&
                basisstations[basisstation].y<vertaxis1) {
                swapInt(&vermogens1[basisstation], &vermogens2[basisstation]);
            }
        }
        return;
    }
    if(sectie==1){
        for(int basisstation = 0; basisstation<aantalBasisstations;basisstation++){
            if (basisstations[basisstation].x>horaxis2 &&
                basisstations[basisstation].y>vertaxis1 &&
                basisstations[basisstation].y<vertaxis2) {
                swapInt(&vermogens1[basisstation], &vermogens2[basisstation]);
            }
        }
        return;
    }
    if(sectie==2){
        for(int basisstation = 0; basisstation<aantalBasisstations;basisstation++){
            if (basisstations[basisstation].x>horaxis2 &&
                basisstations[basisstation].y>vertaxis2) {
                swapInt(&vermogens1[basisstation], &vermogens2[basisstation]);
            }
        }
        return;
    }
    if(sectie==3){
        for(int basisstation = 0; basisstation<aantalBasisstations;basisstation++){
            if (basisstations[basisstation].x>horaxis1 &&
                basisstations[basisstation].x<horaxis2 &&
                basisstations[basisstation].y<vertaxis1) {
                swapInt(&vermogens1[basisstation], &vermogens2[basisstation]);
            }
        }
        return;
    }
    if(sectie==4){
        for(int basisstation = 0; basisstation<aantalBasisstations;basisstation++){
            if (basisstations[basisstation].x>horaxis1 &&
                basisstations[basisstation].x<horaxis2 &&
                basisstations[basisstation].y>vertaxis1 &&
                basisstations[basisstation].y<vertaxis2) {
                swapInt(&vermogens1[basisstation], &vermogens2[basisstation]);
            }
        }
        return;
    }
    if(sectie==5){
        for(int basisstation = 0; basisstation<aantalBasisstations;basisstation++){
            if (basisstations[basisstation].x>horaxis1 &&
                basisstations[basisstation].x<horaxis2 &&
                basisstations[basisstation].y>vertaxis2) {
                swapInt(&vermogens1[basisstation], &vermogens2[basisstation]);
            }
        }
        return;
    }
    if(sectie==6){
        for(int basisstation = 0; basisstation<aantalBasisstations;basisstation++){
            if (basisstations[basisstation].x<horaxis1 &&
                basisstations[basisstation].y<vertaxis1) {
                swapInt(&vermogens1[basisstation], &vermogens2[basisstation]);
            }
        }
        return;
    }
    if(sectie==7){
        for(int basisstation = 0; basisstation<aantalBasisstations;basisstation++){
            if (basisstations[basisstation].x<horaxis1 &&
                basisstations[basisstation].y>vertaxis1 &&
                basisstations[basisstation].y<vertaxis2) {
                swapInt(&vermogens1[basisstation], &vermogens2[basisstation]);
            }
        }
        return;
    }
    if(sectie==8){
        for(int basisstation = 0; basisstation<aantalBasisstations;basisstation++){
            if (basisstations[basisstation].x<horaxis1 &&
                basisstations[basisstation].y>vertaxis2) {
                swapInt(&vermogens1[basisstation], &vermogens2[basisstation]);
            }
        }
        return;
    }
}

/*
 - Een fixed percentage block crossoverfunctie: een groot antal blokken en dan crossover doen adhv het percentage
 argumenten: 2 startconfigs, een percentage, een kansinterval van aantal verdelingen
 returnvalue: niets, doen het in place met pointers.
 */
void percentageBlockCrossover(int * vermogens1, int * vermogens2, struct punt * basisstations, int aantalBasisstations, double percentage, int minVerdelingen, int maxVerdelingen){
    /* NOT IMPLEMENTED */
}

/*
 - Een mutatiefunctie die we toepassen op new-born exemplaren
 argumenten: 1 config, een kansinterval voor aantal mutaties, een kansinterval voor grootte van de mutatie
 returnvalue: niets, doen het in place met pointers.
 */
void mutate(int * vermogens, int aantalVermogens, int minAantalMutaties, int maxAantalMutaties, int minGrootte, int maxGrootte){
    int aantalMutaties = randomIntervalInt(minAantalMutaties, maxAantalMutaties);

    for(int mutatie = 0; mutatie<=aantalMutaties; mutatie++){
        int basisstation = randomIntervalInt(0, aantalVermogens-1);
        vermogens[basisstation] += randomIntervalInt(minGrootte, maxGrootte);
        if (vermogens[basisstation]<0) {
            vermogens[basisstation]=0;
        } else if (vermogens[basisstation]>43) {
            vermogens[basisstation]=43;
        }
    }
}
/*
 - Een EXTRA mutatiefunctie die we toepassen op new-born exemplaren
 Deze zet een random mast op max of volledig af
 argumenten: 1 config, een kansinterval voor aantal mutaties, een kansinterval voor grootte van de mutatie
 returnvalue: niets, doen het in place met pointers.
 */
void mutate2(int * vermogens, int aantalVermogens, int minAantalMutaties, int maxAantalMutaties){
    int aantalMutaties = randomIntervalInt(minAantalMutaties, maxAantalMutaties);
    bool af = false;
    if(randomIntervalInt(0,1)==1){
        af = true;
    }

    for(int mutatie = 0; mutatie<=aantalMutaties; mutatie++){
        int basisstation = randomIntervalInt(0, aantalVermogens-1);

        if (af) {
            vermogens[basisstation]=0;
        } else {
            vermogens[basisstation]=43;
        }
    }
}

//Dé fitnessfunctie
double fitness(int aantalSamples, struct punt * gebied, int aantalGebiedPunten, struct punt * basisstations, int * vermogens, int aantalBasisstations, char * bandbreedte, double dekkingsgraad_minimaal, double dekkingsgraad_overbodig){

    double dekking = dekkingsgraad(aantalSamples, gebied, aantalGebiedPunten, basisstations, vermogens, aantalBasisstations, bandbreedte);
    double verbruik = 0;
    int factor = 1000000;

    if (dekking<dekkingsgraad_minimaal) {
        return dekking;
    }
    if (dekking<dekkingsgraad_overbodig){
        verbruik = totaalEnergieverbruik(vermogens, aantalBasisstations);
        return (dekking-dekkingsgraad_minimaal+dekkingsgraad_overbodig)*factor/verbruik;
    }

    verbruik = totaalEnergieverbruik(vermogens, aantalBasisstations);
    return factor/verbruik;

}