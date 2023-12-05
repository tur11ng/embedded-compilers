CC = gcc
CPPFLAGS = -DN=$(N)
CFLAGS =
LDFLAGS =
LDLIBS =

all: exercise

exercise: exercise.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $< $(LDFLAGS) $(LDLIBS) -o $@

run: exercise
	export PAPI_EVENTS="PAPI_FP_OPS,PAPI_L1_DCM,PAPI_L1_ICM,PAPI_L2_DCM,PAPI_TLB_DM,PAPI_TLB_IM,PAPI_TOT_INS, \
			  PAPI_TOT_CYC,PAPI_L1_DCA,PAPI_L2_DCA"
	./exercise

clean:
	rm -f exercise exercise.o

.PHONY: all clean