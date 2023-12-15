CC = gcc
CPPFLAGS = -DEMBEDDED_COMPILERS_N=$(EMBEDDED_COMPILERS_N) -I../utils/
CFLAGS =
LDFLAGS =
LDLIBS = -lpapi

all: exercise

exercise: exercise.c ../utils/utils.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $^ $(LDFLAGS) $(LDLIBS) -o $@-$(EMBEDDED_COMPILERS_N)

run: exercise
	export PAPI_EVENTS="PAPI_L1_DCA, PAPI_L1_DCM" && \
	export PAPI_MULTIPLEX=1 && \
	export PAPI_OUTPUT_DIRECTORY="./papi-output-$(EMBEDDED_COMPILERS_N)" && \
	../../scripts/runner.sh $(CURDIR)/exercise-$(EMBEDDED_COMPILERS_N) $(TIMES) && \
	../../scripts/stats-calculator.py -p ./papi-output-$(EMBEDDED_COMPILERS_N) -o ./papi-output-$(EMBEDDED_COMPILERS_N)/stats.txt

clean:
	rm -rf exercise-* exercise-$(EMBEDDED_COMPILERS_N).o papi-output*

.PHONY: all clean