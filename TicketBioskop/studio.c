// studio.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bioskop.h"

void edit_studio() {
    int choice;
    printf("\n=== Edit Studio ===\n");
    printf("1. Tambah Studio\n");
    printf("2. Hapus Studio\n");
    printf("3. Kembali\n");
    printf("Pilih opsi: ");
    if (scanf("%d", &choice) != 1) {
        printf("Input tidak valid!\n");
        clear_input_buffer();
        return;
    }
    clear_input_buffer();

    if (choice == 1) {
        Studio studio;
        FILE *fp = fopen("studios.dat", "ab");
        if (fp == NULL) {
            printf("Gagal membuka file.\n");
            return;
        }
        printf("ID Studio: ");
        if (scanf("%d", &studio.id) != 1) {
            printf("Input tidak valid!\n");
            fclose(fp);
            clear_input_buffer();
            return;
        }
        clear_input_buffer();
        printf("Nama Studio: ");
        fgets(studio.name, sizeof(studio.name), stdin);
        studio.name[strcspn(studio.name, "\n")] = 0;
        printf("Total Kursi: ");
        if (scanf("%d", &studio.total_seats) != 1) {
            printf("Input tidak valid!\n");
            fclose(fp);
            clear_input_buffer();
            return;
        }
        clear_input_buffer();
        fwrite(&studio, sizeof(Studio), 1, fp);
        fclose(fp);
        printf("Studio berhasil ditambahkan.\n");
    }
    else if (choice == 2) {
        int id, found = 0;
        printf("ID Studio yang akan dihapus: ");
        if (scanf("%d", &id) != 1) {
            printf("Input tidak valid!\n");
            clear_input_buffer();
            return;
        }
        clear_input_buffer();
        FILE *fp = fopen("studios.dat", "rb");
        FILE *temp = fopen("temp_studios.dat", "wb");
        if (fp == NULL || temp == NULL) {
            printf("Gagal membuka file.\n");
            if(fp) fclose(fp);
            if(temp) fclose(temp);
            return;
        }
        Studio studio;
        while (fread(&studio, sizeof(Studio), 1, fp)) {
            if (studio.id != id) {
                fwrite(&studio, sizeof(Studio), 1, temp);
            } else {
                found = 1;
            }
        }
        fclose(fp);
        fclose(temp);
        remove("studios.dat");
        rename("temp_studios.dat", "studios.dat");
        if (found) {
            printf("Studio berhasil dihapus.\n");
        } else {
            printf("Studio dengan ID tersebut tidak ditemukan.\n");
        }
    }
    else if (choice == 3) {
        return;
    }
    else {
        printf("Opsi tidak valid!\n");
    }
}

