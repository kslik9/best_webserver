SRCS		=	src/main.cpp src/Server/create_http.cpp \
				src/Config/Config.cpp src/Logger/Logger.cpp src/Server/Server.cpp \
				src/ReturnStatus/ReturnStatus.cpp \
				src/ReturnStatus/HttpMessageChecker.cpp \
				src/ReturnStatus/Checkers.cpp \
				src/ReturnStatus/HandleGetMethod.cpp \
				src/ReturnStatus/RequestData.cpp \
				src/CGI/cgi.cpp

OBJS		:= $(SRCS:.cpp=.o)
OBJS		:= $(addprefix obj/, $(OBJS))

CC 			= c++
RM			= rm -f
# CFLAGS		= -std=c++98 -fsanitize=address #-Wall -Wextra -Werror 
CFLAGS      =
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