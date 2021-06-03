#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "tree.h"
#include "task.h"

/*void tree_graphviz(Tree * ptr){
	if (ptr == NULL) return;
	tree_graphviz(ptr->left);
	if (ptr->parent != NULL) {
		char S;
		if(n_side(node) > 0) S = 'R';
		else S = 'L';
		printf("\"%d : %s, %s\" -> \"%d : %s, %s\" [label = %c]\n",
			node->parent->key, node->parent->str1, node->parent->str2, node->key, node->str1, node->str2, &S);
	}
	tree_graphviz(node->right);
}*/

int dialog(const char *msgs[], int N) {
        char *errmsg = "";
        int rc;
        int i, n;
        do{
                puts(errmsg);
                errmsg = "\nYou are wrong. Repeate, please!";
                for(i = 0; i < N; ++i)
                        puts(msgs[i]);
                puts("Make your choice: --> ");
                n = scanf("%d", &rc);
		if (n == EOF) return 0;
                if(n == 0)
                        rc = 0;
        } while(rc < 0 || rc >= N);
        return rc;
}

int main(){
        Tree *root = (Tree *) calloc(1, sizeof(Tree)); // создание пустой таблицы
        if(root == NULL) {
                   printf("Error try alloc\n");
                   return 0;
        }
        init_tree(root);
        const char *msgs[] = {"0. Quit", "1. Add", "2. Find", "3. Delete", "4. Show", "5. Different", "6. Timing", "7. File"};
        const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);
        int dialog(const char *msgs[], int);
        int (*fptr[])(Tree *) = {NULL, D_Add, D_Find, D_Delete, D_Show, D_Different, D_Timing, D_File};
        int rc;
        while(rc = dialog(msgs, NMsgs))
                if(!fptr[rc](root)) // вызов выбранной диалоговой функции
                  break;
        printf("End.\n");
        delTree(root); //удаление таблицы
	return 0;
}
