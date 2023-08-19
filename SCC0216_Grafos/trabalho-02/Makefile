PROJ_NAME=Trabalho2

C_SOURCE=$(filter-out ./source/main.cpp ./source/test.cpp, $(wildcard ./source/*.cpp ./source/*/*.cpp ./source/*/*/*.cpp ))

CC=g++

CC_FLAGS=-c -fsanitize=address

RM = rm -rf

default: all test12 clean

format: 
	clang-format -i ./source/*.cpp
	clang-format -i ./source/*/*.cpp
	clang-format -i ./header/*/*.h
	clang-format -i ./header/*.h

all: $(PROJ_NAME)

$(PROJ_NAME): $(C_SOURCE)
	@$(CC) $^ -o $@ ./source/main.cpp

zip: 
	@zip -r $(PROJ_NAME) ./source ./header Makefile

clean: 
	@$(RM) $(PROJ_NAME)

run:
	@./$(PROJ_NAME)

debug:
	@$(RM) debugProgram
	@$(CC) $(C_SOURCE) -g -o debugProgram ./source/test.cpp

test:
	@$(CC) $(C_SOURCE) -o test ./source/test.cpp
	@./test
	@$(RM) test

test1: 
	@./$(PROJ_NAME) < tests/in/$(subst test,,$@).in > tests/out/$(subst test,,$@).out
	@diff ./tests/out/$(subst test,,$@).out ./tests/correct/$(subst test,,$@).out

test2: 
	@./$(PROJ_NAME) < tests/in/$(subst test,,$@).in > tests/out/$(subst test,,$@).out
	@diff ./tests/out/$(subst test,,$@).out ./tests/correct/$(subst test,,$@).out


test3: 
	@./$(PROJ_NAME) < tests/in/$(subst test,,$@).in > tests/out/$(subst test,,$@).out
	@diff ./tests/out/$(subst test,,$@).out ./tests/correct/$(subst test,,$@).out

test6: 
	@./$(PROJ_NAME) < tests/in/$(subst test,,$@).in > tests/out/$(subst test,,$@).out
	@diff ./tests/out/$(subst test,,$@).out ./tests/correct/$(subst test,,$@).out

test12: 
	@./$(PROJ_NAME) < tests/in/$(subst test,,$@).in > tests/out/$(subst test,,$@).out
	@diff ./tests/out/$(subst test,,$@).out ./tests/correct/$(subst test,,$@).out


.PHONY: all clean run	
.IGNORE: test1 test2 test3 test6 test12
