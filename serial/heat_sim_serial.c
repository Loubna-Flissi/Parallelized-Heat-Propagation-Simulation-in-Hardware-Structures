#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define TAILLE 1000       // Taille de la grille
#define ITERATIONS 1000   // Nombre d'itérations pour la simulation de chaleur

int main() {
    double** grille = (double**)malloc(TAILLE * sizeof(double*)); 
    double** nouvelle_grille = (double**)malloc(TAILLE * sizeof(double*));

    // Allocation de mémoire pour la grille
    for (int i = 0; i < TAILLE; i++) {
        grille[i] = (double*)malloc(TAILLE * sizeof(double));
        nouvelle_grille[i] = (double*)malloc(TAILLE * sizeof(double));
    }

    // Initialisation de la grille avec des valeurs aléatoires
    srand(time(NULL)); // Initialiser le générateur de nombres aléatoires
    for (int i = 0; i < TAILLE; i++)
        for (int j = 0; j < TAILLE; j++)
            grille[i][j] = rand() % 100;

    // Boucle sur les itérations
    for (int t = 0; t < ITERATIONS; t++) {
        // Calcul de la nouvelle grille
        for (int i = 1; i < TAILLE - 1; i++) {
            for (int j = 1; j < TAILLE - 1; j++) {
                nouvelle_grille[i][j] = 0.25 * (grille[i-1][j] + grille[i+1][j] + grille[i][j-1] + grille[i][j+1]) +
                                         10 * sin(i * 0.01) * cos(j * 0.01);
            }
        }

        // Mise à jour de la grille principale
        for (int i = 1; i < TAILLE - 1; i++) {
            for (int j = 1; j < TAILLE - 1; j++) {
                grille[i][j] = nouvelle_grille[i][j];
            }
        }

        // Affichage de l'état d'itération à chaque itération
        printf("Iteration %d/%d terminee\n", t, ITERATIONS);
    }

    // Libération de la mémoire
    for (int i = 0; i < TAILLE; i++) {
        free(grille[i]);
        free(nouvelle_grille[i]);
    }
    free(grille);
    free(nouvelle_grille);

    return 0;
}
