#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KEY_SIZE 10
#define PHONE_SIZE 15
#define TABLE_SIZE 10

//typedef struct {
//    char key[KEY_SIZE];
//    char value[PHONE_SIZE];
//} element;
//
//element hash_table[TABLE_SIZE];
//
//void init_table() {
//    for (int i = 0; i < TABLE_SIZE; i++) {
//        strcpy(hash_table[i].key, "");
//        strcpy(hash_table[i].value, "");
//    }
//}
//
//int hash_function(char* key) {
//    int hash = 0;
//    for (int i = 0; key[i] != '\0'; i++) {
//        hash += key[i];
//    }
//    return hash % TABLE_SIZE;
//}
//
//void hash_dh_add(element item) {
//    int index = hash_function(item.key);
//    int original_index = index;
//    int i = 1;
//
//    while (strcmp(hash_table[index].key, "") != 0) {
//        if (strcmp(hash_table[index].key, item.key) == 0) {
//            printf("해시 중복 오류\n");
//            return;
//        }
//        index = (original_index + i) % TABLE_SIZE;
//        i++;
//        if (index == original_index) {
//            printf("해시 꽉 참\n");
//            return;
//        }
//    }
//
//    strcpy(hash_table[index].key, item.key);
//    strcpy(hash_table[index].value, item.value);
//}
//
//void printHash() {
//    printf("Hash Table:\n");
//    for (int i = 0; i < TABLE_SIZE; i++) {
//        if (strcmp(hash_table[i].key, "") != 0) {
//            if (strlen(hash_table[i].key) < 3)
//                printf("[%d] %s \t\n", i, hash_table[i].key);
//            else
//                printf("[%d] %s \t\n", i, hash_table[i].key);
//        }
//        else {
//            printf("[%d] EMPTY\n", i);
//        }
//    }
//}
//
//int main() {
//    init_table();
//
//    element contacts[] = {
//        {"Hong", "010-1234-0001"},
//        {"Kim", "010-1234-0002"},
//        {"Lee", "010-1234-0003"},
//        {"Nam", "010-1234-0004"},
//        {"Cheon", "010-1234-0005"},
//        {"Ahn", "010-1234-0006"},
//        {"Park", "010-1234-0007"},
//        {"Shin", "010-1234-0008"},
//        {"Oh", "010-1234-0009"},
//        {"Gu", "010-1234-0010"}
//    };
//
//    for (int i = 0; i < 10; i++) {
//        hash_dh_add(contacts[i]);
//    }
//
//    // 해시 출력
//    printHash();
//
//    return 0;
//}

//#define _CRT_SECURE_NO_WARNINGS
//
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//#define KEY_SIZE 10
//#define PHONE_SIZE 15
//#define TABLE_SIZE 10
//
//typedef struct {
//    char key[KEY_SIZE];
//    char value[PHONE_SIZE];
//} element;
//
//element hash_table[TABLE_SIZE];
//
//void init_table() {
//    for (int i = 0; i < TABLE_SIZE; i++) {
//        strcpy(hash_table[i].key, "");
//        strcpy(hash_table[i].value, "");
//    }
//}
//
//int hash_function(char* key) {
//    int hash = 0;
//    for (int i = 0; key[i] != '\0'; i++) {
//        hash += key[i];
//    }
//    return hash % TABLE_SIZE;
//}
//
//int hash_function2(char* key) {
//    int hash = 0;
//    for (int i = 0; key[i] != '\0'; i++) {
//        hash = (hash * 31 + key[i]) % (TABLE_SIZE - 1);
//    }
//    return (hash + 1);
//}
//
//void hash_dh_add(element* contacts) {
//    for (int j = 0; j < KEY_SIZE; j++) {
//        element item = contacts[j];
//        int index = hash_function(item.key);
//        int step_size = hash_function2(item.key);
//        int original_index = index;
//        int i = 1;
//
//        while (strcmp(hash_table[index].key, "") != 0) {
//            if (strcmp(hash_table[index].key, item.key) == 0) {
//                printf("키 중복 감지\n");
//                return;
//            }
//            index = (original_index + i * step_size) % TABLE_SIZE;
//            i++;
//            if (index == original_index) {
//                printf("해시 꽉 참\n");
//                return;
//            }
//        }
//
//        strcpy(hash_table[index].key, item.key);
//        strcpy(hash_table[index].value, item.value);
//    }
//}
//
//void display_table() {
//    printf("Hash Table:\n");
//    for (int i = 0; i < TABLE_SIZE; i++) {
//        if (strcmp(hash_table[i].key, "") != 0) {
//            if (strlen(hash_table[i].key) < 3)
//                printf("[%d] %s \t\n", i, hash_table[i].key);
//            else
//                printf("[%d] %s \t\n", i, hash_table[i].key);
//        }
//        else {
//            printf("[%d] - \n", i);
//        }
//    }
//}
//
//element* hash_dh_search(char* key) {
//    int index = hash_function(key);
//    int step_size = hash_function2(key);
//    int original_index = index;
//    int i = 1;
//
//    while (strcmp(hash_table[index].key, "") != 0) {
//        if (strcmp(hash_table[index].key, key) == 0) {
//            return &hash_table[index];
//        }
//        index = (original_index + i * step_size) % TABLE_SIZE;
//        i++;
//        if (index == original_index) {
//            break;
//        }
//    }
//
//    return NULL;
//}
//
//int main() {
//    init_table();
//
//    element contacts[] = {
//        {"Hong", "010-1234-0001"},
//        {"Kim", "010-1234-0002"},
//        {"Lee", "010-1234-0003"},
//        {"Nam", "010-1234-0004"},
//        {"Cheon", "010-1234-0005"},
//        {"Ahn", "010-1234-0006"},
//        {"Park", "010-1234-0007"},
//        {"Shin", "010-1234-0008"},
//        {"Oh", "010-1234-0009"},
//        {"Gu", "010-1234-0010"}
//    };
//
//    hash_dh_add(contacts);
//    display_table();
//
//    element* result = hash_dh_search("Hong");
//    if (result != NULL) {
//        printf("\n탐색 %s\t성공\t%s\n", result->key, result->value);
//    }
//    else {
//        printf("\n연락처를 찾을 수 없습니다.\n");
//    }
//    result = hash_dh_search("Kim");
//    if (result != NULL) {
//        printf("\n탐색 %s\t성공\t%s\n", result->key, result->value);
//    }
//    else {
//        printf("\n연락처를 찾을 수 없습니다.\n");
//    }
//
//    return 0;
//}


typedef struct element {
    char key[KEY_SIZE];
    char value[PHONE_SIZE];
    struct element* next;
} element;

element* hash_table[TABLE_SIZE];

void init_table() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hash_table[i] = NULL;
    }
}

int hash_function(char* key) {
    int hash = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        hash += key[i];
    }
    return hash % TABLE_SIZE;
}

void hash_chain_add(element* contacts) {
    for (int j = 0; j < KEY_SIZE; j++) {
        element* item = (element*)malloc(sizeof(element));
        strcpy(item->key, contacts[j].key);
        strcpy(item->value, contacts[j].value);
        item->next = NULL;

        int index = hash_function(item->key);

        if (hash_table[index] == NULL) {
            hash_table[index] = item;
        }
        else {
            element* current = hash_table[index];
            while (current->next != NULL) {
                if (strcmp(current->key, item->key) == 0) {
                    printf("키 중복 감지\n");
                    free(item);
                    return;
                }
                current = current->next;
            }
            if (strcmp(current->key, item->key) == 0) {
                printf("키 중복 감지\n");
                free(item);
                return;
            }
            current->next = item;
        }
    }
}

void display_table() {
    printf("hash table:\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("[%d] ", i);
        element* current = hash_table[i];
        while (current != NULL) {
            printf("%s ", current->key);
            if (current->next!=NULL)
                printf(" -> ");
            current = current->next;
        }
        printf("\n");
    }
}

element* hash_chain_search(char* key) {
    int index = hash_function(key);
    element* current = hash_table[index];

    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

int main() {
    init_table();

    element contacts[] = {
        {"hong", "010-1234-0001"},
        {"kim", "010-1234-0002"},
        {"lee", "010-1234-0003"},
        {"nam", "010-1234-0004"},
        {"cheon", "010-1234-0005"},
        {"ahn", "010-1234-0006"},
        {"park", "010-1234-0007"},
        {"shin", "010-1234-0008"},
        {"oh", "010-1234-0009"},
        {"gu", "010-1234-0010"}
    };

    hash_chain_add(contacts);
    display_table();

    element* result = hash_chain_search("hong");
    if (result != NULL) {
        printf("\n찾은 연락처: %s - %s\n", result->key, result->value);
    }
    else {
        printf("\n연락처를 찾을 수 없습니다.\n");
    }

    result = hash_chain_search("kim");
    if (result != NULL) {
        printf("\n찾은 연락처: %s - %s\n", result->key, result->value);
    }
    else {
        printf("\n연락처를 찾을 수 없습니다.\n");
    }

    return 0;
}