#include <stdio.h>
#include <string.h>
int main()
{
	FILE* inp, * fp;
	inp = fopen("input.txt", "r");
	fp = fopen("formula", "w");
	char line[101];
	char c;
	int n = 1;
	int m = 1;
	int line_num = 0;
	int a = 0;
	int count = 1;
	int n_max = 0;
	int done = 0;
	while (!feof(inp)) {
		fscanf(inp, "%c", &c);
		if (c == '?') {
			count = 1;
			continue;
		}
		else if (c == ' ') {
			fprintf(fp, "(declare-const a%d-%d Int)\n", n, m);
			if (line_num != 0) {
				fprintf(fp, "(assert (= a%d-%d ", n, m);
				for (a = 0;a < line_num;a++) {
					fprintf(fp, "%c", line[a]);
				}
				fprintf(fp, "))\n");
				line_num = 0;
			}
			n++;
		}
		else if (c == '\n') {
			if (count == 0) {
				done = 1;
				break;
			}
			if (n_max < n)
				n_max = n;
			fprintf(fp, "(declare-const a%d-%d Int)\n", n, m);
			if (line_num != 0) {
				fprintf(fp, "(assert (= a%d-%d ", n, m);
				for (a = 0;a < line_num;a++) {
					fprintf(fp, "%c", line[a]);
				}
				fprintf(fp, "))\n");
				line_num = 0;
			}
			m++;
			count = 0;
			n = 1;
		}
		else {
			line[line_num] = c;
			line_num += 1;
			count = 1;
		}
		if (done == 1) {
			break;
		}
	}
	n = n_max;
	m--;

	int x, y;
	int max = n * m;

	fprintf(fp, "\n;Q1\n");
	for (x = 1; x <= n; x++)
		for (y = 1; y <= m; y++)
			fprintf(fp, "(assert (and (<= a%d-%d %d) (<= 1 a%d-%d)))\n", x, y, max, x, y);

	fprintf(fp, "\n;Q2\n");
	// difference
	int p_x, p_y;
	for (x = 1; x <= n; x++)
		for (y = 1; y <= m; y++)
			for (p_x = 1;p_x <= n;p_x++)
				for (p_y = 1;p_y <= m;p_y++) {
					if (x * 10 + y >= p_x * 10 + p_y)
						continue;
					fprintf(fp, "(assert (not (= a%d-%d a%d-%d)))\n", x, y, p_x, p_y);
				}

	fprintf(fp, "\n;Q3\n");
	//for corner point
	if ((n > 1) && (m > 1)) {
		for (x = 1; x <= n; x += n - 1) {
			for (y = 1; y <= m; y += m - 1) {
				fprintf(fp, "(assert (=> (and (not(= ");
				fprintf(fp, "a%d-%d 1)) (not(= a%d-%d %d))) ", x, y, x, y, max);
				fprintf(fp, "(or (and (= (- ");
				if ((x == 1) && (y == 1)) {
					fprintf(fp, "a%d-%d a%d-%d) 1) (= (- a%d-%d a%d-%d) 1)) (and (= (- a%d-%d a%d-%d) 1) (= (- a%d-%d a%d-%d) 1)))))\n", x, y + 1, x, y, x, y, x + 1, y, x + 1, y, x, y, x, y, x, y + 1);
				}
				else if (x == 1) {
					fprintf(fp, "a%d-%d a%d-%d) 1) (= (- a%d-%d a%d-%d) 1)) (and (= (- a%d-%d a%d-%d) 1) (= (- a%d-%d a%d-%d) 1)))))\n", x, y - 1, x, y, x, y, x + 1, y, x + 1, y, x, y, x, y, x, y - 1);
				}
				else if (y == 1) {
					fprintf(fp, "a%d-%d a%d-%d) 1) (= (- a%d-%d a%d-%d) 1)) (and (= (- a%d-%d a%d-%d) 1) (= (- a%d-%d a%d-%d) 1)))))\n", x, y + 1, x, y, x, y, x - 1, y, x - 1, y, x, y, x, y, x, y + 1);
				}
				else {
					fprintf(fp, "a%d-%d a%d-%d) 1) (= (- a%d-%d a%d-%d) 1)) (and (= (- a%d-%d a%d-%d) 1) (= (- a%d-%d a%d-%d) 1)))))\n", x, y - 1, x, y, x, y, x - 1, y, x - 1, y, x, y, x, y, x, y - 1);
				}
			}
		}
	}
	fprintf(fp, "\n;Q4\n");
	//for line point xline
	x = 1;
	if((n==1)&&(m!=1))
	fprintf(fp, "(assert (or (= a1-1 1) (= a1-1 %d)))\n", max);
	for (y = 2;y < m;y++) {
		fprintf(fp, "(assert (=> (and (not(= a%d-%d 1)) (not(= a%d-%d %d))) (or ", x, y, x, y, max);
		fprintf(fp, "(and (= (- a%d-%d a%d-%d) 1) (= (- a%d-%d a%d-%d) 1)) ", x, y - 1, x, y, x, y, x, y + 1);
		if (n != 1) {
			fprintf(fp, "(and (= (- a%d-%d a%d-%d) 1) (= (- a%d-%d a%d-%d) 1)) ", x, y - 1, x, y, x, y, x + 1, y);
			fprintf(fp, "(and (= (- a%d-%d a%d-%d) 1) (= (- a%d-%d a%d-%d) 1)) ", x + 1, y, x, y, x, y, x, y - 1);
			fprintf(fp, "(and (= (- a%d-%d a%d-%d) 1) (= (- a%d-%d a%d-%d) 1)) ", x + 1, y, x, y, x, y, x, y - 1);
			fprintf(fp, "(and (= (- a%d-%d a%d-%d) 1) (= (- a%d-%d a%d-%d) 1)) ", x, y + 1, x, y, x, y, x + 1, y);
		}
		fprintf(fp, "(and (= (- a%d-%d a%d-%d) 1) (= (- a%d-%d a%d-%d) 1)))))\n", x, y + 1, x, y, x, y, x, y - 1);
	}
	if (n != 1) {
		x = n;
		for (y = 2;y < m;y++) {
			fprintf(fp, "(assert (=> (and (not(= a%d-%d 1)) (not(= a%d-%d %d))) (or ", x, y, x, y, max);
			fprintf(fp, "(and (= (- a%d-%d a%d-%d) 1) (= (- a%d-%d a%d-%d) 1)) ", x, y - 1, x, y, x, y, x - 1, y);
			fprintf(fp, "(and (= (- a%d-%d a%d-%d) 1) (= (- a%d-%d a%d-%d) 1)) ", x, y - 1, x, y, x, y, x, y + 1);
			fprintf(fp, "(and (= (- a%d-%d a%d-%d) 1) (= (- a%d-%d a%d-%d) 1)) ", x, y + 1, x, y, x, y, x - 1, y);
			fprintf(fp, "(and (= (- a%d-%d a%d-%d) 1) (= (- a%d-%d a%d-%d) 1)) ", x, y + 1, x, y, x, y, x, y - 1);
			fprintf(fp, "(and (= (- a%d-%d a%d-%d) 1) (= (- a%d-%d a%d-%d) 1)) ", x - 1, y, x, y, x, y, x, y + 1);
			fprintf(fp, "(and (= (- a%d-%d a%d-%d) 1) (= (- a%d-%d a%d-%d) 1)))))\n", x - 1, y, x, y, x, y, x, y - 1);
		}
	}
	fprintf(fp, "\n;Q5\n");
	//for line point yline
	y = 1;
	if((m==1)&&(n!=1))
	fprintf(fp, "(assert (or (= a1-1 1) (= a1-1 %d)))\n", max);
	for (x = 2;x < n;x++) {
		fprintf(fp, "(assert (=> (and (not(= a%d-%d 1)) (not(= a%d-%d %d))) (or ", x, y, x, y, max);
		fprintf(fp, "(and (= (- a%d-%d a%d-%d) 1) (= (- a%d-%d a%d-%d) 1)) ", x + 1, y, x, y, x, y, x - 1, y);
		if (m != 1) {
			fprintf(fp, "(and (= (- a%d-%d a%d-%d) 1) (= (- a%d-%d a%d-%d) 1)) ", x + 1, y, x, y, x, y, x, y + 1);
			fprintf(fp, "(and (= (- a%d-%d a%d-%d) 1) (= (- a%d-%d a%d-%d) 1)) ", x, y + 1, x, y, x, y, x + 1, y);
			fprintf(fp, "(and (= (- a%d-%d a%d-%d) 1) (= (- a%d-%d a%d-%d) 1)) ", x, y + 1, x, y, x, y, x - 1, y);
			fprintf(fp, "(and (= (- a%d-%d a%d-%d) 1) (= (- a%d-%d a%d-%d) 1)) ", x - 1, y, x, y, x, y, x, y + 1);
		}
		fprintf(fp, "(and (= (- a%d-%d a%d-%d) 1) (= (- a%d-%d a%d-%d) 1)))))\n", x - 1, y, x, y, x, y, x + 1, y);
	}
	if (m != 1) {
		y = m;
		for (x = 2;x < n;x++) {
			fprintf(fp, "(assert (=> (and (not(= a%d-%d 1)) (not(= a%d-%d %d))) (or ", x, y, x, y, max);
			fprintf(fp, "(and (= (- a%d-%d a%d-%d) 1) (= (- a%d-%d a%d-%d) 1)) ", x + 1, y, x, y, x, y, x - 1, y);
			fprintf(fp, "(and (= (- a%d-%d a%d-%d) 1) (= (- a%d-%d a%d-%d) 1)) ", x + 1, y, x, y, x, y, x, y - 1);
			fprintf(fp, "(and (= (- a%d-%d a%d-%d) 1) (= (- a%d-%d a%d-%d) 1)) ", x, y - 1, x, y, x, y, x + 1, y);
			fprintf(fp, "(and (= (- a%d-%d a%d-%d) 1) (= (- a%d-%d a%d-%d) 1)) ", x, y - 1, x, y, x, y, x - 1, y);
			fprintf(fp, "(and (= (- a%d-%d a%d-%d) 1) (= (- a%d-%d a%d-%d) 1)) ", x - 1, y, x, y, x, y, x + 1, y);
			fprintf(fp, "(and (= (- a%d-%d a%d-%d) 1) (= (- a%d-%d a%d-%d) 1)))))\n", x - 1, y, x, y, x, y, x, y - 1);
		}
	}
	fprintf(fp, "\n;Q6\n");
	for (x = 2; x < n; x++) {
		for (y = 2;y < m;y++) {
			fprintf(fp, "(assert (=> (and (not(= a%d-%d 1)) (not(= a%d-%d %d))) (or ", x, y, x, y, max);
			fprintf(fp, "(and (= (- a%d-%d a%d-%d) 1) (= (- a%d-%d a%d-%d) 1)) ", x + 1, y, x, y, x, y, x - 1, y);
			fprintf(fp, "(and (= (- a%d-%d a%d-%d) 1) (= (- a%d-%d a%d-%d) 1)) ", x + 1, y, x, y, x, y, x, y + 1);
			fprintf(fp, "(and (= (- a%d-%d a%d-%d) 1) (= (- a%d-%d a%d-%d) 1)) ", x + 1, y, x, y, x, y, x, y - 1);
			fprintf(fp, "(and (= (- a%d-%d a%d-%d) 1) (= (- a%d-%d a%d-%d) 1)) ", x, y + 1, x, y, x, y, x + 1, y);
			fprintf(fp, "(and (= (- a%d-%d a%d-%d) 1) (= (- a%d-%d a%d-%d) 1)) ", x, y + 1, x, y, x, y, x - 1, y);
			fprintf(fp, "(and (= (- a%d-%d a%d-%d) 1) (= (- a%d-%d a%d-%d) 1)) ", x, y + 1, x, y, x, y, x, y - 1);
			fprintf(fp, "(and (= (- a%d-%d a%d-%d) 1) (= (- a%d-%d a%d-%d) 1)) ", x - 1, y, x, y, x, y, x + 1, y);
			fprintf(fp, "(and (= (- a%d-%d a%d-%d) 1) (= (- a%d-%d a%d-%d) 1)) ", x - 1, y, x, y, x, y, x, y - 1);
			fprintf(fp, "(and (= (- a%d-%d a%d-%d) 1) (= (- a%d-%d a%d-%d) 1)) ", x - 1, y, x, y, x, y, x, y + 1);
			fprintf(fp, "(and (= (- a%d-%d a%d-%d) 1) (= (- a%d-%d a%d-%d) 1)) ", x, y - 1, x, y, x, y, x, y + 1);
			fprintf(fp, "(and (= (- a%d-%d a%d-%d) 1) (= (- a%d-%d a%d-%d) 1)) ", x, y - 1, x, y, x, y, x + 1, y);
			fprintf(fp, "(and (= (- a%d-%d a%d-%d) 1) (= (- a%d-%d a%d-%d) 1)))))\n ", x, y - 1, x, y, x, y, x - 1, y);
		}
	}
	fprintf(fp, "(check-sat)\n(get-model)\n");

	fclose(fp);

	FILE* fin = popen("z3 formula", "r"); //FIXME
	char buf[128];
	char buf1[128];
	fscanf(fin, "%s %s", buf1, buf);

	if (strcmp(buf1, "unsat") == 0) {
		printf("no solution\n");
		return 0;
	}
	int value = 0; // value
	char save[128];         // keeping array
	int board[n][m];
	char* p;
	int smax;
	while (!feof(fin)) {
		fscanf(fin, "%s", buf);
		if (strcmp(buf, "(define-fun") != 0) break;
		fscanf(fin, "%s", save);
		fscanf(fin, "%s", buf);
		fscanf(fin, "%s", buf);
		fscanf(fin, "%d", &value);
		fscanf(fin, "%s", buf);

		smax = strlen(save);

		for (int i = 0; i < smax - 1; i++) {
			save[i] = save[i + 1];
		}
		p = strtok(save, "-");
		if (p != NULL) {
			x = *p - '0';
			p = strtok(NULL, "-");
			y = *p - '0';
		}
		board[x][y] = value;
	}
	for (y = 1; y <= m; y++) {
		for (x = 1; x <= n; x++) {
			if (max < 10)printf("%1d ", board[x][y]);
			else if (max < 100)printf("%2d ", board[x][y]);
			else if (max < 1000)printf("%3d ", board[x][y]);
			else if (max < 10000)printf("%4d ", board[x][y]);
			else if (max < 100000)printf("%5d ", board[x][y]);
		}
		printf("\n");
	}
	pclose(fin);
}
