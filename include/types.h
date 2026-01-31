#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED

typedef enum Type_noeud {ARRET, TRONCON} t_noeud;

typedef struct T_date {
    int jour;
    int mois;
    int annee;
} t_date;

typedef struct T_station { //représente UN TRONCON (entre deux arrêts) ou UN ARRET (cad une station de la ligne de bus)

    t_noeud arret_ou_troncon;

    //données utiles si le Noeud est un TRONCON
    int idLigneBus;                    //numéro de la ligne de bus par laquelle on arrive sur la station
    struct T_station* depart;          // pointeurs sur les stations de départ et d'arrivée du tronçon
    struct T_station* arrivee;
    int coutTemps;                     // coût en temps de parcours (en secondes)
    int coutDistance;                  // coût en distance (en mètres)
    int tempsCumule, distanceCumule;   // champs utiles pour déterminer le meilleur itinéraire

    //données utiles si le Noeud est un ARRET
    int posX, posY;                    //coordonnées sur le plan de la ville
    char nomStation[30];
    int idStation;                     //numéro unique et non liée à une ligne, une ligne de bus étant constituée d'une suite de d'id stations: exemple : 3  - 7 - 1 - 5
    int coutMaintenance;                //en Kilo euro, une valeur entre 10 et 100  (A VOUS DE GERER)
    t_date dateDerniereMaintenance;     //t_date est à définir, doit permettre de stocker une date jour/mois/année, y mettre une date aléatoire (A VOUS DE GERER)

    //struct T_station* correspondances; //égale à NULL si pas de correspondance, sinon égale à une liste de TRONCONS
    //int coutCumule;                    //pour le calcul du plus court chemin, algo de Djikstra

} t_station;


//type pour la liste doublement chainée, utilisé daans listeDouble.h/.c
typedef struct T_cell{
    struct T_cell *suiv;
    struct T_cell *prec;
    t_station *pdata;              //attention à faire un malloc sur ce champ avant de s'en servir
} t_cellule;
typedef t_cellule* t_liste;


//Une liste de stations  (basée sur listeDouble.h/.c)
typedef t_liste t_liste_station;  //T_liste et TlisteStation sont équivalents, cad pointeur sur Tcellule

//une ligne de bus
typedef struct {
    int idLigneBus;  //donnée qui sera dupliquée dans chaque troncon de la ligne (pour aider au debugage et pour aider à la gestion des correspondances)
    char *nomLigne;
    t_liste_station depart;   //peut etre parcouru dans les deux sens
    t_liste_station arrivee;
} t_ligne;

typedef enum{ depart_vers_arrivee, arrivee_vers_depart} t_sens_parcours;

typedef struct{
    int idBus;
    t_liste_station positionSurLaLigneDeBus; //la derniere station atteinte (dans la liste) du bus est dans le champ pdata, stocké dans un Tcellule
    int posXBus, posYBus;                    //coord du bus pixel par pixel pour les trajets
    int idLigneBusActuelle;                  //un bus suit une ligne de bus à un instant t et peut en changer
    t_sens_parcours sensParcours;
    int hasPrintedTerminus;                  // Champ pour vérifier si le message du terminus a été imprimé
} type_bus;

typedef type_bus *t_bus;

//affichage
void afficheStation( t_station *station );

//Getteurs

t_station* getDepartTroncon(t_station *myStation);
t_station* getArriveeTroncon(t_station *myStation);
int getIdStation( t_station *myStation);
char *getNomStation( t_station *myStation);
int getPosXStation( t_station *myStation );
int getPosYStation( t_station *myStation );
int getIdLigneTroncon(t_station *myStation);
t_station* getStationParId(int id, t_ligne* ligne_bus);
int getIdLigneBusStation(t_station* myStation, t_ligne* tab_ligne) ;
int getDistanceCumule(t_station *myStation);
int getTempsCumule(t_station *myStation);
int getCoutTemps(t_station *myStation);
int getCoutDistance(t_station *myStation);
int getCoutMaintenance(t_station *myStation);
t_date getDateDerniereMaintenance(t_station *myStation);

t_noeud getTypeNoeud(t_station *myStation);

int getPosXBus( t_bus myBus );
int getPosYBus( t_bus myBus );
int getIdBus( t_bus myBus );
int getIdLigneActuelleDuBus( t_bus myBus );
t_sens_parcours getSensParcours(t_bus myBus);
int getIdLigneBusStation(t_station* myStation, t_ligne* tab_ligne);
t_liste_station getPositionSurLaLigneDeBus(t_bus myBus);

//Setteurs

//t_bus
void setPosXBus(t_bus myBus, int newX);
void setPosYBus(t_bus myBus, int newY);
void setIdLigneBusActuelle(t_bus myBus, int idLigne);
void setSensParcours(t_bus myBus, t_sens_parcours sens );
void setPositionSurLaLigneDeBus( t_bus myBus, t_liste_station myStation);
void setIdBus(t_bus myBus, int newidBus);

//t_station
void setArretTroncon(t_station *myStation, t_noeud nouv_noeud);
void setIdLigneBus(t_station *myStation, int nouv_id);
void setStationDepart(t_station *myStation, t_station *nouv_station_dep);
void setStationArrive(t_station *myStation, t_station *nouv_station_arr);
void setCoutTemps(t_station *myStation, int cout_temp);
void setCoutDistance(t_station *myStation, int cout_dist);
void setTempsCumule(t_station *myStation, int temps_cum);
void setDistanceCumule(t_station *myStation, int dist_cum);
void setPosX(t_station *myStation, int new_posX);
void setPosY(t_station *myStation, int new_posY);
void setNomStation(t_station *myStation, const char *nom_station);
void setIdStation(t_station *myStation, int id_station);
void setCoutMaintenance(t_station *myStation, int couts);
void setDateDerniereMaintenance(t_station *myStation);

#endif // TYPES_H_INCLUDED
