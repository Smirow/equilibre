# Team Équilibre IPI2 [![Build Status](https://travis-ci.com/Smirow/equilibre.svg?token=e4iudyJx4ptdm1S88isC&branch=sprint-01)](https://travis-ci.com/Smirow/equilibre)

## Getting Started

```
/* Install CUnit */
sudo apt-get install libcunit1 libcunit1-doc libcunit1-dev libsdl-ttf2.0-dev

/* Compile the app */
make // Compilation on Mac OSX need a SDL lib installed with brew (brew install sdl, or Macport but not tested), if you want to use the SDL framework, you will need to modify the makefile and add the needed files.

/* Run the app */
./equilibre.out

/* Compile tests */
make test // You can compile tests regardless of the app

/* Run tests */
./test.out

/* Create the Documentation */
make doc // The documentation doc.pdf is generated in the root directory

/* Clean */
make clean
```

## HOW TO USE

Selectionner une taille pour la grille. Pour toute grille de taille inferieur a 12, choisissez "PERSONNALISEE" puis taper au clavier la taille souhaitée (>1). Choisissez un niveau de difficulté et demarrez la partie. Le menu n'est pour l'instant pas resisable.

Les coups restant sont affichés sur la barre d'état. La fenêtre est completement "resisable" et l'interface responsive. Cliquez sur la couleur choisie pour jouer, R pour rejouer la partie sans modifier la grille et Q pour quitter.
