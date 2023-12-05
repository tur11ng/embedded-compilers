CC = gcc
CPPFLAGS = -DN=$(N) -DBLOCK_SIZE=10 -DL1_CACHE_LINE_SIZE=64
CFLAGS = -march=native -mavx2 -mfma
LDFLAGS =
LDLIBS = -lblas

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