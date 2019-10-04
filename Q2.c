#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** save(char file[], int* length, int w, int h);
void reset(char** line, char file2[], int size);
void logic (int w, int h, char** input);
char** input_set(char filename[],int* n, int* m);

int main(int argc, const char * argv[]) {
	char **line, ** input;//formula 저장, input 입력받을 용도
	int **output;//결과 저장용
	int size = 0;//-> w, h로 바꿔야함..!! 일단 멀티 하고
	int w, h;
	int length = 0;	//formula가 몇줄이나 저장됐는지
	int i, j, k;
	char buf[128];
	int x, y, z, flag;
	char *matrix = malloc(sizeof(char)*120);
	char *value = malloc(sizeof(char)*120);
	char *ptr_n = malloc(sizeof(char)*20);
	flag = 1;
	FILE* fp, *fin;
	char file_name[100];
	char* mid, *mid1, *mid2, *mid3, *mid4;
	printf("Enter file name!!");
	scanf("%s", file_name);

	input = input_set(file_name, &h, &w);
	printf("%d %d\n", w, h);
	for(i = 0; i<w; i++){
		for(j=0;j<h;j++)
			printf(" %c", input[i][j]);
		printf("\n");
	}
	logic (w, h, input); //로직 짜서 formula에 저장하는 역할
	int s = w*h*20;
	line = save("formula", &length, w, h); //처음 formula를 line에다가 저장하는 역할 여기서 length 받음

	output = malloc(sizeof(int*)*h);
	for(j =0; j<w; j++)
		output[j] = malloc(sizeof(int)*w);
														
	mid = malloc(sizeof(char) *200);
	mid1 = malloc(sizeof(char)*s);
	mid2 = malloc(sizeof(char)*s);
	mid3 = malloc(sizeof(char)*s);
	mid4 = malloc(sizeof(char)*s);
	strcpy(mid1, "\n(assert (or");
	strcpy(mid2, "\n(assert (or");
	strcpy(mid3, "\n(assert (or");
	strcpy(mid4, "\n(assert (or");
	
	for(int k=1; k<6; k++){
		if(k != 1)
			reset(line, "formula", length);
		fin = popen("z3 formula", "r") ;
		fscanf(fin, "%s %*s", buf);
		if(strcmp(buf, "unsat") != 0){
			for(i = 0; i<h*w; i++){
				fscanf(fin, " %*s %s %*s %*s %s", matrix, value);
				x = atoi(matrix+1);
				if(x < 10) y = atoi(matrix+3);
				else if(x < 100) y = atoi(matrix+4);
				else if(x < 1000) y = atoi(matrix+5);
				else y = atoi(matrix+6);
				z = atoi(value);
				output[y][x] = z;
			}
			fscanf(fin, "%*s");
			for(i = 0; i<h; i++){
				for(j=0; j<w; j++){
					printf("%d ", output[i][j]);
				}
				printf("\n");
			}
			printf("\n");
		}else if(k == 1){
			printf("no solution\n");
			flag = 0;
			break;
		}else{
			flag = 0;
			break;
		}
		char* l;
		if(k != 5){
			line[length] = malloc(sizeof(char)*s);
			for(int i = 0; i < h; i++){
				for(int j = 0; j < w; j++){
					sprintf(mid, " (not (= p%d-%d %d))", j,i, output[i][j]);
					if(k == 1)
						strcat(mid1, mid);
					else if(k == 2)
						strcat(mid2, mid);
					else if(k == 3)
						strcat(mid3, mid);
					else if(k == 4)
						strcat(mid4, mid);
				}
			}
			if(k == 1)
				strcat(mid1, "))");
			if(k == 2)
				strcat(mid2, "))");
			if(k == 3)
				strcat(mid3, "))");
			if(k == 4)
				strcat(mid4, "))");
			if(k == 1)
				line[length] = mid1;
			else if(k == 2)
				line[length] = mid2;
			else if(k == 3)
				line[length] = mid3;
			else if(k == 4)
				line[length] = mid4;

			length++;
			pclose(fin);
		}
	}
}

char** input_set(char filename[], int* n, int* m){
	FILE* inp = fopen(filename, "r");
	char* test = malloc(sizeof(char)*1000);
	char c;
	*n = 1;
	*m = 0;
	int m2 = 0;
	char ** input;
	input = malloc(sizeof(char*)*1000);

	while (!feof(inp)) {
		fscanf(inp, "%c", &c);
		if (c == ' ') {
			continue;
		}
		else if (c == '\n') {
			if(*n==1){
				if(m2 ==0)
					continue;
				*m = m2;
				input[0] = malloc(sizeof(char) * m2);
				for(int i =0; i< m2; i++){
					input[0][i] = test[i];
				}
				input[1] = malloc(sizeof(char) * m2);
				(*n)++;
				m2 = 0;
			}else{
				if(m2 ==0)
					continue;
				input[*n] = malloc(sizeof(char) * m2);
				(*n)++;
				m2 = 0;
			}
		}
		else {
			if(*n==1){
				test[m2] = c;
				m2++;
			}else{
				input[*n-1][m2] = c;
				m2++;
			}
		}
	}
	if(*n == 1){
		*m = m2;
		printf("%d", *m);
		input[0] = malloc(sizeof(char) * (*m));
		for(int i =0; i< *m; i++){
			input[0][i] = test[i];
		}
	}
	(*n)--;
	if(*m == 0)
		*n = 0;

	return input;
}


char** save(char file[], int* length, int w, int h){
	FILE *src = fopen(file, "r");
	char** line;
	size_t len;
	ssize_t read;
	int size = w*h*3 + 10;
	line = malloc(sizeof(char*)*size);
	line[0] = malloc(sizeof(char)*200);
	while((read = getline(&line[(*length)], &len, src)) != -1){
		(*length)++;
		line[(*length)] = malloc(sizeof(char)*2000);
	}
	free(line[(*length)]);
	fclose(src);
	
	return line;
}


void reset(char** line, char file2[], int size){
	char *ptr, *ptr2;
	FILE *dest = fopen(file2, "w");
	
	for(int i =0; i< size; i++){
		ptr = strstr(line[i], "(check-sat)");
		ptr2 = strstr(line[i], "(get-model)");
		if((ptr == NULL) && (ptr2 == NULL)){
			fprintf(dest, "%s", line[i]);
		}
	}
	fprintf(dest, "\n(check-sat)\n(get-model)\n");
	
	fclose(dest);
}


void logic (int w, int h, char** input){
	FILE* fp = fopen("formula", "w") ;
	int i, j;
	for (i = 0 ; i < h ; i++)
		for (j = 0 ; j < w ; j++)
			fprintf(fp, "(declare-const p%d-%d Int)\n", j, i);
	
	// Q1 -> 0,1중 하나
	fprintf(fp, "; Q1\n") ;
	for (i = 0 ; i < h ; i++) {
		for (j = 0 ; j < w ; j++) {
			fprintf(fp,"(assert (or (= p%d-%d 0) (= p%d-%d 1)))\n",j, i, j, i);
		}
	}
	if(h == 1){
		if(input[0][0] != '?')
			fprintf(fp,"(assert (= (+ p0-0 p1-0) %d))\n", input[0][0]);
		if(input[w-1][0] != '?')
			fprintf(fp,"(assert (= (+ p%d-0 p%d-0) %d))\n",w-1, w-2, input[w-1][0]);
		for(i = 1; i < w-1; i++){
			if(input[i][0] != '?'){
				fprintf(fp, "(assert (= %c (+", input[i][0]);
				for(j = i-1; j <= i+1; j++)
					fprintf(fp, " p%d-%d",j, 0);
				fprintf(fp, ")))\n") ;
			}
		}
	}
	else if(w == 1){
		if(input[0][0] != '?')
			fprintf(fp,"(assert (= (+ p0-0 p0-1) %d))\n", input[0][0]);
		if(input[0][h-1] != '?')
			fprintf(fp,"(assert (= (+ p0-%d p0-%d) %d))\n",h-1, h-2, input[0][h-1]);
		for(i = 1; i < h-1; i++){
			if(input[0][i] != '?'){
				fprintf(fp, "(assert (= %c (+", input[0][i]);
				for(j = i-1; j <= i+1; j++)
					fprintf(fp, " p%d-%d",0, j);
				fprintf(fp, ")))\n") ;
			}
		}
	}
	else{
		// Q2 -> 가운데
		fprintf(fp, "; Q2\n") ;
		for (int a = 1 ; a < h-1 ; a++) {
			for (int b = 1 ; b < w-1 ; b++) {
				if(input[a][b] != '?'){
					fprintf(fp, "(assert (= %c (+", input[a][b]);
					for(i = a-1; i <= a+1; i++)
						for(j = b-1; j <= b+1; j++)
							fprintf(fp, " p%d-%d",j, i);
					fprintf(fp, ")))\n") ;
				}
			}
		}

		// Q3 -> 위
		fprintf(fp, "; Q3\n") ;
		for (int b = 1 ; b < w-1 ; b++) {
			if(input[0][b] != '?'){
				fprintf(fp, "(assert (= %c (+", input[0][b]);
				for(i = 0; i <= 1; i++)
					for(j = b-1; j <= b+1; j++)
						fprintf(fp, " p%d-%d",j,i);
				fprintf(fp, ")))\n") ;
			}
		}

		// Q4 -> 아래
		fprintf(fp, "; Q4\n") ;
		for (int b = 1 ; b < w-1 ; b++) {
			if(input[h-1][b] != '?'){
				fprintf(fp, "(assert (= %c (+", input[h-1][b]);
				for(i = h-2; i <= h-1; i++)
					for(j = b-1; j <= b+1; j++)
						fprintf(fp, " p%d-%d",j,i);
				fprintf(fp, ")))\n") ;
			}
		}

		// Q5 -> 왼쪽
		fprintf(fp, "; Q5\n") ;
		for (int b = 1 ; b < h-1 ; b++) {
			if(input[b][0] != '?'){
				fprintf(fp, "(assert (= %c (+", input[b][0]);
				for(i = 0; i <= 1; i++)
					for(j = b-1; j <= b+1; j++)
						fprintf(fp, " p%d-%d",i,j);
				fprintf(fp, ")))\n") ;
			}
		}

		// Q6 -> 오른쪽
		fprintf(fp, "; Q6\n") ;
		for (int b = 1 ; b < h-1 ; b++) {
			if(input[b][w-1] != '?'){
				fprintf(fp, "(assert (= %c (+", input[b][w-1]);
				for(i = w-2; i <= w-1; i++)
					for(j = b-1; j <= b+1; j++)
						fprintf(fp, " p%d-%d",i,j);
				fprintf(fp, ")))\n") ;
			}
		}

		//Q7
		fprintf(fp, "; Q7\n") ;
		if(input[0][0] != '?'){
			fprintf(fp, "(assert (= %c (+", input[0][0]);
			fprintf(fp, " p%d-%d", 0, 0);
			fprintf(fp, " p%d-%d", 1, 0);
			fprintf(fp, " p%d-%d", 0, 1);
			fprintf(fp, " p%d-%d", 1, 1);
			fprintf(fp, ")))\n");
		}

		//오른쪽 위
		if(input[0][w-1] != '?'){
			fprintf(fp, "(assert (= %c (+", input[0][w-1]);
			fprintf(fp, " p%d-%d", w-1, 0);
			fprintf(fp, " p%d-%d", w-1, 1);
			fprintf(fp, " p%d-%d", w-2, 0);
			fprintf(fp, " p%d-%d", w-2, 1);
			fprintf(fp, ")))\n");
		}

		//왼쪽 아래
		if(input[h-1][0] != '?'){
			fprintf(fp, "(assert (= %c (+", input[h-1][0]);
			fprintf(fp, " p%d-%d", 0, h-1);
			fprintf(fp, " p%d-%d", 1, h-1);
			fprintf(fp, " p%d-%d", 0, h-2);
			fprintf(fp, " p%d-%d", 1, h-2);
			fprintf(fp, ")))\n");
		}
		//오른쪽 아래
		if(input[h-1][w-1] != '?'){
			fprintf(fp, "(assert (= %c (+", input[h-1][w-1]);
			fprintf(fp, " p%d-%d", h-1, w-1);
			fprintf(fp, " p%d-%d", h-1, w-2);
			fprintf(fp, " p%d-%d", h-2, w-1);
			fprintf(fp, " p%d-%d", h-2, w-2);
			fprintf(fp, ")))\n");
		}
	}
	fprintf(fp, "(check-sat)\n(get-model)");
	fclose(fp);
}
