#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_USERNAME_LENGTH 11
#define MAX_PASSWORD_LENGTH 20

#define MAX_NAMA_LENGTH 100
#define MAX_PRODI_LENGTH 50
#define MAX_KEPERLUANPEMINJAMAN_LENGTH 100
#define MAX_TANGGALPEMINJAMAN_LENGTH 12 
#define MAX_WAKTUMULAI_LENGTH 12
#define MAX_WAKTUSELESAI_LENGTH 12
#define MAX_JUMLAHPEMINJAM_LENGTH 10

//Username : admin
//Password : admin
struct Login {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
};

typedef struct
{
    char Nama[MAX_NAMA_LENGTH]; 
    char Prodi[MAX_PRODI_LENGTH];
    char KeperluanPeminjaman[MAX_KEPERLUANPEMINJAMAN_LENGTH]; 
    char TanggalPeminjaman[MAX_TANGGALPEMINJAMAN_LENGTH];
    char WaktuMulai[MAX_WAKTUMULAI_LENGTH];
    char WaktuSelesai[MAX_WAKTUSELESAI_LENGTH]; 
    int Nim; 
}PeminjamanAula;


int Logins(char *username, char *password) {
    FILE *login = fopen("login/admin.txt", "r");
    if (login == NULL) {
        printf("Error!\n");
        return 0;
    }
    
    struct Login logins;
    while (fscanf(login, "%s %s", logins.username, logins.password) != EOF) {
        if (strcmp(username, logins.username) == 0 && strcmp(password, logins.password) == 0) {
            fclose(login);
            return 1;
        }
    }

    fclose(login);
    return 0;
}

void CekLogin(){
    bool login = true;
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    
    login:
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    while (login)
    {
        if (Logins(username, password)) {
            printf("\nSelamat Datang!\n");
            break;
        } else {
            printf("Username atau password tidak sesuai!\n\n");
            goto login;
        }
    }
    
}

void TambahData(PeminjamanAula data[],int total){         
    for(int a = 0; a < total; a++){
        fflush(stdin);
        printf("Nama Lengkap Peminjam ke-%d : ", a + 1);
        scanf("%[^\n]s", data[a].Nama);
        fflush(stdin);
        printf("Prodi : ");
        scanf("%[^\n]s", data[a].Prodi);
        fflush(stdin);
        printf("Keperluan Peminjaman : ");
        scanf("%[^\n]s", data[a].KeperluanPeminjaman);
        fflush(stdin);
        printf("Tanggal Peminjaman (dd/mm/yyyy) : ");
        scanf("%[^\n]s", data[a].TanggalPeminjaman);
        fflush(stdin);
        printf("Dari Pukul (hh.mm) : ");
        scanf("%[^\n]s", data[a].WaktuMulai);
        fflush(stdin);
        printf("Hingga Pukul (hh.mm) : ");
        scanf("%[^\n]s", data[a].WaktuSelesai);
        fflush(stdin);
        printf("Nomor Induk Mahasiswa : ");
        scanf("%d", &data[a].Nim);
        printf("\n");
    }
}

void LihatData(PeminjamanAula* data, int* total) {
    FILE* Aula = fopen("database-aula.txt", "r");
    if (Aula == NULL) {
        perror("Gagal membuka File: ");
        return;
    }
    *total = 0;
    
    while
    (fscanf(Aula, "%[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %d", 
    data[*total].Nama, data[*total].Prodi, data[*total].KeperluanPeminjaman, data[*total].TanggalPeminjaman, data[*total].WaktuMulai, data[*total].WaktuSelesai,  &data[*total].Nim) == 7) {
      (*total)++;  
    }
    fclose(Aula);
}

void TampilkanData(PeminjamanAula data[], int c){
    for(int a = 0; a < c; a++){
        printf("Nomor Peminjaman : %d\n", a+1);
        printf("Nama Lengkap : %s\n", data[a].Nama);
        printf("Prodi : %s\n", data[a].Prodi);
        printf("Keperluan Peminjaman : %s\n", data[a].KeperluanPeminjaman);
        printf("Tanggal Peminjaman (dd/mm/yyyy) : %s\n", data[a].TanggalPeminjaman);
        printf("Dari Pukul (hh.mm) : %s\n", data[a].WaktuMulai);
        printf("Hingga Pukul (hh.mm) : %s\n", data[a].WaktuSelesai);
        printf("Nim : %d\n", data[a].Nim);
        printf("\n");
    }
}

void SimpanData(PeminjamanAula* data, int total){
    FILE* Aula = fopen("database-aula.txt", "a");
    if(Aula == NULL){
        perror("Gagal membuka File: ");
    }

    for(int a = 0; a < total; a++){
        fprintf(Aula, "%s, %s, %s, %s, %s, %s, %d\n",
        data[a].Nama, data[a].Prodi, data[a].KeperluanPeminjaman, data[a].TanggalPeminjaman, data[a].WaktuMulai, data[a].WaktuSelesai, data[a].Nim);
    }
    fclose(Aula);
    printf("\nData Peminjaman tersimpan!");
}

void Edit(PeminjamanAula data[], int c){
    int row;
    fflush(stdin);
    printf("Masukkan Nomor Peminjaman Aula : ");
    scanf("%d", &row);
    fflush(stdin);

    printf("Ubah Nama : ");
    scanf("%[^\n]s", data[row - 1].Nama);
    fflush(stdin);
    printf("Ubah Prodi : ");
    scanf("%[^\n]s", data[row - 1].Prodi);
    fflush(stdin);
    printf("Ubah Keperluan Peminjaman : ");
    scanf("%[^\n]s", data[row - 1].KeperluanPeminjaman);
    fflush(stdin);
    printf("Ubah Tanggal Peminjaman (dd/mm/yyyy) : ");
    scanf("%[^\n]s", data[row - 1].TanggalPeminjaman);
    fflush(stdin);
    printf("Ubah Dari Pukul (hh.mm) : ");
    scanf("%[^\n]s", data[row - 1].WaktuMulai);
    fflush(stdin);
    printf("Ubah Hingga Pukul (hh.mm) : ");
    scanf("%[^\n]s", data[row - 1].WaktuSelesai);
    fflush(stdin);
    printf("Ubah Nim : ");
    scanf("%d", &data[row - 1].Nim);
    fflush(stdin);

    printf("\nData Peminjaman tersimpan!");
}

void CariData(PeminjamanAula data[], int total){
    fflush(stdin);
    int CariNim, ketemu = 0;
    printf("Cari Berdasarkan Nomor Induk Mahasiswa : \n");
    scanf("%d", &CariNim);

    for(int a = 0; a < total; a++){
        if(CariNim == data[a].Nim){
            printf("Data ditemukan pada Peminjaman Aula ke : %d\n", a+1);
            printf("Nama : %s\n", data[a].Nama);
            printf("Prodi : %s\n", data[a].Prodi);
            printf("Keperluan Peminjaman : %s\n", data[a].KeperluanPeminjaman);
            printf("Tanggal Peminjaman (dd/mm/yyyy) : %s\n", data[a].TanggalPeminjaman);
            printf("Dari Pukul (hh.mm) : %s\n", data[a].WaktuMulai);
            printf("Hingga Pukul (hh.mm) : %s\n", data[a].WaktuSelesai);
            printf("Nim : %d\n", data[a].Nim);
            ketemu = 1;
        }
    }
    if(!ketemu){
        printf("Data yang anda cari tidak ada, mohon cek kembali Nomor Induk Mahasiswa!");
    }
}

void InsertionSort(PeminjamanAula data[], int total) //Insertion sort
{
    for (int a = 1; a < total; a++)
    {
        if (data[a].Nim < data[a - 1].Nim)
        {
            int b = a;
            while (data[b].Nim < data[b - 1].Nim && b > 0)
            {
                PeminjamanAula tmp = data[b];
                data[b] = data[b - 1];
                data[b - 1] = tmp;
                b--;
            }
        }
    }
}

void UrutkanData(PeminjamanAula data[], int total)
{
    for(int a = 0; a < total; a++){
        printf("Data ditemukan pada Peminjaman Aula ke : %d\n", a+1);
        printf("Nama : %s\n", data[a].Nama);
        printf("Prodi : %s\n", data[a].Prodi);
        printf("Keperluan Peminjaman : %s\n", data[a].KeperluanPeminjaman);
        printf("Tanggal Peminjaman (dd/mm/yyyy) : %s\n", data[a].TanggalPeminjaman);
        printf("Dari Pukul (hh.mm) : %s\n", data[a].WaktuMulai);
        printf("Hingga Pukul (hh.mm) : %s\n", data[a].WaktuSelesai);
        printf("Nim : %d\n", data[a].Nim);
        printf("\n");
    }
}

int menu() {
    PeminjamanAula pinjam[MAX_JUMLAHPEMINJAM_LENGTH];
    FILE* Aula;
    int menu, jumlah, jumlahpeminjam;

    do{
        printf("\n\t|---------------------------------------|\n");
        printf("\t|---------- ITTELKOM SURABAYA ----------|\n");
        printf("\t|----------- Peminjaman Aula -----------|\n");
        printf("\t|-------------- Mahasiswa --------------|\n");
        printf("\t|---------------------------------------|\n");
        printf("\t|- Cek Jadwal dahulu sebelum meminjam! -|\n");
        printf("\t|---------------------------------------|\n");
        printf("\t|---------------------------------------|\n");
        printf("\t| 1. Lihat Daftar Peminjaman \t\t|\n");
        printf("\t| 2. Pinjam Ruang Aula \t\t\t|\n");
        printf("\t| 3. Edit Data Peminjaman \t\t|\n");
        printf("\t| 4. Cari Data Peminjaman \t\t|\n");
        printf("\t| 5. Urutkan Data Peminjaman \t\t|\n");
        printf("\t| 6. Keluar \t\t\t\t|\n");
        printf("\t|---------------------------------------|\n\n");
        scanf("%d", &menu);
                system("cls");

            switch (menu){
            case 1:
                system("cls");
                LihatData(pinjam, &jumlah);
                TampilkanData(pinjam, jumlah);
                break;
            case 2:
                system("cls");
                printf("\nMau pinjam Ruangan berapa kali : ");
                scanf("%d", &jumlah);
                fflush(stdin);
                TambahData(pinjam, jumlah);
                SimpanData(pinjam, jumlah);
            break;
            case 3:
                system("cls");
                Aula = fopen("database-aula.txt", "w");
                Edit(pinjam, jumlah);
                    if(Aula == NULL){
                        perror("Data tidak ada!");
                    }
                    for(int a = 0; a < jumlah; a++){
                        fprintf(Aula, "%s, %s, %s, %s, %s, %s, %d",
                        pinjam[a].Nama, pinjam[a].Prodi, pinjam[a].KeperluanPeminjaman, pinjam[a].TanggalPeminjaman, pinjam[a].WaktuMulai, pinjam[a].WaktuSelesai, pinjam[a].Nim);
                    }
                    fclose(Aula);
                break;
            case 4:
                system("cls");
                CariData(pinjam, jumlah);
               break;
            case 5:
                system("cls");
                InsertionSort(pinjam, jumlah);
                UrutkanData(pinjam, jumlah);
                break;
            case 6:
                printf("\n|---------------------------------------|\n");
                printf("|----------- Terimakasih :D ------------|\n");
                printf("|------ Tetaplah Bertanggungjawab ------|\n");
                printf("|---------- Dalam Segala Hal -----------|\n");
                printf("|---------------------------------------|\n");
            break;
            default:
                printf("Pilih salah satu Menu ini!\n");
                break;
            }
        }while (menu != 6);
    
    return 0;
}

int main(){
    CekLogin();
    menu();
}