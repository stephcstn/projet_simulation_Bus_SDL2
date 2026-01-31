//NOM prénom étudiant 1 : Stephane Castan
//NOM prénom étudiant 2 : Basile Dufrene

#include "SDL.h"
#include "maSDL.h"
#include "SDL_VSYNC.h"
#include "listeDouble.h"

//#include "types.h"
#include "ligneBus.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NB_BUS 4

/*--------- Main ---------------------*/
int main(int argc, char* argv[])
{
    srand(time(NULL));


    //SDL
    //fenetre dans windows
    SDL_Window *gWindow = NULL;
    SDL_Init(SDL_INIT_VIDEO);

    //la texture (charge dans la ram de la carte graphique) target representant tout le jeu
    SDL_Renderer* gRenderer = NULL;

    //Les textures, le type Ltexture est defini dans SDL_VSYNC.h
    LTexture gSpriteBus;
    LTexture gSpriteArretBus;

    //Start up SDL and create window
	if( !init(&gWindow,&gRenderer) )  //initialise la fenetre SDL et charge UNE texture
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadAnimation(&gSpriteBus, gRenderer, "./data/4bus.png")
            || !loadSprite(&gSpriteArretBus, gRenderer, "./data/arret_bus_50x27.png"))
        {
			fprintf(stdout,"echec de chargement du sprite (%s)\n",SDL_GetError());
		}
		else
		{
        //A COMMENTER quand vous en aurez assez de cliquer sur ces popups ^^
        message("Welcome in BusProject","Ceci est un point de depart de votre future interface de vos lignes de Bus");
        message("et fin","ECHAP->quitter, + vos touches + D/V pour sauvegarer/restaurer un bus et le reseau de lignes");

        t_ligne* lignes_bus = creeListeLigneDeBus();
        t_station* depart = getStationParId(2, lignes_bus);
        t_station* arrivee = getStationParId(15, lignes_bus);

        creerLigneEntre2Stations(depart, arrivee, lignes_bus, 3);

        //tri_selection_liste_comp(ligne1.depart,comp_coutMaintenance_AsupB,1);
        //tri_selection_liste_comp(lignes_bus[1].depart,comp_dateMaintenance_AplusAncienQueB,2);

        suppressionStationLigneDeBus(lignes_bus,2,"Jules_Ferry");

        rendreCirculaireLigneBus(lignes_bus[1]);

        //creation d'un (seul) bus
        t_bus* tab_bus = (t_bus*)malloc(NB_BUS * sizeof(t_bus));

        tab_bus[0] = creeBus(1, lignes_bus[0]);
        tab_bus[1] = creeBus(2, lignes_bus[1]);
        tab_bus[2] = creeBus(3, lignes_bus[2]);
        tab_bus[3] = creeBus(4, lignes_bus[3]);

        t_bus bus1 = tab_bus[0];
        t_bus bus2 = tab_bus[1];
        t_bus bus3 = tab_bus[2];
        t_bus bus4 = tab_bus[3];





        //affiche sur la console les stations et troncons des lignes de bus
        afficheConsoleLigneBus(lignes_bus,4);
        printf("\n\n\n");



        //Current animation frame
        int frame = 0;

        //affiche et initialise le sprite du bus au depart
        for (int i = 0; i < NB_BUS; i++){
            Affiche_Sprite(&gSpriteBus, gRenderer, getPosXBus( tab_bus[i] ), getPosYBus( tab_bus[i] ), getIdFrame(frame));
        }


        // boucle principale du jeu
        int cont = 1;
        int* incXDeplSpriteBus = (int*)malloc(NB_BUS * sizeof(int));
        int* incYDeplSpriteBus = (int*)malloc(NB_BUS * sizeof(int)); //deplacement du sprite du bus a chaque passage dans la boucle principale

        for(int j = 0; j < NB_BUS; j++){
            incXDeplSpriteBus[j] = 0;
            incYDeplSpriteBus[j] = 0;
        }

        int count = 0;

        bool deja_compte_ce_tour[NB_BUS] = {false};
        int compte_tour[NB_BUS] = {0};

        int etatSelection = 0; // 0 = attente de sélection de bus, 1 = attente de sélection de ligne
        int busActif = -1;
        int ligneActuelle = -1;

        while ( cont != 0 ){
                SDL_PumpEvents(); //do events

                  //deplaceBus g�re le d�placement du bus sur sa ligne, selon son sens du parcours de la ligne;
                //met � jour les variations en X et Y pour d�placer le sprite du Bus (cf ligne 151)
                for (int k =  0; k < NB_BUS; k++){
                    deplaceBus(tab_bus[k], getSensParcours(tab_bus[k]), &incXDeplSpriteBus[k], &incYDeplSpriteBus[k]);
                }

                const Uint8* pKeyStates = SDL_GetKeyboardState(NULL);

                if (etatSelection == 0) {
                    if (pKeyStates[SDL_SCANCODE_1]) {
                        SDL_Delay(150);
                        printf("\n\nBus 1 selectionne\n");
                        busActif = 1;
                        etatSelection = 1;
                    }
                    if (pKeyStates[SDL_SCANCODE_2]) {
                        SDL_Delay(150);
                        printf("\n\nBus 2 selectionne\n");
                        busActif = 2;
                        etatSelection = 1;
                    }
                    if (pKeyStates[SDL_SCANCODE_3]) {
                        SDL_Delay(150);
                        printf("\n\nBus 3 selectionne\n");
                        busActif = 3;
                        etatSelection = 1;
                    }
                    if (pKeyStates[SDL_SCANCODE_4]) {
                        SDL_Delay(150);
                        printf("\n\nBus 4 selectionne\n");
                        busActif = 4;
                        etatSelection = 1;
                    }
            } else if (etatSelection == 1) {
                if (pKeyStates[SDL_SCANCODE_1]) {
                    SDL_Delay(150);
                    printf("\n\nLigne 1 affectee au bus %d\n", busActif);
                    ligneActuelle = 1;
                    etatSelection = 2;
                }
                if (pKeyStates[SDL_SCANCODE_2]) {
                    SDL_Delay(150);
                    printf("\n\nLigne 2 affectee au bus %d\n", busActif);
                    ligneActuelle = 2;
                    etatSelection = 2;
                }
                if (pKeyStates[SDL_SCANCODE_3]) {
                    SDL_Delay(150);
                    printf("\n\nLigne 3 affectee au bus %d\n", busActif);
                    ligneActuelle = 3;
                    etatSelection = 2;
                }
                if (pKeyStates[SDL_SCANCODE_4]) {
                    SDL_Delay(150);
                    printf("\n\nLigne 4 affectee au bus %d\n", busActif);
                    ligneActuelle = 4;
                    etatSelection = 2;
                }
            } else if (etatSelection == 2) {
                if (pKeyStates[SDL_SCANCODE_W]) {
                    SDL_Delay(150);
                    printf("\n\nDepart vers terminus pour bus %d sur ligne %d\n", busActif, ligneActuelle);
                    setSensParcours(tab_bus[busActif - 1], depart_vers_arrivee);

                if (ligneActuelle == 1)
                    busSurStation(tab_bus[busActif - 1], lignes_bus[0].depart, depart_vers_arrivee);
                else if (ligneActuelle == 2)
                    busSurStation(tab_bus[busActif - 1], lignes_bus[1].depart, depart_vers_arrivee);
                else if (ligneActuelle == 3)
                    busSurStation(tab_bus[busActif - 1], lignes_bus[2].depart, depart_vers_arrivee);
                else if (ligneActuelle == 4)
                    busSurStation(tab_bus[busActif - 1], lignes_bus[3].depart, depart_vers_arrivee);

                Affiche_Sprite(&gSpriteBus, gRenderer, getPosXBus(tab_bus[busActif - 1]), getPosYBus(tab_bus[busActif - 1]), getIdFrame(frame));
                etatSelection = 0;  // Reset
                }

                if (pKeyStates[SDL_SCANCODE_S]) {
                    SDL_Delay(150);
                    printf("\n\nTerminus vers depart pour bus %d sur ligne %d\n", busActif, ligneActuelle);
                    setSensParcours(tab_bus[busActif - 1], arrivee_vers_depart);

                if (ligneActuelle == 1)
                    busSurStation(tab_bus[busActif - 1], lignes_bus[0].arrivee, arrivee_vers_depart);
                else if (ligneActuelle == 2)
                    busSurStation(tab_bus[busActif - 1], lignes_bus[1].arrivee, arrivee_vers_depart);
                else if (ligneActuelle == 3)
                    busSurStation(tab_bus[busActif - 1], lignes_bus[2].arrivee, arrivee_vers_depart);
                else if (ligneActuelle == 4)
                    busSurStation(tab_bus[busActif - 1], lignes_bus[3].arrivee, arrivee_vers_depart);

                Affiche_Sprite(&gSpriteBus, gRenderer, getPosXBus(tab_bus[busActif - 1]), getPosYBus(tab_bus[busActif - 1]), getIdFrame(frame));
                etatSelection = 0;  // Reset
                }
            }

                if ( pKeyStates[SDL_SCANCODE_ESCAPE] ){

                        printf("\nTouche ECHAP");
                        cont = 0;  //sortie de la boucle
                }

                //affichage du jeu a chaque tour
                for (int i = 0; i < NB_BUS; i++) {
                    if (estListeStationCirculaire(tab_bus[i]->positionSurLaLigneDeBus)) {
                        if (tab_bus[i]->positionSurLaLigneDeBus == trouveStationDepart(tab_bus[i], lignes_bus)) {
                            if (!deja_compte_ce_tour[i]) {
                                printf("\n\nLe bus %d a termine %d tours sur la ligne %d circulaire.",
                                tab_bus[i]->idBus, compte_tour[i] + 1, tab_bus[i]->idLigneBusActuelle);
                                afficheStation(trouveStationDepart(tab_bus[i], lignes_bus)->pdata);
                                compte_tour[i]++;
                                deja_compte_ce_tour[i] = true;
                            }
                        } else {
                            deja_compte_ce_tour[i] = false;  // On quitte la station de départ → on réarme le drapeau
                        }
                    }
                }

                //on efface toute la fenetre
                efface_fenetre_texture(gRenderer);

                //D�placement de sprite du bus sur la texture
                for (int l = 0; l < NB_BUS; l++) {
                    int x = getPosXBus(tab_bus[l]);
                    int y = getPosYBus(tab_bus[l]);
                    Affiche_Sprite(&gSpriteBus, gRenderer, x, y, getIdFrame(frame));
                }

                //r�affichage a chaque tour de toutes les stations
                DessineUneLigneBus(lignes_bus[0].depart, gSpriteArretBus, gRenderer);
                DessineUneLigneBus(lignes_bus[1].depart, gSpriteArretBus, gRenderer);
                DessineUneLigneBus(lignes_bus[2].depart, gSpriteArretBus, gRenderer);
                DessineUneLigneBus(lignes_bus[3].depart, gSpriteArretBus, gRenderer);

                //affichage de la texture ainsi mis a jour
                maj_fenetre_texture(gRenderer);

                SDL_Delay(1); //valeur du delai modifiable en fonction de votre CPU
                ++frame;
            }
        //fin boucle du jeu
        }
	}

	//Free resources and close SDL
	free_Ltexture(&gSpriteBus);
	free_Ltexture(&gSpriteArretBus);
	close(gWindow, gRenderer);

    return 0;
}
