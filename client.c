// user.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bioskop.h"

void user_menu(const char *username) {
    int choice;
    while (1) {
        printf("\n=== Menu Client ===\n");
        printf("1. Pesan Tiket\n");
        printf("2. Logout\n");
        printf("Pilih opsi: ");
        if (scanf("%d", &choice) != 1) {
            printf("Input tidak valid!\n");
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();

        switch (choice) {
            case 1:
                book_ticket(username);
                break;
            case 2:
                printf("Logout Client.\n");
                return;
            default:
                printf("Opsi tidak valid!\n");
        }
    }
}

void book_ticket(const char *username) {
    int selected_day, selected_film_id, selected_showtime_id;
    char selected_seat[10];
    float ticket_price;

    // Step 1: Pilih Hari
    printf("\n=== Pilih Hari ===\n");
    printf("1. Senin\n");
    printf("2. Selasa\n");
    printf("3. Rabu\n");
    printf("4. Kamis\n");
    printf("5. Jumat\n");
    printf("6. Sabtu\n");
    printf("7. Minggu\n");
    printf("Pilih hari (1-7): ");
    if (scanf("%d", &selected_day) != 1 || selected_day < 1 || selected_day > 7) {
        printf("Input tidak valid!\n");
        clear_input_buffer();
        return;
    }
    clear_input_buffer();

    // Konversi nomor hari ke nama hari
    const char *hari[] = {"Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu", "Minggu"};
    const char *selected_day_name = hari[selected_day - 1];

    // Step 2: Pilih Film
    printf("\n=== Pilih Film ===\n");
    FILE *fp_film = fopen("films.dat", "rb");
    if (fp_film == NULL) {
        printf("Tidak ada film yang tersedia.\n");
        return;
    }
    Film film;
    while (fread(&film, sizeof(Film), 1, fp_film)) {
        printf("ID: %d | Judul: %s\n", film.id, film.title);
    }
    fclose(fp_film);

    printf("Masukkan ID Film yang ingin Anda tonton: ");
    if (scanf("%d", &selected_film_id) != 1) {
        printf("Input tidak valid!\n");
        clear_input_buffer();
        return;
    }
    clear_input_buffer();

    // Validasi ID Film
    fp_film = fopen("films.dat", "rb");
    int film_found = 0;
    char film_title[100];
    while (fread(&film, sizeof(Film), 1, fp_film)) {
        if (film.id == selected_film_id) {
            film_found = 1;
            strcpy(film_title, film.title);
            break;
        }
    }
    fclose(fp_film);
    if (!film_found) {
        printf("Film tidak ditemukan.\n");
        return;
    }

    // Step 3: Pilih Jam Tayang
    printf("\n=== Pilih Jam Tayang untuk '%s' pada hari %s ===\n", film_title, selected_day_name);
    FILE *fp_showtime = fopen("showtimes.dat", "rb");
    if (fp_showtime == NULL) {
        printf("Tidak ada jam tayang yang tersedia.\n");
        return;
    }
    Showtime show;
    int showtime_available = 0;
    while (fread(&show, sizeof(Showtime), 1, fp_showtime)) {
        if (show.film_id == selected_film_id && strcmp(show.day, selected_day_name) == 0) {
            printf("ID Showtime: %d | Jam: %s\n", show.id, show.time);
            showtime_available = 1;
        }
    }
    fclose(fp_showtime);

    if (!showtime_available) {
        printf("Tidak ada jam tayang untuk film tersebut pada hari %s.\n", selected_day_name);
        return;
    }

    printf("Masukkan ID Showtime yang Anda inginkan: ");
    if (scanf("%d", &selected_showtime_id) != 1) {
        printf("Input tidak valid!\n");
        clear_input_buffer();
        return;
    }
    clear_input_buffer();

    // Validasi ID Showtime
    fp_showtime = fopen("showtimes.dat", "rb");
    if (fp_showtime == NULL) {
        printf("Tidak dapat membuka file showtimes.\n");
        return;
    }
    int showtime_found = 0;
    char show_time[10];
    while (fread(&show, sizeof(Showtime), 1, fp_showtime)) {
        if (show.id == selected_showtime_id && show.film_id == selected_film_id && strcmp(show.day, selected_day_name) == 0) {
            showtime_found = 1;
            strcpy(show_time, show.time);
            break;
        }
    }
    fclose(fp_showtime);
    if (!showtime_found) {
        printf("ID Showtime tidak valid.\n");
        return;
    }

    // Step 4: Pilih Tempat Duduk
    printf("\n=== Pilih Tempat Duduk ===\n");
    printf("Kursi tersedia: A1, A2, A3, A4, A5\n"); // Contoh kursi, bisa dikembangkan lebih lanjut
    printf("Masukkan nomor kursi yang diinginkan: ");
    fgets(selected_seat, sizeof(selected_seat), stdin);
    selected_seat[strcspn(selected_seat, "\n")] = 0;

    // Validasi kursi (untuk kesederhanaan, kita anggap kursi selalu tersedia)
    // Pada implementasi sebenarnya, Anda perlu memeriksa ketersediaan kursi di database

    // Step 5: Hitung Harga Tiket
    FILE *fp_harga = fopen("harga.dat", "rb");
    if (fp_harga == NULL) {
        printf("Harga tiket belum diatur.\n");
        return;
    }
    Harga harga_list[2];
    fread(&harga_list, sizeof(Harga), 2, fp_harga);
    fclose(fp_harga);

    if (selected_day >= 1 && selected_day <= 5) { // Weekday
        ticket_price = harga_list[0].price;
    } else { // Weekend
        ticket_price = harga_list[1].price;
    }

    printf("Harga tiket: %.2f\n", ticket_price);

    // Step 6: Konfirmasi Pembayaran
    printf("\n=== Pembayaran ===\n");
    printf("Total yang harus dibayar: %.2f\n", ticket_price);
    printf("Apakah Anda ingin melanjutkan pembayaran? (y/n): ");
    char confirm;
    scanf(" %c", &confirm);
    clear_input_buffer();
    if (confirm != 'y' && confirm != 'Y') {
        printf("Pembayaran dibatalkan.\n");
        return;
    }

    // Simpan booking ke file bookings.dat
    Booking booking;
    strcpy(booking.username, username);
    booking.film_id = selected_film_id;
    booking.showtime_id = selected_showtime_id;
    strcpy(booking.seat, selected_seat);
    booking.price = ticket_price;

    FILE *fp_booking = fopen("bookings.dat", "ab");
    if (fp_booking == NULL) {
        printf("Gagal menyimpan data pemesanan.\n");
        return;
    }
    fwrite(&booking, sizeof(Booking), 1, fp_booking);
    fclose(fp_booking);

    // Step 7: Cetak Tiket
    printf("\n=== Tiket Anda ===\n");
    printf("Username   : %s\n", booking.username);
    printf("Film       : %s\n", film_title);
    printf("Hari       : %s\n", selected_day_name);
    printf("Jam        : %s\n", show_time);
    printf("Kursi      : %s\n", booking.seat);
    printf("Harga      : %.2f\n", booking.price);
    printf("Terima kasih telah memesan tiket!\n");
}

