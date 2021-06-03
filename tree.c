#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

int init_tree(Tree *root){
	root->info = NULL;
	root->key = NULL;
	root->prev = NULL;
	root->next = NULL;
	root->left = NULL;
	root->right = NULL;
	root->lvl = 0;// высота
	return 1;
}

int delTree(Tree *root){
	if (root->info == NULL){
		free(root);
		return 1;
	}
	Tree *ptr = root;
	Tree *tmp = NULL;
	Info *inf = NULL;
	while(ptr->next != NULL)
                ptr = ptr->next;
        while(ptr != NULL){
		tmp = ptr;
		ptr = ptr->prev;
		inf = tmp->info;
		while (tmp->info){
			inf = tmp->info;
			tmp->info = tmp->info->next;
			free(inf->string);
			free(inf);
		}
		free(tmp->key);
		free(tmp);
	}
	return 1;
}

int find(Tree *root, char *key, int num1, int num2, char *string, int flag_t){// создание элемента, поиск, добавление
	if (root->info == NULL)
		return 0;//новое дерево
	Tree *ptr = root;
	// ptr = лист с ключем key
	while(ptr){
                if (strcmp(ptr->key, key) > 0)
			ptr = ptr->right;
		else if (strcmp(ptr->key, key) < 0)
		     	ptr = ptr->left;
		     else if (strcmp(ptr->key, key) == 0){
				if (flag_t != 1) free(key);
        			Info *info = (Info *)calloc(1, sizeof(Info));
        			if(info == NULL){
                			return 1;
        			}
		      	  	Info *last = NULL;
				last = ptr->info;
				while(last->next != NULL)
					last = last->next;
				info->num1 = num1;
				info->num2 = num2;
				info->string = string;
				info->next = NULL;
				last->next = info;
				return 1; // повторяющися ключ добавлен
			}
	}
	return 0;//нет такого ключа
}

Tree *newlist(char *key, int num1, int num2, char *string){
	Info *info = (Info *)calloc(1, sizeof(Info));
	if(info == NULL){
		return NULL;
	Tree *newl = (Tree *)calloc(1, sizeof(Tree));
	if(newl == NULL){
		return NULL;
	}
	info->num1 = num1;
	info->num2 = num2;
	info->string = string;
	info->next = NULL;
	newl->key = key;
	newl->info = info;
	newl->next = NULL;
	newl->prev = NULL;
	newl->left = NULL;
	newl->right = NULL;
	newl->lvl = 0;
	return newl;
}

int insert(Tree *root, char *key, int num1, int num2, char *string, int flag_t){
        if(find(root, key, num1, num2, string, flag_t) == 1)// поиск такого же ключа
                return 0;
        else   {
		        Tree *newl = newlist(key, num1, num2, string);
			if (newl == NULL) return 4;
			Info *info = newl->info;
			if (root->info == NULL) { // заполнение корня
				root->info = info;
				root->key = key;
				free(newl);
				return 0;
        		} else {
				int flag = 0;//при изменении направления
                		Tree *ptr = root;
				Tree *parent = NULL;
				Tree *tmp = NULL;
				while(ptr){
					newl->lvl++;
					if (strcmp(ptr->key, key) > 0){ // идем в правое поддерево
						if (flag == 0)
							flag = 1;
						else if (flag == -1){// tmp = первое до смены направления
							tmp = parent;
							flag = 1;
						     }
						if(ptr->right != NULL){
							parent = ptr;
							ptr = ptr->right;
						} else {
							newl->prev = ptr;
							newl->next = tmp;
							ptr->right = newl;
							ptr->next = newl;
							if (tmp != NULL)
								tmp->prev = newl;
							return 0;
							}
					} else { // идем в левое поддерево
						if (flag == 0)
							flag = -1;
						else if (flag == 1){
							flag = -1;
							tmp = parent;
						     }
						if(ptr->left != NULL){
							parent = ptr;
							ptr = ptr->left;
						} else {
							newl->next = ptr;
							newl->prev = tmp;
							ptr->left = newl;
							ptr->prev = newl;
							if (tmp != NULL)
								tmp->next = newl;
							return 0;
						}
					}
				}
			    }
		}
		return 0;
}

int choose(int r, int n){
	int w;
	printf("There are %d info's with this key\nEnter number of info: 1<=x<=%d -->\n", n, n);
	w = scanf("%d", &r);
	if (w == EOF) return 0;
	if (r > n) r = n;
	return r;
}

int print_find(char *key, Info *info){
	printf("key %s : %d %d %s \n", key, info->num1, info->num2, info->string);
	return 1;
}

int T_Find(Tree *root, char *key){
	Tree *ptr = root;
	Info *info = NULL;
	int n, r, w;
        while(ptr){
        	if (strcmp(ptr->key, key) > 0)
                        ptr = ptr->right;
                else if (strcmp(ptr->key, key) < 0)
                        ptr = ptr->left;
                else if (strcmp(ptr->key, key) == 0){
			if(ptr->info->next != NULL){
				n = 0;
				info = ptr->info;
				while(info != NULL){
					n++;
					info = info->next;
				}
				info = ptr->info;
				if (n > 0){
					r = choose(r, n);
					if (r == 0) return 3;
					for (int i = 0; i<r-1; i++){
						info = info->next;
					}
				}
			} else info = ptr->info;
			print_find(key, info);
			free(key);
			return 0;
		}
	}
	free(key);
        return 5;
}

int lvldown(Tree *ptr){
	if (ptr){
		lvldown(ptr->left);
		lvldown(ptr->right);
		ptr->lvl--;
	}
	return 1;
}

int T_Delete(Tree *root, char *key, int flag){//удаление корня
	int n, r, w, d = 0;
	Tree *ptr = root;
	Tree *parent = NULL;
	Info *info = NULL;
	Info *par = NULL;
        while(ptr){
                if (strcmp(ptr->key, key) > 0){
			parent = ptr;
                        ptr = ptr->right;
			d = 1;
		}
                else if (strcmp(ptr->key, key) < 0){
			parent = ptr;
                        ptr = ptr->left;
			d = -1;
		}
		else if (strcmp(ptr->key, key) == 0){
			if(ptr->info->next != NULL && flag == 1){
				n = 0;
				info = ptr->info;
				while(info != NULL){
					n++;
					info = info->next;
				}
				info = ptr->info;
				if (n > 1){
					r = choose(r, n);
					if (r == 0) return 3;
					if (r == 1){
						//info = ptr->info;
						ptr->info = info->next;
						free(info->string);
						free(info);
						return 0;
					}
					for (int i = 0; i < r-1; i++){
						par = info;
						info = info->next;
					}
					par->next = info->next;
					free(info->string);
					free(info);
					return 0;
				}
			}else {
				Tree *qwe = NULL;
				Tree *asd = NULL;
				if(ptr->left == NULL && ptr->right == NULL){//нет ветвей
					if (d == -1) parent->left = NULL;
					else parent->right = NULL;
				}else if (ptr->right == NULL){//одна левая ветвь
					   if (d == -1) parent->left = ptr->left;
					   else parent->right = ptr->left;
					   lvldown(ptr);
				      }else if (ptr->left == NULL){//одна правая ветвь
						if (d == -1) parent->left = ptr->right;
                                        	else parent->right = ptr->right;
						lvldown(ptr);
					}else{//2 ветви
						char *key_asd;
						Info *info_asd;
						char *string_asd;
						if (d == -1) asd = ptr->prev;
                                                else asd = ptr->next;
						flag = 0;
						key_asd = asd->key;
                                                info_asd = asd->info;
                                                string_asd = asd->info->string;
						info_asd->string = string_asd;
                                                T_Delete(root, key_asd, flag);
						free(ptr->info->string);
						free(ptr->info);
						free(ptr->key);
                                                ptr->key = key_asd;
                                                ptr->info = info_asd;
                                              return 0;
					     }
				qwe = ptr->prev;
                                asd = ptr->next;
                                if (qwe != NULL) qwe->next = asd;
                                if (asd != NULL) asd->prev = qwe;
				if (flag == 1){
                                	free(ptr->info->string);
                                	free(ptr->info);
                                	free(ptr->key);
				}
                                free(ptr);
				return 0;
			      }
		}
	}
        return 5;
}

int T_Different(Tree *root, char *key){
	Tree *ptr = root;
	Info *info = NULL;
	Tree *tmp = root;
	int n, w, r, cmp, max = 10;
	while(ptr->next != NULL)
                ptr = ptr->next;
        while(ptr != NULL){ // поиск наиболее отличного элемента
		cmp = strcmp(ptr->key, key);
		if (cmp < 0)
			cmp = -cmp;//модуль
                if (cmp < max){
			max = cmp;
			tmp = ptr;
		}
		ptr = ptr->prev;
	}
        info = tmp->info;
        n = 0;
	if(tmp->info->next != NULL){
        	while(info != NULL){
               	 	n++;
                	info = info->next;
        	}
        	info = tmp->info;
        	if (n > 0){
        		printf("There are %d info's with this key\nEnter number or info: 1<=x<=%d -->\n", n, n);
               		w = scanf("%d", &r);
               		if (w == EOF) return 0;
                	if (r > n) r = n;
                	for (int i = 0; i<r-1; i++){
                		info = info->next;
                	}
        	}
	}
        printf("key %s - most different key %s : %d %d %s \n", key, tmp->key, info->num1, info->num2, info->string);
	free(key);
	return 1;
}

int T_File(Tree *root, int m){
	FILE *in;
	in = fopen("filein.txt", "r");
	if(in == NULL){
		printf("Файл не найден\n");
		return 0;
	}
	int num1, num2, flag = 0;
        char **key = NULL;
        char **string = NULL;
        key = (char **)calloc(m, sizeof(char *));
        string = (char **)calloc(m, sizeof(char *));
        for (int q = 0; q < m; q++){
                key[q] = (char *)calloc(15, sizeof(char));
                if(key[q] == NULL) {
                        //printf("Error try alloc\n");
                        return 0;
                }
                string[q] = (char *)calloc(15, sizeof(char));
                if(string[q] == NULL) {
                        //printf("Error try alloc\n");
                        return 0;
                }
        }
	for (int i = 0; i < m; i++) {
        	fscanf(in, "%s", key[i]);
        	fscanf(in, "%d", &num1);
        	fscanf(in, "%d", &num2);
		fscanf(in, "%s", string[i]);
		insert(root, key[i], num1, num2, string[i], flag);
	}
	free(key);
	free(string);
	fclose(in);
	return 1;
}

int find_time(Tree *root, char* key){
        Tree *ptr = root;
        while(ptr){
                if (strcmp(ptr->key, key) > 0)
                        ptr = ptr->right;
                else if (strcmp(ptr->key, key) < 0)
                        ptr = ptr->left;
                else if (strcmp(ptr->key, key) == 0) return 1;
	}
	return 0;
}

int T_Timing(Tree *root, int cnt){
        int first, last;
        srand(time(NULL));
	char **key = NULL;
        char **string = NULL;
	key = (char **)calloc(cnt, sizeof(char *));
	string = (char **)calloc(cnt, sizeof(char *));
	for (int q = 0; q < cnt; q++){
		key[q] = (char *)calloc(15, sizeof(char));
		if(key[q] == NULL) {
                        //printf("Error try alloc\n");
                        return 4;
                }
		string[q] = (char *)calloc(15, sizeof(char));
                if(string[q] == NULL) {
                        //printf("Error try alloc\n");
                        return 4;
                }

	}
	int num1, num2, i, m = 0, flag = 1;
	char *x;
	int z, j;
	for (i = 0; i < cnt; i++){
		num1 = rand();
		num2 = rand() * rand();
		z = rand()%15;
                x = key[i];
                for (j = 0; j < z; j++)
                        x[j] = rand()%26+'A';
		x = string[i];
		z = rand()%5;
		for (j = 0; j < z; j++)
                        x[j] = rand()%26+'A';
		insert(root, key[i], num1, num2, string[i], flag);
	}
	first = clock();
	for (i = 0; i < cnt; i++)
		if (find_time(root, key[i]))
			++m;
	last = clock();
	printf("number of nodes = %d, time = %d\n", m, last - first);
	return 1;
}
