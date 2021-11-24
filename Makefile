# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gvarys <gvarys@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/23 12:29:23 by gvarys            #+#    #+#              #
#    Updated: 2021/11/23 15:39:26 by gvarys           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SERVER						= server
CLIENT						= client
NAME						= minitalk

SRC_UTILS					= utils.c
SRC_CLIENT					= client.c
SRC_SERVER					= server.c
HEADER						= minitalk.h

OBJS_CLIENT					=$(patsubst %.c, %.o, $(SRC_CLIENT))
OBJS_SERVER					=$(patsubst %.c, %.o, $(SRC_SERVER))
OBJS_UTILS					=$(patsubst %.c, %.o, $(SRC_UTILS))

CC							= gcc
CFLAGS						= -O2 -Wall -Wextra -Werror
RM							= rm -f

.PHONY:						all clean fclean re

%.o:						%.c $(HEADER)
								$(CC) $(CFLAGS) -c $< -o $@

all:						$(NAME)

$(NAME): 					$(CLIENT) $(SERVER)
						
$(CLIENT):					$(OBJS_CLIENT) $(OBJS_UTILS)
								$(CC) -o $(CLIENT) $(OBJS_CLIENT) $(OBJS_UTILS)

$(SERVER):					$(OBJS_SERVER) $(OBJS_UTILS)
								$(CC) -o $(SERVER) $(OBJS_SERVER) $(OBJS_UTILS)

clean:
								$(RM) $(OBJS_CLIENT) $(OBJS_SERVER) $(OBJS_UTILS) \
								$(OBJS_CLIENT_BONUS) $(OBJS_SERVER_BONUS) $(OBJS_UTILS_BONUS)
				
fclean:						clean
								$(RM) $(SERVER) $(CLIENT)

re:							fclean all
