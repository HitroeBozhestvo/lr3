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

struct node* head = NULL, * last = NULL; // указатели на первый и последний элементы списка

// Функции добавления элемента, просмотра списка
void enqueue(void);
void dequeue(void);
void review(void);

struct node* get_struct(void)
{
    struct node* p = NULL;
    char s[256];

    if ((p = (struct node*)malloc(sizeof(struct node))) == NULL)  // выделяем память под новый элемент списка
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

/* Добавление элемента в очередь (в конец) */
void enqueue(void)
{
    struct node* p = NULL;
    p = get_struct();
    if (head == NULL && p != NULL)// если очереди нет, то устанавливаем голову и хвост очереди
    {
        head = p;
        last = p;
    }
    else if (head != NULL && p != NULL) // очередь уже есть, то вставляем в конец
    {
        last->next = p;
        last = p;
    }
    return;
}

/* Удаление элемента из очереди (из начала) */
void dequeue(void)
{
    if (head == NULL) // если очередь пуста
    {
        printf("Очередь пуста\n");
        return;
    }

    struct node* temp = head;
    head = head->next; // устанавливаем голову на следующий элемент
    free(temp); // освобождаем память, выделенную для удаленного элемента

    if (head == NULL) // если после удаления очередь стала пустой
    {
        last = NULL; // обнуляем хвост очереди
    }

    return;
}

/* Просмотр содержимого очереди */
void review(void)
{
    struct node* struc = head;
    if (head == NULL)
    {
        printf("Очередь пуста\n");
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
        printf("\nОчередь:\n");
        printf("1. Добавить элемент\n");
        printf("2. Удалить элемент\n");
        printf("3. Просмотреть очередь\n");
        printf("4. Выход\n");
        printf("Выберите операцию: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            enqueue();
            break;
        case 2:
            dequeue();
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
