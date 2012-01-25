#include <stdio.h>

#define n 40
#define maxlen n*n
#define ERR_FORK 1
char arr1[maxlen] = {0};
char arr2[maxlen] = {0};
char user_pole[maxlen] = {0};
char SIMB_0 = ' ';
char SIMB_1 = '*';
//using namespace std;

void write_pole(char *pole)
{
	int i,j,ind;
	for(i = 0; i < n; i++ )
	{
		ind = i*n;
		for(j = 0; j < n; j++)
		{
			if(pole[ind+j])
			{
				printf( "%c", SIMB_1);
			}
			else
			{
				printf ("%c", SIMB_0);
			}
		}
		printf ("\n");
	}
	
	for(i = 0; i<n; i++)
	{
		printf ("=");
	}

	printf ("\n");
	// рисовать поле
}
int sosedi (char* pole, int x, int y)
{
	int i,j, sosed_num = 0 ;
		
	for (i = x-1; i <= x+1; i++)
	{
		if( i >= 0 && i < n )
		{
			for(j = y-1; j <= y+1; j++)
			{
				if (j >= 0 && j < n)
				{
					sosed_num += pole[j * n + i];
				}
	
			}

		}
	}
	sosed_num -= pole[y * n + x];
	return sosed_num;
}


void copy_to_user_pole(char *pole)
{
	int i = 0;
	for(i = 0; i < maxlen; i++)
	{
		user_pole[i] = pole[i];
	}
}

void init_pole ()
{
	// начальная инициализация поля
	int arr[5] = {n+2, 2*n+3, 3*n+1, 3*n+2, 3*n+3}; // glider
	int arr_size = 5, i;
	for(i = 0; i< arr_size; i++)
	{
		arr1[arr[i]] = 1;
	}
	write_pole(arr1);	
}
void make_hod(char* old, char* new)
{
	int i,s,ind,j;
	for(i = 0; i < n; i++)
	{
		for(j = 0; j< n; j++)
		{	
			s = sosedi(old,j,i);
//			printf ("%d ", s);
			ind = i * n + j;
			if ( (old[ind] == 1 && (s == 2 || s == 3) ) || ( old[ind] == 0 && s == 3))
			{
				new[ind] = 1;
			}
			else
			{
				new[ind] = 0;
			}
		}
//		printf("\n");
	}
}
int main()
{
	int hod_num = 0;
	int pid;
	char *old_pole = arr1;
	char *new_pole = arr2;
	char *tmp_pole;
	int game_continue = 1;
	
	init_pole();
//	pid = fork();
//	if(pid == -1)
//	{
//		printf ("Error in fork().\n");
//		exit(ERR_FORK);
//	}
//	if (pid == 0)
//	{
		// дочерний процесс - отдавать пользователю матрицу
//		write_pole();
//		sleep(1);
//		copy_to_user_pole(*old_pole);
//	}
//	else
//	{
		while (hod_num < 20)
		{
			make_hod(old_pole,new_pole);
			tmp_pole = new_pole;
			new_pole = old_pole;
			old_pole = tmp_pole;
///////////////
		
		sleep(1);
		write_pole(old_pole);

///////////////
			hod_num++;
		}
//	}
}
