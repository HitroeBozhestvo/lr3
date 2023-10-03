#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

struct node
{
    char inf[256];  // полезная информация
    struct node* next; // ссылка на следующий элемент 
};

struct node* head = NULL; // указатель на вершину стека
int dlinna = 0;

// Функции добавления элемента, удаления элемента и просмотра стека
void push(void), pop(void), review(void);

struct node* get_struct(void)
{
    struct node* p = NULL;
    char s[256];

    if ((p = (struct node*)malloc(sizeof(struct node))) == NULL)  // выделяем память под новый элемент стека
    {
        printf("Ошибка при распределении памяти\n");
        exit(1);
    }

    printf("Введите название объекта: \n");   // вводим данные
    scanf("%s", s);
    if (*s == 0)
    {
        printf("Запись не была произведена\n");
        return NULL;
    }
    strcpy(p->inf, s);

    p->next = NULL;

    return p;// возвращаем указатель на созданный элемент
}

/* Добавление элемента в стек (в начало) */
void push(void)
{
    struct node* p = NULL;
    p = get_struct();
    if (p != NULL)
    {
        p->next = head;
        head = p;
        dlinna++;
    }
    return;
}

/* Удаление элемента из стека (с начала) */
void pop(void)
{
    struct node* p = NULL;
    if (head == NULL)
    {
        printf("Стек пуст\n");
        return;
    }
    p = head;
    head = head->next;
    free(p);
    dlinna--;
    return;
}

/* Просмотр содержимого стека */
void review(void)
{
    struct node* struc = head;
    if (head == NULL)
    {
        printf("Стек пуст\n");
    }
    while (struc)
    {
        printf("Имя - %s\n", struc->inf);
        struc = struc->next;
    }
    return;
}

int main()
{

    setlocale(LC_ALL, "Rus");
    int choice;
    while (1)
    {
        printf("\n1. Добавить элемент в стек\n");
        printf("2. Удалить элемент из стека\n");
        printf("3. Просмотреть содержимое стека\n");
        printf("4. Выход\n");
        printf("Введите ваш выбор: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            push();
            break;
        case 2:
            pop();
            break;
        case 3:
            review();
            break;
        case 4:
            exit(0);
        default:
            printf("Неверный выбор. Попробуйте снова.\n");
        }
    }

    return 0;
}

