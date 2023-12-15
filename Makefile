SRCS		=	src/main.cpp \
				src/Server/create_http.cpp \
				src/Config/Config.cpp \
				src/Logger/Logger.cpp \
				src/Server/Server.cpp \
				src/ReturnStatus/HttpRequestFlow.cpp \
				src/ReturnStatus/Checkers.cpp \
				src/ReturnStatus/HandleGetMethod.cpp \
				src/ReturnStatus/HandlePostMethod.cpp \
				src/ReturnStatus/HandleDeleteMethod.cpp \
				src/ReturnStatus/RequestData.cpp \
				src/ReturnStatus/Response/NotFound404.cpp \
				src/ReturnStatus/Response/MovedPermanently301.cpp \
				src/ReturnStatus/Response/MethodNotAllowed405.cpp \
				src/ReturnStatus/Response/Conflict409.cpp \
				src/ReturnStatus/Response/NoContent204.cpp \
				src/ReturnStatus/Response/InternalServerError500.cpp \
				src/ReturnStatus/Response/Forbidden403.cpp \
				src/ReturnStatus/Response/ResponseFromCgi.cpp \
				src/ReturnStatus/Response/OK200.cpp \
				src/ReturnStatus/Response/UriTooLong414.cpp \
				src/ReturnStatus/Response/BadRequest400.cpp \
				src/ReturnStatus/Response/Created201.cpp \
				src/ReturnStatus/Response/PayloadTooLarge413.cpp \
				src/ReturnStatus/Response/CommonFuncs.cpp \
				src/Config/ServConf.cpp \
				src/FileUploadHandler/FileUploadHandler.cpp \
				src/Server/Socket.cpp \
				src/utils.cpp

OBJS		:= $(SRCS:.cpp=.o)
OBJS		:= $(addprefix obj/, $(OBJS))

CC 			= c++
RM			= rm -f
CFLAGS		= -Wall -Wextra -Werror -std=c++98
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