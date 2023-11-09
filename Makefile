SRCS		=	src/main.cpp src/handle_client.cpp src/create_http.cpp src/CreateServerSocket.cpp \
				src/Config/Config.cpp src/Session/Session.cpp src/Server/Server.cpp \
				src/Logger/Logger.cpp
OBJS		:= $(SRCS:.cpp=.o)
OBJS		:= $(addprefix obj/, $(OBJS))

CC 			= c++
RM			= rm -f
CFLAGS		= -std=c++98 #-Wall -Wextra -Werror 
NAME		= webserv
INCLUDE		= -Iinc/

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(INCLUDE) -o $(NAME)

obj/%.o: %.cpp
	@mkdir -p $(shell dirname $@)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	$(RM) $(OBJS)
	$(RM) -rf obj/

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re