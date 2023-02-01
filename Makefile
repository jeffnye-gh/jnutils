.PHONY: default tar clean

default:
	$(MAKE) -C mshtcp
	$(MAKE) -C mshell

tar:
	tar jcvf jnutils.bz2 msg mshell mshtcp Vars.mk Makefile README.md LICENSE
clean:
	$(MAKE) -C mshtcp clean
	$(MAKE) -C mshell clean
