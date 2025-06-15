# Volcanos VS Dinos - Tower Defense

Un mini-jeu Tower Defense développé en C++ avec SFML.  
Le joueur doit défendre son territoire en plaçant des tours sur la carte pour stopper les vagues de dinosaures.

---

## 🎯 Objectifs pédagogiques

- Gestion complète d'un projet C++ orienté objet.
- Architecture modulaire et évolutive.
- Utilisation de SFML pour le rendu graphique.
- Implémentation d'une machine à états pour la gestion des écrans.
- Build system 100% automatisé via CMake.
- Gestion de la mémoire manuelle (pointeurs sur les ennemis).

---

## 📦 Fonctionnalités actuelles

- **Menu principal interactif** (navigation clavier).
- **HomeScreen animé** au lancement.
- **Moteur de jeu Tower Defense** :
  - Génération des vagues de dinosaures.
  - Système de placement de tours.
  - Gestion de la portée, des tirs, des points de vie.
  - Barre de vie dynamique sur les ennemis.
- **Gestion des assets** (fonds d'écran, polices).
- **Architecture extensible** : facilement adaptable pour de nouveaux modes de jeu, types de tours, et mécaniques de gameplay.
- **Portable et cross-platform** (Windows, Linux, WSL, macOS).

---

## 🛠 Technologies utilisées

- **Langage** : C++17
- **Moteur graphique** : SFML 2.5+
- **Système de build** : CMake
- **Architecture** : Machine à états / MVC simplifié

---

## ⚙ Instructions de compilation

### Prérequis

- CMake ≥ 3.16
- SFML ≥ 2.5 (installé sur le système)

### Build

```bash
mkdir build
cd build
cmake ..
cmake --build .
./TowerDefense
