NAME = uls

CC = clang

INC = inc/uls.h \
		libmx/inc/libmx.h \

INCL = libmx/inc inc \

FILES = mx_parse_flags mx_main mx_set_flags_false \
		mx_create_list_of_catalog mx_init_info mx_print_lflag \
		mx_get_full_path mx_ifl_true mx_get_permissions \
		mx_chk_xatr mx_add_links mx_add_usr mx_add_filesize \
		mx_add_lastchange_time mx_add_hardlink mx_print_totalsize \
		mx_add_minor_major mx_util mx_change_size_h mx_r_flag \
		mx_swap_cat mx_list_edit mx_util_swaps mx_swap_dirs \
		mx_print_R_start_point mx_print_default mx_counters \
		mx_get_name_dir mx_set_start_dir mx_get_valid mx_get_dirs \
		mx_func_for_R

LFLGS = -std=c11 -Wall -Wpedantic -Wextra -Werror# -g -fsanitize=address

CFLAGS = $(addprefix -I, $(INCL))

DEPS = $(INC)

LIBFILE = libmx/libmx.a

OBJD = obj

SRCD = src

OBJO = $(addprefix obj/, $(addsuffix .o, $(FILES)))

COMPILE = $(CC) $(LFLGS) -o $(NAME) $^ $(CFLAGS) $(LIBFILE)

all: install

install: $(LIBFILE) $(OBJD) compile

$(LIBFILE):
	@make -C libmx -f Makefile all

compile: $(OBJO)
	@$(COMPILE)

reinstall: uninstall all

uninstall: clean
	@make -C libmx -f Makefile uninstall
	@rm -rf $(NAME)

clean:
	@make -C libmx -f Makefile clean
	@rm -rf $(OBJD)

$(OBJD)/%.o: $(SRCD)/%.c $(DEPS)
	@$(CC) $(LFLGS) -c -o $@ $< $(CFLAGS)

$(OBJD):
	@mkdir -p $@
