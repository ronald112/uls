NAME = libmx.a

CC = clang

INC = libmx.h

RAW = printchar print_unicode printstr print_strarr printint pow sqrt \
	nbr_to_hex hex_to_nbr itoa foreach binary_search bubble_sort quicksort \
	\
	strlen swap_char str_reverse strdel del_strarr get_char_index strdup \
	strndup strcpy strncpy strcmp strcat strstr get_substr_index count_substr \
	count_words strnew strtrim del_extra_spaces strsplit strjoin file_to_str \
	replace_substr \
	\
	memset memcpy memccpy memcmp memchr memrchr memmem memmove realloc \
	\
	create_node push_front push_back pop_front pop_back list_size sort_list \
	\
	atoi printerr \
	isalpha isdigit isspace islower isupper \
	\
	tolower toupper pow_for_mx_hex_to_nbr \
	strlen_for_mx_str_reverse isspace_forsplit strtrim_forsplit del_extra_spaces_forsplit \
	\
	open read_mod \
	\
	clear_list print_list swap_node printull add_del_str ltoa addchr \
	strjoin_to_dst_malloc

SRCD = src
OBJD = obj
COMPILE = $(CC) $(CFLAGS) -c -o $@ $< -Iinc
OBJ = $(addprefix obj/,$(addprefix mx_, $(addsuffix .o, $(RAW))))
CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic

all: install

install: $(OBJD) compile_lib

compile_lib: $(OBJ)
	@ar rcs $(NAME) $^ inc/$(INC)

$(OBJD):
	@mkdir -p $@

$(OBJD)/%.o: $(SRCD)/%.c $(addprefix inc/, $(INC))
	@$(COMPILE)

uninstall: clean
	@rm -rf $(NAME)

clean:
	@rm -rf $(OBJD)

reinstall: uninstall install
