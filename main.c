// main.c
#include <stdio.h>
#include <string.h>
#include "bioskop.h"

#define ADMIN_USERNAME "admin"
#define ADMIN_PASSWORD "admin123"

#define USER_FILE "users.dat"

int main() {
    int choice;
    char username[50], password[50];

    while (1) {
        printf("\n=== Sistem Pemesanan Tiket Bioskop ===\n");
        printf("1. Admin\n");
        printf("2. Client\n");
        printf("3. Exit\n");
        printf("Pilih opsi: ");
        if (scanf("%d", &choice) != 1) {
            printf("Input tidak valid!\n");
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();

        if (choice == 1) { // Admin
            int admin_choice;
            printf("\n=== Admin ===\n");
            printf("1. Login\n");
            printf("2. Kembali\n");
            printf("Pilih opsi: ");
            if (scanf("%d", &admin_choice) != 1) {
                printf("Input tidak valid!\n");
                clear_input_buffer();
                continue;
            }
            clear_input_buffer();

            if (admin_choice == 1) {
                printf("Username Admin: ");
                fgets(username, sizeof(username), stdin);
                username[strcspn(username, "\n")] = 0; // Menghapus newline

                printf("Password Admin: ");
                fgets(password, sizeof(password), stdin);
                password[strcspn(password, "\n")] = 0;

                if (strcmp(username, ADMIN_USERNAME) == 0 && strcmp(password, ADMIN_PASSWORD) == 0) {
                    printf("Login Admin Berhasil!\n");
                    admin_menu();
                } else {
                    printf("Username atau Password Admin salah!\n");
                }
            }
            else if (admin_choice == 2) {
                // Kembali ke menu utama
                continue;
            }
            else {
                printf("Opsi tidak valid!\n");
            }
        }
        else if (choice == 2) { // Client
            int client_choice;
            printf("\n=== Client ===\n");
            printf("1. Login\n");
            printf("2. Register\n");
            printf("3. Kembali\n");
            printf("Pilih opsi: ");
            if (scanf("%d", &client_choice) != 1) {
                printf("Input tidak valid!\n");
                clear_input_buffer();
                continue;
            }
//            clear_input_buffer();

            if (client_choice == 1) { // Login Client
                char user_username[50], user_password[50];
                printf("Username Client: ");
                fgets(user_username, sizeof(user_username), stdin);
                user_username[strcspn(user_username, "\n")] = 0;

                printf("Password Client: ");
                fgets(user_password, sizeof(user_password), stdin);
                user_password[strcspn(user_password, "\n")] = 0;

                // Cek user di file users.dat
                FILE *fp = fopen(USER_FILE, "rb");
                if (fp == NULL) {
                    printf("Belum ada user yang terdaftar!\n");
                } else {
                    int found = 0;
                    User user;
                    while (fread(&user, sizeof(User), 1, fp)) {
                        if (strcmp(user_username, user.username) == 0 && strcmp(user_password, user.password) == 0) {
                            found = 1;
                            break;
                        }
                    }
                    fclose(fp);
                    if (found) {
                        printf("Login Client Berhasil!\n");
                        user_menu(user_username);
                    } else {
                        printf("Username atau Password salah!\n");
                    }
                }
            }
            else if (client_choice == 2) { // Register Client
                char new_username[50], new_password[50];
                printf("=== Registrasi Client ===\n");
                printf("Masukkan Username: ");
                fgets(new_username, sizeof(new_username), stdin);
                new_username[strcspn(new_username, "\n")] = 0;

                printf("Masukkan Password: ");
                fgets(new_password, sizeof(new_password), stdin);
                new_password[strcspn(new_password, "\n")] = 0;

                // Cek apakah username sudah ada
                FILE *fp = fopen(USER_FILE, "rb");
                int exists = 0;
                if (fp != NULL) {
                    User user;
                    while (fread(&user, sizeof(User), 1, fp)) {
                        if (strcmp(new_username, user.username) == 0) {
                            exists = 1;
                            break;
                        }
                    }
                    fclose(fp);
                }

                if (exists) {
                    printf("Username sudah digunakan. Silakan gunakan username lain.\n");
                }
                else {
                    // Simpan user baru ke file
                    fp = fopen(USER_FILE, "ab");
                    if (fp == NULL) {
                        printf("Gagal membuka file untuk menyimpan user.\n");
                    } else {
                        User new_user;
                        strcpy(new_user.username, new_username);
                        strcpy(new_user.password, new_password);
                        fwrite(&new_user, sizeof(User), 1, fp);
                        fclose(fp);
                        printf("Registrasi berhasil! Silakan login.\n");
                    }
                }
            }
            else if (client_choice == 3) {
                // Kembali ke menu utama
                continue;
            }
            else {
                printf("Opsi tidak valid!\n");
            }
        }
        else if (choice == 3) { // Exit
            printf("Keluar dari program.\n");
            break;
        }
        else {
            printf("Opsi tidak valid!\n");
        }
    }

    return 0;
}

