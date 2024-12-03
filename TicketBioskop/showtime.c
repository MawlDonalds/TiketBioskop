// showtime.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bioskop.h"

void edit_showtime() {
    int choice;
    printf("\n=== Edit Jam Tayang ===\n");
    printf("1. Tambah Jam Tayang\n");
    printf("2. Hapus Jam Tayang\n");
    printf("3. Kembali\n");
    printf("Pilih opsi: ");
    if (scanf("%d", &choice) != 1) {
        printf("Input tidak valid!\n");
        clear_input_buffer();
        return;
    }
    clear_input_buffer();

    if (choice == 1) {
        Showtime show;
        FILE *fp = fopen("showtimes.dat", "ab");
        if (fp == NULL) {
            printf("Gagal membuka file.\n");
            return;
        }
        printf("ID Showtime: ");
        if (scanf("%d", &show.id) != 1) {
            printf("Input tidak valid!\n");
            fclose(fp);
            clear_input_buffer();
            return;
        }
        clear_input_buffer();
        printf("ID Film: ");
        if (scanf("%d", &show.film_id) != 1) {
            printf("Input tidak valid!\n");
            fclose(fp);
            clear_input_buffer();
            return;
        }
        clear_input_buffer();
        printf("Hari (e.g., Senin): ");
        fgets(show.day, sizeof(show.day), stdin);
        show.day[strcspn(show.day, "\n")] = 0;
        printf("Jam (e.g., 18:00): ");
        fgets(show.time, sizeof(show.time), stdin);
        show.time[strcspn(show.time, "\n")] = 0;
        fwrite(&show, sizeof(Showtime), 1, fp);
        fclose(fp);
        printf("Jam Tayang berhasil ditambahkan.\n");
    }
    else if (choice == 2) {
        int id, found = 0;
        printf("ID Showtime yang akan dihapus: ");
        if (scanf("%d", &id) != 1) {
            printf("Input tidak valid!\n");
            clear_input_buffer();
            return;
        }
        clear_input_buffer();
        FILE *fp = fopen("showtimes.dat", "rb");
        FILE *temp = fopen("temp_showtimes.dat", "wb");
        if (fp == NULL || temp == NULL) {
            printf("Gagal membuka file.\n");
            if(fp) fclose(fp);
            if(temp) fclose(temp);
            return;
        }
        Showtime show;
        while (fread(&show, sizeof(Showtime), 1, fp)) {
            if (show.id != id) {
                fwrite(&show, sizeof(Showtime), 1, temp);
            } else {
                found = 1;
            }
        }
        fclose(fp);
        fclose(temp);
        remove("showtimes.dat");
        rename("temp_showtimes.dat", "showtimes.dat");
        if (found) {
            printf("Jam Tayang berhasil dihapus.\n");
        } else {
            printf("Jam Tayang dengan ID tersebut tidak ditemukan.\n");
        }
    }
    else if (choice == 3) {
        return;
    }
    else {
        printf("Opsi tidak valid!\n");
    }
}

void choose_time(const char *username) {
    // Fungsi ini sekarang tidak digunakan karena pemesanan terintegrasi
    // Bisa dihapus atau dikomentari
}

