#ifndef LIGNEBUS_H_INCLUDED
#define LIGNEBUS_H_INCLUDED

#include <stdbool.h>
#include "types.h"
t_bus creeBus(int idBus, t_ligne start);
t_station *creeArret( int posX, int posY, int idStation, char* nomStation);
int resultat_distance_vecteur(int cord_a, int cord_b);
t_station *creeTroncon( int idLigneBus, t_station* depart, t_station *arrivee);

//TlisteStation* initReseauLignesDeBus(int *nbLignes);
t_liste_station trouveStationDepart(t_bus bus, t_ligne* tab_ligne);
t_liste* creeListeLigneDeBus();
t_liste_station decoupeLigneStationDepart(t_station* debut, t_ligne* ligne_bus, int nb_lignes);
t_liste_station decoupeLigneStationArrivee(t_station* fin, t_ligne* ligne_bus, int nb_lignes);
void creerLigneEntre2Stations(t_station* debut, t_station* fin, t_ligne* lignes_bus, int n_ligne);
void suppressionStationLigneDeBus(t_ligne* tab_ligne, int n_ligne, char* nom_arret);
void rendreCirculaireLigneBus(t_ligne ligne);
void afficheConsoleUneLigneBus(t_liste_station l);
void afficheConsoleLigneBus(t_ligne* l, int nb_lignes);
//void afficheConsoleLigneBusCirculaire(t_liste_station l);

t_liste_station getNextStation( t_liste_station l);
t_liste_station getNextTroncon( t_liste_station l);
t_liste_station getPreviousStation( t_liste_station l);
bool ligneBusVide( t_liste_station l);

int getPosXListeStation( t_liste_station myStationInListe );
int getPosYListeStation( t_liste_station myStationInListe );

//renseigne incX et incY pour le déplacement du sprite dans le main, ET modifie la position du bus qd il atteint les coord X Y de la station d'arrivée
void deplaceBus1(t_bus myBus, t_sens_parcours sens_deplacement, int *incXSprite, int *incYSprite);

void busSurStation( t_bus myBus, t_liste_station myStation, t_sens_parcours sens);
void busSurLigneX( t_bus myBus, int idLigneX );
t_liste_station stationSuivantePourLeBus(t_bus myBus);

void afficheCoordonneesBus( t_bus myBus );

// ****   Lister ci-dessous vos fonctions  ****


#endif // LIGNEBUS_H_INCLUDED
