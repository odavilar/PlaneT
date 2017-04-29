CC=g++
XENOCFLAGS=`/usr/xenomai/bin/xeno-config --skin native --cflags`
XENOLDFLAGS=`/usr/xenomai/bin/xeno-config --skin native --ldflags`
CPRCFLAGS=`curl-config --cflags --libs` -I /home/debian/Desktop/cpr/cpr-example/opt/cpr/include/ -I /home/debian/Desktop/cpr/cpr-example/opt/json/src/
CPRLDFLAGS=-lcpr -L/home/debian/Desktop/cpr/cpr-example/build/lib/
CFLAGS=-std=c++11 -I. `pkg-config opencv --cflags --libs` $(XENOCFLAGS) $(CPRCFLAGS)
LDFLAGS=$(XENOLDFLAGS) $(CPRLDFLAGS) -Xlinker -rpath -Xlinker /usr/xenomai/lib
DEPS=ImageCapturer.h LEDController.h Recognizer.h
OBJ=main.o LEDController.o ImageCapturer.o Recognizer.o

all: plane

plane: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm *.o plane
