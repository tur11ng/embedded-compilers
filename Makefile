SUBDIRS := question-2 question-3

.PHONY: all run clean $(SUBDIRS)

all: $(SUBDIRS)

run:
	$(MAKE) -C question-2 run N=128
	$(MAKE) -C question-2 run N=1024
	$(MAKE) -C question-3 run N=128
	$(MAKE) -C question-3 run N=1024

$(SUBDIRS):
	$(MAKE) -C $@

clean:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir clean; \
	done