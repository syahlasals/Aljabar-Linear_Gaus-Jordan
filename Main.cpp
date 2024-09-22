#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>

#define SIZE 20

using namespace std;

void cetakMatriks(double matriks[][SIZE], int baris, int kolom) {
    for (int i = 0; i < baris; i++) {
        for (int j = 0; j < kolom; j++) {
            if (fabs(matriks[i][j]) < 1e-9) {
                matriks[i][j] = 0;
            }
            printf("%.2f\t", matriks[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void gaussJordan(double matriks[][SIZE], int baris, int kolom) {
    int lead = 0;
    for (int r = 0; r < baris; r++) {
        if (lead >= kolom) break;
        int i = r;
        while (matriks[i][lead] == 0) {
            i++;
            if (i == baris) {
                i = r;
                lead++;
                if (lead == kolom) return;
            }
        }

        // Tukar baris
        if (i != r) {
            for (int j = 0; j < kolom; j++) {
                double temp = matriks[i][j];
                matriks[i][j] = matriks[r][j];
                matriks[r][j] = temp;
            }
            printf("Tukar baris ke-%d dengan baris ke-%d:\n", i + 1, r + 1);
            cetakMatriks(matriks, baris, kolom);
        }

        // Pembagian
        double div = matriks[r][lead];
        for (int j = 0; j < kolom; j++) {
            matriks[r][j] /= div;
        }
        printf("Membagi baris ke-%d dengan %.2f:\n", r + 1, div);
        cetakMatriks(matriks, baris, kolom);

        // Operasi lain
        for (int i = 0; i < baris; i++) {
            if (i != r) {
                double sub = matriks[i][lead];
                for (int j = 0; j < kolom; j++) {
                    matriks[i][j] -= sub * matriks[r][j];
                }
                printf("Mengurangi baris ke-%d dengan %.2f kali baris ke-%d:\n", i + 1, sub, r + 1);
                cetakMatriks(matriks, baris, kolom);
            }
        }
        
        lead++;
    }
}

void eliminasiMatriks() {
    int baris, kolom;

    printf("Jumlah baris: ");
    scanf("%d", &baris);
    printf("Jumlah kolom: ");
    scanf("%d", &kolom);

    double matriks[SIZE][SIZE];

    printf("Masukkan elemen matriks:\n");
    for (int i = 0; i < baris; i++) {
        for (int j = 0; j < kolom; j++) {
            printf("M[%d][%d] = ", i + 1, j + 1);
            scanf("%lf", &matriks[i][j]);
        }
    }

    printf("\nMatriks:\n");
    cetakMatriks(matriks, baris, kolom);

    gaussJordan(matriks, baris, kolom);

    printf("HASIL MATRIKS ESELON BARIS TEREDUKSI: \n");
    cetakMatriks(matriks, baris, kolom);
}

// Fungsi-fungsi untuk operasi matriks invers
void inputMatrix(float M[SIZE][SIZE], int &n) {
    printf("Ordo matriks: ");
    scanf("%d", &n);

    printf("Masukkan elemen matriks: \n");
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            printf("M[%d][%d] = ", i, j);
            scanf("%f", &M[i][j]);
        }
    }
}

void augmentIdentityMatrix(float M[SIZE][SIZE], int n) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            M[i][j + n] = (i == j) ? 1 : 0;
        }
    }
    printf("\nMatriks augmented (Matriks dan Identitas):\n");
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            printf("%.2f\t", M[i][j]);
        }
        printf("|\t");
        for (int j = n + 1; j <= 2 * n; j++) {
            printf("%.2f\t", M[i][j]);
        }
        printf("\n");
    }
}

void printMatrix(float M[SIZE][SIZE], int n) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            printf("%.2f\t", M[i][j]);
        }
        printf("|\t");
        for (int j = n + 1; j <= 2 * n; j++) {
            printf("%.2f\t", M[i][j]);
        }
        printf("\n");
    }
}

bool gaussJordanElimination(float M[SIZE][SIZE], int n) {
    float ratio;
    for (int i = 1; i <= n; i++) {
        if (M[i][i] == 0.0) {
            printf("Kesalahan Matematis! (Pembagi nol)\n");
            return false;
        }

        for (int j = 1; j <= n; j++) {
            if (i != j) {
                ratio = M[j][i] / M[i][i];
                printf("\nMengurangi baris ke-%d dengan %.2f kali baris ke-%d:\n", j, ratio, i);
                
                for (int k = 1; k <= 2 * n; k++) {
                    M[j][k] -= ratio * M[i][k];
                }

                printMatrix(M, n);
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        float divisor = M[i][i];
        printf("\nMembagi baris ke-%d dengan %.2f:\n", i, divisor);

        for (int j = n + 1; j <= 2 * n; j++) {
            M[i][j] /= divisor;
        }

        printMatrix(M, n);
    }
    return true;
}

void cetakMatriksInvers(float M[SIZE][SIZE], int n) {
    printf("\nMatriks Invers adalah:\n");
    for (int i = 1; i <= n; i++) {
        for (int j = n + 1; j <= 2 * n; j++) {
            printf("%.2f\t", M[i][j]);  // Menampilkan hanya matriks invers
        }
        printf("\n");
    }
}

void matriksInvers() {
    float M[SIZE][SIZE];
    int n;

    inputMatrix(M, n);
    augmentIdentityMatrix(M, n);

    if (gaussJordanElimination(M, n)) {
        cetakMatriksInvers(M, n);
    }
}

int main() {
    int pilihan;
    
    do {
        cout << "\nMenu Operasi Matriks:" << endl;
        cout << "1. Eliminasi Matriks" << endl;
        cout << "2. Matriks Invers" << endl;
        cout << "3. Keluar" << endl;
        cout << "Pilihan Anda: ";
        cin >> pilihan;
        
        switch(pilihan) {
            case 1:
                eliminasiMatriks();
                break;
            case 2:
                matriksInvers();
                break;
            case 3:
                cout << "Keluar Program..." << endl;
                break;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    } while (pilihan != 3);
    
    return 0;
}