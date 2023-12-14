CC = gcc
CPPFLAGS = -DN=$(N) -Iutils/
CFLAGS =
LDFLAGS =
LDLIBS = -lpapi

all: exercise

exercise: exercise.c ../utils/utils.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $^ $(LDFLAGS) $(LDLIBS) -o $@-$(N)

run: exercise
	export PAPI_EVENTS="PAPI_L1_DCM, PAPI_L2_DCM"
	./exercise-$(N)

clean:
	rm -f exercise exercise.o

.PHONY: all clean