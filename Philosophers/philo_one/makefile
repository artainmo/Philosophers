SRC = philo_one.c \
			actions.c \
			handle_struct.c \
			utils.c \
			utils2.c \
			utils3.c \
			utils4.c \

OBJ = $(SRC:.c=.o) #transform c files in object files

all: $(OBJ)
	gcc  -Wall -Wextra -Werror $(OBJ) -lpthread -o philo_one #-o is to define executable name

clean:
	rm -f $(OBJ)

fclean:
	rm -f $(OBJ) philo_one

re: fclean all
