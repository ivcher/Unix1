#include <stdio.h>

#define n 20
#define maxlen n*n
#define ERR_FORK 1
#define ERR_WRITE 2
#define USER_NUM 5

char SIMB_0 = ' ';
char SIMB_1 = '*';

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
void init_pole (char *pole)
{
	// начальная инициализация поля
	int fields_numbers[5] = {n+2, 2*n+3, 3*n+1, 3*n+2, 3*n+3}; // glider
	int arr_size = 5, i;
	for(i = 0; i< arr_size; i++)
	{
		pole[fields_numbers[i]] = 1;
	}
	//write_pole(arr1);	
}
void make_hod(char* old, char* new)
{
	int i,s,ind,j;
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
		{	
			s = sosedi(old,j,i);
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
	}
}
int main()
{	
	int user = 0;
	int pipe_user[USER_NUM][2];	
			
	do{
		int pid;
		pipe(pipe_user[user]);
		pid = fork();
	
		printf("my pid %d, fork return: %d\n", getpid(), pid);	

		if(pid == -1)
		{
			printf ("Error in fork().\n");
			exit(ERR_FORK);
		}
		if (pid == 0)
		{
			char user_pole[maxlen] = {0};
			int count = 0, hod = 0;
			char user_name = '0' + user; 
			char file_name[] = "userN";
			file_name[4] = user_name;			
			FILE *proc_file;
			close(pipe_user[user][1]);   // закрываем запись
			// дочерний процесс - получать матрицу 
			while(1)
			{
				if( (count = read(pipe_user[user][0], user_pole, maxlen) ) > 0 )
				{
					hod++;
					write_pole(user_pole);
						
					// проверяем,что потоки работают.
					proc_file = fopen(file_name, "wt" );
					fprintf(proc_file,"Hod number: %d. \n", hod);
					fclose(proc_file);				
				}
			}
		}
		user++;
	} while (user < USER_NUM);

	char arr1[maxlen] = {0}, arr2[maxlen] = {0};
	char *old_pole = arr1; 
	char *new_pole = arr2;
	char *tmp_pole;
	init_pole(old_pole);
	
	for(user = 0; user < USER_NUM; user++)
		close(pipe_user[user][0]); 
	// закрываем чтение
	// главный процесс - пересчитываем матрицу
	while (1)
	{
		make_hod(old_pole,new_pole);
		tmp_pole = new_pole;
		new_pole = old_pole;
		old_pole = tmp_pole;
		for(user = 0; user < USER_NUM; user++ )		
			if(write(pipe_user[user][1], (void * )old_pole, maxlen) < 0)
				exit(ERR_WRITE);
		sleep(1);
	}
}
