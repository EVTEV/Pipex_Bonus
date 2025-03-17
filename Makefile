NAME = pipex
BONUS = pipex_bonus

MAKEFLAGS = --no-print-directory

LIBFT_DIR = ./Libft
LIBFT = $(LIBFT_DIR)/libft.a
INC_LIBFT = -I$(LIBFT_DIR)/inc
LIBFT_FLAGS = -L$(LIBFT_DIR) -lft

INC_DIR = ./inc
INC = -I$(INC_DIR)

SRC_DIR = src
OBJ_DIR = obj

SRC = main.c \
	  $(wildcard $(SRC_DIR)/pars/*.c) \
	  $(wildcard $(SRC_DIR)/pipe/*.c) \
	  $(wildcard $(SRC_DIR)/exec/*.c) \
	  $(wildcard $(SRC_DIR)/here_doc/*.c) \
	  $(wildcard $(SRC_DIR)/utils/*.c)

OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror #-g -gdwarf-4
RM = @rm -rf
AR = ar -rcs

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT_FLAGS) -o $(NAME)

bonus: $(BONUS)

$(BONUS): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT_FLAGS) -o $(BONUS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ $(INC) $(INC_LIBFT)

$(LIBFT):
	echo "CREATING LIBFT"
	$(MAKE) -C $(LIBFT_DIR)

clean:
	$(RM) $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME) $(BONUS)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all bonus

.PHONY: all clean fclean re
