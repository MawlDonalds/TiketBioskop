// bioskop.h
#ifndef BIOSKOP_H
#define BIOSKOP_H

// ================== Definisi Struct ==================

typedef struct {
    int id;
    char title[100];
} Film;

typedef struct {
    int id;
    int film_id;
    char day[20];
    char time[10];
} Showtime;

typedef struct {
    int id;
    char name[50];
    int total_seats;
} Studio;

typedef struct {
    char type[10]; // "weekday" atau "weekend"
    float price;
} Harga;

typedef struct {
    char username[50];
    char password[50];
} User;

typedef struct {
    char username[50];
    int film_id;
    int showtime_id;
    char seat[10];
    float price;
} Booking;

// ================== Deklarasi Fungsi ==================

// Admin Functions
void admin_menu();
void edit_film();
void edit_showtime();
void edit_studio();
void edit_harga();
void view_booking_history();
void edit_seat();

// User (Client) Functions
void user_menu(const char *username);
void book_ticket(const char *username);

// Utility Functions
//void clear_input_buffer();

#endif

