# ----------------------------------------------------------------------
#  This file is part of jnutils, made public 2023, (c) Jeff Nye.
#  See LICENSE in the root directory.
# ----------------------------------------------------------------------
OS   = $(shell lsb_release -si)

CC   = gcc
CPP  = g++
AR   = ar

ifeq ($(OS),Ubuntu)
  MAKE = make
else
  MAKE = make
endif

OBJC = objcopy

#STD = -std=gnu++2a
#STD = -std=c++2a

ifeq ($(OS),Ubuntu)
  STD = -std=c++17
else
  STD = -std=c++2a
endif

CPPSTD = $(STD)

CSTD = -std=c99

VIS = -fvisibility=default
ARFLAGS = rcs
DEF = \
  -DTRACE_EN=1 \
  -DMFM_VIRTUAL=1 \
  -DMFM_ASSERT_EN=1 \
  -DMFM_EVENT_DEBUG=1 \
  -DMFM_VFSB_DEBUG=1

#-DMFM_LIMIT_CHECKS=1
#-DCPP_BUILD

#OPT = -O3 -fPIC
OPT = -g -fPIC -no-pie
