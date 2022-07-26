NAME := philo
BONUS := bonus

SRCS_DIR := ./src
OBJS_DIR := ./obj

SRCS := main.c functions.c
OBJS := ${SRCS:%.c=${OBJS_DIR}/%.o}

CC := gcc -Wall -Werror -Wextra

FLAGS := #-lpthread

LIB := -lft -L ./libft

RED := \033[0;31m
GREEN := \033[0;32m
BLUE := \033[0;34m
PURPLE := \033[0;35m
YELLOW := \033[0;33m
CYAN := \033[0;36m
NC := \033[0m

all : ${NAME}

# "make -C" run make in specific folder
# "-I" is  to look for header file in folder
# "$<" is to match prerequisites
# "$@" is to match target
${NAME} : ${OBJS}
	make -C ./libft
	${CC} ${FLAGS} -I includes -I libft ${OBJS} ${LIB} -o $@
	@echo "${GREEN}Philo Compiled Successful."

# "mkdir -p" creates dir if necessary, if dir exist, no error specified
# "gcc -c" is to create .o files or object files
# "gcc -o 'file' " use as a naming feature / place the output result to 'file'
${OBJS_DIR}/%.o : ${SRCS_DIR}/%.c
	@mkdir -p ${OBJS_DIR}
	@${CC} ${FLAGS} -I includes -I libft -c $< -o $@

# "echo -e" to allow backslash escapes \ 
clean :
	@rm -rf ${OBJS_DIR}
	@make clean -C ./libft
	@echo "${RED}Cleaned.${NC}"

fclean : clean
	@make fclean -C ./libft
	@rm -rf ${NAME}
	@echo "${RED}Full Cleaned.${NC}"

re : fclean all

.PHONY: all clean fclean re