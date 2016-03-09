# Makefile to compile all the examples

# gcc
GCC=gcc
GCC_FLAGS=-Wall -Wextra -I..

# executables
EXECS=$(patsubst %.c, %.out, $(wildcard *.c))

all: ${EXECS}

# rule to compile
define ex_rule
$(1): $(patsubst %.out, %.c, $(notdir $(1)))
	$$(GCC) $(patsubst %.out, %.c, $(notdir $(1))) -o $(1) $$(GCC_FLAGS)
endef

$(foreach exec,$(EXECS),$(eval $(call ex_rule, $(exec))))
