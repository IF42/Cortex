CC=clang
CFLAGS=-Wall -Wextra -pedantic -std=c2x -Ofast
LIBS=-lm


INCLUDE_PATH=/usr/include/
LIB_PATH=/usr/lib64/

TARGET=neuron
CACHE=.cache
OUTPUT=$(CACHE)/release

MODULES += main.o
MODULES += layer.o
MODULES += dense.o
MODULES += activation.o
MODULES += loss.o
MODULES += optimizer.o
MODULES += SGD.o
MODULES += adam.o


OBJ=$(addprefix $(CACHE)/,$(MODULES))


all: env $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(OUTPUT)/$(TARGET)


%.o:
	$(CC) $(CFLAGS) -c $< -o $@


-include dep.list


exec: all $(T_OBJ)
	$(OUTPUT)/$(TARGET)


.PHONY: env dep clean


dep:
	$(CC) -MM app/*.c src/*.c | sed 's|[a-zA-Z0-9_-]*\.o|$(CACHE)/&|' > dep.list


env:
	mkdir -pv $(CACHE)
	mkdir -pv $(OUTPUT)


clean: 
	rm -rvf $(OUTPUT)
	rm -vf $(CACHE)/*.o



