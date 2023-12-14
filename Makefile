SUBDIRS := question-2 question-3

.PHONY: all run clean $(SUBDIRS)

all: $(SUBDIRS)

run: run-question-1 run-question-2

run-question-2: clean
	$(MAKE) -C question-2 run N=128 TIMES=10
	$(MAKE) -C question-2 run N=512 TIMES=10

run-question-3:
	#$(MAKE) -C question-3 run N=128
	$(MAKE) -C question-3 run N=1024

$(SUBDIRS):
	$(MAKE) -C $@

clean:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir clean; \
	done