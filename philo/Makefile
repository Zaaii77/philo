# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lowatell <lowatell@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/20 13:23:46 by lowatell          #+#    #+#              #
#    Updated: 2025/05/08 19:30:01 by lowatell         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -g3 -Wall -Wextra -Werror
RM = rm -rf

INCS_DIR = incs
OBJS_DIR = objs

NAME = philo

SRCS =	main.c init_data.c init_utils.c parsing_init_utils.c routine.c \
		routine_utils.c cleanup.c 

OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

GREEN = \033[32m

all: $(NAME)

$(OBJS_DIR)/%.o: %.c | $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INCS_DIR)

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

clean:
	@$(RM) $(OBJS_DIR)
	@echo "$(GREEN)Objects files have been deleted."

fclean: clean
	@$(RM) $(NAME)
	@echo "$(GREEN)$(NAME) has been deleted."

re: fclean all

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)$(NAME) has been compiled."

.PHONY: all clean fclean re

