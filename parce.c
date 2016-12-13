#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXNUM 100
#define MAXVAL 101

int arrnum[MAXNUM];
int file[10][MAXNUM];
int sernum[3][MAXNUM];
int sernum2[2][MAXNUM];
int pos[3];
int i, j, g, p, n;
char type;

int randnum(int n);
int wr2file(int arr[]);
int isplit(int arr[]);
int desplit(int arr[]);
int compare(int array[][100]);




int main()
{
	printf("Enter the n: ");
	scanf("%d", &n);
	printf("\n");
	randnum(n);
	wr2file(arrnum);

/*	printf("Enter the type sort (i or d): ");
	scanf("%s", type);
	switch (type) {
		case i:
		do {	*/
		isplit(arrnum);
//
	for (i = 0; i < 3; i++) {
		for(j = 0; j < n; j++) {
			printf("%d ", sernum[i][j]);
		}
		printf("\n");
//		printf("%d \n", pos[i]);
	}
	printf("\n");
//
		compare(sernum);
//
	for (i = 0; i < 2; i++) {
			for(j = 0; j < n; j++) {
			printf("%d ", sernum2[i][j]);
		}
		printf("\n");
//		printf("%d \n", pos[i]);
	}
	return 0;
} 
//		merge();
		
	


int randnum(int n) {
	srand(time(NULL));
	for (i = 0; i < n; ++i) {
		arrnum[i] = rand() % n + 1;
	}
	return 0;
}



int wr2file(int arr[]) {
	FILE *in;
	
	if ((in = fopen("arrnum","w+")) == NULL) 
		exit(1);		

	for (i = 0; i < n; ++i) {
		fprintf(in, "%d  %d\n", i, arr[i]);
	}
	fclose(in);

	return 0;
}



int isplit(int arr[]) {
	int p; 

	p = 0;
        sernum[p][pos[0]++] = arr[0];
 
        for (i = 1; i < n; ++i) {
                if (arr[i] < arr[i - 1])
                        ++p;
                p = (p < 3) ? p : 0;
                sernum[p][pos[p]++] = arr[i];
        }
	return 0;
}


int desplit(int arr[]) {
	int p; 

	p = 0;
        sernum[p][pos[0]++] = arr[0];
 
        for (i = 1; i < n; ++i) {
                if (arr[i] > arr[i - 1])
                        ++p;
                p = (p < 3) ? p : 0;
                sernum[p][pos[p]++] = arr[i];
        }
	return 0;
}



int compare(int arr[][100]) {
	int h;
	int pos1[3]={0};
	int pos2[2]={0};

	i = 0;
	j = 1;
	g = 2;

	for (h = 0; h < 101; ++h) {
		i = (i < 3) ? i : 0;
        	j = (j < 3) ? j : 0;
                g = (g < 3) ? g : 0;

		if (arr[i][pos1[i]] == 0) //switch
			arr[i][pos1[i]] = MAXVAL;
		if (arr[j][pos1[j]] == 0)
			arr[j][pos1[j]] = MAXVAL;
		if (arr[g][pos1[g]] == 0)
			arr[g][pos1[g]] = MAXVAL;
	
		if (arr[i][pos1[i]] == MAXVAL && arr[j][pos1[j]] == MAXVAL && arr[g][pos1[g]] != MAXVAL)
                        ++p;

		if (arr[i][pos1[i]] == MAXVAL && arr[j][pos1[j]] == MAXVAL && arr[g][pos1[g]] == MAXVAL)
			break;

                if (arr[g][pos1[g]] <= arr[j][pos1[j]] && arr[j][pos1[j]] <= arr[i][pos1[i]])
                         sernum2[p][pos2[p]++] = arr[g][pos1[g]++];
                else if (arr[i][pos1[i]] <= arr[j][pos1[j]] && arr[j][pos1[j]] <= arr[g][pos1[g]])
                         sernum2[p][pos2[p]++] = arr[i][pos1[i]++];
 
                else {
                        ++i;
                        ++j;
                        ++g;
                }
	}  
	return 0;
}
