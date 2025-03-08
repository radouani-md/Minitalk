NAME = server	

NAME2 = client

NAME_BNS = server_bonus

NAME2_BNS = client_bonus

CC = cc

CFLAGS = -Wall -Wextra -Werror

BONS = bonuses

SRC_SERVER = server.c

SRC_CLIENT = client.c 	

SRC_SERVER_BNS = $(BONS)/server_bonus.c $(BONS)/utils_bonus.c

SRC_CLIENT_BNS = $(BONS)/client_bonus.c 

OBJ_SERVER = $(SRC_SERVER:.c=.o)

OBJ_CLIENT = $(SRC_CLIENT:.c=.o)

OBJ_BNS_SERVER = $(SRC_SERVER_BNS:.c=.o)

OBJ_BNS_CLIENT = $(SRC_CLIENT_BNS:.c=.o)


HEADER = minitalk.h

HEADER_BNS = minitalk_bonus.h

all: $(NAME) $(NAME2)

bonus: $(NAME_BNS) $(NAME2_BNS)

$(NAME): $(OBJ_SERVER)
	$(CC) $(CFLAGS) $(OBJ_SERVER) -o $(NAME)

$(NAME2): $(OBJ_CLIENT)
	$(CC) $(CFLAGS) $(OBJ_CLIENT) -o $(NAME2)

$(NAME_BNS): $(OBJ_BNS_SERVER)
	$(CC) $(CFLAGS) $(OBJ_BNS_SERVER) -o $(NAME_BNS)

$(NAME2_BNS): $(OBJ_BNS_CLIENT)
	$(CC) $(CFLAGS) $(OBJ_BNS_CLIENT) -o $(NAME2_BNS)


%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

$(BNS)/%.o: $(BNS)/%.c $(HEADER_BNS)
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -f $(OBJ_SERVER) $(OBJ_CLIENT) $(OBJ_BNS_CLIENT) $(OBJ_BNS_SERVER) 

fclean: clean
	rm -f $(NAME2) $(NAME) $(NAME2_BNS) $(NAME_BNS)

re: fclean all