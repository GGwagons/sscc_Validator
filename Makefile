NAME = sscc

RED = \033[1;7;31m
GREEN = \033[1;7;32m
YELLOW = \033[1;7;33m
BLUE = \033[1;7;34m
MAGENTA = \033[1;3;35m
CYAN = \033[0;36m
RESET = \033[0m

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++17

RM = rm -rf

INCLUDE = -I$(HEADER_DIR)

HEADER_LIST = ./include/
HEADER_DIR = ./
HEADER = $(addprefix $(HEADER_DIR), $(HEADER_LIST))

SOURCES_DIR = ./src/
SOURCES_LIST =	../main.cpp \
				SSCC.cpp

SOURCES = $(addprefix $(SOURCES_DIR), $(SOURCES_LIST))
OBJECTS_DIR = objects/
OBJECTS_LIST = $(patsubst %.cpp, %.o, $(SOURCES_LIST))
OBJECTS = $(addprefix $(OBJECTS_DIR), $(OBJECTS_LIST))

all: $(NAME)

$(NAME): $(OBJECTS_DIR) $(OBJECTS)
	@echo "$(YELLOW) Building $(BLUE) IRC $(YELLOW) program... $(RESET)\n"
	@$(CXX) $(CXXFLAGS) $(INCLUDE) $(OBJECTS) $(INCL) -o $@
	@echo "$(GREEN) Done $(RESET)\n"

$(OBJECTS_DIR):
	@mkdir -p $(OBJECTS_DIR)
	@echo "$(GREEN) Create objects folder $(RESET)\n"

$(OBJECTS_DIR)%.o: $(SOURCES_DIR)%.cpp $(HEADER)
	@$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@
	@echo "$(GREEN) OBJECTS ADDED $(RESET)\n"

clean:
	@echo "$(RED) Deleting objects files... $(RESET)\n"
	@$(RM) $(OBJECTS_DIR)
	@$(RM) main.o

fclean: clean
	@echo "$(RED) Cleaning built program... $(RESET)\n"
	@$(RM) -f $(NAME) $(OBJECTS_DIR)
	@$(RM) main.o

re:
	@$(MAKE) -s fclean
	@$(MAKE) -s all
	@echo "$(GREEN) DELETED AND RECOMPILED $(RESET)\n"

.PHONY: all clean fclean re