# LIBFT = libft/libft.a

# LIBFT_H = libft/libft.h

# SRC = test.c ft_parser.c ft_lexer.c ft_tree_node.c ft_split_line.c ft_tokenlen.c \
# 		ft_expand_token.c ft_empty_token.c ft_heredoc.c ft_token.c ft_free_tree.c utils.c \
# 		my_execution/execution/execution_entry.c my_execution/execution/my_echo.c my_execution/execution/my_env.c \
# 		my_execution/execution/utils.c my_execution/execution/my_pwd.c my_execution/execution/my_cd.c my_execution/execution/my_unset.c \
# 		my_execution/execution/my_export.c \


# OBJ = $(SRC:.c=.o)

# NAME = test

# CC =	cc #-Wall -Wextra -Werror
# RM =	rm -f

# %.o: %.c minishell.h $(LIBFT_H)
# 	$(CC) -c $< -o $@

# all: $(NAME)

# $(NAME): $(LIBFT) $(OBJ)
# 	$(CC) $(OBJ) $(LIBFT) -lreadline -o $(NAME)

# $(LIBFT):
# 	make -C libft all bonus

# clean:
# 	make -C libft clean
# 	$(RM) $(OBJ)

# fclean: clean
# 	make -C libft fclean
# 	$(RM) $(NAME)

# re: fclean all
LIBFT = libft/libft.a
LIBFT_H = libft/libft.h

SRC = test.c ft_parser.c ft_lexer.c ft_tree_node.c ft_split_line.c ft_tokenlen.c \
	ft_expand_token.c ft_empty_token.c ft_heredoc.c ft_token.c ft_free_tree.c utils.c \
	my_execution/execution/execution_entry.c my_execution/execution/my_echo.c my_execution/execution/my_env.c \
	my_execution/execution/utils.c my_execution/execution/my_pwd.c my_execution/execution/my_cd.c my_execution/execution/my_unset.c \
	my_execution/execution/my_export.c

OBJ = $(SRC:.c=.o)

NAME = minishell

CC = cc #-fsanitize=address #-Wall -Wextra -Werror
RM = rm -f

%.o: %.c minishell.h $(LIBFT_H)
	$(CC) -c $< -o $@

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(OBJ) $(LIBFT) -lreadline -o $(NAME)

$(LIBFT):
	make -C libft all bonus

clean:
	make -C libft clean
	$(RM) $(OBJ)

fclean: clean
	make -C libft fclean
	$(RM) $(NAME)

re: fclean all
