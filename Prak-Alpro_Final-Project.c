#include <stdio.h>      // test
#include <stdlib.h>
#include <string.h>

struct data{
    char absen[5], nama[50], gender[5], telepon[15];
};

int cekData(){
    FILE *baca = fopen("Prak-Alpro_Final-Project_Data.txt", "r");
    char cek[999];
    int hitung=0;
    while(fgets(cek, sizeof(cek), baca)){
        hitung++;
    }
	fclose(baca);
    return hitung;
}

void addData(char *absen, char *nama, char *gender, char *telepon){
    FILE *add = fopen("Prak-Alpro_Final-Project_Data.txt", "a");
    fprintf(add, "\nAbsen        : %s\n", absen);
    fprintf(add, "Nama         : %s\n", nama);
    fprintf(add, "Gender (L/P) : %s\n", gender);
	fprintf(add, "Telepon      : %s", telepon);
    fclose(add);
	printf("\n(Data berhasil ditambahkan)\n");
}

void readData(){
    FILE *read = fopen("Prak-Alpro_Final-Project_Data.txt" , "r");
	char str, rts;
    int tanda=0, jml=0;
    do{
        str = fgetc(read);
        tanda++;
    }while(str != EOF);
    fclose(read);
    if(tanda == 1){
        printf("\n(Data Masih Kosong)\n");
    }
    else{
        FILE *read = fopen("Prak-Alpro_Final-Project_Data.txt" , "r");
        printf("\n==========================");
        jml = -1;
        do{
            if(jml==4){
                printf("\n==========================\n");
                jml = 0;
            }
            rts = fgetc(read);
            printf("%c", rts);
            if(rts=='\n')
                jml++;
        }while(rts != EOF);
	    fclose(read);
        printf("\n");
    }
}

void removeData(char *nama, char *gender, char *telepon){
    FILE *read = fopen("Prak-Alpro_Final-Project_Data.txt" , "r");
	char find;
    int mark=0;
    do{
        find = fgetc(read);
        if(find=='\n')
            mark++;
    }while(find != EOF);
    fclose(read);
    if(mark == 0){
        printf("\n(Data Masih Kosong)\n");
    }
    else{
        FILE *real1 = fopen("Prak-Alpro_Final-Project_Data.txt" , "r");
        FILE *temp1 = fopen("Prak-Alpro_Final-Project_Data_Temp.txt" , "w+");
        char copy[999], awal[] = "Absen        : ", akhir[999], hapus[999], salin[999];
        int count=0, hitung=0;
        printf("\nMasukkan absen partisipan yang ingin dihapus : ");
        gets(akhir);
        strcat(awal, akhir);
        strcpy(hapus, awal);
        while(fgets(copy, sizeof(copy), real1)){
            if(strstr(copy, hapus) != 0){
                count = 4;
                hitung++;
            }
            if(count == 0)
                fprintf(temp1, "%s", copy);
            else
                count--;
        }
        fclose(temp1);
        fclose(real1);
        remove("Prak-Alpro_Final-Project_Data.txt");
        if(mark!=4 || mark==4 && hitung==0){
            FILE *temp2 = fopen("Prak-Alpro_Final-Project_Data_Temp.txt" , "r");
            FILE *real2 = fopen("Prak-Alpro_Final-Project_Data.txt" , "w+");
            while(fgets(salin, sizeof(salin), temp2)){
                    fprintf(real2, "%s", salin);
            }
            fclose(real2);
            fclose(temp2);
            remove("Prak-Alpro_Final-Project_Data_Temp.txt");
        }
        if(hitung!=0)
            printf("\n(Data berhasil dihapus)\n");
        else{
            printf("\n(Absen tidak ada)\n");
        }
    }
}

int main(){
    int menu;
    struct data partisipan;
    printf("==========================\nProgram Partisipan Tamasya\n==========================");
    do{
        menu:
        printf("\n\nMenu :\n1. Tambah Partisipan\n2. Cek Partisipan\n3. Hapus Partisipan\n4. Keluar\nPilihan : ");
        scanf("%d", &menu);
        getchar();
        switch(menu){
            case 1:
                printf("\nMasukkan data partisipan\nAbsen        : ");
                gets(partisipan.absen);
                char angka[999];
                strcpy(angka, partisipan.absen);
                if(cekData() != 0){
                    FILE *data = fopen("Prak-Alpro_Final-Project_Data.txt" , "r");
                    char point[999], first[] = "Absen        : ", cek[999], salin[999];
                    int count=0;
                    strcat(first, partisipan.absen);
                    strcpy(cek, first);
                    while(fgets(point, sizeof(point), data)){
                        if(strstr(point, cek) != 0){
                            printf("\n(Absen sudah ada)\n");
                            goto menu;
                        }
                    }
                    fclose(data);
                }
                printf("Nama         : ");
                gets(partisipan.nama);
                printf("Gender (L/P) : ");
                gets(partisipan.gender);
                printf("Telepon      : ");
                gets(partisipan.telepon);
                addData(angka, partisipan.nama, partisipan.gender, partisipan.telepon);
                break;
            case 2:
                readData();
                break;
            case 3:
                removeData(partisipan.nama, partisipan.gender, partisipan.telepon);
                break;
            case 4:
                return 0;
            default:
                printf("\n(Pilihan anda tidak tertera pada menu)\n");
        }
    }while(menu!=4);
}