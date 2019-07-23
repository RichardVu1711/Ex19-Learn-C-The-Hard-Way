CFLAGS=-Wall	-g
src = $(wildcard *.c)
obj = $(src:.c=.o)

game: $(obj)
	gcc	-o $@ $^	
clean:
	rm -f	$(object)	game
test:
	chmod 755 MakeTest.sh
	./MakeTest.sh
