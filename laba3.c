#include <stdlib.h>
#include <stdio.h>

struct stack
{
	char symbol;
	struct stack* next;
};
int priority(char a)
{
	switch (a)
	{
	case '*': case '/': return 3;
	case '+': case '-': return 2;
	case '(': return 1;
	}
	return 0;
}
struct stack* push(struct stack* head, char a)
{
	struct stack* point;
	if (!(point = (struct stack*)malloc(sizeof(struct stack)))) // выделяем память под новый элемент стека
	{
		printf("Error\n");
		exit(-1);
	}
	point->symbol = a; // записываем в стек символ
	point->next = head; // новая вершина стека
	return point; // возвращаем новую вершину стека
}

char pop(struct stack** head)
{
	struct stack* point;
	char a;
	if (*head == NULL) // если стек пуст
		return '\0';
	point = *head; // поинт указывает на вершину стека
	a = point->symbol; // запоминаем символ
	*head = point->next; // новая вершина стека
	free(point); // освобождаем память
	return a; // вазращаем симвод
}

int main()
{
	char* str, * out;
	struct stack* stack = NULL;
	int k, m, j = 0;
	do
	{
		puts("Введите выражениe: ");
		fflush(stdin);
		str = (char*)malloc(1);
		while ((str[j++] = getchar()) != '\n')
			str = (char*)realloc(str, j + 1);
		str[j - 1] = '\0';
		out = (char*)malloc(j);
		j = 0;
		k = m = 0;
		while (str[k] != '\0')
		{
			if (str[k] == ')')
			{
				while ((stack->symbol) != '(')
					out[m++] = pop(&stack);
				pop(&stack);
			}
			if (str[k] != '+' && str[k] != '-' && str[k] != '*' && str[k] != '/' && str[k] != '(' && str[k] != ')')
				out[m++] = str[k];
			if (str[k] == '(')
				stack = push(stack, str[k]);
			if (str[k] == '+' || str[k] == '-' || str[k] == '*' || str[k] == '/')
			{
				while ((stack != NULL) && (priority(stack->symbol) >= priority(str[k])))
					out[m++] = pop(&stack);
				stack = push(stack, str[k]);
			}
			k++;
		}
		while (stack)
			out[m++] = pop(&stack);
		out[m] = '\0';
		printf("%s\n", out);
		fflush(stdin);
		puts("Повторить? (y/n)");
	} while (getchar() == 'y');
}