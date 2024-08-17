#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define MAX 100

int m;
int rotirana[MAX][MAX];
int original[MAX][MAX];

typedef struct {
    int pocetni_red;
    int poslednji_red;
} thread_data_t;

void read(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Greska!");
        exit(1);
    }

    fscanf(file, "%d", &m);

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            fscanf(file, "%d", &original[i][j]);
        }
    }
    fclose(file);
}

void* rotiranje(void* arg) {
    thread_data_t* podaci = (thread_data_t*)arg;
    for (int i = podaci->pocetni_red; i <= podaci->poslednji_red; i++) {
        for (int j = 0; j < m; j++) {
            rotirana[j][m - 1 - i] = original[i][j];
        }
    }
    pthread_exit(NULL);
}

void write(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        perror("Greska!");
        exit(2);
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            fprintf(file, "%d ", rotirana[i][j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

int main() {
    // Čitanje matrice iz fajla
    read("input.txt");

    int num_threads = m < MAX ? m : MAX; // Broj niti je min(m, MAX)
    pthread_t niti[num_threads];
    thread_data_t podatak[num_threads];

    int rows_per_thread = m / num_threads;
    int extra_rows = m % num_threads;

    for (int i = 0; i < num_threads; i++) {
        podatak[i].pocetni_red = i * rows_per_thread;
        podatak[i].poslednji_red = (i + 1) * rows_per_thread - 1;

        if (i == num_threads - 1) {
            podatak[i].poslednji_red += extra_rows; // Dodaj ostatak redova poslednjoj niti
        }

        pthread_create(&niti[i], NULL, rotiranje, (void*)&podatak[i]); // ovde se prosledjuje pokazivac na strukturu u kojoj se 
        // nalaze podaci o pocetnok i posl redu..
    }

    for (int i = 0; i < num_threads; i++) {
        pthread_join(niti[i], NULL);
    }

    write("output.txt");

    printf("Nova matrica se nalazi u fajlu output.txt\n");
    return 0;
}
