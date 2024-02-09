NAME = philo

CC = cc 

CFLAGS = -Wall -Wextra -Werror

SRCS = check_arguments.c philo.c handl_safly.c getters_setters.c \
	   utils_time.c utils_status.c utils_init.c utils_routine.c \
	   ft_wait_all_threads.c utils_free.c

OBJS = ${SRCS:.c=.o}


%.o:%.c philo.h
	@echo "$@ ✅"
	@${CC} ${CFLAGS} -c $< -o $@

all: ${NAME}

${NAME} : ${OBJS}
	@${CC}  ${CFLAGS} ${OBJS} -o $@
	@echo "$@ ✅"


clean :
	@rm -rf ${OBJS}
	@echo "Cleaned object files ✅"

fclean : clean
	@rm -rf ${NAME}
	@echo "Cleaned files executable ✅"

re : fclean all