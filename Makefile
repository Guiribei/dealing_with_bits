ENCODER = encoder
DECODER = decoder

PATH_SRC_ENC = ./sources_encoder/
PATH_SRC_DEC = ./sources_decoder/

PATH_OBJ_ENC = ./objects_encoder/
PATH_OBJ_DEC = ./objects_decoder/


OBJ_ENC = ${SRC_ENC:%.c=$(PATH_OBJ_ENC)%.o}
OBJ_DEC = ${SRC_DEC:%.c=$(PATH_OBJ_DEC)%.o}


SRC_ENC = encoder.c huffman.c list.c tree.c dictionary.c

SRC_DEC = decoder.c

INCLUDE = -I ./includes/
FLAGS = -Wall -Wextra -Werror -g3


all:		$(ENCODER)	$(DECODER)

$(ENCODER):	$(OBJ_ENC)
	@cc $(FLAGS) $(OBJ_ENC) -o $(ENCODER)

$(DECODER):	$(OBJ_DEC)
	@cc $(FLAGS) $(OBJ_DEC) -o $(DECODER)

$(PATH_OBJ_ENC)%.o: $(PATH_SRC_ENC)%.c
	@mkdir -p $(PATH_OBJ_ENC)
	cc $(FLAGS) $(INCLUDE) -c $< -o $@
	@echo "\033[1;92m[SUCCESS] Objects creation done!\033[0m"

$(PATH_OBJ_DEC)%.o: $(PATH_SRC_DEC)%.c
	@mkdir -p $(PATH_OBJ_DEC)
	cc $(FLAGS) $(INCLUDE) -c $< -o $@
	@echo "\033[1;92m[SUCCESS] Objects creation done!\033[0m"

clean:
	@rm -rf $(PATH_OBJ_ENC)
	@rm -rf $(PATH_OBJ_DEC)
	@echo "\33[1;93m[SUCCESS] Objects removal done!\33[0m"

fclean: clean
	@rm -f $(ENCODER)
	@rm -f $(DECODER)
	@echo "\033[1;93m[SUCCESS] Removal done!\33[0m"

re: fclean all

.PHONY: all clean fclean re