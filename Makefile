CC = gcc
LDFLAGS =-ldl -shared -Wl,-soname,gloverrides.so
CFLAGS = -Wall -Ofast -fstrict-aliasing -march=native -fPIC
OBJECTS = gloverrides.o stringlib.o framerate.o shader.o state.o mathlib.o color.o

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

gloverrides.so: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@ $(LDFLAGS)

debug:	CFLAGS= -Wall -O0 -g -fstrict-aliasing -march=native -fPIC
debug: 	$(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@.so $(LDFLAGS)
clean:
	rm -f $(OBJECTS)
