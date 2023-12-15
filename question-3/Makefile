CC = gcc
CPPFLAGS = -DN=$(N) -DK=$(K) -DGEMM_BLOCK_SIZE=$(GEMM_BLOCK_SIZE) -I../utils/
CFLAGS =
LDFLAGS =
LDLIBS = -lpapi -lblas

all: exercise

exercise: exercise.c ../utils/utils.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $^ $(LDFLAGS) $(LDLIBS) -o $@-$(N)

run: exercise
	export PAPI_EVENTS="PAPI_L1_DCA, PAPI_L1_DCM" && \
	export PAPI_MULTIPLEX=1 && \
	export PAPI_OUTPUT_DIRECTORY="./papi-output-$(N)" && \
	../scripts/runner.sh $(CURDIR)/exercise-$(N) $(TIMES) && \
	../scripts/stats-calculator.py -p ./papi-output-$(N) -o ./papi-output-$(N)/stats.txt

clean:
	rm -rf exercise-* exercise-$(N).o papi-output*

.PHONY: all clean