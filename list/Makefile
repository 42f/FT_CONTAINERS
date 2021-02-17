EOC = \033[0m
BOLD = \033[1m
GREEN = \033[32m
YELLOW = \033[33m

NAME := ft_container_list
INCLUDES = ./includes
SRCS_DIR = ./srcs
CC = clang++
OBJ_DIR = ./objs_$(NAME)/

CFLAGS += -std=c++98
CFLAGS += -g3
CFLAGS += -Wall
CFLAGS += -Wextra
# CFLAGS += -fPIC

ifeq ($(noassert), 1)
	CFLAGS += -DNDEBUG=1
endif

ifeq ($(print_all), 1)
	CFLAGS += -D NOPRINT=1
else
	CFLAGS += -D NOPRINT=0
endif

ifeq ($(unused), 1)
	CFLAGS += -Wno-unused
endif

ifeq ($(help), 1)
	CFLAGS += -Wconversion
else ifeq ($(help), 2)
	CFLAGS += -Wsuggest-attribute=pure
else ifeq ($(help), 3)
	CFLAGS += -Wsuggest-attribute=const
else ifeq ($(help), 4)
	CFLAGS += -Wsuggest-attribute=noreturn
else ifeq ($(help), 5)
	CFLAGS += -fsanitize-undefined-trap-on-error
else ifneq ($(no_error), 1)
	CFLAGS += -Werror
endif

ifeq ($(debug), 1)
	CFLAGS += -g3
else ifeq ($(debug), 2)
	CFLAGS += -fsanitize=address,undefined
	CFLAGS += -g3
else ifeq ($(debug), 3)
	CFLAGS += -fsanitize=address,undefined
	CFLAGS += -g3
	CFLAGS += -Wpadded
else ifeq ($(debug), 4)
	CFLAGS += -fsanitize=address,undefined
	CFLAGS += -g3
	CFLAGS += -Wpadded
	ifneq ($(CC), gcc)
		CFLAGS += -Weverything
	endif
endif

ifeq ($(opti), 1)
	CFLAGS += -O3
endif

ifeq ($(debug_mode), 1)
	CFLAGS += -D DEBUG_MODE=1
else ifeq ($(debug_mode), 2)
	CFLAGS += -D DEBUG_MODE=2
else ifeq ($(debug_mode), 3)
	CFLAGS += -D DEBUG_MODE=3
else ifeq ($(debug_mode), 4)
	CFLAGS += -D DEBUG_MODE=4
endif

HEADER += ./list.hpp
HEADER += ./bvaletteTester.hpp

SRCS += ./main.cpp
SRCS += ./main_tester_list.cpp
SRCS += ./test_list_instantiation.cpp
SRCS += ./test_list_push_back_push_front_pop_back_pop_front.cpp
SRCS += ./test_list_clear.cpp
SRCS += ./test_list_capacities.cpp
SRCS += ./test_list_insert_erase.cpp
SRCS += ./test_list_operatorEqual.cpp
SRCS += ./test_list_resize.cpp
SRCS += ./test_list_assign.cpp
SRCS += ./test_list_member_swap.cpp
SRCS += ./test_list_nonmember_swap.cpp
SRCS += ./test_list_relational_operators.cpp
SRCS += ./test_list_splice.cpp
SRCS += ./test_list_remove_if.cpp
SRCS += ./test_list_remove.cpp
SRCS += ./test_list_unique.cpp
SRCS += ./test_list_merge.cpp
SRCS += ./test_list_sort.cpp
SRCS += ./test_list_iterator.cpp
SRCS += ./test_list_reverseIterator.cpp
SRCS += ./test_list_reverse.cpp
SRCS += ./test_list_element_access.cpp

vpath %.cpp ./srcs
vpath %.cpp ./srcs/list_tests
vpath %.hpp ./includes

OBJS = $(patsubst %.cpp, $(OBJ_DIR)%.o, $(SRCS))

all :
	$(MAKE) $(NAME)
	@echo
	@echo

$(OBJS): $(OBJ_DIR)%.o: %.cpp $(HEADER)
	$(CC) $(CFLAGS) -c $<  -I $(INCLUDES) -o $@

$(NAME): $(OBJ_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -I$(INCLUDES) -o $@
	@echo "🎉 \033[32m$@ is ready !\033[0m ✅"

$(OBJ_DIR):
	@mkdir -p $@

FORCE :

clean :
	$(RM) -R $(OBJ_DIR)

fclean : clean
	$(RM) $(NAME) output.log

re : fclean
	@$(MAKE)

f : all
	@echo
	@echo
	@./$(NAME) | cat -n

cmp: all
	./$(NAME) > output.log
	@echo "\n 🎉  \033[32m Colordiff. Reference on the left, my output on the right\033[0m"
	diff -y ./subject.log ./output.log

.PHONY: all clean fclean mclean re FORCE cmp
#.SILENT:
