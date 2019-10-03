#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main ()
{
	FILE *fp = fopen("input.txt", "r") ;

	char* line[100];
	char * string_ptr;
	char** input;
    FILE* inp = fopen(filename, "r");
	int m = 0;
	int n = 0;
	char ** input;
	char c;
	
	input = malloc(sizeof(char*)*9);
	input[0] = malloc(sizeof(char*)*9);
	while (!feof(inp)) {
		fscanf(inp, "%c", &c);
		if (c == ' ') {
			continue;
		}
		else if (c == '\n') {
			continue;
			n++;
			input[n] = malloc(sizeof(char*)*9);
		}
		else {
			intput[n][m] = c;
			m++;
		}
	}

	int size = 9;

 	fp = fopen("formula", "w") ;

	for (i = 1 ; i <= size ; i++)
		for (j = 1 ; j <= size ; j++)
			fprintf(fp, "(declare-const p%d%d Int)\n", i, j) ;

	//input
	fprintf(fp, "; input\n");
		for(i = 1 ; i < m ; i++)
			for(j = 1 ; j < m ; j++) {
				if(input[i][j] != '?' && input[i][j] != '*')
					fprintf(fp, "(assert (and (= p%d%d %c)))\n",  i, j, input[i][j]) ;
			}

	//cell
	fprintf(fp, "; cell\n") ;
		for (i = 1 ; i <= size ; i++)
			for (j = 1 ; j <= size ; j++)
				fprintf(fp, "(assert (and (> p%d%d 0) (< p%d%d 10)))\n", i, j, i, j) ;


	for(i = 1 ; i <= size ; i++) {
		for(j = 1 ; j <= size ; j++) {
			fprintf(fp,"(assert (not (and ");
			for(k = 1 ; k <= size ; k++) {
				fprintf(fp,"(= p%d%d %d) ", i,j,k);
			}
			fprintf(fp,")))\n");
		}
	}

	//row
	fprintf(fp, "; row\n") ;

	for(i = 1 ; i <= size ; i++) {
		for(j = 1 ; j < size ; j++) {
			fprintf(fp, "(assert (not (or ");
			for(k = j+1 ; k <= size ; k++) {
				fprintf(fp, "(= p%d%d p%d%d) ", i, j, i, k) ;
			}
			fprintf(fp, ")))\n");
		}
	}

	//column
	fprintf(fp, "; column\n") ;

	for(j = 1 ; j <= size ; j++) {
		for(i = 1 ; i < size ; i++) {
			fprintf(fp, "(assert (not (or ");
			for(k = i+1 ; k <= size ; k++) {
				fprintf(fp, "(= p%d%d p%d%d) ", i, j, k, j) ;
			}
			fprintf(fp, ")))\n");
		}
	}

	//subgrid
	//grid 1
	fprintf(fp,"; subgrid1\n");
	fprintf(fp, "(assert (not (or ");
  	for(i = 1 ; i <= 3 ; i++) {
		for(j = 1 ; j <= 3 ; j++) {
			for(k = 1 ; k <= 3 ; k++) {
				for(l = 1 ; l <= 3 ; l++) {
					if(((i!=k)||(j!=l))&&(i+j<=k+l))
						fprintf(fp, "(= p%d%d p%d%d) ", i, j, k, l) ;
				}
			}
		}
	}
	fprintf(fp, ")))\n");

	//grid 2
	fprintf(fp,"; subgrid2\n");
	fprintf(fp, "(assert (not (or ");
  	for(i = 1 ; i <= 3 ; i++) {
		for(j = 4 ; j <= 6 ; j++) {
			for(k = 1 ; k <= 3 ; k++) {
				for(l = 4 ; l <= 6 ; l++) {
					if(((i!=k)||(j!=l))&&(i+j<=k+l))
						fprintf(fp, "(= p%d%d p%d%d) ", i, j, k, l) ;
				}
			}
		}
	}
	fprintf(fp, ")))\n");

	//grid 3
	fprintf(fp,"; subgrid3\n");
	fprintf(fp, "(assert (not (or ");
  	for(i = 1 ; i <= 3 ; i++) {
		for(j = 7 ; j <= 9 ; j++) {
			for(k = 1 ; k <= 3 ; k++) {
				for(l = 7 ; l <= 9 ; l++) {
					if(((i!=k)||(j!=l))&&(i+j<=k+l))
						fprintf(fp, "(= p%d%d p%d%d) ", i, j, k, l) ;
				}
			}
		}
	}
	fprintf(fp, ")))\n");

	//grid 4
	fprintf(fp,"; subgrid4\n");
	fprintf(fp, "(assert (not (or ");
  	for(i = 4 ; i <= 6 ; i++) {
		for(j = 1 ; j <= 3 ; j++) {
			for(k = 4 ; k <= 6 ; k++) {
				for(l = 1 ; l <= 3 ; l++) {
					if(((i!=k)||(j!=l))&&(i+j<=k+l))
						fprintf(fp, "(= p%d%d p%d%d) ", i, j, k, l) ;
				}
			}
		}
	}
	fprintf(fp, ")))\n");

	//grid 5
	fprintf(fp,"; subgrid5\n");
	fprintf(fp, "(assert (not (or ");
  	for(i = 4 ; i <= 6 ; i++) {
		for(j = 4 ; j <= 6 ; j++) {
			for(k = 4 ; k <= 6 ; k++) {
				for(l = 4 ; l <= 6 ; l++) {
					if(((i!=k)||(j!=l))&&(i+j<=k+l))
						fprintf(fp, "(= p%d%d p%d%d) ", i, j, k, l) ;
				}
			}
		}
	}
	fprintf(fp, ")))\n");

	//grid 6
	fprintf(fp,"; subgrid6\n");
	fprintf(fp, "(assert (not (or ");
  	for(i = 4 ; i <= 6 ; i++) {
		for(j = 7 ; j <= 9 ; j++) {
			for(k = 4 ; k <= 6 ; k++) {
				for(l = 7 ; l <= 9 ; l++) {
					if(((i!=k)||(j!=l))&&(i+j<=k+l))
						fprintf(fp, "(= p%d%d p%d%d) ", i, j, k, l) ;
				}
			}
		}
	}
	fprintf(fp, ")))\n");

	//grid 7
	fprintf(fp,"; subgrid7\n");
	fprintf(fp, "(assert (not (or ");
  	for(i = 7 ; i <= 9 ; i++) {
		for(j = 1 ; j <= 3 ; j++) {
			for(k = 7 ; k <= 9 ; k++) {
				for(l = 1 ; l <= 3 ; l++) {
					if(((i!=k)||(j!=l))&&(i+j<=k+l))
						fprintf(fp, "(= p%d%d p%d%d) ", i, j, k, l) ;
				}
			}
		}
	}
	fprintf(fp, ")))\n");

	//grid 8
	fprintf(fp,"; subgrid8\n");
	fprintf(fp, "(assert (not (or ");
  	for(i = 7 ; i <= 9 ; i++) {
		for(j = 4 ; j <= 6 ; j++) {
			for(k = 7 ; k <= 9 ; k++) {
				for(l = 4 ; l <= 6 ; l++) {
					if(((i!=k)||(j!=l))&&(i+j<=k+l))
						fprintf(fp, "(= p%d%d p%d%d) ", i, j, k, l) ;
				}
			}
		}
	}
	fprintf(fp, ")))\n");

	//grid 9
	fprintf(fp,"; subgrid9\n");
	fprintf(fp, "(assert (not (or ");
  	for(i = 7 ; i <= 9 ; i++) {
		for(j = 7 ; j <= 9 ; j++) {
			for(k = 7 ; k <= 9 ; k++) {
				for(l = 7 ; l <= 9 ; l++) {
					if(((i!=k)||(j!=l))&&(i+j<=k+l))
						fprintf(fp, "(= p%d%d p%d%d) ", i, j, k, l) ;
				}
			}
		}
	}
	fprintf(fp, ")))\n");

	//asterisk
	char nums[9] ={0};
	int a = 0;
	for(i = 1 ; i < m ; i++) {
		for(j = 1 ; j < m ; j++) {
			if(input[i][j] == '*') {
				nums[a] = i*10 + j ;
				a++;
			}
		}
	}
	fprintf(fp,"; asterisk\n");
	for(i = 0; i < 9 ; i++) {
		for(j = i+1; j < 9 ; j++) {
			if(nums[j] != 0)
				fprintf(fp, "(assert (not (or (= p%d p%d) )))\n", nums[i], nums[j]);
		}
	}

	fprintf(fp, "(check-sat)\n(get-model)\n") ;

	fclose(fp) ;


	FILE * fin = popen("z3 formula", "r") ; //FIXME
	char b[128] ;
	char s[128] ;
	char t[128] ;
	char board[i][j];

	fscanf(fin, "%s %s", b, b) ;
	if (strcmp(b, "unsat")==0) {
  	printf("no solution\n");
    return 0;
  }
	for (k = 1 ; k <= 81 ; k++) {
		fscanf(fin, "%s %s %s %s %s", b, s, b, b, t) ;

		i = s[1] - '0' ;
		j = s[2] - '0' ;


		board[i][j] = atoi(t) ;

	}

	for (i = 1 ; i <= 9 ; i++) {
		for (j = 1 ; j <= 9 ; j++) {
			printf("%d ", board[i][j]) ;
		}
		printf("\n") ;
	}
	pclose(fin);
}
