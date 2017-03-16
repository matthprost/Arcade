##
## Makefile for Makefile in /home/jabbar_y/rendu/cpp_arcade
##
## Made by Yassir Jabbari
## Login   <jabbar_y@epitech.net>
##
## Started on  Mon Mar  6 09:53:13 2017 Yassir Jabbari
## Last update Mon Mar  6 10:31:07 2017 Loic Lopez
##

SFML	=	./lib/lib_arcade_SFML.so
Qt	=	./lib/lib_arcade_Qt.so
Ncurses	=	./lib/lib_arcade_Ncurses.so


################# LIB SRCS ################

SFML_SRCS	=	lib-sources/SFMLController.cpp

Qt_SRCS		=	lib-sources/QtController.cpp

Ncurses_SRCS	=	lib-sources/NcursesController.cpp

###########################################


################# LIB OBJS ################

SFML_OBJS	=	$(SFML_SRCS:.cpp=.o)

Qt_OBJS		=	$(Qt_SRCS:.cpp=.o)

Ncurses_OBJS	=	$(Ncurses_SRCS:.cpp=.o)

###########################################

ECHO	=	/bin/echo -e

DEFAULT	=	"\033[00m"
GREEN	=	"\033[0;32m"
TEAL	=	"\033[1;36m"
RED	=	"\033[5;31m"

CC              = g++

RM              = rm -f

CXXFLAGS 	= -Wall -Wextra -Werror -I./include

NAME            = arcade

SRCS            = sources/main.cpp \
		   sources/GameCore.cpp

OBJS            = $(SRCS:.cpp=.o)

all: $(SFML) $(Ncurses) $(Qt) $(NAME)

$(SFML):	$(SFML_OBJS)
	@$(CC) $(SFML_OBJS) -fPIC -shared -o $(SFML) && \
        $(ECHO) $(GREEN) "[OK]"$(TEAL)"  BUILD :" $(SFML) $(DEFAULT)  || \
        $(ECHO) $(RED) "[ERROR]" $(TEAL) $(SFML) $(DEFAULT)

$(Ncurses):	$(Ncurses_OBJS)
	@$(CC) $(Ncurses_OBJS) -fPIC -shared -o $(Ncurses) && \
        $(ECHO) $(GREEN) "[OK]"$(TEAL)"  BUILD :" $(Ncurses) $(DEFAULT)  || \
        $(ECHO) $(RED) "[ERROR]" $(TEAL) $(Ncurses) $(DEFAULT)

$(Qt):		$(Qt_OBJS)
	@$(CC) $(Qt_OBJS) -fPIC -shared -o $(Qt) && \
        $(ECHO) $(GREEN) "[OK]"$(TEAL)"  BUILD :" $(Qt) $(DEFAULT)  || \
        $(ECHO) $(RED) "[ERROR]" $(TEAL) $(Qt) $(DEFAULT)

$(NAME)	:	$(OBJS)
	@$(CC) $(OBJS)  $(CXXFLAGS) -o $(NAME) && \
	$(ECHO) $(GREEN) "[OK]"$(TEAL)"  BUILD :" $(NAME) $(DEFAULT)  || \
	$(ECHO) $(RED) "[ERROR]" $(TEAL) $(NAME) $(DEFAULT)
clean	:
	@rm -f $(OBJS) $(SFML_OBJS) $(Qt_OBJS) $(Ncurses_OBJS) && \
	$(ECHO) $(GREEN) "[OK] remove" $(TEAL) $(OBJS) $(SFML_OBJS) $(Qt_OBJS) $(Ncurses_OBJS) $(DEFAULT) || \
	$(ECHO) $(RED) "[ERROR] doesn't exist" $(TEAL) $(OBJS) $(SFML_OBJS) $(Qt_OBJS) $(Ncurses_OBJS) $(DEFAULT)

fclean	:	clean
	@rm -f $(NAME) $(SFML) $(Ncurses) $(Qt) && \
	$(ECHO) $(GREEN) "[OK] remove" $(TEAL) $(NAME) $(SFML) $(Ncurses) $(Qt) $(DEFAULT) || \
	$(ECHO) $(RED) "[ERROR] doesn't exist" $(TEAL) $(NAME) $(SFML) $(Ncurses) $(Qt) $(DEFAULT)

re	:	fclean all

.cpp.o	:
	@$(CC) $(CXXFLAGS) -c -o $@ $< && \
	$(ECHO) $(GREEN) "[OK]" $(TEAL) $< "--->" $@ $(DEFAULT) || \
	$(ECHO) $(RED) "[ERROR] doesn't exist" $(TEAL) $^ $(DEFAULT)
