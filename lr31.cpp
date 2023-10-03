#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Структура для представления элемента очереди
typedef struct {
    char* data;
    int priority;
} QueueElement;

// Структура для представления приоритетной очереди
typedef struct {
    QueueElement* elements;
    int maxSize;
    int currentSize;
} PriorityQueue;

// Функция для создания приоритетной очереди
PriorityQueue* createPriorityQueue(int maxSize) {
    PriorityQueue* queue = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    queue->elements = (QueueElement*)malloc(maxSize * sizeof(QueueElement));
    queue->maxSize = maxSize;
    queue->currentSize = 0;
    return queue;
}

// Функция для проверки, является ли очередь пустой
int isEmpty(PriorityQueue* queue) {
    return queue->currentSize == 0;
}

// Функция для проверки, является ли очередь полной
int isFull(PriorityQueue* queue) {
    return queue->currentSize == queue->maxSize;
}

// Функция для добавления элемента в приоритетную очередь
void enqueue(PriorityQueue* queue, char* data, int priority) {
    if (isFull(queue)) {
        printf("Очередь полна. Невозможно добавить элемент.\n");
        return;
    }

    QueueElement newElement;
    newElement.data = (char*)malloc((strlen(data) + 1) * sizeof(char));
    strcpy(newElement.data, data);
    newElement.priority = priority;

    int i;
    for (i = queue->currentSize - 1; i >= 0; i--) {
        if (queue->elements[i].priority > newElement.priority) {
            queue->elements[i + 1] = queue->elements[i];
        }
        else {
            break;
        }
    }

    queue->elements[i + 1] = newElement;
    queue->currentSize++;
}

// Функция для удаления элемента из приоритетной очереди
void dequeue(PriorityQueue* queue) {
    if (isEmpty(queue)) {
        printf("Очередь пуста. Невозможно удалить элемент.\n");
        return;
    }

    printf("Удален элемент с данными: %s\n", queue->elements[0].data);

    free(queue->elements[0].data);

    int i;
    for (i = 0; i < queue->currentSize - 1; i++) {
        queue->elements[i] = queue->elements[i + 1];
    }

    queue->currentSize--;
}

// Функция для вывода элементов приоритетной очереди
void printPriorityQueue(PriorityQueue* queue) {
    if (isEmpty(queue)) {
        printf("Очередь пуста.\n");
        return;
    }

    printf("Элементы приоритетной очереди:\n");
    for (int i = 0; i < queue->currentSize; i++) {
        printf("Данные: %s, Приоритет: %d\n", queue->elements[i].data, queue->elements[i].priority);
    }
}

// Функция для освобождения памяти, занятой приоритетной очередью
void freePriorityQueue(PriorityQueue* queue) {
    for (int i = 0; i < queue->currentSize; i++) {
        free(queue->elements[i].data);
    }
    free(queue->elements);
    free(queue);
}

int main() {
    setlocale(LC_ALL, "Rus");
    int maxSize;
    printf("Введите максимальный размер приоритетной очереди: ");
    scanf("%d", &maxSize);

    PriorityQueue* queue = createPriorityQueue(maxSize);

    int choice;
    char data[100];
    int priority;

    while (1) {
        printf("\n1. Добавить элемент в очередь\n");
        printf("2. Удалить элемент из очереди\n");
        printf("3. Вывести элементы очереди\n");
        printf("4. Выход\n");
        printf("Выберите действие: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Введите данные элемента: ");
            scanf("%s", data);
            printf("Введите приоритет элемента: ");
            scanf("%d", &priority);
            enqueue(queue, data, priority);
            break;
        case 2:
            dequeue(queue);
            break;
        case 3:
            printPriorityQueue(queue);
            break;
        case 4:
            freePriorityQueue(queue);
            return 0;
        default:
            printf("Неверный выбор. Попробуйте снова.\n");
        }
    }
}
