#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "types.h"
#include "listeDouble.h"


//initListe ne fait pas de malloc, juste une initialisation à NULL du pointeur de liste
void initListe(t_liste *l){
*l=NULL;
}


bool listeVide( t_liste l){
    return (l==NULL);
}

void afficheListe( t_liste l){
    t_liste courant = l;
    while (courant!=NULL){
        afficheStation(courant->pdata);  //fourni par types.h
        courant=courant->suiv;
    }
}

t_liste ajoutEnTete(t_liste l, t_station* mydata){
    t_liste nouv = (t_liste)malloc(sizeof(struct T_cell));

    //CHANGEMENT par rapport à la partie2 d'updago
    //nouv->pdata = (int*)malloc(sizeof(int)); ATTENTION PLUS DE RECOPIE de mydata, donc plus d'allocation mémoire sur ce champ

    //SIMPLE BRANCHEMENT EN MEMOIRE ENTRE POINTEURS (SUR LA STATION EXISTANTE)
    nouv->pdata=mydata;

    if (l==NULL) // on cree en fait la premiere cellule de la liste
    {
        nouv->suiv = NULL;  //sécurise la présence de NULL sur le champ suiv, au cas où le ptr l n'aurait pas été  initialisé correctement via initListe
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
    else  // la liste n'etant pas vide,déplacment sur la derniere cellule, malloc et branchements
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
    return l;  //la tête d'origine, qui n'a pas changé
}

t_station* getPtrData(t_liste l){
    if (l==NULL)
    {
        printf("\nERREUR ptr pdata non alloué");
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




bool comp_coutMaintenance_AinfB(t_station a, t_station b) {
    return a.coutMaintenance < b.coutMaintenance;
}


bool comp_dateMaintenance_AsupB(t_station a, t_station b) {
    t_date a_date = a.dateDerniereMaintenance;
    t_date b_date = b.dateDerniereMaintenance;

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



void tri_selection_liste_comp(t_liste l, bool(*fcomp)(t_station A, t_station B))
{
    t_liste en_cours, comparatif, j;

    for (en_cours = l; en_cours != NULL; en_cours = getNextCell(en_cours))
    {
        comparatif = en_cours;
        for (j = getNextCell(en_cours); j != NULL; j = getNextCell(j))
        {
            if (fcomp(*(getPtrData(comparatif)), *(getPtrData(j))))
            {
                comparatif = j;
            }
        }
        if (comparatif != en_cours)
        {
            swapPtrData(en_cours, comparatif);
        }
    }
}



//A vous la suite si besoin
