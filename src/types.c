#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#define SORTIE1 "stations_et_ligneDeBus.txt"

void afficheStation( t_station *station){
    if (station == NULL){
        printf("\nerreur station non allouee!\n");
    }
    else{
        if (station->arret_ou_troncon == ARRET){
            t_date date = station->dateDerniereMaintenance;
            printf("\nSTATION idStation: %d, Station : %s, posX = %d, posY = %d, cout_maintenance = %d, date = %d/%d/%d", station->idStation, station->nomStation, station->posX, station->posY, station->coutMaintenance , date.jour, date.mois, date.annee);
        }
        else{ //alors le noeud est un tron�on
            printf("\n\nTRONCON idLigneBus: %d, temps: %d sec, distance a parcourir: %d metres", station->idLigneBus, station->coutTemps, station->coutDistance);
            afficheStation(station->depart);
            afficheStation(station->arrivee);
            printf("\nfin troncon\n");
        }
    }
}

// Getteurs

t_station* getDepartTroncon(t_station *myStation) {
    if (getTypeNoeud(myStation) == TRONCON) {
        return myStation->depart;
    } else {
        return NULL;
    }
}

t_station* getArriveeTroncon(t_station *myStation) {
    if (getTypeNoeud(myStation) == TRONCON) {
        return myStation->arrivee;
    } else {
        return NULL;
    }
}

int getIdStation( t_station *myStation){
    return myStation->idStation;
}

char *getNomStation( t_station *myStation){
    return myStation->nomStation;
}

int getPosXStation( t_station *myStation ){
    return myStation->posX;
}
int getPosYStation( t_station *myStation ){
    return myStation->posY;
}

int getIdLigneTroncon(t_station *myStation){
    //une station n'est pas li�e � une ligne, seulement le troncon
    if (getTypeNoeud(myStation)==TRONCON)
        return myStation->idLigneBus;
    else{
        printf("\n(getIdLigneTroncon) Erreur algo, vous n etes pas sur un troncon");
        return -1;
    }
}


t_station* getStationParId(int id, t_ligne* ligne_bus) {
    for (int i = 0; ligne_bus[i].depart != NULL; i++) {
        t_liste_station courant = ligne_bus[i].depart;
        while (courant != NULL) {
            if (courant->pdata->idStation == id) {
                return courant->pdata;
            }
            courant = courant->suiv;
        }
    }
    return NULL;
}


int getIdLigneBusStation(t_station* myStation, t_ligne* tab_ligne) {
    FILE *f_in;
    int n_ligne;

    // Ouverture du fichier
    if ((f_in = fopen(SORTIE1, "r")) == NULL) {
        fprintf(stderr, "\nErreur: Impossible de lire le fichier %s\n", SORTIE1);
        return -1;
    }

    fscanf(f_in, "%d", &n_ligne); // Lecture du nombre de lignes

    fclose(f_in);

    for (int i = 0; i < n_ligne; i++) {
        int id_ligne_bus = tab_ligne[i].idLigneBus;
        t_liste_station courant = tab_ligne[i].depart;
        while (courant != NULL) {
            if (courant->pdata == myStation) {
                return id_ligne_bus;
            }
            courant = courant->suiv;
        }
    }
    return -1; // station non trouv�e
}

int getDistanceCumule(t_station *myStation){
    return myStation->distanceCumule;
}

int getTempsCumule(t_station *myStation){
    return myStation->tempsCumule;
}

int getCoutTemps(t_station *myStation){
    return myStation->coutTemps;
}

int getCoutDistance(t_station *myStation){
    return myStation->coutDistance;
}

int getCoutMaintenance(t_station *myStation){
    return myStation->coutMaintenance;
}

t_date getDateDerniereMaintenance(t_station *myStation){
    return myStation->dateDerniereMaintenance;
}


t_noeud getTypeNoeud(t_station *myStation){
    return myStation->arret_ou_troncon;
}


int getPosXBus( t_bus myBus ){
    return myBus->posXBus;
}
int getPosYBus( t_bus myBus ){
    return myBus->posYBus;
}
int getIdBus( t_bus myBus ){
    return myBus->idBus;
}
int getIdLigneActuelleDuBus( t_bus myBus ){
    return myBus->idLigneBusActuelle;
}

t_sens_parcours getSensParcours(t_bus myBus){
    return myBus->sensParcours;
}

t_liste_station getPositionSurLaLigneDeBus(t_bus myBus){
    return myBus->positionSurLaLigneDeBus;
}





// Setteurs

void setPosXBus(t_bus myBus, int newX){
    myBus->posXBus = newX;
}

void setPosYBus(t_bus myBus, int newY){
    myBus->posYBus = newY;
}

void setIdLigneBusActuelle(t_bus myBus, int idLigne){
    myBus->idLigneBusActuelle = idLigne;
}

void setSensParcours(t_bus myBus, t_sens_parcours sens ){
    myBus->sensParcours = sens;
}

void setPositionSurLaLigneDeBus( t_bus myBus, t_liste_station myStation){
    myBus->positionSurLaLigneDeBus = myStation;
}

void setIdBus(t_bus myBus, int newidBus){
    myBus->idBus = newidBus;
}

void setArretTroncon(t_station *myStation, t_noeud nouv_noeud){
    myStation->arret_ou_troncon = nouv_noeud;
}

void setIdLigneBus(t_station *myStation, int nouv_id){
    myStation->idLigneBus = nouv_id;
}

void setStationDepart(t_station *myStation, t_station *nouv_station_dep){
    myStation->depart = nouv_station_dep;
}

void setStationArrive(t_station *myStation, t_station *nouv_station_arr){
    myStation->arrivee = nouv_station_arr;
}

void setCoutTemps(t_station *myStation, int cout_temp){
    myStation->coutTemps = cout_temp;
}

void setCoutDistance(t_station *myStation, int cout_dist){
    myStation->coutDistance = cout_dist;
}

void setTempsCumule(t_station *myStation, int temps_cum){
    myStation->tempsCumule = temps_cum;
}

void setDistanceCumule(t_station *myStation, int dist_cum){
    myStation->distanceCumule = dist_cum;
}

void setPosX(t_station *myStation, int new_posX){
    myStation->posX = new_posX;
}

void setPosY(t_station *myStation, int new_posY){
    myStation->posY = new_posY;
}

void setNomStation(t_station *myStation, const char *nom_station) {
    if (myStation == NULL || nom_station == NULL) {
        return;
    }

    int taille = strlen(nom_station);

    if (taille >= sizeof(myStation->nomStation)-1) {
        return;
    }
    int i;
    for ( i = 0; i < taille; i++) {
        myStation->nomStation[i] = nom_station[i];
    }
    myStation->nomStation[i] = '\0';
}

void setIdStation(t_station *myStation, int id_station){
    myStation->idStation = id_station;
}



void setCoutMaintenance(t_station *myStation, int couts) {
    if (couts >= 10 && couts <= 100) {
        myStation->coutMaintenance = couts;
    } else {
        printf("Erreur: le co�t de maintenance doit �tre entre 10 et 100 Kilo-Euros.\n");
    }
}

void setDateDerniereMaintenance(t_station *myStation) {

    int jour = rand() % 31 + 1;
    int mois = rand() % 12 + 1;
    int annee = rand() % 26 + 2000;

    myStation->dateDerniereMaintenance.jour = jour;
    myStation->dateDerniereMaintenance.mois = mois;
    myStation->dateDerniereMaintenance.annee = annee;
}
