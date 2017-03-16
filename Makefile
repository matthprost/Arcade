##
## Makefile for Makefile in /home/jabbar_y/rendu/cpp_arcade
##
## Made by Yassir Jabbari
## Login   <jabbar_y@epitech.net>
##
## Started on  Mon Mar  6 09:53:13 2017 Yassir Jabbari
## Last update Mon Mar  6 10:31:07 2017 Loic Lopez
##

ECHO	=	/bin/echo -e

DEFAULT	=	"\033[00m"
GREEN	=	"\033[0;32m"
TEAL	=	"\033[1;36m"
RED	=	"\033[5;31m"

CC              = g++

RM              = rm -f

CXXFLAGS 	= -Wall -Wextra -Werror -I./include

NAME            = arcade

SRCS            = sources/main.cpp

OBJS            = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME)	:	$(OBJS)
	@$(CC) $(OBJS)  $(CXXFLAGS) -o $(NAME) && \
	$(ECHO) $(GREEN) "[OK]"$(TEAL)"  BUILD :" $(NAME) $(DEFAULT)  || \
	$(ECHO) $(RED) "[ERROR]" $(TEAL) $(OBJDUMP) $(DEFAULT)
clean	:
	@rm -f $(OBJS) && \
	$(ECHO) $(GREEN) "[OK] remove" $(TEAL) $(OBJS) $(DEFAULT) || \
	$(ECHO) $(RED) "[ERROR] doesn't exist" $(TEAL) $(OBJS) $(DEFAULT)

fclean	:	clean
	@rm -f $(NAME) && \
	$(ECHO) $(GREEN) "[OK] remove" $(TEAL) $(NAME) $(DEFAULT) || \
	$(ECHO) $(RED) "[ERROR] doesn't exist" $(TEAL) $(NAME) $(DEFAULT)

re	:	fclean all

.cpp.o	:
	@$(CC) $(CXXFLAGS) -c -o $@ $< && \
	$(ECHO) $(GREEN) "[OK]" $(TEAL) $< "--->" $@ $(DEFAULT) || \
	$(ECHO) $(RED) "[ERROR] doesn't exist" $(TEAL) $^ $(DEFAULT)
