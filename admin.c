// admin.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bioskop.h"

void admin_menu() {
    int choice;
    while (1) {
        printf("\n=== Menu Admin ===\n");
        printf("1. Edit Film\n");
        printf("2. Edit Jam Tayang\n");
        printf("3. Edit Studio\n");
        printf("4. Edit Harga Tiket\n");
        printf("5. Lihat Riwayat Pemesanan\n");
        printf("6. Edit Tempat Duduk\n");
        printf("7. Logout\n");
        printf("Pilih opsi: ");
        if (scanf("%d", &choice) != 1) {
            printf("Input tidak valid!\n");
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();

        switch (choice) {
            case 1:
                edit_film();
                break;
            case 2:
                edit_showtime();
                break;
            case 3:
                edit_studio();
                break;
            case 4:
                edit_harga();
                break;
            case 5:
                view_booking_history();
                break;
            case 6:
                edit_seat();
                break;
            case 7:
                printf("Logout Admin.\n");
                return;
            default:
                printf("Opsi tidak valid!\n");
        }
    }
}

// Edit Tempat Duduk (Placeholder)
void edit_seat() {
    // Implementasi fitur edit tempat duduk
    printf("Fitur ini akan diimplementasikan.\n");
}

