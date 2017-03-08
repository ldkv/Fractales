#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

#define E	2.718281
#define PI	3.14159265358979
#define RATIO 0.3063489

QVector3D perp(const QVector3D &v);
// Génération aléatoire d'un nombre entier dans l'intervalle donnée
int randomGeneration(int min, int max);
// Convertir la classe QVector3D pour utiliser avec les fonctions OpenGL
void glVector3D(QVector3D p, bool vertex);
// Convertir les couleurs entre valeurs entières et normalisées
QColor convertColor(QVector3D col);