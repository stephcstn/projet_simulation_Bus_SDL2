#ifndef LISTEDOUBLE_H_INCLUDED
#define LISTEDOUBLE_H_INCLUDED

#include <stdbool.h>
#include "types.h"

/*  défini dans types.h
typedef struct T_cell{
    struct T_cell *suiv;
    struct T_cell *prec;
    Tstation *pdata;              //attention à faire un malloc sur ce champ avant de s'en servir
} T_cellule;
typedef T_cellule* T_liste;
*/

void initListe(t_liste *l);
bool listeVide( t_liste l);

void afficheListe( t_liste l);

//Pour "AfficheListeV1" Vous avez le droit de lire directement dans la structure de données
//Utile pour afficher et debuguer les fonctions ci-dessous

t_liste ajoutEnTete(t_liste l, t_station* mydata);
t_liste ajoutEnFin(t_liste l, t_station* mydata);

t_station* getPtrData(t_liste l);
t_liste getNextCell(t_liste l);
t_liste getPrevCell(t_liste l);
bool comp_coutMaintenance_AinfB(t_station a, t_station b);
bool comp_dateMaintenance_AsupB(t_station a, t_station b);
void tri_selection_liste_comp(t_liste l, bool(*fcomp)(t_station A, t_station B));
/* fin de tag ligne 50
T_liste ajoutEnN(T_liste l, int pos, Tstation* mydata);

T_liste suppEnTete(T_liste l);
T_liste suppEnFin(T_liste l);
T_liste suppEnN(T_liste l, int pos);

T_liste getptrFirstCell(T_liste l);
T_liste getptrLastCell(T_liste l);
T_liste getptrNextCell(T_liste l);
T_liste getptrPrevCell(T_liste l);

void swapPtrData( T_liste source, T_liste destination );

int getNbreCell(T_liste l);
int getSizeBytes(T_liste l); //utilisation de sizeof

T_liste creatNewListeFromFusion(T_liste l1, T_liste l2); //on souhaite CREER une nouvelle liste sans modifier l1 et l2
T_liste addBehind(T_liste debut, T_liste suite);

T_liste findCell(T_liste l, Tstation* data);
int getOccurences(T_liste l, Tstation* data);  //nbre de fois que data est présent dans toute la liste l1

void afficheListeV2( T_liste l);
//Pour "AfficheListeV2", vous devez utiliser uniquement les fonctions écrites ci-dessus (interdiction de passer directement par les champs ptr de la SD)

début de tag ligne 16 */

#endif // LISTEDOUBLE_H_INCLUDED

