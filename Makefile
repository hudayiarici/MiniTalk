# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: harici <harici@student.42istanbul.com.t    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/22 14:40:07 by harici            #+#    #+#              #
#    Updated: 2025/11/02 17:39:23 by harici           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_SERVER = server
NAME_CLIENT = client

CC = cc
CFLAGS = -Wall -Wextra -Werror

# Mandatory files
SRC_SERVER = server.c utils.c
SRC_CLIENT = client.c utils.c

OBJ_SERVER = $(SRC_SERVER:.c=.o)
OBJ_CLIENT = $(SRC_CLIENT:.c=.o)

# Bonus files
SRC_SERVER_BONUS = server_bonus.c utils_bonus.c
SRC_CLIENT_BONUS = client_bonus.c utils_bonus.c

OBJ_SERVER_BONUS = $(SRC_SERVER_BONUS:.c=.o)
OBJ_CLIENT_BONUS = $(SRC_CLIENT_BONUS:.c=.o)

# Default target - Mandatory
all: $(NAME_SERVER) $(NAME_CLIENT)

# Mandatory rules
$(NAME_SERVER): $(OBJ_SERVER)
	$(CC) $(CFLAGS) $(OBJ_SERVER) -o $(NAME_SERVER)

$(NAME_CLIENT): $(OBJ_CLIENT)
	$(CC) $(CFLAGS) $(OBJ_CLIENT) -o $(NAME_CLIENT)

# Bonus rule
bonus: $(OBJ_SERVER_BONUS) $(OBJ_CLIENT_BONUS)
	$(CC) $(CFLAGS) $(OBJ_SERVER_BONUS) -o $(NAME_SERVER)
	$(CC) $(CFLAGS) $(OBJ_CLIENT_BONUS) -o $(NAME_CLIENT)
	@touch bonus

# Compile .c to .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean object files
clean:
	rm -f $(OBJ_SERVER) $(OBJ_CLIENT)
	rm -f $(OBJ_SERVER_BONUS) $(OBJ_CLIENT_BONUS)
	rm -f bonus

# Clean everything
fclean: clean
	rm -f $(NAME_SERVER) $(NAME_CLIENT)

# Rebuild
re: fclean all

.PHONY: all clean fclean re