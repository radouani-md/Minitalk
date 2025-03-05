NAME = push_swap

NAME_BNS = checker

CC = cc

CFLAGS = -Wall -Wextra -Werror

BONS = bonuses

SRC = md_utils.c push_swap.c parsing.c md_split.c free_data.c lst_functions.c md_opr_s.c \
	md_opr_b.c md_opr_r.c sort_three_five.c roud_to_algo.c utils_of_algo.c function_norm.c \

SRC_BONUS = $(BONS)/md_utils_bonus.c $(BONS)/md_split_bonus.c $(BONS)/parsing_bonus.c $(BONS)/lst_functions_bonus.c \
	$(BONS)/checker_bonus.c $(BONS)/free_data_bonus.c $(BONS)/read_and_put_bonus.c $(BONS)/get_next_line_bonus.c $(BONS)/get_next_line_utils_bonus.c \
	$(BONS)/md_opr_b_bonus.c $(BONS)/md_opr_r_bonus.c $(BONS)/md_opr_s_bonus.c $(BONS)/after_read_bonus.c $(BONS)/function_norm_bonus.c \

OBJ = $(SRC:.c=.o)

OBJ_BONUS = ${SRC_BONUS:.c=.o}

HEADER = push_swap.h

HEADER_BNS = bonuses/checker_bonus.h

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

bonus: ${NAME_BNS}

$(NAME_BNS): $(OBJ_BONUS)
	${CC} $(CFLAGS) ${OBJ_BONUS} -o $(NAME_BNS)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

$(BONS)/%.o: $(BONS)/%.c $(HEADER_BNS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) ${OBJ_BONUS}

fclean: clean
	rm -f $(NAME) $(NAME_BNS)

re: fclean allv