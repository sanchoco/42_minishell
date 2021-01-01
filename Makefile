NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror
LIBFT_FLAGS = -lft -L./lib/libft
INC = -I./includes
RM = rm -rf

BUILTIN_SRCS = \
				ft_first_envv.c \
				ft_env.c \
				ft_execve.c \
				ft_export.c \
				ft_unset.c \
				ft_cd.c \
				ft_echo.c \
				ft_pwd.c \
				ft_exit.c

BUILTIN_SRCS_DIR = ./srcs/builtin

COMMAND_SRCS = \
				ft_pipe.c \
				ft_redirection.c \
				ft_semicolon.c \
				ft_controller.c \
				ft_command_utils.c \
				ft_pipe_utils.c \
				ft_pipe_utils_2.c \
				ft_check_cmd.c \
				ft_execute_builtin_utils_1.c \
				ft_execute_builtin_utils_2.c

COMMAND_SRCS_DIR = ./srcs/command

PARSING_SRCS = \
				ft_parsing_push.c \
				ft_parsing_second.c \
				ft_parsing_first.c \
				ft_parsing_second_utils.c

PARSING_SRCS_DIR = ./srcs/parsing

UTILS_SRCS = \
			double_ptr_utils.c

UTILS_SRCS_DIR = ./srcs/utils

ERROR_SRCS = \
				ft_error_free_utils.c \
				ft_error.c \
				ft_parsing_error.c

ERROR_SRCS_DIR = ./srcs/error

SRCS_LIST = \
			$(addprefix $(PARSING_SRCS_DIR)/, $(PARSING_SRCS)) \
			$(addprefix $(UTILS_SRCS_DIR)/, $(UTILS_SRCS)) \
			$(addprefix $(BUILTIN_SRCS_DIR)/, $(BUILTIN_SRCS)) \
			$(addprefix $(COMMAND_SRCS_DIR)/, $(COMMAND_SRCS)) \
			$(addprefix $(ERROR_SRCS_DIR)/, $(ERROR_SRCS)) \
			./srcs/main.c

OBJS = $(SRCS:%.c=%.o)

all : $(NAME)

$(NAME) : $(OBJS) $(SRCS_LIST)
	$(MAKE) -C lib/libft bonus
	$(CC) $(CFLAGS) $(INC) $(SRCS_LIST) $(LIBFT_FLAGS) -o $(NAME)

clean :
	$(MAKE) -C lib/libft clean
	$(RM) $(OBJS)

fclean : clean
	$(MAKE) -C lib/libft fclean
	$(RM) $(NAME)

re : fclean all

norminette :
	norminette $(SRCS_LIST)
.PHONY: all bonus clean fclean re
