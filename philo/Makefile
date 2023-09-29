# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaimmart <jaimmart@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/27 11:30:37 by jaimmart          #+#    #+#              #
#    Updated: 2023/09/29 16:09:48 by jaimmart         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = gcc
FLAGS = -Wall -Wextra -Werror -pthread -g3 -fsanitize=address

RM = rm -rf

#HEADER = 
PHILO_SRC = main.c check_args.c routine.c time.c finish.c
PHILO_OBJ = $(PHILO_SRC:.c=.o)
$(NAME):    $(PHILO_OBJ)
				@${CC} ${FLAGS} ${PHILO_OBJ} -o ${NAME}
				@echo "$(NAME) created."
$(PHILO_OBJ):    $(PHILO_SRC)
				@echo  "     - Making object files..."
				@$(CC) $(FLAGS) -c $(PHILO_SRC)
all:        $(NAME)

clean:
			@$(RM) $(PHILO_OBJ)
			@echo "object files removed."

fclean: clean
			@$(RM) $(NAME)
			@echo "everything removed."

re:     fclean all

.PHONY:     all clean fclean re