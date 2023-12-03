SRCS		=	src/main.cpp src/Server/create_http.cpp \
				src/Config/Config.cpp src/Logger/Logger.cpp src/Server/Server.cpp \
				src/ReturnStatus/ReturnStatus.cpp \
				src/ReturnStatus/HttpRequestChecker.cpp \
				src/ReturnStatus/Checkers.cpp \
				src/ReturnStatus/HandleGetMethod.cpp \
				src/ReturnStatus/HandlePostMethod.cpp \
				src/ReturnStatus/RequestData.cpp \
				src/ReturnStatus/Response/NotFound404.cpp \
				src/ReturnStatus/Response/MovedPermanently301.cpp \
				src/ReturnStatus/Response/MethodNotAllowed405.cpp \
				src/ReturnStatus/Response/OK200.cpp \
				src/ReturnStatus/Response/Forbidden403.cpp \
				src/ReturnStatus/Response/CommonFuncs.cpp \
				src/CGI/cgi.cpp \
				src/Config/ServConf.cpp 

OBJS		:= $(SRCS:.cpp=.o)
OBJS		:= $(addprefix obj/, $(OBJS))

CC 			= c++
RM			= rm -f
# CFLAGS		= -std=c++98 -fsanitize=address
# CFLAGS		=
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