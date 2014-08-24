SRCS = runas.c
OBJS = $(patsubst %.c,%.o, $(SRCS))

runas: $(OBJS)
	$(CC) -o $@ $(OBJS)

%.o: %.c
	$(CC) -c -o $@ $<

.PHONY: clean

clean:
	rm -f *.o runas
