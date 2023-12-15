SUBDIRS := question-2 question-3

.PHONY: all run clean $(SUBDIRS)

all: $(SUBDIRS)

run: run-question-2 run-question-3

run-question-2:
	$(MAKE) -C question-2 clean
	$(MAKE) -C question-2 run N=128 TIMES=10
	$(MAKE) -C question-2 run N=512 TIMES=10

run-question-3:
	$(MAKE) -C question-3 clean
	$(MAKE) -C question-3 run N=128 K=16 GEMM_BLOCK_SIZE=64 TIMES=10
	$(MAKE) -C question-3 run N=1024 K=16 GEMM_BLOCK_SIZE=64 TIMES=10

$(SUBDIRS):
	$(MAKE) -C $@

clean:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir clean; \
	done