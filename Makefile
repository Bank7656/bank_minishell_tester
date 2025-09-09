NAME = execute_tester

CC = cc
CFLAGS = -g

MAIN_SRC_DIR := ../src/
TESTER_SRC_DIR := ./
TESTER_HEADER_DIR := ./
OBJ_DIR := ./objects/
HEADER_DIR = ../include/
LIBFT_DIR := ../libft/

HEADER = execute.h
TESTER_HEADER = tester.h
LIBFT_NAME = libft.a

MAIN_SRC = execute.c \
	execute_pipeline.c \
	execute_utils.c \
	command_utils.c
MAIN_OBJECTS = $(MAIN_SRC:.c=.o)

TESTER_SRC = tester_main.c \
						 dummy.c \
						 test.c
TESTER_OBJECTS = $(TESTER_SRC:.c=.o)


HEADERS = $(addprefix $(HEADER_DIR), $(HEADER))
SRCS = $(addprefix $(MAIN_SRC_DIR), $(MAIN_SRC)) \
			 $(addprefix $(TESTER_DIR), $(TESTER_SRC))
OBJS = $(addprefix $(OBJ_DIR), $(MAIN_OBJECTS)) \
			 $(addprefix $(OBJ_DIR), $(TESTER_OBJECTS))
LIBFT = $(addprefix $(LIBFT_DIR), $(LIBFT_NAME))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ_DIR) $(OBJS) $(HEADERS) $(TESTER_HEADER)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)%.o:$(MAIN_SRC_DIR)%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I $(HEADER_DIR) -c  $< -o $@

$(OBJ_DIR)%.o:$(TESTER_DIR)%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I $(TESTER_HEADER_DIR) -c  $< -o $@

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean:
	rm -rf $(NAME)
	rm -rf $(OBJ_DIR)
	$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: re fclean clean run all



