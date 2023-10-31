# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ylabrahm <ylabrahm@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/18 18:12:29 by macbook           #+#    #+#              #
#    Updated: 2023/10/31 08:37:28 by ylabrahm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = src/main.cpp
OBJS := $(SRCS:.cpp=.o)
OBJS := $(addprefix obj/, $(OBJS))

CC = c++
RM = rm -f
CFLAGS = -std=c++98 #-Wall -Wextra -Werror 
NAME = webserv

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

obj/%.o: %.cpp
	@mkdir -p $(shell dirname $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)
	$(RM) -rf obj/

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re