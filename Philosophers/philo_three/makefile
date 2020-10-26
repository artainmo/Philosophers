SRC = philo_three.c \
			actions.c \
			handle_struct.c \
			utils.c \
			utils2.c \
			utils3.c \
			utils4.c

OBJ = $(SRC:.c=.o) #transform c files in object files

all: $(OBJ)
	gcc  -Wall -Wextra -Werror $(OBJ) -o philo_three #-o is to define executable name
	#-lpthread is necessary for threads compilation

clean:
	rm -f $(OBJ)

fclean:
	rm -f $(OBJ) philo_three

re: fclean all
