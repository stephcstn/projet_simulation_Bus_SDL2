# Simulateur de Réseau de Bus (SDL2)

![C](https://img.shields.io/badge/Language-C-blue.svg)
![SDL2](https://img.shields.io/badge/Library-SDL2-green.svg)
![Platform](https://img.shields.io/badge/Platform-Windows-lightgrey.svg)

Ce projet est une application de simulation et de gestion de lignes de bus développée en **C** avec la bibliothèque graphique **SDL2**. Il permet de visualiser un réseau, de gérer des stations, des tronçons et de simuler le déplacement des bus.

## Structure du Projet

L'organisation du dépôt suit les standards de développement C :

* `src/` : Fichiers sources (`.c`).
* `include/` : Fichiers d'en-tête (`.h`).
* `bin/Debug/` : Contient l'exécutable final et les DLL nécessaires.
* `obj/Debug/` : Fichiers objets temporaires issus de la compilation.
* `SDL2/` : Dossier contenant la bibliothèque de développement (MinGW64).
* `assets/` : Ressources du jeu (images, données des lignes).

## Prérequis

Pour compiler ce projet, vous avez besoin de :
1.  **MSYS2** avec le compilateur **MinGW-w64**.
2.  La bibliothèque **SDL2** (incluse dans le dépôt pour Windows).
3.  L'outil **Make** (`mingw32-make` sur Windows).

## Compilation

Le projet utilise un `Makefile` pour automatiser la compilation. Ouvrez un terminal à la racine du projet et tapez :

```powershell
mingw32-make