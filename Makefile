ARGS=""
all:
	gcc -o main main.c util.h tema1.c tema23.c
.PHONY:run
run:
	./main $(ARGS)
