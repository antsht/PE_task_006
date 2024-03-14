BUILD_PATH=../bin/
CC=gcc
CFLAGS=-g -Wall -Wextra -Werror
EXTRAFLAGS=-fsanitize=leak -fsanitize=address -fsanitize=undefined -fsanitize=unreachable -fno-sanitize-recover -fstack-protector 

all: check rebuild

rebuild: clean_all air_traffic cafe clean

air_traffic: clean air_traffic.c common/errors.c common/logger.c
	$(CC) $(CFLAGS) $(EXTRAFLAGS) air_traffic.c common/errors.c common/logger.c -o  $(BUILD_PATH)air_traffic 

cafe: clean cafe.c cafe_libs/cafe_logic.c common/errors.c common/logger.c 
	$(CC) $(CFLAGS) $(EXTRAFLAGS) cafe.c cafe_libs/cafe_logic.c common/errors.c common/logger.c -o  $(BUILD_PATH)cafe

clean_all:
	rm -rf *.o *.a *.so $(BUILD_PATH)*
	
clean:
	rm -rf *.o *.a

check:
	clang-format -i *.c
	clang-format -i *.h
	clang-format -i */*.c
	clang-format -i */*.h
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h common/*.c common/*.h

test:
	pytest --color=yes -v --tb=short  

test_config:
	python3 -m venv test-env  
	source test-env/bin/activate 
	pip install -r tests/requirements.txt



