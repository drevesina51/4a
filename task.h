#ifndef TASK_H
#define TASK_H
#include "tree.h"

int D_Add(Tree *), //вставка элемента в дерево
    D_Find(Tree *), //поиск элемента в дереве по ключу
    D_Delete(Tree *), //удаление по ключу
    D_Show(Tree *), //вывод дерева на экран
    D_Different(Tree *), //поиск максимально отличающегося
    D_Timing(Tree *), // таймирование
    D_File(Tree *); // ввод из вайла

#endif // TASK_H
