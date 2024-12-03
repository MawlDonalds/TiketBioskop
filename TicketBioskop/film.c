// film.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bioskop.h"

void edit_film() {
    int choice;
    printf("\n=== Edit Film ===\n");
    printf("1. Tambah Film\n");
    printf("2. Hapus Film\n");
    printf("3. Kembali\n");
    printf("Pilih opsi: ");
    if (scanf("%d", &choice) != 1) {
        printf("Input tidak valid!\n");
        clear_input_buffer();
        return;
    }
    clear_input_buffer();

    if (choice == 1) {
        Film film;
        FILE *fp = fopen("films.dat", "ab");
        if (fp == NULL) {
            printf("Gagal membuka file.\n");
            return;
        }
        printf("ID Film: ");
        if (scanf("%d", &film.id) != 1) {
            printf("Input tidak valid!\n");
            fclose(fp);
            clear_input_buffer();
            return;
        }
        clear_input_buffer();
        printf("Judul Film: ");
        fgets(film.title, sizeof(film.title), stdin);
        film.title[strcspn(film.title, "\n")] = 0;
        fwrite(&film, sizeof(Film), 1, fp);
        fclose(fp);
        printf("Film berhasil ditambahkan.\n");
    }
    else if (choice == 2) {
        int id, found = 0;
        printf("ID Film yang akan dihapus: ");
        if (scanf("%d", &id) != 1) {
            printf("Input tidak valid!\n");
            clear_input_buffer();
            return;
        }
        clear_input_buffer();
        FILE *fp = fopen("films.dat", "rb");
        FILE *temp = fopen("temp_films.dat", "wb");
        if (fp == NULL || temp == NULL) {
            printf("Gagal membuka file.\n");
            if(fp) fclose(fp);
            if(temp) fclose(temp);
            return;
        }
        Film film;
        while (fread(&film, sizeof(Film), 1, fp)) {
            if (film.id != id) {
                fwrite(&film, sizeof(Film), 1, temp);
            } else {
                found = 1;
            }
        }
        fclose(fp);
        fclose(temp);
        remove("films.dat");
        rename("temp_films.dat", "films.dat");
        if (found) {
            printf("Film berhasil dihapus.\n");
        } else {
            printf("Film dengan ID tersebut tidak ditemukan.\n");
        }
    }
    else if (choice == 3) {
        return;
    }
    else {
        printf("Opsi tidak valid!\n");
    }
}

void choose_film(const char *username) {
    // Fungsi ini sekarang tidak digunakan karena pemesanan terintegrasi
    // Bisa dihapus atau dikomentari
}

