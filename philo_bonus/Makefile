NAME_B = philo_bonus

CC = cc

CFLAGS = -Wall -Wextra -Werror

SRCS_B = check_arguments_b.c philo_bonus.c utils_init_bonus.c \
		 utils_time_bonus.c utils_init_creat.c utils_action.c \
		 ft_atoi.c

OBJS_B = ${SRCS_B:.c=.o}

%.o:%.c philo_bonus.h
	@${CC} ${CFLAGS} -c $< -o $@
	@echo "$@ ✅"

all: ${NAME_B}

${NAME_B} : ${OBJS_B}
	@${CC}  ${CFLAGS} ${OBJS_B} -o $@
	@echo "$@ ✅"

clean :
	@rm -rf ${OBJS_B}
	@echo "Cleaned object files ✅"

fclean : clean
	@rm -rf ${NAME_B}
	@echo "Cleaned files executable ✅"

re : fclean all