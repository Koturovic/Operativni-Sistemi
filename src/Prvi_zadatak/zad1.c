#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

#define MATRIX_SIZE 3
#define TMP 50

typedef struct {
    double vreme_izvrsavanje;
    int matrix[MATRIX_SIZE * MATRIX_SIZE];
    int zbir;
} Rezultat;

// Funkcija za čitanje matrice iz fajla input<i>.txt
void citajIzFajla(const char* ulazni_fajl, int matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    FILE *in = fopen(ulazni_fajl, "r");
    if (!in) {
        perror("Neuspelo otvaranje fajla");
        exit(1);
    }

    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            fscanf(in, "%d", &matrix[i][j]);
        }
    }
    fclose(in);
}

// Funkcija koja sabira pozitivne članove matrice
int saberiPozitivne(int matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    int zbir = 0;
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            if (matrix[i][j] >= 0) {
                zbir += matrix[i][j];
            }
        }
    }
    return zbir;
}

// Funkcija za upis rezultata u tmp fajl
void racunaj_upisi(int id, const char* ulazni_fajl, const char* tmp_fajl) {
    int matrix[MATRIX_SIZE][MATRIX_SIZE];

    clock_t citanje_time = clock();
    citajIzFajla(ulazni_fajl, matrix);
    clock_t citanje_end = clock();
    double citanje_ukupno_vreme = ((double)(citanje_end - citanje_time)) / CLOCKS_PER_SEC;

    printf("Dete %d: Matricu je procitalo iz %s:\n", id + 1, ulazni_fajl);
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    clock_t zbir_vreme = clock();
    int zbir = saberiPozitivne(matrix);
    clock_t zbir_end_vreme = clock();
    double zbir_ukupno_vreme = ((double)(zbir_end_vreme - zbir_vreme)) / CLOCKS_PER_SEC;

    double ukupno_vreme = citanje_ukupno_vreme + zbir_ukupno_vreme;

    FILE *out = fopen(tmp_fajl, "w");
    if (!out) {
        perror("Neuspelo otvaranje");
        exit(1);
    }
    fprintf(out, "Ukupno vreme izvrsavanja: %.6f\n", ukupno_vreme);
    fprintf(out, "Matrica:\n");
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            fprintf(out, "%d ", matrix[i][j]);
        }
        fprintf(out, "\n");
    }
    fprintf(out, "Zbir: %d\n", zbir);
    fclose(out);
    printf("Dete %d: Upisao sam podatke u %s\n", id + 1, tmp_fajl);
    exit(0);
}

// Funkcija za čitanje i sortiranje rezultata iz tmp fajlova
void citaj_sortiraj(int n, Rezultat rezultati[]) {
    char tmp_fajl[20];
    FILE* file;
    for (int i = 0; i < n; i++) {
        sprintf(tmp_fajl, "tmp%d.txt", i + 1);
        file = fopen(tmp_fajl, "r");
        if (file) {
            fscanf(file, "Ukupno vreme izvrsavanja: %lf\n", &rezultati[i].vreme_izvrsavanje);
            fscanf(file, "Matrica:\n");
            for (int j = 0; j < MATRIX_SIZE; j++) {
                for (int k = 0; k < MATRIX_SIZE; k++) {
                    fscanf(file, "%d", &rezultati[i].matrix[j * MATRIX_SIZE + k]);
                }
                fscanf(file, "\n");
            }
            fscanf(file, "Zbir: %d\n", &rezultati[i].zbir);
            fclose(file);
        } else {
            perror("Neuspelo otvaranje fajla");
        }
    }

        // Sortiranje rezultata po vremenu izvršavanja
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (rezultati[i].vreme_izvrsavanje > rezultati[j].vreme_izvrsavanje) {
                Rezultat tmp = rezultati[i];
                rezultati[i] = rezultati[j];
                rezultati[j] = tmp;
            }
        }
    }
}

// Funkcija za upis rezultata u output.txt
void upisi_u_output(int n, Rezultat rezultati[]) {
    FILE *out = fopen("output.txt", "w");
    if (out) {
        for (int i = 0; i < n; i++) {
            fprintf(out, "Ukupno vreme izvrsavanja: %.6f\n", rezultati[i].vreme_izvrsavanje);
            fprintf(out, "Matrica:\n");
            for (int j = 0; j < MATRIX_SIZE; j++) {
                for (int k = 0; k < MATRIX_SIZE; k++) {
                    fprintf(out, "%d ", rezultati[i].matrix[j * MATRIX_SIZE + k]);
                }
                fprintf(out, "\n");
            }
            fprintf(out, "Zbir: %d\n\n", rezultati[i].zbir);
        }
        fclose(out);
    } else {
        perror("Neuspelo otvaranje output fajla");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Upotreba: %s n\n", argv[0]);
        return 1;
    }
    int n = atoi(argv[1]);
    

    printf("Broj novih procesa je: %d\n", n);
    pid_t pids[n];

    for (int i = 0; i < n; i++) {
        if (fork() == 0) {
            // Dete proces
            char ulazni_fajl[20];
            char tmp_fajl[20];
            sprintf(ulazni_fajl, "input%d.txt", i + 1);
            sprintf(tmp_fajl, "tmp%d.txt", i + 1);
            racunaj_upisi(i, ulazni_fajl, tmp_fajl);
        }
    }

    // Roditelj čeka da deca završe
    for (int i = 0; i < n; i++) {
        wait(NULL);
    }

    // Čitanje i sortiranje rezultata, i upis u output.txt
    Rezultat rezultati[TMP];
    citaj_sortiraj(n, rezultati);
    upisi_u_output(n, rezultati);

    return 0;
}

