#include "common.h"

int parse_file() {
    /* File: dim_stmt */
    parse_dim_list();
    /* should encounter end of file */
    get_lexeme();
    if (lex.type != LEX_EOF) {
        print_err("expected end of file.", NULL);
    }
}