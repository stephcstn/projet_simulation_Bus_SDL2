#ifndef LIGNEBUS_H_INCLUDED
#define LIGNEBUS_H_INCLUDED

#include <stdbool.h>
#include "types.h"
t_bus creeBus( int idBus, t_liste_station start );
t_station *creeArret( int posX, int posY, char* nomStation, int idStation);
int resultat_distance_vecteur(int cord_a, int cord_b);
t_station *creeTroncon( int idLigneBus, t_station* depart, t_station *arrivee);

//TlisteStation* initReseauLignesDeBus(int *nbLignes);
t_liste_station creeLigneDeBus1(void);
t_liste_station creeLigneDeBus2(void);
t_liste_station creeLigneDeBus3(void);
void afficheConsoleLigneBus( t_liste_station l);

t_liste_station getNextStation( t_liste_station l);
t_liste_station getNextTroncon( t_liste_station l);
t_liste_station getPreviousStation( t_liste_station l);
bool ligneBusVide( t_liste_station l);

int getPosXListeStation( t_liste_station myStationInListe );
int getPosYListeStation( t_liste_station myStationInListe );

//renseigne incX et incY pour le déplacement du sprite dans le main, ET modifie la position du bus qd il atteint les coord X Y de la station d'arrivée
void deplaceBus(t_bus myBus, t_sens_parcours sens_deplacement, int *incX, int *incY);

void busSurStation( t_bus myBus, t_liste_station myStation, t_sens_parcours sens);
void busSurLigneX( t_bus myBus, int idLigneX );
t_liste_station stationSuivantePourLeBus(t_bus myBus);

void afficheCoordonneesBus( t_bus myBus );

// ****   Lister ci-dessous vos fonctions  ****


#endif // LIGNEBUS_H_INCLUDED
