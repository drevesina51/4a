#ifndef TREE_H
#define TREE_H
#include <time.h>
#define KeyType char

typedef struct Info{
    int num1; //первое число
    int num2; //второе число
    char *string; //строка
    struct Info *next; // следущий элемент с таким же ключем
} Info;

typedef struct Tree{
    Info *info; // информационное поле
    KeyType *key; // ключ
    int lvl;
    struct Tree *left; // левое поддерево
    struct Tree *right; // правое поддерево
    struct Tree *prev; // предыдущий узел
    struct Tree *next; // следующий узел
} Tree;

int T_Find(Tree *, char *), //поиск элемента в дереве по ключу
    T_Delete(Tree *, char *, int), //удаление по ключу
    T_Different(Tree *, char *), //поиск максимально отличающегося
    T_Timing(Tree *, int), // таймирование
    T_File(Tree *, int); // ввод из файла

int init_tree(Tree *), // создание нового корня
    delTree(Tree *), // удаление дерева
    insert(Tree *root, char *, int, int, char *, int),
    lvldown(Tree *),
    find_time(Tree *, char *),
    find(Tree *, char *, int, int, char *, int);

#endif // TREE_H
