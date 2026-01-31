#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "ligneBus.h"
#include "listeDouble.h"

#define SORTIE1 "stations_et_ligneDeBus.txt"
t_bus creeBus(int idBus, t_ligne start) {
    t_bus myBus = (t_bus)malloc(sizeof(type_bus));
    if (myBus == NULL) {
        printf("Erreur d'allocation pour le bus.\n");
        return NULL;
    }
    myBus->idBus = idBus;
    myBus->idLigneBusActuelle = start.idLigneBus;

    // Initialisation de la position du bus
    busSurStation(myBus, start.depart, depart_vers_arrivee);

    // le tronçon suivant existe et est valide
    t_liste_station nextTroncon = getNextTroncon(start.depart);
    if (nextTroncon != NULL) {
        busSurLigneX(myBus, getIdLigneTroncon(getPtrData(nextTroncon)));
    } else {
        printf("Erreur : Tronçon suivant non valide.\n"); // sinon pas valide
    }

    return myBus;
}

t_station *creeArret( int posX, int posY, int idStation, char* nomStation){
    t_station* newStation = (t_station*)malloc(sizeof(t_station));

    if (strlen(nomStation) >= 30) {
        printf("Le nom de station '%s' est trop long. Il sera tronqué à 29 caractères.\n", nomStation);
    }

    newStation->arret_ou_troncon = ARRET;

    int cout_maintenance = rand() % 91 + 10;

    //champs utiles si ARRET
    newStation->posX = posX;
    newStation->posY = posY;
    strcpy(newStation->nomStation, nomStation);
    newStation->idStation = idStation;
    newStation->coutMaintenance = cout_maintenance;
    setDateDerniereMaintenance(newStation);

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


    //champs utiles si ARRET
    newStation->posX = 0;
    newStation->posY = 0;
    strcpy(newStation->nomStation, "");
    newStation->idStation = -1;

    //champs utiles si TRONCON
    newStation->idLigneBus=idLigneBus;
    newStation->depart = depart;
    newStation->arrivee = arrivee;
    newStation->coutTemps = dist_arr_dep;
    newStation->coutDistance = dist_arr_dep;

    return newStation;
}

t_liste_station trouveStationDepart(t_bus bus, t_ligne* tab_ligne){
    int ligne = bus->idBus;

    if (bus->sensParcours == depart_vers_arrivee){
        return tab_ligne[ligne - 1].depart;
    }
    else if (bus->sensParcours == arrivee_vers_depart){
            return tab_ligne[ligne - 1].arrivee;
    }
    printf("erreur : pas de sens");
    return NULL;
}

t_liste* creeListeLigneDeBus() {
    FILE *f_in;
    int n_ligne;

    // Ouverture du fichier
    if ((f_in = fopen(SORTIE1, "r")) == NULL) {
        fprintf(stderr, "\nErreur: Impossible de lire le fichier %s\n", SORTIE1);
        return NULL;
    }

    fscanf(f_in, "%d", &n_ligne); // Lecture du nombre de lignes

    // Création du tableau de lignes de bus
    t_ligne* lignes_bus = malloc(n_ligne * sizeof(t_ligne)); // Allocation correcte pour les lignes de bus

    for (int i = 0; i < n_ligne; i++) {
        char nom_ligne[100]; // Déclaration du nom de la ligne
        fscanf(f_in, "%s", nom_ligne); // Lecture du nom de la ligne

        int n_arret;
        fscanf(f_in, "%d", &n_arret); // Lecture du nombre d'arrêts

        t_liste_station* arrets = malloc(n_arret * sizeof(t_station));

        for (int j = n_arret - 1; j >= 0; j--) {
            int posx, posy, id;
            char nom[100];
            fscanf(f_in, "%d,%d,%d,%s", &posx, &posy, &id, nom);
            arrets[j] = creeArret(posx, posy, id, nom);
        }

        // Initialisation de la ligne de bus
        int id_ligne_bus = i + 1; // Id de ligne unique
        t_liste_station ligne_bus_depart = NULL;
        t_liste_station ligne_bus_arrivee = NULL;

        // Création de la ligne de bus pour le sens départ -> arrivée
        for (int k = 0; k < n_arret - 1; k++) {
            ligne_bus_depart = ajoutEnTete(ligne_bus_depart, arrets[k]);
            ligne_bus_depart = ajoutEnTete(ligne_bus_depart, creeTroncon(id_ligne_bus, arrets[k + 1], arrets[k]));
        }
        ligne_bus_depart = ajoutEnTete(ligne_bus_depart, arrets[n_arret - 1]); // Dernier arrêt sans tronçon après

        // Création de la ligne de bus pour le sens arrivée -> départ
        for (int k = n_arret - 1; k > 0; k--) {
            ligne_bus_arrivee = ajoutEnTete(ligne_bus_arrivee, arrets[k]);
            ligne_bus_arrivee = ajoutEnTete(ligne_bus_arrivee, creeTroncon(id_ligne_bus, arrets[k - 1], arrets[k]));
        }
        // Dernier arrêt dans le sens arrivé -> départ
        ligne_bus_arrivee = ajoutEnTete(ligne_bus_arrivee, arrets[0]);

        // Stockage de la ligne de bus
        lignes_bus[i].idLigneBus = id_ligne_bus;
        lignes_bus[i].depart = ligne_bus_depart;
        lignes_bus[i].arrivee = ligne_bus_arrivee;
        lignes_bus[i].nomLigne = strdup(nom_ligne); // Copie du nom de la ligne (si alloué dynamiquement)

        free(arrets); // Libération de la mémoire pour les arrêts
    }

    fclose(f_in);  // Fermeture du fichier
    return lignes_bus;
}



t_liste_station decoupeLigneStationDepart(t_station* debut, t_ligne* ligne_bus, int nb_lignes) {
    // On parcourt chaque ligne de bus dans le tableau de lignes
    for (int i = 0; i < nb_lignes; i++) {
        t_liste_station courant = ligne_bus[i].depart; // L'élément courant de la ligne de bus

        // Parcours de la ligne de bus jusqu'à trouver la station de départ
        while (courant != NULL) {
            // Vérifie si l'élément courant est une station et si c'est la station de départ
            if (courant->pdata->arret_ou_troncon == ARRET && courant->pdata->idStation == debut->idStation) {
                return courant; // Retourne la station trouvée
            }
            courant = courant->suiv; // Passe à la station suivante
        }
    }

    // Si la station n'est pas trouvée après avoir parcouru toutes les lignes, retourner NULL
    return NULL;
}

t_liste_station decoupeLigneStationArrivee(t_station* fin, t_ligne* ligne_bus, int nb_lignes) {
    // On parcourt chaque ligne de bus dans le tableau de lignes
    for (int i = 0; i < nb_lignes; i++) {
        t_liste_station courant = ligne_bus[i].depart; // L'élément courant de la ligne de bus

        // Parcours de la ligne de bus jusqu'à trouver la station d'arrivée
        while (courant != NULL) {
            // Vérifie si l'élément courant est une station et si c'est la station d'arrivée
            if (courant->pdata->arret_ou_troncon == ARRET && courant->pdata->idStation == fin->idStation) {
                return courant; // Retourne la station trouvée
            }
            courant = courant->suiv; // Passe à la station suivante
        }
    }
    // Si la station n'est pas trouvée après avoir parcouru toutes les lignes, retourner NULL
    return NULL;
}


void creerLigneEntre2Stations(t_station* debut, t_station* fin, t_ligne* lignes_bus, int n_ligne) {

    // Récupération des pointeurs vers les bonnes parties des lignes
    t_liste_station debut_ptr = decoupeLigneStationDepart(debut, lignes_bus, n_ligne);
    t_liste_station fin_ptr   = decoupeLigneStationArrivee(fin, lignes_bus, n_ligne);
    int id_ligne_debut = getIdLigneBusStation(debut, lignes_bus);
    int id_ligne_fin = getIdLigneBusStation(fin, lignes_bus);
    t_liste_station debut_ligne_fin = lignes_bus[id_ligne_fin - 1].depart;

    if (debut_ptr == NULL || fin_ptr == NULL) {
        fprintf(stderr, "Erreur : station de début ou de fin non trouvée\n");
        return;
    }
    // Construction de la nouvelle ligne en inversé
    t_liste_station nouvelle_ligne_inverse = NULL;

    // Parcours de la première partie (debut_ptr -> fin)
    t_liste_station courant = debut_ptr;
    while (courant != NULL) {
        nouvelle_ligne_inverse = ajoutEnTete(nouvelle_ligne_inverse, courant->pdata);
        if (courant == fin_ptr) {
            courant = NULL;
        } else {
            courant = courant->suiv;
        }
    }

    // Ajout du tronçon seulement si les stations ne sont pas sur la même ligne
    if (id_ligne_debut != id_ligne_fin){

    nouvelle_ligne_inverse = ajoutEnTete(nouvelle_ligne_inverse, creeTroncon(n_ligne + 1, nouvelle_ligne_inverse->pdata, debut_ligne_fin->pdata));

    // Parcours de la seconde partie (debut_ligne_fin -> fin_ptr)
    t_liste_station courant2 = debut_ligne_fin;
    int fin_atteinte = 0;

    while (courant2 != NULL && !fin_atteinte) {
        nouvelle_ligne_inverse = ajoutEnTete(nouvelle_ligne_inverse, courant2->pdata);
        if (courant2 == fin_ptr) {
            fin_atteinte = 1;
        } else {
            courant2 = courant2->suiv;
        }
    }

    lignes_bus[n_ligne].arrivee = nouvelle_ligne_inverse;

    // Réinversion de la liste pour obtenir l'ordre correct
    t_liste_station nouvelle_ligne_finale = NULL;
    courant = nouvelle_ligne_inverse;
    while (courant != NULL) {
        nouvelle_ligne_finale = ajoutEnTete(nouvelle_ligne_finale, courant->pdata);
        courant = courant->suiv;
    }

    // Ajout de la nouvelle ligne dans le tableau (à l'indice n_ligne)
    lignes_bus[n_ligne].depart = nouvelle_ligne_finale;
    }
}


void suppressionStationLigneDeBus(t_ligne* tab_ligne, int n_ligne, char* nom_arret) {
    t_liste_station courant_dep = tab_ligne[n_ligne - 1].depart;
    t_liste_station courant_arr = tab_ligne[n_ligne - 1].arrivee;

    // Recherche de la station à supprimer (doit être un ARRET avec le bon nom)
    while (courant_dep != NULL &&(courant_dep->pdata->arret_ou_troncon != ARRET || strcmp(courant_dep->pdata->nomStation, nom_arret) != 0)) {
        courant_dep = courant_dep->suiv;
    }

    while (courant_arr != NULL &&(courant_arr->pdata->arret_ou_troncon != ARRET || strcmp(courant_arr->pdata->nomStation, nom_arret) != 0)) {
        courant_arr = courant_arr->suiv;
    }

    if (courant_dep == NULL) {
        printf("\nStation '%s' non trouvee dans depart -> arrivee.\n", nom_arret);
        return;
    }

    if (courant_arr == NULL) {
        printf("\nStation '%s' non trouvee dans arrivee -> depart.\n", nom_arret);
        return;
    }

    // Cas 1 : station unique
    if (courant_dep->prec == NULL && courant_dep->suiv == NULL) {
        tab_ligne[n_ligne - 1].depart = NULL;
        free(courant_dep);
        printf("\nDerniere station supprimee dans depart -> arrivee.\n");
        return;
    }

    if (courant_arr->prec == NULL && courant_arr->suiv == NULL) {
        tab_ligne[n_ligne - 1].arrivee = NULL;
        free(courant_arr);
        printf("\nDerniere station supprimee dans arrivee -> depart.\n");
        return;
    }

    // Cas 2 : station en début de ligne
    if (courant_dep->prec == NULL) {
        t_liste_station troncon_suivant_dep = courant_dep->suiv;
        t_liste_station suivant_dep = courant_dep->suiv->suiv;
        if (suivant_dep != NULL){
            suivant_dep->prec = NULL;
        }
        tab_ligne[n_ligne - 1].depart = suivant_dep;
        free(troncon_suivant_dep);
        free(courant_dep);
        printf("\nStation et troncon en tete de ligne supprimes dans depart -> arrivee.\n");
        return;
    }

     if (courant_arr->prec == NULL) {
        t_liste_station troncon_suivant_arr = courant_arr->suiv;
        t_liste_station suivant_arr = courant_arr->suiv->suiv;
        if (suivant_arr != NULL){
            suivant_arr->prec = NULL;
        }
        tab_ligne[n_ligne - 1].arrivee = suivant_arr;
        free(troncon_suivant_arr);
        free(courant_arr);
        printf("\nStation et troncon en tete de ligne supprimes dans arrivee -> depart.\n");
        return;
    }

    // Cas 3 : station en fin de ligne
    if (courant_dep->suiv == NULL) {
        t_liste_station troncon_prec_dep = courant_dep->prec;
        t_liste_station precedent_dep = troncon_prec_dep->prec;
        if (precedent_dep != NULL){
           precedent_dep->suiv = NULL;
        }
        free(troncon_prec_dep);
        free(courant_dep);
        printf("\nStation et troncon en fin de ligne supprimes dans depart -> arrivee.\n");
        return;
    }

     if (courant_arr->suiv == NULL) {
        t_liste_station troncon_prec_arr = courant_arr->prec;
        t_liste_station precedent_arr = troncon_prec_arr->prec;
        if (precedent_arr != NULL){
           precedent_arr->suiv = NULL;
        }
        free(troncon_prec_arr);
        free(courant_arr);
        printf("\nStation et troncon en fin de ligne supprimes dans arrivee -> depart.\n");
        return;
    }

    // Cas 4 : station au milieu → suppression + création nouveau tronçon
    t_liste_station troncon_avant_dep = courant_dep->prec;
    t_liste_station troncon_apres_dep = courant_dep->suiv;
    t_liste_station station_avant_dep = troncon_avant_dep->prec;
    t_liste_station station_apres_dep = troncon_apres_dep->suiv;

    // Création du nouveau tronçon entre station_avant et station_apres
    if (station_avant_dep != NULL && station_apres_dep != NULL) {
        t_station* new_troncon_dep = creeTroncon(n_ligne, station_avant_dep->pdata, station_apres_dep->pdata);

        // Insertion dans la liste
        t_liste_station noeud_troncon_dep = (t_liste_station)malloc(sizeof(t_liste_station));
        noeud_troncon_dep->pdata = new_troncon_dep;
        noeud_troncon_dep->prec = station_avant_dep;
        noeud_troncon_dep->suiv = station_apres_dep;

        station_avant_dep->suiv = noeud_troncon_dep;
        station_apres_dep->prec = noeud_troncon_dep;
    }

    // Libération mémoire
    free(troncon_avant_dep);
    free(troncon_apres_dep);
    free(courant_dep);

    printf("\nStation '%s' supprimee du milieu de la ligne dans depart -> arrivee.\n", nom_arret);

    t_liste_station troncon_avant_arr = courant_arr->prec;
    t_liste_station troncon_apres_arr = courant_arr->suiv;
    t_liste_station station_avant_arr = troncon_avant_arr->prec;
    t_liste_station station_apres_arr = troncon_apres_arr->suiv;

    // Création du nouveau tronçon entre station_avant et station_apres
    if (station_avant_arr != NULL && station_apres_arr != NULL) {
        t_station* new_troncon_arr = creeTroncon(n_ligne, station_avant_arr->pdata, station_apres_arr->pdata);

        // Insertion dans la liste
        t_liste_station noeud_troncon_arr = (t_liste_station)malloc(sizeof(t_liste_station));
        noeud_troncon_arr->pdata = new_troncon_arr;
        noeud_troncon_arr->prec = station_avant_arr;
        noeud_troncon_arr->suiv = station_apres_arr;

        station_avant_arr->suiv = noeud_troncon_arr;
        station_apres_arr->prec = noeud_troncon_arr;
    }

    // Libération mémoire
    free(troncon_avant_arr);
    free(troncon_apres_arr);
    free(courant_arr);

    printf("\nStation '%s' supprimee du milieu de la ligne dans arrivee -> depart.\n", nom_arret);
}


void rendreCirculaireLigneBus(t_ligne ligne) {
    if (ligne.depart == NULL || ligne.depart->suiv == NULL) {
        printf("Pas assez de stations pour rendre circulaire.\n");
        return;
    }

    t_liste_station courant_dep = ligne.depart;


    while (courant_dep->suiv != NULL) {
        courant_dep = courant_dep->suiv;
    }

    // Tronçon pour ligne.depart
    t_liste_station troncon_dep = malloc(sizeof(t_cellule));
    if (troncon_dep == NULL) {
        printf("Erreur d'allocation mémoire.\n");
        return;
    }
    troncon_dep->pdata = creeTroncon(ligne.idLigneBus, courant_dep->pdata, ligne.depart->pdata);
    troncon_dep->suiv = ligne.depart;
    troncon_dep->prec = courant_dep;

    courant_dep->suiv = troncon_dep;
    ligne.depart->prec = troncon_dep;

    // Assurer que le tronçon est bien relié dans les deux sens
    troncon_dep->suiv->prec = troncon_dep;

    t_liste_station courant_arr = ligne.arrivee;

     while (courant_arr->suiv != NULL) {
        courant_arr = courant_arr->suiv;
    }


    // Tronçon pour ligne.arrivee
    t_liste_station troncon_arr = malloc(sizeof(t_cellule));
    if (troncon_arr == NULL) {
        printf("Erreur d'allocation mémoire.\n");
        return;
    }
    troncon_arr->pdata = creeTroncon(ligne.idLigneBus, courant_arr->pdata, ligne.arrivee->pdata);
    troncon_arr->suiv = ligne.arrivee;
    troncon_arr->prec = courant_arr;

    courant_arr->suiv = troncon_arr;
    ligne.arrivee->prec = troncon_arr;

    // Assurer que le tronçon est bien relié dans les deux sens
    troncon_arr->suiv->prec = troncon_arr;

    printf("La ligne est maintenant circulaire.\n");
}





void afficheConsoleUneLigneBus(t_liste_station l){
        afficheListe(l);
}

void afficheConsoleLigneBus(t_ligne* l, int nb_lignes){
    for(int i = 0; i < nb_lignes; i++){
        afficheListe(l[i].depart);
        printf("\n\n\n\n");
    }
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


void deplaceBus(t_bus myBus, t_sens_parcours sens_deplacement, int *incXSprite, int *incYSprite) {
    t_liste_station dest;
    int xdep, ydep, xarr, yarr, pas;
    float ratio;
    pas = 2;

    dest = getNextStation(getPositionSurLaLigneDeBus(myBus));


    // Ligne circulaire : revenir au début
    if (dest == NULL && getSensParcours(myBus) == depart_vers_arrivee && estListeStationCirculaire(getPositionSurLaLigneDeBus(myBus))) {
        dest = getPositionSurLaLigneDeBus(myBus); // Ou retrouve le départ réel
    }

    *incXSprite = 0;
    *incYSprite = 0;

    // Si pas de prochaine station => terminus
    if (ligneBusVide(dest)) {
        if (!myBus->hasPrintedTerminus) {
            printf("\n\nBus id%d est arrive au TERMINUS de la ligne %d a la station %d %s\n",
                   getIdBus(myBus),
                   getIdLigneActuelleDuBus(myBus),
                   getIdStation(getPtrData(getPositionSurLaLigneDeBus(myBus))),
                   getNomStation(getPtrData(getPositionSurLaLigneDeBus(myBus))));
            myBus->hasPrintedTerminus = true;
        }
    } else {
        myBus->hasPrintedTerminus = false;  // Réinitialisation pour la prochaine fois
        xdep = getPosXBus(myBus);
        ydep = getPosYBus(myBus);
        xarr = getPosXListeStation(dest);
        yarr = getPosYListeStation(dest);

        if ((abs(xdep - xarr) <= pas) && (abs(ydep - yarr) <= pas)) {
            setPositionSurLaLigneDeBus(myBus, dest);
            printf("\n Bus id%d arrive a la station id%d %s",
                   getIdBus(myBus),
                   getIdStation(getPtrData(getPositionSurLaLigneDeBus(myBus))),
                   getNomStation(getPtrData(getPositionSurLaLigneDeBus(myBus))));
        } else {
            ratio = (float)(abs(yarr - ydep)) / (float)(abs(xarr - xdep));
            if (xarr > xdep) *incXSprite = pas;
            else if (xarr < xdep) *incXSprite = -pas;

            if (yarr > ydep) *incYSprite = (int)((float)(pas) * ratio);
            else if (yarr < ydep) *incYSprite = (int)((float)(-pas) * ratio);

            setPosXBus(myBus, xdep + *incXSprite);
            setPosYBus(myBus, ydep + *incYSprite);
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
