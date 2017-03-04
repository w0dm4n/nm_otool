# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/05/20 17:57:50 by frmarinh          #+#    #+#              #
#    Updated: 2017/03/01 19:12:38 by frmarinh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_OTOOL	=	ft_otool
NAME_NM     =   ft_nm
NAME		=   nm_otool
NAMEBASE    =   $(shell basename $(NAME))
LENGTHNAME	=	`printf "%s" $(NAMEBASE) | wc -c`
MAX_COLS	=	$$(echo "$$(tput cols)-24-$(LENGTHNAME)"|bc)

CC			=	gcc
FLAGS		=	-Wall -Wextra -Werror -O3
#FLAGS       =
FLAGS_O		=	

SRCDIR_OTOOL		=	srcs/otool/
SRCDIR_NM			=	srcs/nm/

OBJDIR_OTOOL		=	objs/otool/
OBJDIR_NM			=	objs/nm/

INCDIR				=	includes/
LIBFT_DIR			=	libft/
LIBFT_LIB			=	$(LIBFT_DIR)libft.a

SRCBASE_OTOOL	=	\
					ft_otool.c                              \
					mach_header.c							\
					swap.c                                  \
					read_x64.c								\
					read_x32.c                              \
					check_file.c							\
					do.c									\
					utils.c

SRCBASE_NM		=	\
					ft_nm.c                                 \
					mach_header.c							\
					swap.c                                  \
					read_x64.c								\
					read_x32.c                              \
					check_file.c							\
					do.c									\
					utils.c									\
					custom_nlist.c

INCS		=	$(addprefix $(INCDIR), $(INCBASE))

SRCS_OTOOL		=	$(addprefix $(SRCDIR_OTOOL), $(SRCBASE_OTOOL))
OBJS_OTOOL		=	$(addprefix $(OBJDIR_OTOOL), $(SRCBASE_OTOOL:.c=.o))

SRCS_NM		=	$(addprefix $(SRCDIR_NM), $(SRCBASE_NM))
OBJS_NM		=	$(addprefix $(OBJDIR_NM), $(SRCBASE_NM:.c=.o))

.SILENT:

all:		$(NAME)

$(NAME):
	if test -f $(NAME_OTOOL) && test -f $(NAME_NM) ; then					\
		echo "make: Nothing to be done for \`all\`.";				        \
	else																	\
		make otool && make nm && 											\
		echo "\r\033[38;5;184m👥  AUTHOR(s): \033[0m\033[K" && 		\
		echo "\r\033[38;5;15m`cat auteur | sed s/^/\ \ \ \ -/g`\033[0m\033[K" && \
		echo "\033[38;5;44m☑️  ALL    $(NAMEBASE) is done\033[0m\033[K";		\
	fi

$(OBJDIR_OTOOL):
	mkdir -p $(OBJDIR_OTOOL)
	mkdir -p $(dir $(OBJS_OTOOL))

$(OBJDIR_OTOOL)%.o : $(SRCDIR_OTOOL)%.c | $(OBJDIR_OTOOL)
	$(CC) $(FLAGS) -MMD -c $< -o $@											\
		-I $(LIBFT_DIR)$(INCDIR)											\
		-I $(INCDIR)
	printf "\r\033[38;5;11m%s%*.*s\033[0m\033[K"							\
		"⌛  MAKE          wait ..."										\
		$(MAX_COLS) $(MAX_COLS) "($(@))"

$(OBJDIR_NM):
	mkdir -p $(OBJDIR_NM)
	mkdir -p $(dir $(OBJS_NM))

$(OBJDIR_NM)%.o : $(SRCDIR_NM)%.c | $(OBJDIR_NM)
	$(CC) $(FLAGS) -MMD -c $< -o $@											\
		-I $(LIBFT_DIR)$(INCDIR)											\
		-I $(INCDIR)
	printf "\r\033[38;5;11m%s%*.*s\033[0m\033[K"							\
		"⌛  MAKE   pls wait ..."											\
		$(MAX_COLS) $(MAX_COLS) "($(@))"

fcleanlib:	fclean
	make -C $(LIBFT_DIR) fclean

re:			fclean all

relib:		fclean fcleanlib all

.PHONY:		fclean fcleanlib clean re relib

nm: $(OBJDIR_NM) $(OBJS_NM)
	make -C $(LIBFT_DIR)
	$(CC) $(FLAGS) $(FLAGS_O) -o $(NAME_NM) $(OBJS_NM) $(LIBFT_LIB)
	echo "\r\033[38;5;22m📗  MAKE $(NAME_NM)"

otool: $(OBJDIR_OTOOL) $(OBJS_OTOOL)
	make -C $(LIBFT_DIR)
	$(CC) $(FLAGS) $(FLAGS_O) -o $(NAME_OTOOL) $(OBJS_OTOOL) $(LIBFT_LIB)
	echo "\r\033[38;5;22m📗  MAKE $(NAME_OTOOL)"

clean:
	printf "\r\033[38;5;11m⌛  CLEAN  $(NAME_OTOOL) pls wait ...\033[0m\033[K"
	if [[ `rm -R $(OBJDIR_OTOOL) &> /dev/null 2>&1; echo $$?` == "0" ]]; then	\
		echo "\r\033[38;5;124m📕  CLEAN  $(NAME_OTOOL)\033[0m\033[K";			\
	else																	    \
		printf "\r";														    \
	fi
	printf "\r\033[38;5;11m⌛  CLEAN  $(NAME_NM) pls wait ...\033[0m\033[K"
	if [[ `rm -R $(OBJDIR_NM) &> /dev/null 2>&1; echo $$?` == "0" ]]; then	\
		echo "\r\033[38;5;124m📕  CLEAN  $(NAME_NM)\033[0m\033[K";			\
	else																	\
		printf "\r";														\
	fi

fclean:		clean
	printf "\r\033[38;5;11m⌛  FCLEAN $(NAME_OTOOL) pls wait ...\033[0m\033[K"
	if [[ `rm $(NAME_OTOOL) &> /dev/null 2>&1; echo $$?` == "0" ]]; then		\
		echo "\r\033[38;5;124m📕  FCLEAN $(NAME_OTOOL)\033[0m\033[K";			\
	else																	    \
		printf "\r";														    \
	fi
	printf "\r\033[38;5;11m⌛  FCLEAN $(NAME_NM) pls wait ...\033[0m\033[K"
	if [[ `rm $(NAME_NM) &> /dev/null 2>&1; echo $$?` == "0" ]]; then		    \
		echo "\r\033[38;5;124m📕  FCLEAN $(NAME_NM)\033[0m\033[K";			    \
	else																	    \
		printf "\r";														    \
	fi

-include $(OBJS:.o=.d)
