CC := gcc
CFLAGS := -Wall -Wextra -O2
BINDIR := bin

MAIN_FILES := $(shell find . -maxdepth 2 -name "main.c" -type f | grep -v $(BINDIR))
PROJECTS := $(patsubst ./%,%,$(patsubst %/main.c,%,$(MAIN_FILES)))
TARGETS := $(addprefix $(BINDIR)/,$(notdir $(PROJECTS)))

all: $(BINDIR) $(TARGETS)

$(BINDIR):
	mkdir -p $(BINDIR)

$(BINDIR)/%: %/main.c
	@echo "Building $@ from $<"
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -rf $(BINDIR)
	find . -name "a.out" -type f -delete 2>/dev/null || true
	find . -name "*.o" -type f -delete 2>/dev/null || true

list:
	@echo "MAIN_FILES: $(MAIN_FILES)"
	@echo "PROJECTS: $(PROJECTS)"
	@echo "TARGETS: $(TARGETS)"

test:
	@echo "Testing pattern matching for snake:"
	@echo "Pattern: snake/main.c -> $(BINDIR)/snake"
	@echo "Rule test: $(BINDIR)/snake: snake/main.c"

.PHONY: all clean list test
