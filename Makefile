CC=g++
XENOCFLAGS=`/usr/xenomai/bin/xeno-config --skin native --cflags`
XENOLDFLAGS=`/usr/xenomai/bin/xeno-config --skin native --ldflags`
CFLAGS=-I. `pkg-config opencv --cflags --libs` $(XENOCFLAGS)
LDFLAGS=$(XENOLDFLAGS) -Xlinker -rpath -Xlinker /usr/xenomai/lib
DEPS=ImageCapturer.h LEDController.h Recognizer.h
OBJ=main.o LEDController.o ImageCapturer.o Recognizer.o

all: plane

plane: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm *.o plane
