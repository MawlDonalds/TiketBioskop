// booking.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bioskop.h"

void view_booking_history() {
    FILE *fp = fopen("bookings.dat", "rb");
    if (fp == NULL) {
        printf("Belum ada pemesanan.\n");
        return;
    }
    Booking booking;
    printf("\n=== Riwayat Pemesanan ===\n");
    while (fread(&booking, sizeof(Booking), 1, fp)) {
        printf("User: %s | Film ID: %d | Showtime ID: %d | Kursi: %s | Harga: %.2f\n",
               booking.username, booking.film_id, booking.showtime_id, booking.seat, booking.price);
    }
    fclose(fp);
}

// Fungsi-fungsi berikut ini adalah placeholder karena pemesanan terintegrasi
void choose_day(const char *username) {
    printf("Fitur ini akan diimplementasikan.\n");
}

void choose_seat(const char *username) {
    printf("Fitur ini akan diimplementasikan.\n");
}

void print_ticket(const char *username) {
    printf("Fitur ini akan diimplementasikan.\n");
}

void process_payment(const char *username) {
    printf("Fitur ini akan diimplementasikan.\n");
}

