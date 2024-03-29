Main Page {#mainpage}
======================

## Génération des Makefile à l'aide de CMake3

A partir de la racine, il est possible de générer les Makefile propres au projet en lançant la commande suivante à partir d'un des PC de l'ENSIMAG :

`mkdir build && cd build &&  cmake3 -DCMAKE_PREFIX_PATH=/matieres/5MMPMP6/pnl ..`

A partir d'un ordinateur personnel, remplacez `cmake3` par `cmake` et le chemin vers votre librairie PNL.

---

## Compilation des sources

A partir du dossier build, lancez la commande :

`make all`

afin de générer tous les exécutables et documentations du projet.

---

## Lancement des tests Python fournis

Vous pouvez lancer le fichier test Python fourni qui va comparer nos résultats à des fichiers expected sur des paramètres prédéfinis. Pour celà, lancez la commande suivante à partir du dossier build :

* `python3 ../PythonForMod.py --price --exec=. --datadir=../data/data-price/ --outdir=../` pour le calcul du prix en 0 et des deltas de différentes options.

* `python3 ../PythonForMod.py --hedge --exec=. --datadir=../data/data-hedge/ --outdir=../` pour le calcul du P&L et du portefeuille de couverture de différentes options.

## Affichage de la documentation

A partir du dossier build, lancez la commande :

`firefox ../doc/html/index.html &`

pour afficher la documentation générée par Doxygen. Elle se crée à partir d'un fichier cfg de Doxygen et d'un template html pour plus de visibilité.

---

## Lancement des différents tests

A partir du dossier build, lancez les différentes commandes : 

* `./test-asset` pour tester la simulation d'un marché et le remplissage de la matrice path.

* `./test-payoff` pour tester le calcul de payoff pour différentes options implémentées selon un marché simulé.

* `./test-price0` pour tester le calcul de prix en 0  pour différentes options implémentées et par la méthode de Monte Carlo.

* `./test-pricet` pour tester le calcul de prix en t pour différentes options implémentées et par la méthode de Monte Carlo.

* `./test-deltas` pour tester le calcul des deltas pour différentes options implémentées et par la méthode de Monte Carlo.

* `./test-couverture` pour tester le calcul du portefeuille de couverture et du P&L pour différentes options implémentées et par la méthode de Monte Carlo.

* `./test-simulmarket` pour tester la simulation d'un marché avec des paramètres pré-déterminés.

---

Vous pouvez nettoyer tous les fichiers temporaires ou non nécessaires à l'aide de la commande 

`make clean`

---

## Rapport

Notre rapport est disponible [ici](../../AUTHORS/Projet_MP.pdf)

