#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "task.h"

    /* массив диагностических сообщений об ошибках */
const char *errmsgs[] = {"Ok", "Duplicate key", "Tree overflow", "Input Error", "Error try alloc"};

int D_Add(Tree *root){
	int num1, num2, n, n1, n2, n3, rc, flag_t = 0;
        char *string = (char *)calloc(15, sizeof(char));
        if(string == NULL) {
                printf("Error try alloc\n");
                return 0;
        }
        char *key = (char *)calloc(15, sizeof(char));
        if(key == NULL) {
                printf("Error try alloc\n");
                return 0;
        }
        printf("Enter key: -->\n");
        n = scanf("%s", key);
	if (n == EOF) return 0;
        printf("Enter num1: -->\n");
        n1 = scanf("%d", &num1);
	if (n1 == EOF) return 0;
	printf("Enter num2: -->\n");
        n2 = scanf("%d", &num2);
        if (n2 == EOF) return 0;
	printf("Enter string: -->\n");
        n3 = scanf("%s", string);
        if (n2 == EOF) return 0;
	if(n == 0 || n1 == 0 || n2 == 0 || n3 == 0) {
                rc = 3;
                printf("%s\n", errmsgs[rc]);
                return 1; //ошибка ввода
        }
        rc = insert(root, key, num1, num2, string, flag_t);
        printf("%s: %s\n", errmsgs[rc], key);
	return 1;
}

int D_Find(Tree *root){
	int n;
	char *key = (char *)calloc(15, sizeof(char));
	if(key == NULL) {
                printf("Error try alloc\n");
                return 0;
        }
	printf("Enter key: -->\n");
	n = scanf("%s", key);
        if (n == EOF) return 0;
	if (T_Find(root, key) == 0) return 0;
	return 1;
}

int D_Delete(Tree *root){
        int n;
	int flag = 1;
        char *key = (char *)calloc(15, sizeof(char));
        if(key == NULL) {
                printf("Error try alloc\n");
                return 0;
        }
        printf("Enter key: -->\n");
        n = scanf("%s", key);
        if (n == EOF) return 0;
	if (T_Delete(root, key, flag) == 0) {
		free(key);
		return 0;
	}
	free(key);
        return 1;
}

int D_Different(Tree *root){
	int n;
	char *key = (char *)calloc(15, sizeof(char));
        if(key == NULL) {
                printf("Error try alloc\n");
                return 0;
        }
	printf("Enter key: -->\n");
        n = scanf("%s", key);
        if (n == EOF) return 0;
	if (T_Different(root, key) == 0) return 0;
	return 1;
}

int D_Show(Tree *root){
	Tree *ptr = root;
	Info *info;
	while(ptr->next != NULL)
		ptr = ptr->next; // находим самый маленький ключ
	while(ptr != NULL){ // идем по возрастанию
		for (int i = 0; i < ptr->lvl; i++) printf("   ");
		printf("   /\n");
		for (int j = 0; j < ptr->lvl; j++) printf("    "); // высота
		printf("%s :  ", ptr->key);
		info = ptr->info;
		while(info != NULL){// проход по всему списку info
			printf("%d %d %s; ", info->num1, info->num2, info->string);
			info = info->next;
		}
		printf("\n");
		for (int c = 0; c < ptr->lvl; c++) printf("   ");
                printf("   \\\n");
		ptr = ptr->prev;
	}
        return 1;
}

int D_File(Tree *root){
        int n, k;
        printf("Enter number or items: -->\n 1<=x<=10\n");
        n = scanf("%d", &k);
        if (n == EOF) return 0;
	T_File(root, k);
	return 1;
}

int D_Timing(Tree *root){
        int n, k;
        printf("Enter number or keys: -->\n");
        n = scanf("%d", &k);
        if (n == EOF) return 0;
	T_Timing(root, k);
	return 1;
}
