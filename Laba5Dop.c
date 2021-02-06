#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

//Из введенного набора букв составить палиндром максимальной длины

#define Check_Symbol ( ( (a >= 'A') && (a <= 'Z') ) || ( (a >= 'a') && (a <= 'z') ) )

void print(unsigned char* m, int a, int b)
{
	for (int i = a; i <= b; i++)
	{
		printf("%c", m[i]);
	}

	printf("\n");
}
//Функция выводит слово

int create_letters_array(unsigned char *array)
{
	int a;
	int k = 0;
	int sizef = 1000;

	while (((a = getchar()) != '\n') && (a != EOF))
	{
		if (Check_Symbol)
		{
			if (k + 1 == sizef)
			{
				sizef += 2;

				array = (unsigned char*)realloc(array, sizef * sizeof(unsigned char));

				if (array == NULL)
				{
					printf("Memory not allocated.\n");
					return 0;
				}
			}
			array[k] = a;

			k++;
		}
	}
	sizef = k;

	return sizef;

}

void times_of_repeat(unsigned char* array, int** times, int size)
{
	int i;
	int j;

	for (i = 0; i < size; i++)
	{
		for (j = 0; j < 2; j++)
		{
			times[i][j] = 1;
		}
	}
	//Заполнение массива единицами
	for (i = 0; i < size; i++)
	{

		for (j = 0; j < size; j++)
		{
			if ((i != j) && (times[i][0] != 2))
			{
				if (array[i] == array[j])
				{
					times[i][0] = 1;

					times[j][0] = 2;

					times[i][1]++;
				}
			}
		}
	}
	//Сформирован массив с количеством повторений каждой буквы
}

void pal_size_check(int** t, int size, int *chet, int *max_nechet, int *max_index)
{
	int i;

	for (i = 0; i < size; i++)
	{
		if (t[i][0] == 1)
		{
			if (t[i][1] % 2 == 0)
			{
				*chet += t[i][1];
			}
			else
			{
				if (t[i][1] > *max_nechet)
				{
					*max_nechet = t[i][1];

					*max_index = i;
				}
			}
		}
	}
	//Подсчет переменных для нахождения размера палиндрома
}

void create_pal(unsigned char* let, int** t, unsigned char* pal, int size, int size_p, int max_index, int max_nechet)
{
	int j = 0;
	int z = size_p - 1;

	for (int i = 0; i < size; i++)
	{

		if (t[i][0] == 1)
		{
			if (t[i][1] % 2 == 0)
			{
				for (int count = 0; count < t[i][1] / 2; count++)
				{
					pal[j] = let[i];
					pal[z] = let[i];

					j++;
					z--;
				}
			}
			else if (i == max_index)
			{
				for (int count = size_p / 2 - max_nechet / 2; count <= size_p / 2 + max_nechet / 2; count++)
				{
					pal[count] = let[i];
				}
			}
		}
	}
	//Создание палиндрома
}
int main()
{
	int i = 0;

	int size = 1000;
	int size_p;

	unsigned char* let; //для букв

	unsigned char* pal; //для палиндрома

	int** t; //для количества повторений

	int chet = 0;
	int max_nechet = 0;
	int max_index = -1;

	let = (unsigned char*)calloc(size, sizeof(unsigned char));

	if (let == NULL)
	{
		printf("Memory not allocated.\n");

		free(let);

		return 0;
	}

	printf("Letters in palyndrome:\n");


	//Из введенной строки сформирован массив алфавита

	size = create_letters_array(let);

	if (size == 0)
	{
		printf("There is no letters to create palyndrome\n");
		free(let);
		return 0;
	}

	let = (unsigned char*)realloc(let, size * sizeof(unsigned char));

	t = (int**)calloc(size, sizeof(int*));

	if (t == NULL) 
	{
		printf("Memory not allocated.\n");

		free(let);
		free(t);

		return 0;
	}

	for (i = 0; i < size; i++)
	{
		t[i] = (int*)malloc(2 * sizeof(int));
	}

	if (let == NULL)
	{
		printf("Memory not allocated.\n");

		for (i = size - 1; i > 0; i--)
		{
			free(t[i]);
		}

		free(t);
		free(let);

		return 0;

	}

	times_of_repeat(let, t, size);

	pal_size_check(t, size, &chet, &max_nechet, &max_index);

	size_p = chet + max_nechet;

	printf("\nChet = %d\nmax_nechet = %d\nmax_index = %d\nSize = %d\nsize_p = %d\n", chet, max_nechet, max_index, size, size_p);

	pal = (unsigned char*)calloc(size_p, sizeof(unsigned char));

	if (pal == NULL)
	{
		printf("Memory not allocated.\n");

		for (i = size - 1; i > 0; i--)
		{
			free(t[i]);
		}

		free(t);
		free(let);
		free(pal);

		return 0;

	}

	create_pal(let, t, pal, size, size_p, max_index, max_nechet);

	printf("\nBiggest palyndrome:\n");

	print(pal, 0, size_p - 1);

	free(pal);
	//}
	

	free(let);

	for (i = size - 1; i > 0; i--)
	{
		free(t[i]);
	}

	free(t);

	return 0;
}
