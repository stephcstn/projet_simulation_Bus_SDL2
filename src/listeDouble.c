#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "types.h"
#include "listeDouble.h"

struct T_station; // Déclaration anticipée
typedef struct T_station t_station;
t_station *creeTroncon(int idLigneBus, t_station* depart, t_station *arrivee);

//initListe ne fait pas de malloc, juste une initialisation � NULL du pointeur de liste
void initListe(t_liste *l){
*l=NULL;
}


bool listeVide( t_liste l){
    return (l==NULL);
}

void afficheListe(t_liste l) {
    if (l == NULL) {
        printf("La liste est vide.\n");
        return;
    }

    t_liste courant = l;
    t_liste tete = l;  // Pour d�tecter si on revient � la t�te de la liste dans le cas d'une liste circulaire

    do {
        afficheStation(courant->pdata);  // Affiche les informations de la station ou du tron�on
        courant = courant->suiv;         // Passe � l'�l�ment suivant de la liste
    } while (courant != NULL && courant != tete);  // Arr�te si courant devient NULL (pour une liste non circulaire) ou revient � la t�te (pour une liste circulaire)
}

bool elementPasDansListe(t_station* myStation, t_liste_station l) {
    t_liste_station courant = l;

    while (courant != NULL) {
        if (getIdStation(myStation) == getIdStation(courant->pdata)) {
            return false;  // L'�l�ment existe d�j� dans la liste
        }
        courant = courant->suiv;  // On passe � l'�l�ment suivant
    }
    return true;  // Si l'�l�ment n'est pas trouv�, il n'existe pas d�j� dans la liste
}

t_liste ajoutEnTete(t_liste l, t_station* mydata){
    t_liste nouv = (t_liste)malloc(sizeof(struct T_cell));

    //CHANGEMENT par rapport � la partie2 d'updago
    //nouv->pdata = (int*)malloc(sizeof(int)); ATTENTION PLUS DE RECOPIE de mydata, donc plus d'allocation m�moire sur ce champ

    //SIMPLE BRANCHEMENT EN MEMOIRE ENTRE POINTEURS (SUR LA STATION EXISTANTE)
    nouv->pdata=mydata;

    if (l==NULL) // on cree en fait la premiere cellule de la liste
    {
        nouv->suiv = NULL;  //s�curise la pr�sence de NULL sur le champ suiv, au cas o� le ptr l n'aurait pas �t�  initialis� correctement via initListe
        nouv->prec = NULL;
    }
    else  // la lste n'etait pas vide, on doit donc faire les branchements
    {
        nouv->suiv = l;
        nouv->prec = NULL;
        l->prec = nouv;
    }
    return nouv;
}

t_liste ajoutEnFin(t_liste l, t_station* mydata){
    t_liste nouv, courant=l;  //remarque: pas de malloc si on appelle ajoutEnTete

    if (l==NULL) // on cree en fait la premiere cellule de la liste
    {
        return ajoutEnTete(l, mydata);
    }
    else  // la liste n'etant pas vide,d�placment sur la derniere cellule, malloc et branchements
    {
        while (courant->suiv != NULL){
            courant=courant->suiv;
        }
        nouv = (t_liste)malloc(sizeof(struct T_cell));
        nouv->pdata=mydata;

        nouv->suiv = NULL;
        nouv->prec = courant;
        courant->suiv = nouv;
    }
    return l;  //la t�te d'origine, qui n'a pas chang�
}

t_liste ajoutEnN(t_liste l, int pos, t_station* mydata) {
    t_liste nouv = (t_liste)malloc(sizeof(t_cellule));
    nouv->pdata = (t_station*)malloc(sizeof(t_station));
    nouv->pdata = mydata;

    if (pos == 0 || l == NULL) {
        return ajoutEnTete(l, mydata);
    }

    t_liste temp = l;
    int i;

    for (i = 0; i < pos - 1 && temp->suiv != NULL; i++) {
        temp = temp->suiv;
    }

    nouv->suiv = temp->suiv;
    nouv->prec = temp;

    if (temp->suiv != NULL) {
        temp->suiv->prec = nouv;
    }

    temp->suiv = nouv;

    return l;
}

t_station* getPtrData(t_liste l){
    if (l==NULL)
    {
        printf("\nERREUR ptr pdata non allou�");
        return NULL;
    }
    else
    {
        return l->pdata;
    }
}

t_liste getNextCell(t_liste l){
    if (l==NULL)
    {
        return NULL;  //convention
    }
    else{
        return l->suiv;
    }
}

t_liste getPrevCell(t_liste l){
    if (l==NULL)
    {
        return NULL;  //convention
    }
    else{
        return l->prec;
    }
}


void swapPtrData( t_liste source, t_liste destination )
{
    if (listeVide(source)||listeVide(destination)){
        printf("Erreur swapPtrData ptr = NULL");
    }
    else {
    t_station* tmp = source->pdata;
    source->pdata = destination->pdata;
    destination->pdata = tmp;
    }
}




bool comp_coutMaintenance_AsupB(t_station* a, t_station* b) {
    return a->coutMaintenance > b->coutMaintenance; // Tri d�croissant
}

bool comp_dateMaintenance_AplusAncienQueB(t_station* a, t_station* b) {
    t_date a_date = a->dateDerniereMaintenance;
    t_date b_date = b->dateDerniereMaintenance;

    if (a_date.annee < b_date.annee) {
        return true;
    } else if (a_date.annee == b_date.annee) {
        if (a_date.mois < b_date.mois) {
            return true;
        } else if (a_date.mois == b_date.mois) {
            return a_date.jour < b_date.jour;
        }
    }
    return false;
}



void tri_selection_liste_comp(t_liste l, bool(*fcomp)(t_station* A, t_station* B), int id_ligne) {
    t_liste en_cours, comparatif, j;

    // Tri par s�lection des arr�ts uniquement
    for (en_cours = l; en_cours != NULL && getNextCell(en_cours) != NULL; en_cours = getNextCell(getNextCell(en_cours))) {
        comparatif = en_cours;

        for (j = getNextCell(getNextCell(en_cours)); j != NULL && getNextCell(j) != NULL; j = getNextCell(getNextCell(j))) {
            if (fcomp(getPtrData(comparatif), getPtrData(j))) {
                comparatif = j;
            }
        }

        if (comparatif != en_cours) {
            swapPtrData(en_cours, comparatif);
        }
    }

    // Reconstruction des tron�ons apr�s le tri
    t_liste arrivee;
    t_liste nouv_troncon_cell = (t_liste)malloc(sizeof(struct T_cell));
    t_liste cell_arret = l;

    while (cell_arret != NULL && cell_arret->suiv != NULL && cell_arret->suiv->suiv != NULL) {
        arrivee = cell_arret->suiv->suiv;  // Arr�t d'arriv�e

        // Cr�er un nouveau tron�on entre les deux arr�ts
        t_station* nouv_troncon = creeTroncon(id_ligne,cell_arret->pdata,arrivee->pdata);
        t_liste nouv_troncon_cell = (t_liste)malloc(sizeof(struct T_cell));

        nouv_troncon_cell->pdata = nouv_troncon;  // Stocke le tron�on dans la cellule

        // Mise � jour des pointeurs de la liste doublement cha�n�e
        nouv_troncon_cell->suiv = arrivee;  // Le tron�on pointe vers l'arr�t d'arriv�e
        nouv_troncon_cell->prec = cell_arret;  // Le tron�on pointe vers l'arr�t de d�part

        // Ins�rer le tron�on entre l'arr�t actuel et l'arr�t suivant
        cell_arret->suiv = nouv_troncon_cell;  // L'arr�t actuel pointe vers le tron�on
        arrivee->prec = nouv_troncon_cell;  // L'arr�t suivant pointe vers le tron�on

        // Avancer de deux cellules (vers l'arr�t suivant)
        cell_arret = cell_arret->suiv->suiv;
    }
}

bool estListeStationCirculaire(t_liste_station tete) {
    if (tete == NULL) return false;

    t_cellule* lent = tete;
    t_cellule* rapide = tete;

    while (rapide != NULL && rapide->suiv != NULL) {
        lent = lent->suiv;
        rapide = rapide->suiv->suiv;

        if (lent == rapide) {
            // La liste est circulaire
            return true;
        }
    }

    // La liste est lin�aire
    return false;
}



//A vous la suite si besoin
