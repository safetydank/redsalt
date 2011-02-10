# Copyright 2010, The Native Client SDK Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can
# be found in the LICENSE file.

.PHONY: all clean

# soft-links to SDK dirs
CINDER_SDK_ROOT = cinder
NACL_SDK_ROOT 	= native_client_sdk

DIST_DIR   = dist
SOURCE_DIR = src

SOURCE = red/gl.cc \
		 red/GlslProg.cc \
		 red/Vbo.cc \
		 cube.cc \
         npn_bridge.cc \
         npp_gate.cc \
         tumbler.cc \
         tumbler_module.cc \
         scripting_bridge.cc \
         transforms.cc

# a growing selection of modules from Cinder
CINDER_SOURCE = Camera.cpp \
				Color.cpp \
				Matrix.cpp \
				Perlin.cpp

VPATH = nacl_module

CCFILES 	   = $(SOURCE:%.cc=$(SOURCE_DIR)/%.cc)
CINDER_CCFILES = $(CINDER_SOURCE:%.cpp=$(CINDER_SDK_ROOT)/src/cinder/%.cpp)
OBJECTS_X86_32 = $(CCFILES:%.cc=%_x86_32.o) $(CINDER_CCFILES:%.cpp=%_x86_32.o)
OBJECTS_X86_64 = $(CCFILES:%.cc=%_x86_64.o) $(CINDER_CCFILES:%.cpp=%_x86_64.o)

CFLAGS = -Wall -Wno-long-long -pthread -DXP_UNIX -DCINDER_GLES2 -Werror -Wno-reorder -Wno-unused
INCLUDES = -I$(NACL_SDK_ROOT) -Iinclude -I$(CINDER_SDK_ROOT)/include -I$(CINDER_SDK_ROOT)/boost
LDFLAGS = -lgoogle_nacl_imc \
          -lgoogle_nacl_npruntime \
          -lpthread \
          -lsrpc \
          -lgoogle_nacl_pgl \
          -lgoogle_nacl_gpu
OPT_FLAGS = -O2

SHADERS = v_red.glsl \
		  f_red.glsl
SHADER_HEADERS = $(SHADERS:%=include/shaders/%.h)

%.glsl.h: %.glsl
	python dev/glsl2h.py $< $@

all: check_variables $(SHADER_HEADERS) tumbler_x86_32.nexe tumbler_x86_64.nexe

tags: $(CCFILES) $(CINDER_CCFILES)
	ctags -R cinder/include cinder/src include src

# common.mk has rules to build .o files from .cc files.
-include common.mk

tumbler_x86_32.nexe: $(OBJECTS_X86_32)
	$(CPP) $^ $(LDFLAGS) -m32 -o $(DIST_DIR)/$@

tumbler_x86_64.nexe: $(OBJECTS_X86_64)
	$(CPP) $^ $(LDFLAGS) -m64 -o $(DIST_DIR)/$@

# dev alias
rs: tumbler_x86_64.nexe

clean:
	-$(RM) $(OBJECTS_X86_32) $(OBJECTS_X86_64) \
	    $(DIST_DIR)/tumbler_x86_32.nexe $(DIST_DIR)/tumbler_x86_64.nexe \
		$(SHADER_HEADERS)

