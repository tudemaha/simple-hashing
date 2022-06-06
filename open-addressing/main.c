#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 3

void insertData();
void seekData();
int insertLinear(int data);
int insertQuadratic(int data);

int hash_table[MAX_SIZE][2];

int main() {
    char choice;
    int banyak_data;

    for(int i = 0; i < MAX_SIZE; i++) {
        hash_table[i][0] = 0;
    }

    start:
    system("cls");
    printf(
        "===== OPEN ADDRESSING HASH TABLE =====\n"
        "======================================\n\n"
    );

    printf("Menu:\n1. Input Data\n2. View Data\n3. Cari Data\n4. Keluar\n");
    insert_choice:
    printf("Masukkan pilihan: ");
    scanf(" %c", &choice);

    switch(choice) {
        case '1':
            insertData();
            system("pause");
            goto start;
            break;
        case '2':
            printf("\nData terdaftar:\n");
            for(int i = 0; i < MAX_SIZE; i++) {
                printf("%d ", hash_table[i][1]);
            }
            printf("\n");
            system("pause");
            goto start;
            break;
        case '3':
            seekData();
            system("pause");
            goto start;
            break;
        case '4':
            exit(0);
            break;
        default:
            goto insert_choice;
            break;
    }

    return 0;
}

void insertData() {
    int choice, how_many, temp_value, status = 1;

    printf("\nPilihan probing:\n1. Linear Probing\n2. Quadratic Probing\n");
    insert_option:
    printf("Masukkan pilihan: ");
    scanf("%d", &choice);

    switch(choice) {
        case 1:
        case 2:
            printf("\nJumlah data: ");
            scanf("%d", &how_many);

            printf("\n");
            for(int i = 0; i < how_many; i++) {
                printf("Data-%d: ", i + 1);
                scanf("%d", &temp_value);
                if(choice == 1) status = insertLinear(temp_value);
                else status = insertQuadratic(temp_value);

                if(!status) {
                    printf("Array penuh!\n");
                    break;
                } else printf("Berhasil memasukkan data.\n\n");
            }
            break;
        default:
            goto insert_option;
            break;

    }
}

int insertLinear(int data) {
    int index = data % MAX_SIZE;
    int status = 0;

    for(int i = 0; i < MAX_SIZE; i++) {
        if(hash_table[i][0] == 0) {
            status = 1;
            break;
        }
    }
    
    if(status) {
        if(hash_table[index][0] == 0) {
            hash_table[index][0] = 1;
            hash_table[index][1] = data;
        } else {
            for(int i = 1; i < MAX_SIZE; i++) {
                if(hash_table[(index + i) % MAX_SIZE][0] == 0) {
                    hash_table[(index + i) % MAX_SIZE][0] = 1;
                    hash_table[(index + i) % MAX_SIZE][1] = data;
                    break;
                }
            }
        }
    } else return 0;

    return 1;
}

int insertQuadratic(int data) {
    int index = data % MAX_SIZE;
    int status = 0;
    int up_down = 1;

    for(int i = 0; i < MAX_SIZE; i++) {
        if(hash_table[i][0] == 0) {
            status = 1;
            break;
        }
    }

    if(status) {
        if(hash_table[index][0] == 0) {
            hash_table[index][0] = 1;
            hash_table[index][1] = data;
        } else {
            for(int i = 1; i < MAX_SIZE; i++) {
                for(int j = 0; j < 2; j++) {
                    if(up_down == 1) {
                        if(hash_table[(index + i * i) % MAX_SIZE][0] == 0) {
                            hash_table[(index + i * i) % MAX_SIZE][0] = 1;
                            hash_table[(index + i * i) % MAX_SIZE][1] = data;
                            i += MAX_SIZE;
                            break;
                        }
                        up_down = -1;
                    } else {
                        if(hash_table[(index - i * i) % MAX_SIZE][0] == 0) {
                            hash_table[(index - i * i) % MAX_SIZE][0] = 1;
                            hash_table[(index - i * i) % MAX_SIZE][1] = data;
                            i += MAX_SIZE;
                            break;
                        }
                        up_down = 1;
                    }
                }
                
            }
        }
    } else return 0;

    return 1;
}

void seekData() {
    int choice, temp_value, up_down = 1, find = 1, find_index = -1;

    printf("\nData dicari: ");
    scanf("%d", &temp_value);

    printf("\nPilihan pencarian:\n1. Linear Probing\n2. Quadratic Probing\n");
    insert_option:
    printf("Masukkan pilihan: ");
    scanf("%d", &choice);

    int index = temp_value % MAX_SIZE;

    if(choice == 1) {
        if(hash_table[index][1] == temp_value) find_index = index;
        else {
            for(int i = 1; i < MAX_SIZE; i++) {
                find++;
                if(hash_table[(index + i) % MAX_SIZE][1] == temp_value) {
                    find_index = index + i % MAX_SIZE;
                    break;
                }
            }
        }
    }
    else if(choice == 2) {
        if(hash_table[index][1] == temp_value) find_index = index;
        else {
            for(int i = 1; i < MAX_SIZE; i++) {
                for(int j = 0; j < 2; j++) {
                    find++;
                    if(up_down == 1) {
                        if(hash_table[(index + i * i) % MAX_SIZE][1] == temp_value) {
                            find_index = (index + i * i) % MAX_SIZE;
                            i += MAX_SIZE;
                            break;
                        }
                        up_down = -1;
                    } else {
                        if(hash_table[(index - i * i) % MAX_SIZE][1] == temp_value) {
                            find_index = (index - i * i) % MAX_SIZE;
                            i += MAX_SIZE;
                            break;
                        }
                        up_down = 1;
                    }
                }
            }
        }
    }
    else goto insert_option;

    if(find_index == -1) printf("\nData tidak ditemukan!\n");
    else printf("\nData ditemukan pada index %d pencarian ke-%d.\n", find_index, find);

}