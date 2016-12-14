#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAXNUM 1000000
#define MAXVAL 1000001

int arrnum[MAXNUM];
int endarr[MAXNUM];
int sernum[3][MAXNUM];
int sernum2[2][MAXNUM];
int pos[3];
int i, j, g, p, n;
int type;

int randnum(int n);
int wr2file(int arr[]);
int isplit(int arr[]);
int desplit(int arr[]);
int compare(int arr[][1000000]);
int decompare(int arr[][1000000]);
int merge(int arr[][1000000]);
int check(int arr[]);
int demerge(int arr[][1000000]);
int decheck(int arr[]);


int main()
{
	printf("Enter the n: ");
	scanf("%d", &n);
	printf("\n");
	randnum(n);
	wr2file(arrnum);
	for(j = 0; j < n; j++) {
		printf("%d ", arrnum[j]);
	}
	printf("\n");


	printf("Enter the type sort \n 1. increment \n 2. decrement \n $: ");
	scanf("%d", &type);
	switch (type) {
		case 1:
			do {	
			isplit(arrnum);
			compare(sernum);
			merge(sernum2);

			if (check(endarr) == 0) 
				break;

			for (i = 0; i < n; ++i) 
				arrnum[i] = endarr[i];

			//clean arrays
			memset(sernum, 0, sizeof(sernum)); 
			memset(sernum2, 0, sizeof(sernum2)); 
			memset(pos, 0, sizeof(pos));

			} while (check(endarr) == -1);
			break;
		case 2:
			do {	
			desplit(arrnum);
			decompare(sernum);
			demerge(sernum2);

			if (decheck(endarr) == 0) 
				break;

			for (i = 0; i < n; ++i) 
				arrnum[i] = endarr[i];

			//clean arrays
			memset(sernum, 0, sizeof(sernum)); 
			memset(sernum2, 0, sizeof(sernum2)); 
			memset(pos, 0, sizeof(pos));

			} while (decheck(endarr) == -1);
			break;
	}
	printf("\n");

	for (i = 0; i < 3; i++) {
		for (j = 0; j < n; j++) {
			printf("%d ", sernum[i][j]);
		}
		printf("\n");
	}
		printf("\n");

	for (i = 0; i < 2; i++) {
		for (j = 0; j < n; j++) {
			printf("%d ", sernum2[i][j]);
		}
			printf("\n");

	}
			printf("\n");

	printf("\n");
       	for (j = 0; j < n; j++) {
		printf("%d ", endarr[j]);
	}
	printf("\n");

	return 0;
}	


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



int compare(int arr[][1000000]) {
	int pos1[3]={0};
	int pos2[2]={0};

	i = 0;
	j = 1;
	g = 2;

	do {		
		i = (i < 3) ? i : 0; 
        	j = (j < 3) ? j : 0;
                g = (g < 3) ? g : 0;

		if (arr[i][pos1[i]] == 0) 
			arr[i][pos1[i]] = MAXVAL;
		if (arr[j][pos1[j]] == 0)
			arr[j][pos1[j]] = MAXVAL;
		if (arr[g][pos1[g]] == 0)
			arr[g][pos1[g]] = MAXVAL;
	
		if (arr[i][pos1[i]] == MAXVAL && arr[j][pos1[j]] == MAXVAL && arr[g][pos1[g]] == MAXVAL) //*
			break;

                if (arr[g][pos1[g]] <= arr[j][pos1[j]] && arr[j][pos1[j]] <= arr[i][pos1[i]]) {
			if (arr[i][pos1[i]] == MAXVAL && arr[j][pos1[j]] == MAXVAL && arr[g][pos1[g]] != MAXVAL) 
				sernum2[1][pos2[1]++] = arr[g][pos1[g]++];
			else
				sernum2[0][pos2[0]++] = arr[g][pos1[g]++];
		} else if (arr[i][pos1[i]] <= arr[j][pos1[j]] && arr[j][pos1[j]] <= arr[g][pos1[g]]) {
			if (arr[g][pos1[g]] == MAXVAL && arr[j][pos1[j]] == MAXVAL && arr[i][pos1[i]] != MAXVAL)
				sernum2[1][pos2[1]++] = arr[i][pos1[i]++];
			else
                        	sernum2[0][pos2[0]++] = arr[i][pos1[i]++];
 		} else {
                        ++i;
                        ++j;
                        ++g;
                }
	} while (arr[i][pos1[i]] != MAXVAL || arr[j][pos1[j]] != MAXVAL || arr[g][pos1[g]] != MAXVAL);

	for (i = 0; i < 3; ++i) {
		for (j = 0; j < n; ++j) {
			if (arr[i][j] == MAXVAL)	
				arr[i][j] = 0;
		}	
	}
	return 0;
}



int decompare(int arr[][1000000]) {
	int pos1[3]={0};
	int pos2[2]={0};

	i = 2;
	j = 1;
	g = 0;

	do {		
		i = (i < 3) ? i : 0; 
        	j = (j < 3) ? j : 0;
                g = (g < 3) ? g : 0;

		if (arr[i][pos1[i]] == 0 && arr[j][pos1[j]] == 0 && arr[g][pos1[g]] == 0) //*
			break;

                if (arr[g][pos1[g]] >= arr[j][pos1[j]] && arr[j][pos1[j]] >= arr[i][pos1[i]]) {
			if (arr[i][pos1[i]] == 0 && arr[j][pos1[j]] == 0 && arr[g][pos1[g]] != 0) 
				sernum2[1][pos2[1]++] = arr[g][pos1[g]++];
			else
				sernum2[0][pos2[0]++] = arr[g][pos1[g]++];
		} else if (arr[i][pos1[i]] >= arr[j][pos1[j]] && arr[j][pos1[j]] >= arr[g][pos1[g]]) {
			if (arr[g][pos1[g]] == 0 && arr[j][pos1[j]] == 0 && arr[i][pos1[i]] != 0)
				sernum2[1][pos2[1]++] = arr[i][pos1[i]++];
			else
                        	sernum2[0][pos2[0]++] = arr[i][pos1[i]++];
 		} else {
                        ++i;
                        ++j;
                        ++g;
                }
	} while (arr[i][pos1[i]] != 0 || arr[j][pos1[j]] != 0 || arr[g][pos1[g]] != 0);
	return 0;
}



int merge(int arr[][1000000]) {
	int j = 0;
	for (i = 0; i < n; ++i) {
		
		if (arr[0][i] <= arr[1][j] && arr[0][i] != 0) {
			endarr[i] = arr[0][i];
		}
		else {
			endarr[i] = arr[1][j];
			j++;
		}
	}
	return 0;	
}



int demerge(int arr[][1000000]) {
	int j = 0;
	for (i = 0; i < n; ++i) {
		
		if (arr[0][i] <= arr[1][j] && arr[0][i] != 0) {
			endarr[i] = arr[1][j];
			j++;
		}
		else {
			endarr[i] = arr[0][i];
		}
	}
	return 0;	
}



int check(int arr[]) {
	for (i = 1; i < n; ++i) 
		if (arr[i - 1] > arr[i])
			return -1;
	return 0;
}

int decheck(int arr[]) {
	for (i = 1; i < n; ++i) 
		if (arr[i - 1] < arr[i])
			return -1;
	return 0;
}
