CC = gcc
LDFLAGS =-ldl -shared -Wl,-soname,shadershitter.so
CFLAGS = -Wall -Ofast -fstrict-aliasing -march=native -fPIC
OBJECTS = shadershitter.o stringlib.o framerate.o shader.o

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

shadershitter.so: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@ $(LDFLAGS)

debug:	CFLAGS= -Wall -O0 -g -fstrict-aliasing -march=native -fPIC
debug: 	$(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@.so $(LDFLAGS)
clean:
	rm -f $(OBJECTS)