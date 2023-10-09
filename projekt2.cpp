#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ADD_LINES 128
#define ADD_CHARS 1024
#pragma warning(disable:4996)
FILE* fd;

void usun_znak(char** str, char znak) {
	char * dd1, * dd2;

	int i = 0;
	while (str[i] != (char*)0) {
		dd1 = str[i];
		int p = 0;
		while (*dd1) {
			if (*dd1 == znak) {
				dd2 = dd1;
				while (*dd2) {
					*dd2 = *(dd2 + 1);
					dd2++;
				}
				dd1--;
			}
			dd1++;
			p++;
		}
		i++;
	}
}

int main()
{
	char* windows[] = { -91, -58, -54, -93, -47, -45, -116, -113, -81, -71, -26, -22, -77, -15, -13, -100, -97, -65 };
	char* dos[] =	  { -92, -113, -88, -99, -29, -32, -105, -115, -67, -91, -122, -87, -120, -28, -94, -104, -85, -66 };

	char** d, c;
	int lines = 0, chars = 0, i;

	if (!(fd = fopen("input", "r")))
	{
		fprintf(stderr, "Blad otwarcia zbioru wejscia\n");
		exit(2);
	}
	
	d = malloc(sizeof(char*) * ADD_LINES);
	while (1)
	{
		c = fgetc(fd);

		if (ferror(fd)) {
			fprintf(stderr, "Blad czytania z pliku");
			exit(1);
		}

		if (feof(fd)) {
			if (chars) {
				d[lines] = realloc(d[lines], sizeof(char) * (chars + 1));
				d[lines][chars] = '\0';

				lines++;
			}
			
			break;
		}

		if (!chars)
			d[lines] = malloc(sizeof(char) * ADD_CHARS);

		d[lines][chars] = c;
		chars++;

		if (c == '\n') {
			d[lines] = realloc(d[lines], sizeof(char) * (chars + 1));
			d[lines][chars] = '\0';

			lines++;
			chars = 0;

			if (lines % 128 == 0)
				d = realloc(d, sizeof(char*) * (lines + ADD_LINES));

			else if (chars & 1024 == 0)
				d[lines] = realloc(d[lines], sizeof(char) * (chars + ADD_CHARS));
		}
	} 
	d = realloc(d, sizeof(char*) * lines);
	
	d[lines] = (char*)0;
	fclose(fd);
	fd = NULL;

	printf("[Tylko pierwszy wpisany znak jest brany pod uwage]\nPodaj znak: ");
	scanf("%c", &c);
	
	for (i = 0; i < 18; i++)
		if (c == dos[i])
			c = windows[i];

	usun_znak(d, c);

	if (!(fd = fopen("output.txt", "w")))
	{
		fprintf(stderr, "Blad otwarcia zbioru wyjscia\n");
		exit(3);
	}

	i = 0;
	while (d[i] != (char*)0) {
		fprintf(fd, "%s\n", d[i]);
		i++;
	}

	printf("%d\n%d", d[0][0], ' ');

	fclose(fd);
	fd = NULL;

	return 0;
}