#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "ligneBus.h"
#include "listeDouble.h"


t_bus creeBus( int idBus, t_liste_station start ){
    t_bus myBus = (t_bus)malloc(sizeof(type_bus));
    myBus->idBus = idBus;
    busSurStation( myBus, start, depart_vers_arrivee);
    busSurLigneX ( myBus, getIdLigneTroncon(getPtrData(getNextTroncon(start))));
    return myBus;
}


t_station *creeArret( int posX, int posY, char* nomStation, int idStation){
    t_station* newStation = (t_station*)malloc(sizeof(t_station));

    newStation->arret_ou_troncon = ARRET;

    //champs utiles si ARRET
    newStation->posX = posX;
    newStation->posY = posY;
    strcpy(newStation->nomStation, nomStation);
    newStation->idStation = idStation;

    //champs non utiles si ARRET
    newStation->depart = NULL;
    newStation->arrivee = NULL;
    newStation->coutTemps = 0;
    newStation->coutDistance = 0;
    newStation->idLigneBus= -1;  //id inexistant
    return newStation;
}
//fonction qui calcule une distance avec un vecteur de cordonnees a et b
int resultat_distance_vecteur(int cord_a, int cord_b) {
    return (int)sqrt((double)(cord_a * cord_a) + (double)(cord_b * cord_b));
}

t_station *creeTroncon(int idLigneBus, t_station* depart, t_station *arrivee){
    t_station* newStation = (t_station*)malloc(sizeof(t_station));

    newStation->arret_ou_troncon = TRONCON;

    int posx_dep;
    int posy_dep;
    int posx_arr;
    int posy_arr;

    t_station* next_cell = getNextCell(depart);

    posx_dep = getPosXStation(depart);
    posy_dep = getPosYStation(depart);
    posx_arr = getPosXStation(arrivee);
    posy_arr = getPosYStation(arrivee);

    int posx_vecteur = posx_arr - posx_dep;
    int posy_vecteur = posy_arr - posy_dep;

    int dist_arr_dep = resultat_distance_vecteur(posx_vecteur,posy_vecteur);


    //champs non utiles si TRONCON
    newStation->posX = 0;
    newStation->posY = 0;
    strcpy(newStation->nomStation, "");
    newStation->idStation = -1;  //id inexistant

    //champs utiles si TRONCON
    newStation->idLigneBus=idLigneBus;
    newStation->depart = depart;
    newStation->arrivee = arrivee;
    newStation->coutTemps = dist_arr_dep;
    newStation->coutDistance = dist_arr_dep;
    return newStation;
}

t_liste_station creeLigneDeBus1(){
    t_liste_station newLigne;
    t_station *dep,*troncon,*arr;

    initListe(&newLigne);

    //creation en mémoire des stations et troncons
    dep = creeArret(10,10,"Charles de Gaulle",1);
    arr = creeArret(300,400,"Jules Ferry",2);
    troncon = creeTroncon(1,dep,arr);

    //ajout de ces stations et troncons dans la liste doublement chainée  (champ pdata)
    newLigne = ajoutEnFin(newLigne, dep);  //donc la tête)
    newLigne = ajoutEnFin(newLigne, troncon);
    newLigne = ajoutEnFin(newLigne, arr);

    dep = creeArret(10,410,"Jacques Brel",3);
    troncon = creeTroncon(1,arr,dep);
    newLigne = ajoutEnFin(newLigne, troncon);
    newLigne = ajoutEnFin(newLigne, dep);

    arr = creeArret(200,350,"Saint Exupery",4);
    troncon = creeTroncon(1,dep,arr);
    newLigne = ajoutEnFin(newLigne, troncon);
    newLigne = ajoutEnFin(newLigne, arr);

    dep = creeArret(500,410,"Stalingrad",5);
    troncon = creeTroncon(1,arr,dep);
    newLigne = ajoutEnFin(newLigne, troncon);
    newLigne = ajoutEnFin(newLigne, dep);

    return newLigne;
}


t_liste_station creeLigneDeBus2(){
    t_liste_station newLigne;
    t_station *dep,*troncon,*arr;

    initListe(&newLigne);

    //creation en mémoire des stations et troncons
    dep = creeArret(10,100,"Republique",6);
    arr = creeArret(30,300,"Jules Ferry",7);
    troncon = creeTroncon(2,dep,arr);

    //ajout de ces stations et troncons dans la liste doublement chainée  (champ pdata)
    newLigne = ajoutEnFin(newLigne, dep);  //donc la tête)
    newLigne = ajoutEnFin(newLigne, troncon);
    newLigne = ajoutEnFin(newLigne, arr);

    dep = creeArret(100,40,"PLace d'armes",8);
    troncon = creeTroncon(2,arr,dep);
    newLigne = ajoutEnFin(newLigne, troncon);
    newLigne = ajoutEnFin(newLigne, dep);

    arr = creeArret(300,30,"Place de l'etoile",9);
    troncon = creeTroncon(2,dep,arr);
    newLigne = ajoutEnFin(newLigne, troncon);
    newLigne = ajoutEnFin(newLigne, arr);

    dep = creeArret(400,210,"Bobigny",10);
    troncon = creeTroncon(2,arr,dep);
    newLigne = ajoutEnFin(newLigne, troncon);
    newLigne = ajoutEnFin(newLigne, dep);

    return newLigne;
}

t_liste_station creeLigneDeBus3(){
    t_liste_station newLigne;
    t_station *dep,*troncon,*arr;

    initListe(&newLigne);

    //creation en mémoire des stations et troncons
    dep = creeArret(150,10,"Clemenceau",11);
    arr = creeArret(300,100,"Montmartre",12);
    troncon = creeTroncon(3,dep,arr);

    //ajout de ces stations et troncons dans la liste doublement chainée  (champ pdata)
    newLigne = ajoutEnFin(newLigne, dep);  //donc la tête)
    newLigne = ajoutEnFin(newLigne, troncon);
    newLigne = ajoutEnFin(newLigne, arr);

    dep = creeArret(600,610,"Tour eiffel",13);
    troncon = creeTroncon(3,arr,dep);
    newLigne = ajoutEnFin(newLigne, troncon);
    newLigne = ajoutEnFin(newLigne, dep);

    arr = creeArret(70,350,"Les invalides",14);
    troncon = creeTroncon(3,dep,arr);
    newLigne = ajoutEnFin(newLigne, troncon);
    newLigne = ajoutEnFin(newLigne, arr);

    dep = creeArret(150,510,"Gare du nord",15);
    troncon = creeTroncon(3,arr,dep);
    newLigne = ajoutEnFin(newLigne, troncon);
    newLigne = ajoutEnFin(newLigne, dep);

    return newLigne;
}

t_liste_station* creeListeLigneDeBus(int n_ligne, t_liste_station* liste_ligne) {
    FILE *f_in;
    char nom[100];
    int posx, posy, id;
    int n_arret, n_troncon;
    int pos_troncon = 1;

    // Ouverture du fichier de données
    if ((f_in = fopen(SORTIE1, "r")) == NULL) {
        fprintf(stderr, "\nErreur: Impossible de lire le fichier %s\n", SORTIE1);
        return NULL;
    }

    // Parcours des lignes de bus
    for (int j = 0; j < n_ligne; j++) {
        fscanf(f_in, "%d", &n_arret); // Lire le nombre d'arrêts pour la ligne de bus

        t_liste tmp_ligne = NULL; // Liste temporaire pour ajouter les arrêts

        // Parcours des arrêts pour chaque ligne
        for (int i = 0; i < n_arret; i++) {
            // Lire les informations de chaque arrêt
            fscanf(f_in, "%d,%d,%d,%s", &posx, &posy, &id, nom);

            // Ajouter l'arrêt à la ligne
            t_station* arret = creeArret(posx, posy, id, nom);
            tmp_ligne = ajoutEnFin(tmp_ligne, arret);

            // Si ce n'est pas le premier arrêt, ajouter un tronçon
            if (i > 0) {
                // Ajouter un tronçon entre le précédent arrêt et celui-ci
                t_station* prev_arret = tmp_ligne->suiv->pdata;  // Arrêt précédent
                t_station* curr_arret = tmp_ligne->pdata;        // Arrêt actuel
                t_station* troncon = creeTroncon(pos_troncon++, prev_arret, curr_arret);
                tmp_ligne = ajoutEnFin(tmp_ligne, troncon);
            }
        }

        // Après avoir ajouté tous les arrêts et tronçons pour la ligne
        liste_ligne[j] = tmp_ligne;

        // Assigner la position du bus (par exemple à la première station ou selon un critère)
        int pos_bus;
        fscanf(f_in, "%d", &pos_bus);
        // Ajoute une logique pour mettre à jour la position du bus si nécessaire
    }

    // Message de confirmation de lecture du fichier
    printf("Le fichier %s a été lu et les lignes de bus ont été initialisées\n", SORTIE1);
    fclose(f_in);

    return liste_ligne;
}


void afficheConsoleLigneBus( t_liste_station l){
    afficheListe(l);
}

t_liste_station getNextStation( t_liste_station l){
    if (ligneBusVide(l)) return NULL;
    else {
            if (getTypeNoeud(getPtrData(l))==ARRET) {
                    if (ligneBusVide( getNextCell(l) )) return NULL;  //nous sommes sur un terminus
                    else return getNextCell( getNextCell( l ) );  //le prochain arret est dans 2 cellules dans la liste, la cellule suivaante étant un TRONCON
            }
            else return getNextCell( l );  //si on est sur un TRONCON alors la prochaine cellule est la prochaine station (ARRET)
    }
}

t_liste_station getNextTroncon( t_liste_station l){
    if (ligneBusVide(l)) return NULL;
    else {
            if (getTypeNoeud(getPtrData(l))==ARRET) {
                return getNextCell(l);  //la prochaine cellule est un TRONCON, peut être égale à NULL si on est sur un terminus
            }
            else{
                    printf("\n(getNextTroncon) erreur algo, on est deja sur un troncon");
                    return l;  //on retourne le troncon actuel
            }
    }
}

t_liste_station getPreviousStation( t_liste_station l){
    if (ligneBusVide(l)) return NULL;
    else {
            if (getTypeNoeud(getPtrData(l))==ARRET) {
                    if (ligneBusVide( getPrevCell(l) )) return NULL;  //nous sommes sur un terminus
                    return getPrevCell( getPrevCell( l ) );  //le prochain arret est dans 2 cellules dans la liste, la cellule suivaante étant un TRONCON
            }
            else return getPrevCell( l );  //si on est sur un TRONCON alors la prochaine cellule est la prochaine station (ARRET)
    }
}

bool ligneBusVide( t_liste_station l){
    return listeVide( l );
}

int getPosXListeStation( t_liste_station myStationInListe ){
    return getPosXStation(getPtrData(myStationInListe));
}

int getPosYListeStation( t_liste_station myStationInListe ){
    return getPosYStation(getPtrData(myStationInListe));
}

void deplaceBus(t_bus myBus, t_sens_parcours sens_deplacement, int *incXSprite, int *incYSprite){
    t_liste_station dest;
    int xdep, ydep, xarr, yarr, pas;
    float ratio;
    pas = 2;  //équivalent au parametre d'erreur dans le tracé de Segment de Bresenham
    //https://fr.wikipedia.org/wiki/Algorithme_de_trac%C3%A9_de_segment_de_Bresenham


    if (sens_deplacement == depart_vers_arrivee) dest = getNextStation(getPositionSurLaLigneDeBus(myBus));
        else dest = getPreviousStation(getPositionSurLaLigneDeBus(myBus));

    //par défaut: pas de déplacement du bus
    *incXSprite = 0; *incYSprite = 0;

    //si un prochain arret existe?
    if (ligneBusVide(dest)){
        //printf("\nBus id%d est au terminus de la ligne %d sur la station id=%d %s", getIdBus(myBus), getIdLigneActuelleDuBus(myBus),getIdStation(getPtrData(getActualStation(myBus))),getNomStation(getPtrData(getActualStation(myBus))));
    }
    else //s'il existe:
    {
        //soit on est arrivé, soit on est en cours de trajet
        //récupération des coordonnées
        xdep = getPosXBus(myBus);
        ydep = getPosYBus(myBus);
        xarr = getPosXListeStation(dest);
        yarr = getPosYListeStation(dest);

        //sommes-nous arrivés?
        if ((abs(xdep-xarr)<=pas) && (abs(ydep-yarr)<=pas)){
            //alors mise à jour de la station actuelle du bus
            setPositionSurLaLigneDeBus( myBus, dest );
            printf("\nLe Bus id%d arrive sur la station id%d %s",getIdBus(myBus),getIdStation(getPtrData(getPositionSurLaLigneDeBus(myBus))),getNomStation(getPtrData(getPositionSurLaLigneDeBus(myBus))));
        }
        else{
            //sinon on calcule les offsets de déplacements pour la boucle main qui réalise les affichages
            ratio = (float)(abs(yarr-ydep))/(float)(abs(xarr-xdep)); //div euclydienne

            //algo de Bresenham "simplifié de façon ad hoc" et non optimisé (à cause des floats)
            if (xarr>xdep) *incXSprite = pas;
            else if (xarr<xdep) *incXSprite = -pas;

            if (yarr>ydep) *incYSprite = (int)((float)(pas) * ratio);             //pour un déplacement proportionnel en Y selon Y/X
            else if (yarr<ydep) *incYSprite = (int)((float)(-pas) * ratio);

            //remmarque: si xarr==ydep alors *incXSprite reste à 0, idem en Y

            //maj des coord du bus
            setPosXBus(myBus, getPosXBus(myBus) + *incXSprite);
            setPosYBus(myBus, getPosYBus(myBus) + *incYSprite);
        }
    }
}



void busSurStation( t_bus myBus, t_liste_station myStation, t_sens_parcours sens){

    //Exemple encapsulation: on a préféré les fonctions setteurs à un accés direct aux champs

    setPositionSurLaLigneDeBus( myBus, myStation);
    //myBus->positionSurLaLigneDeBus = myStation;  //interdit

    setSensParcours( myBus, sens);
    //myBus->sensParcours = sens;

    setPosXBus( myBus, getPosXListeStation( myStation ) );
    //myBus->posXBus = getPosXListeStation( myStation );

    setPosYBus( myBus, getPosYListeStation( myStation ) );
    //myBus->posYBus = getPosYListeStation( myStation );

    //idem : on passe ci-dessous par les getteurs et non par un accés direct via les champs
    printf("\nBus id%d est en (x = %d, y = %d) sur la ligne %d, station %s", getIdBus(myBus), getPosXBus(myBus), getPosYBus(myBus), getIdLigneActuelleDuBus(myBus), getNomStation(getPtrData(myStation)));
}

void busSurLigneX( t_bus myBus, int idLigneX ){
    setIdLigneBus(myBus, idLigneX);
}

t_liste_station stationSuivantePourLeBus(t_bus myBus){
    t_liste_station prochaineStation;
    if (getSensParcours(myBus)==depart_vers_arrivee) prochaineStation = getNextStation(getPositionSurLaLigneDeBus(myBus));
    else prochaineStation = getPreviousStation(getPositionSurLaLigneDeBus(myBus));
    return prochaineStation;
}

void afficheCoordonneesBus( t_bus myBus ){
    char *nomProchaineStation;
    t_liste_station prochaineStation = stationSuivantePourLeBus(myBus);

    if (ligneBusVide(prochaineStation)) printf("\nBus id: %d est en (x = %d, y = %d) ligne %d, derniere station %s (Terminus)", getIdBus(myBus), getPosXBus(myBus), getPosYBus(myBus), getIdLigneActuelleDuBus(myBus), getNomStation(getPtrData(getPositionSurLaLigneDeBus(myBus))));
    else {
            nomProchaineStation = getNomStation(getPtrData(prochaineStation));
            printf("\nBus id: %d est en (x = %d, y = %d) ligne %d, derniere station %s, prochaine station %s", getIdBus(myBus), getPosXBus(myBus), getPosYBus(myBus), getIdLigneActuelleDuBus(myBus), getNomStation(getPtrData(getPositionSurLaLigneDeBus(myBus))), nomProchaineStation);
    }
}


//Créer ci-dessous vos fonctions
