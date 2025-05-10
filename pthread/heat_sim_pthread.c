#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <pthread.h>

#define TAILLE 1000       // Taille de la grille
#define ITERATIONS 1000   // Nombre d'itérations pour la simulation de chaleur
#define N_THREADS 4       // Nombre de threads à utiliser

typedef struct {
    double** grille;
    double** nouvelle_grille;
    int thread_id;
    int iterations_per_thread;
} ThreadData;

// Structure pour stocker l'état d'itération
typedef struct {
    int iteration_done;
    int thread_id;
} IterationStatus;

IterationStatus status[ITERATIONS]; // Statut des itérations
pthread_mutex_t print_mutex;         // Mutex pour protéger l'affichage
pthread_barrier_t barrier;           // Déclaration de la barrière en tant que variable globale

void* simuler_chaleur_partie(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    double** grille = data->grille;
    double** nouvelle_grille = data->nouvelle_grille;

    int start_iteration = data->thread_id * data->iterations_per_thread;
    int end_iteration = start_iteration + data->iterations_per_thread;

    for (int t = start_iteration; t < end_iteration; t++) {
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

        // Enregistrement de l'état d'itération
        pthread_mutex_lock(&print_mutex);
        status[t].iteration_done = t;
        status[t].thread_id = data->thread_id;
        printf("Iteration %d/%d terminee par le thread %d\n", status[t].iteration_done, ITERATIONS, status[t].thread_id);
        pthread_mutex_unlock(&print_mutex);

        // Synchronisation pour la prochaine itération
        pthread_barrier_wait(&barrier);
    }
    return NULL;
}

int main() {
    double** grille = (double**)malloc(TAILLE * sizeof(double*));
    double** nouvelle_grille = (double**)malloc(TAILLE * sizeof(double*));
    pthread_t threads[N_THREADS];
    ThreadData thread_data[N_THREADS];

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

    // Initialisation de la barrière
    pthread_barrier_init(&barrier, NULL, N_THREADS);
    pthread_mutex_init(&print_mutex, NULL); // Initialisation du mutex

    // Création des threads
    int iterations_per_thread = ITERATIONS / N_THREADS;
    for (int i = 0; i < N_THREADS; i++) {
        thread_data[i].grille = grille;
        thread_data[i].nouvelle_grille = nouvelle_grille;
        thread_data[i].thread_id = i; // Identifier le thread
        thread_data[i].iterations_per_thread = iterations_per_thread;
        pthread_create(&threads[i], NULL, simuler_chaleur_partie, &thread_data[i]);
    }

    // Attente de la fin des threads
    for (int i = 0; i < N_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Libération de la mémoire
    for (int i = 0; i < TAILLE; i++) {
        free(grille[i]);
        free(nouvelle_grille[i]);
    }
    free(grille);
    free(nouvelle_grille);

    // Destruction de la barrière et du mutex
    pthread_barrier_destroy(&barrier);
    pthread_mutex_destroy(&print_mutex);

    return 0;
}