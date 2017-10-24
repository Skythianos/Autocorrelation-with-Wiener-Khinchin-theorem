NAME=autocorrelation_example

FLAGS= -lglut -lGL -lGLU -lGLEW -lgsl -lgslcblas -lm `pkg-config –cflags opencv`
COMPILE= -g -Wall `pkg-config –libs opencv'

$(NAME): $(NAME).o
	g++ -o $@ $< $(FLAGS)
%.o: %.c
	g++  -c $<  -o $@ $(COMPILE)

.PHONY:

clean:
	rm -f *.o

