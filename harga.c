// harga.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bioskop.h"

void edit_harga() {
    int choice;
    printf("\n=== Edit Harga Tiket ===\n");
    printf("1. Ubah Harga Weekday\n");
    printf("2. Ubah Harga Weekend\n");
    printf("3. Kembali\n");
    printf("Pilih opsi: ");
    if (scanf("%d", &choice) != 1) {
        printf("Input tidak valid!\n");
        clear_input_buffer();
        return;
    }
    clear_input_buffer();

    if (choice == 1 || choice == 2) {
        Harga harga;
        FILE *fp = fopen("harga.dat", "rb+");
        if (fp == NULL) {
            // Jika file belum ada, buat baru
            fp = fopen("harga.dat", "wb");
            if (fp == NULL) {
                printf("Gagal membuka file.\n");
                return;
            }
            // Inisialisasi harga
            strcpy(harga.type, "weekday");
            harga.price = 10000.0;
            fwrite(&harga, sizeof(Harga), 1, fp);
            strcpy(harga.type, "weekend");
            harga.price = 15000.0;
            fwrite(&harga, sizeof(Harga), 1, fp);
            fclose(fp);
            printf("Harga awal telah diinisialisasi.\n");
            return;
        }

        // Baca harga yang ada
        Harga harga_list[2];
        fread(&harga_list, sizeof(Harga), 2, fp);

        if (choice == 1) {
            printf("Harga Weekday saat ini: %.2f\n", harga_list[0].price);
            printf("Masukkan harga baru untuk Weekday: ");
            if (scanf("%f", &harga_list[0].price) != 1) {
                printf("Input tidak valid!\n");
                clear_input_buffer();
                fclose(fp);
                return;
            }
            clear_input_buffer();
        }
        else if (choice == 2) {
            printf("Harga Weekend saat ini: %.2f\n", harga_list[1].price);
            printf("Masukkan harga baru untuk Weekend: ");
            if (scanf("%f", &harga_list[1].price) != 1) {
                printf("Input tidak valid!\n");
                clear_input_buffer();
                fclose(fp);
                return;
            }
            clear_input_buffer();
        }

        // Simpan kembali harga
        fseek(fp, 0, SEEK_SET);
        fwrite(&harga_list, sizeof(Harga), 2, fp);
        fclose(fp);
        printf("Harga berhasil diperbarui.\n");
    }
    else if (choice == 3) {
        return;
    }
    else {
        printf("Opsi tidak valid!\n");
    }
}

