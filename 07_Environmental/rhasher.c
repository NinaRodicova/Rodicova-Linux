#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rhash.h"
#include <errno.h>

#ifdef USE_READLINE
#include <readline/readline.h>
#include <readline/history.h>
#endif

char *my_read(void) {
	#ifdef USE_READLINE
		char *s = readline("");
		if (s && *s) {
			add_history(s);
		}
		return s;
	#else
		char *s = NULL;
		size_t n = 0;
		if (getline(&s, &n, stdin) == -1) {
			free(s);
			return NULL;
		}
		return s;
	#endif
}
	
int
get_hash_type(const char *name) {
    if (strcmp(name, "MD5") == 0 |strcmp(name, "md5") == 0) return RHASH_MD5;
    if (strcmp(name, "SHA1") == 0 || strcmp(name, "sha1") == 0) return RHASH_SHA1;
    if (strcmp(name, "TTH") == 0 || strcmp(name, "tth") == 0) return RHASH_TTH;
    return -1;
}
int
main()
{
	rhash_library_init();
	printf("> ");
	while (1) {
		char *s = my_read();
		if (s == NULL)
			return 0;
		if (strlen(s) == 1 || strlen(s) == 0) {
			printf("> ");
			continue;
		}
		char *word1 = NULL;
		char *word2 = NULL;

		char *t = strtok(s, " \n");
		if (t)
			word1 = t;
		t = strtok(NULL, " \n");
		if (t)
			word2 = t;
		if (word1 == NULL || word2 == NULL || strlen(word1) == 0 || strlen(word2) == 0) {
			fprintf(stderr, "Error: Bad arguments");
            printf("> ");
            free(s);
            continue;
		}
		int hash_type = get_hash_type(word1);
		if (hash_type == -1) {
            fprintf(stderr, "Error: unknown command '%s'\n", word1);
            printf("> ");
            free(s);
            continue;
        }
        int out_flags;
        if (word1[0] == 'M' || word1[0] == 'S' || word1[0] == 'T')
			out_flags = RHPR_HEX;
		else
			out_flags = RHPR_BASE64;
	
		unsigned char digest[64];
        char output[130];
        int res;
        
        if (word2[0] == '"') {
			size_t n2 = strlen(word2);
            const char *str = word2 + 1;
            res = rhash_msg(hash_type, str, n2 - 2, digest);
        } else {
            res = rhash_file(hash_type, word2, digest);
        }
        if (res < 0) {
            fprintf(stderr, "Error: %s: %s\n", word2, strerror(errno));
            printf("> ");
            free(s);
            continue;
        }

        rhash_print_bytes(output, digest, rhash_get_digest_size(hash_type), out_flags);
        printf("%s\n", output);
        printf("> ");
        free(s);
	}
	return 0;
}

