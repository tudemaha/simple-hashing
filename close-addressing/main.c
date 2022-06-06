#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define SIZE 3

struct hash {
    int value;
    bool used;
    struct hash *next;
};

void manyHash(int count, struct hash *table);
bool insertData(int data, struct hash *table);
void viewData(struct hash *table);
int seekData(int data, struct hash *table);

int main() {
    char choice;
    int count, temp_data, data_index;

    struct hash *hashTable = (struct hash*)malloc(10 * sizeof(struct hash));
    for(int i = 0; i < SIZE; i++) {
        hashTable[i].used = false;
        hashTable[i].next = NULL;
    }

    start:
    printf(
        "===== CLOSE ADDRESSING HASH TABLE =====\n"
        "=======================================\n\n"
    );

    printf("Menu:\n1. Input Data\n2. View Data\n3. Cari Data\n4. Keluar\n");
    insert_choice:
    printf("Masukkan pilihan: ");
    scanf(" %c", &choice);

    switch(choice) {
        case '1':
            printf("\nMasukkan jumlah data: ");
            scanf("%d", &count);
            manyHash(count, hashTable);
            getchar(); getchar();
            goto start;
            break;

        case '2':
            viewData(hashTable);
            getchar(); getchar();
            goto start;
            break;

        case '3':
            printf("Masukkan bilangan dicari: ");
            scanf("%d", &temp_data);
            data_index = seekData(temp_data, hashTable);
            if(data_index) printf("%d ditemukan pada pencarian ke-%d\n", temp_data, data_index);
            else printf("Data tidak tercatat\n");
            getchar(); getchar();
            goto start;
            break;

        case '4':
            printf("\n");
            insert_exit:
            printf("Yakin keluar? (y/n): ");
            scanf(" %c", &choice);
            if(choice == 'y' || choice == 'Y') exit(0);
            else if(choice == 'n' || choice == 'N') goto start;
            else goto insert_exit;
            break;

        default:
            goto insert_choice;
            break;
    }

    return 0;
}

void manyHash(int count, struct hash *table) {
    int temp_data;

    printf("\n");
    for(int i = 0; i < count; i++) {
        printf("Data ke-%d: ", i + 1);
        scanf("%d", &temp_data);
        if(insertData(temp_data, table)) printf("Berhasil memasukkan data.\n");
        else printf("Gagal memasukkan data.\n");
    }
}

bool insertData(int data, struct hash *table) {
    int index = data % SIZE;

    if(table[index].used == false) {
        table[index].value = data;
        table[index].used = true;

        return 1;
    } else {
        struct hash *iterate = &(table[index]);
        
        struct hash *new_data = (struct hash*)malloc(sizeof(struct hash));
        new_data->value = data;
        new_data->used = true;
        new_data->next = NULL;
        
        while(iterate->next != NULL) {
            iterate = iterate->next;
        }
 
        iterate->next = new_data;
        return 1;
    }

    return 0;
}

void viewData(struct hash *table) {
    printf("\nData pada hash table:\n");
    for(int i = 0; i < SIZE; i++) {
        if(table[i].used) printf("%d ", table[i].value);

        if(table[i].next != NULL) {
            struct hash *iterate = table[i].next;
            while(iterate != NULL) {
                printf("%d ", iterate->value);
                iterate = iterate->next;
            }
        }
    }
    printf("\n");
}

int seekData(int data, struct hash *table) {
    int index = data % SIZE;
    bool status = false;
    int count = 1;
    
    if(table[index].value == data) {
        status = true;
    } else {
        struct hash *iterate = table[index].next;
        while(iterate != NULL) {
            count++;
            if(iterate->value == data) {
                status = true;
                break;
            }
            iterate = iterate->next;
        }
    }

    if(status) return count;
    else return 0;
}