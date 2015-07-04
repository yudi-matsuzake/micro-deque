all: exs 

exs:	../deque.h ex*.c
	@for i in ex*.c ; \
	do \
		echo clang "$$i" -o "$${i%.c}.out" -I.. ; \
		clang "$$i" -o "$${i%.c}.out" -I.. ; \
	done ; \

% :
	@if [ $@ != "all" ] ; \
	then \
		gcc $@.c -o $@.out -I.. ; \
	fi ;
