# ----------------------------------------------------------------------
#  This file is part of jnutils, made public 2023, (c) Jeff Nye.
#  See LICENSE in the root directory.
# ----------------------------------------------------------------------
.PHONY: default tar clean

default:
	$(MAKE) -C _makefile only
	$(MAKE) -C msg only
	$(MAKE) -C mshell only
	$(MAKE) -C mshtcp only
	$(MAKE) -C program_options only

tar:
	$(MAKE) clean
	tar jcvf jnutils.bz2 \
    Makefile README.md LICENSE Vars.mk \
  	_makefile \
  	msg \
	  mshell \
    mshtcp \
    program_options \

clean:
	$(MAKE) -C _makefile clean
	$(MAKE) -C msg clean
	$(MAKE) -C mshell clean
	$(MAKE) -C mshtcp clean
	$(MAKE) -C program_options clean

