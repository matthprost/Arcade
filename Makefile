##
## Makefile for Makefile in /home/jabbar_y/rendu/cpp_arcade
## 
## Made by Yassir Jabbari
## Login   <jabbar_y@epitech.net>
## 
## Started on  Mon Mar  6 09:53:13 2017 Yassir Jabbari
## Last update Mon Mar  6 09:57:19 2017 Yassir Jabbari
##

CC              = g++

RM              = rm -rf

CFLAGS          = -std=c++11 -W -Wall -Wextra -Werror -Iinclude

NAME            = arcade

SRCS            = src/main.cpp

OBJS            = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(CFLAGS)
clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

