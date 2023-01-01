# Projet_ZZ1

## _Structure_du_code_

> First part :

- [`Windows`](https://github.com/lotfiElKhalidy/Projet_ZZ1/tree/main/First%20Part/Windows) : ouverture, déplacement et redimensionnement des fenêtres.

- [`Renderers`](https://github.com/lotfiElKhalidy/Projet_ZZ1/tree/main/First%20Part/Renderers) : affiche des carrés qui se déplacent sur la fenêtre (Utilisation des rendus).

- [`Jeu de vie`](https://github.com/lotfiElKhalidy/Projet_ZZ1/tree/main/First%20Part/Game_Of_Life) : Le jeu se déroule sur une grille à deux dimensions.

![alt text](https://github.com/lotfiElKhalidy/Projet_ZZ1/blob/main/First%20Part/Game_Of_Life/game%20of%20life.gif)

- [`Sprites`](https://github.com/lotfiElKhalidy/Projet_ZZ1/tree/main/First%20Part/Sprites) : animations.

![alt text](https://github.com/lotfiElKhalidy/Projet_ZZ1/blob/main/First%20Part/Sprites/FlyingBird/img/flying%20bird.gif)

- [`2D_Game`](https://github.com/lotfiElKhalidy/Projet_ZZ1/tree/main/First%20Part/2D_Game) : Le chef d'oeuvre représente un jeu 2D de survie utilisant les chaines de Markov.

![alt text](https://github.com/lotfiElKhalidy/Projet_ZZ1/blob/main/First%20Part/2D_Game/img/ralph%20the%20runner.gif)

> Second part :

- [`Apprentissage par renforcement`](https://github.com/lotfiElKhalidy/Projet_ZZ1/tree/main/Second%20Part) : Jeu 2D utilisant l'apprentissage par renforcement en C.

    🌟 **Principe :** Entrainement d'un agent en utilisant Q-learning.<br/>
    🌟 **Choix de l'action :** 90% exploration et 10% exploitation au début et diminution avec le temps (epsilon-greedy).

![alt text](https://github.com/lotfiElKhalidy/Projet_ZZ1/blob/main/Second%20Part/img/Q%20learning.gif)

## _Compilation_et_exécution_

- Pour compiler le fichier :

```
$ gcc nom_fichier.c -o nom_exécutable -Wall -Wextra -lSDL2 lSDL2_image -lm
$ ./nom_exécutable
```
