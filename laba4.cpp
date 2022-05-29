#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

struct queue
{
	int* info;
	int first, last;
};

int init(struct queue*, int);
int entersize(int);
void enterqueue(struct queue*, int, int);
void unionqueue(struct queue*, struct queue*, struct queue*);
void printqueue(struct queue*);

int main()
{
	setlocale(LC_ALL, "ru");
	struct queue* q1, * q2, * q3;
	int n1, n2, n3;

	n1 = entersize(1);
	q1 = (struct queue*)malloc(sizeof(struct queue));
	if (init(q1, n1))
	{
		printf("Память не выделилась");
		return 1;
	}
	n2 = entersize(2);
	q2 = (struct queue*)malloc(sizeof(struct queue));
	if (init(q2, n2))
	{
		printf("Память не выделилась");
		return 1;
	}
	n3 = n2 + n1;
	q3 = (struct queue*)malloc(sizeof(struct queue));
	if (init(q3, n3))
	{
		printf("Память не выделилась");
		return 1;
	}
	system("cls");
	enterqueue(q1, n1, 1);
	printf("\n");
	enterqueue(q2, n2, 2);
	printf("\n");
	unionqueue(q1, q2, q3);
	printqueue(q3);
	return 0;
	free(q1);
	free(q2);
	free(q3);
}
int entersize(int a)
{
	int n;
	printf("Введите размерность %d очереди: ", a);
	do
	{
		printf("");
		rewind(stdin);
	} while (!scanf_s("%d", &n));

	return n;
}
int init(struct queue* q, int n)
{
	q->first = 1;
	q->last = 0;
	q->info = (int*)malloc(n * sizeof(int));
	if (!q->info)
		return 1;
	else
		return 0;
}
void enterqueue(struct queue* q, int n, int numqueue)
{
	int number;
	while (n--)
	{
		printf("Введите элемент %d очереди: ", numqueue);
		do
		{
			printf("");
			rewind(stdin);
		} while (!scanf_s("%d", &number));
		q->last++;
		q->info[q->last] = number;
	}
}
void unionqueue(struct queue* q1, struct queue* q2, struct queue* q3)
{
	q3->last++;
	while (q1->first <= q1->last && q2->first <= q2->last)
	{
		while (q1->first <= q1->last && q1->info[q1->first] < q2->info[q2->first])
			q3->info[q3->last++] = q1->info[q1->first++];
		if (q1->first > q1->last) break;
		while (q2->first <= q2->last && q1->info[q1->first] >= q2->info[q2->first])
			q3->info[q3->last++] = q2->info[q2->first++];
	}
	while (q1->first <= q1->last)
		q3->info[q3->last++] = q1->info[q1->first++];
	while (q2->first <= q2->last)
		q3->info[q3->last++] = q2->info[q2->first++];
	q1->first = 0; q2->first = 0;
}
void printqueue(struct queue* q)
{
	printf("Объединенная очередь: ");
	for (int i = q->first; i < q->last; i++)
		printf("%d ", q->info[i]);
}