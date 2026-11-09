#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <libintl.h>
#include <config.h>

#define _(String) gettext(String)

int main()
{
	setlocale(LC_ALL, "");
	bindtextdomain(PACKAGE, LOCALEDIR);
	textdomain(PACKAGE);

	char *s = NULL;
	size_t n = 0;
	printf(_("Pick a number from 1 to 100\n"));
	int a = 1;
	int b = 100;
	while (1) {
		int c = (a + b) / 2;
		printf(_("This number is greater than %d?\n"), c);
		if (getline(&s, &n, stdin) == -1) {
			fprintf(stderr, _("Error!\n"));
			if (feof(stdin)) {
				clearerr(stdin);
				continue;
			} else
				break;
		}
		if (strcmp(s, _("Yes\n")) == 0) {
			if ((b - a == 1) || (b - c == 1)) {
				printf(_("Your number: %d\n"), b);
				break;
			}
			a = c;
		}
		else if (strcmp(s, _("No\n")) == 0) {
			if (b - a == 1) {
				printf(_("Your number: %d\n"), a);
				break;
			}
			b = c;
		}
		else {
			fprintf(stderr, _("Error!\n"));
		}
		if (a == b) {
			printf(_("Your number: %d\n"), a);
			break;
		}
	}
	free(s);
	return 0;
}
