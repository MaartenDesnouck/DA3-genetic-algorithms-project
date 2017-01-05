//
//  src/maximast.c
//  ADIII
//
//  Created by Maarten Desnouck on 23/09/15.
//  Copyright © 2015 Maarten Desnouck. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <time.h>

#include "vermogenEnBereik.h"
#include "puntInVeelhoek.h"
#include "graden.h"
#include "dekkingsgraad.h"
#include "hulpfuncties.h"
#include "genetisch.h"
#include "punt.h"

#define EXIT_OK 0
#define EXIT_WRONG_NUMBER_OF_PARAMETERS 1
#define EXIT_FILE_DOES_NOT_EXIST 2
#define EXIT_BANDBREEDTE_NOT_RECOGNIZED 3
#define EXIT_DEKKINGSGRAAD_MINIMAAL_INCORRECT 4
#define EXIT_DEKKINGSGRAAD_OVERBODIG_INCORRECT 5
#define EXIT_MEM_ALLOC_FAILED 6

//Variables
FILE* gebiedFile;
FILE* basisstationsFile;
char* bandbreedte;
float dekkingsgraad_minimaal;
float dekkingsgraad_overbodig;
struct punt referentiePunt;

double minBreedte;
double maxBreedte;
double minLengte;
double maxLengte;

//Parameters
int aantalBasisstations;
int aantalGebiedpunten;

int populatieGrootte = 5;
int aantalGeneraties = 2000;
int aantalSamples = 10000;

int mutatieGrootte = 43;
int minAantalMutaties = 1;
int maxAantalMutaties = 3;

//Main
int main(int argc, const char * argv[]) {

    //Argumenten inladen
    if(argc == 6){
        srand((unsigned)clock()); //rand seeden
        
        //Openen van file met gebiedpunten
        gebiedFile=fopen(argv[1],"r");
        if(gebiedFile == NULL) {
            printf("EXIT_FILE_DOES_NOT_EXIST: %s\n", argv[1]);
            return EXIT_FILE_DOES_NOT_EXIST;
        }
        
        //Openen van file met locaties zendmasten
        basisstationsFile=fopen(argv[2],"r");
        if(basisstationsFile == NULL) {
            printf("EXIT_FILE_DOES_NOT_EXIST: %s\n", argv[2]);
            return EXIT_FILE_DOES_NOT_EXIST;
        }
        
        //Bandbeedte instellen
        if(strcmp(argv[3],"high") == 0){
            bandbreedte = "high";
        } else if (strcmp(argv[3],"low") == 0){
            bandbreedte = "low";
        } else{
            printf("EXIT_BANDBREEDTE_NOT_RECOGNIZED: %s\n", argv[3]);
            return EXIT_BANDBREEDTE_NOT_RECOGNIZED;
        }
        
        //Minimale dekkkingsgraad instellen
        if (atof(argv[4])>0 && atof(argv[4])<=1) {
            dekkingsgraad_minimaal = atof(argv[4]);
        } else{
            printf("EXIT_DEKKINGSGRAAD_MINIMAAL_INCORRECT: %s\n", argv[4]);
            return EXIT_DEKKINGSGRAAD_MINIMAAL_INCORRECT;
        }

        //Overbodige dekkingsgraad instellen
        if (atof(argv[5])>=dekkingsgraad_minimaal && atof(argv[5])<=1) {
            dekkingsgraad_overbodig = atof(argv[5]);
        } else{
            printf("EXIT_DEKKINGSGRAAD_OVERBODIG_INCORRECT: %s\n", argv[5]);
            return EXIT_DEKKINGSGRAAD_OVERBODIG_INCORRECT;
        }

        //Tel aantal gebiedpunten en basisstations
        aantalGebiedpunten = lijnen(argv[1]);
        aantalBasisstations = lijnen(argv[2]);

        //Gebiedpunten inladen in datastructuur
        struct punt* gebiedPunten = malloc(aantalGebiedpunten * sizeof(struct punt));
        if (NULL == gebiedPunten) {
            fprintf(stderr, "EXIT_MEM_ALLOC_FAILED\n");
            return(EXIT_MEM_ALLOC_FAILED);
        }

        //Variablelen voor getNextLijn
        char * lijn = NULL;
        int lengte = 0;
        int lijnlengte;
        int entry = 0;

        //hier minLengte, minBreedte, maxLengte en maxBreedte bepalen
        while ((lijnlengte = getNextLijn(&lijn, &lengte, gebiedFile)) != -1) {
            char * i;
            int slashLocatie = 0;
            i=lijn;

            while(*i != '/'){
                slashLocatie++;
                i++;
            }

            float lengtegraad = atof(substring(lijn, 1, slashLocatie));
            float breedtegraad = atof(substring(lijn, slashLocatie+2, lijnlengte+1));

            //Min en max -lengte en -breedte bepalen
            if (lengtegraad>maxBreedte) {
                maxBreedte = lengtegraad;
            } else if (lengtegraad<minBreedte) {
                minBreedte = lengtegraad;
            }
            if (breedtegraad>maxLengte) {
                maxLengte = breedtegraad;
            } else if (breedtegraad<minLengte) {
                minLengte = breedtegraad;
            }

            gebiedPunten[entry].x = lengtegraad;
            gebiedPunten[entry].y = breedtegraad;
            entry++;
        }

        //Basisstations inladen in datastructuur
        struct punt * basisstations = malloc(aantalBasisstations * sizeof(struct punt));
        if (NULL == basisstations) {
            fprintf(stderr, "EXIT_MEM_ALLOC_FAILED\n");
            return(EXIT_MEM_ALLOC_FAILED);
        }

        lijn = NULL;
        lengte = 0;
        entry = 0;

        while ((lijnlengte = getNextLijn(&lijn, &lengte, basisstationsFile)) != -1) {
            char * i;
            int slashlocatie1 = 0;
            int slashlocatie2 = 0;
            int aantalSlashes = 0;
            i=lijn;

            while(aantalSlashes < 2){
                if(*i == '/'){
                    aantalSlashes++;
                }
                if (aantalSlashes==0) {
                    slashlocatie1++;
                    slashlocatie2++;
                } else if (aantalSlashes==1) {
                    slashlocatie2++;
                }
                i++;
            }

            float lengtegraad = atof(substring(lijn, 1, slashlocatie1));
            float breedtegraad = atof(substring(lijn, slashlocatie1+2, slashlocatie2));
            basisstations[entry].z = atof(substring(lijn, slashlocatie2+2, lijnlengte+1));

            //Men en max -lengte en -breedte nog bijwerken
            if (lengtegraad>maxBreedte) {
                maxBreedte = lengtegraad;
            } else if (lengtegraad<minBreedte) {
                minBreedte = lengtegraad;
            }
            if (breedtegraad>maxLengte) {
                maxLengte = breedtegraad;
            } else if (breedtegraad<minLengte) {
                minLengte = breedtegraad;
            }

            basisstations[entry].x = lengtegraad;
            basisstations[entry].y = breedtegraad;

            entry++;
        }

        //Basisstationpunten en gebiedpunten omzetten
        for(int station = 0; station<aantalBasisstations;station++){
            basisstations[station].x = lengtegraadNaarCoord(minBreedte, basisstations[station].x);
            basisstations[station].y = breedtegraadNaarCoord(minLengte, basisstations[station].y);
        }
        for(int punt = 0; punt<aantalGebiedpunten;punt++){
            gebiedPunten[punt].x = lengtegraadNaarCoord(minBreedte, gebiedPunten[punt].x);
            gebiedPunten[punt].y = breedtegraadNaarCoord(minLengte, gebiedPunten[punt].y);
        }


        //Initiaties voor het genetisch algoritme
        int ** populatie = malloc(populatieGrootte * sizeof(int*)); //vermogens van alle masten
        for(int i = 0; i<populatieGrootte;i++){
            populatie[i] = malloc(aantalBasisstations * sizeof(int));
        }

        //double histogram[aantalGeneraties+1]; //historiek van de fitness (handig voor de testen)
        //histogram[0] = 0;

        //populatie met overal 0 dBm vermogen initialiseren
        for(int exemplaar=0;exemplaar<populatieGrootte;exemplaar++){
            for(int mast=0;mast<aantalBasisstations;mast++){
                populatie[exemplaar][mast]=0;
            }
        }

        //Het Genetisch Algoritme
        for(int generatie = 1; generatie<=aantalGeneraties; generatie++){
            //Kiezen 3 random exemplaren uit de populatie en berekenen hun fitness

            int eerste = randomIntervalInt(0, populatieGrootte-1);
            int tweede = eerste;
            int derde = eerste;

            while(tweede == eerste){
                tweede = randomIntervalInt(0, populatieGrootte-1);
            }
            while (derde == eerste || derde == tweede) {
                derde = randomIntervalInt(0, populatieGrootte-1);
            }

            double eerstefitness = fitness(aantalSamples, gebiedPunten, aantalGebiedpunten, basisstations, populatie[eerste], aantalBasisstations, bandbreedte, dekkingsgraad_minimaal, dekkingsgraad_overbodig);
            double tweedefitness = fitness(aantalSamples, gebiedPunten, aantalGebiedpunten, basisstations, populatie[tweede], aantalBasisstations, bandbreedte, dekkingsgraad_minimaal, dekkingsgraad_overbodig);
            double derdefitness = fitness(aantalSamples, gebiedPunten, aantalGebiedpunten, basisstations, populatie[derde], aantalBasisstations, bandbreedte, dekkingsgraad_minimaal, dekkingsgraad_overbodig);

            //We sorteren de 3 gekozen exemplaren op basis van hun fitness
            if (tweedefitness > eerstefitness){
                swapInt(&tweede, &eerste);
                swapDouble(&tweedefitness, &eerstefitness);
            }
            if (derdefitness > tweedefitness){
                swapInt(&derde, &tweede);
                swapDouble(&derdefitness, &tweedefitness);
            }
            if (tweedefitness > eerstefitness){
                swapInt(&tweede, &eerste);
                swapDouble(&tweedefitness, &eerstefitness);
            }

            //We slaan het beste resultaat op om een histogram van de scores te verkrijgen
            //histogram[generatie] = eerstefitness;


            //We kopieren het beste exemplaar over het slechtste exemplaar
            //We doen vervolgens een crossover tussen 2 en 3 gevolgd door een mutatie op 2 en 3

            //Dit resulteert in het volgende
                //1 -> 1
                //2 -> crossover1(1,2)+mutate en/of mutate2
                //3 -> crossover2(1,2)+mutate en/of mutate2

            for(int index=0; index<aantalBasisstations;index++){
                populatie[derde][index] = populatie[eerste][index];
            }

            int minGrootte = -1 * mutatieGrootte;
            int maxGrootte = mutatieGrootte;

            singleAxisCrossover(populatie[tweede], populatie[derde], basisstations, aantalBasisstations, maxBreedte, minBreedte,maxLengte, minLengte);

            mutate(populatie[tweede], aantalBasisstations, minAantalMutaties, maxAantalMutaties, minGrootte, maxGrootte);
            mutate(populatie[derde], aantalBasisstations, minAantalMutaties, maxAantalMutaties, minGrootte, maxGrootte);
            //mutate2(populatie[tweede], aantalBasisstations, minAantalMutaties, maxAantalMutaties);
            //mutate2(populatie[derde], aantalBasisstations, minAantalMutaties, maxAantalMutaties);

        }

        //Volledige populatie na alle genraties overlopen en de beste er uit halen
        double bestefitness = 0;
        int besteExemplaar = 0;
        for(int volledig = 0; volledig<populatieGrootte;volledig++){
            double defitness = fitness(aantalSamples, gebiedPunten, aantalGebiedpunten, basisstations, populatie[volledig], aantalBasisstations, bandbreedte, dekkingsgraad_minimaal, dekkingsgraad_overbodig);
            if(defitness>bestefitness){
                bestefitness = defitness;
                besteExemplaar = volledig;
            }
        }

        //Resultaten printen
        for(int mast = 0; mast<aantalBasisstations; mast++){
            printf("%d\n",populatie[besteExemplaar][mast]);
        }
        printf("%f\n", fitness(aantalSamples, gebiedPunten, aantalGebiedpunten, basisstations, populatie[besteExemplaar], aantalBasisstations, bandbreedte, dekkingsgraad_minimaal, dekkingsgraad_overbodig));
        printf("%f\n", dekkingsgraad(aantalSamples, gebiedPunten, aantalGebiedpunten, basisstations, populatie[besteExemplaar], aantalBasisstations, bandbreedte));

        return EXIT_OK;
    }
    else {
        printf("EXIT_WRONG_NUMBER_OF_PARAMETERS: %i\n", argc);
        for (int i = 0; i < argc; i++){
            printf("%s\n", argv[i]);
        }
        return EXIT_WRONG_NUMBER_OF_PARAMETERS;
    }
}

