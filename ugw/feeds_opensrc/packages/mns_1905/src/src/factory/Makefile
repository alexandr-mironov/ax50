###############################################################################
#  
# Copyright (c) 2017, Broadband Forum
# Copyright (c) 2017, MaxLinear, Inc. and its affiliates
# 
# Redistribution and use in source and binary forms, with or
# without modification, are permitted provided that the following
# conditions are met:
# 
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 
# 2. Redistributions in binary form must reproduce the above
#    copyright notice, this list of conditions and the following
#    disclaimer in the documentation and/or other materials
#    provided with the distribution.
# 
# 3. Neither the name of the copyright holder nor the names of its
#    contributors may be used to endorse or promote products
#    derived from this software without specific prior written
#    permission.
# 
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
# CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
# INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
# MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
# CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
# SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
# NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
# STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
# ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
# 
# The above license is used as a license under copyright only.
# Please reference the Forum IPR Policy for patent licensing terms
# <https://www.broadband-forum.org/ipr-policy>.
# 
# Any moral rights which are necessary to exercise under the above
# license grant are also deemed granted under this license.

# When calling this Makefile, the following environment variables must be set:
#
#   CC ------------> Path to the compiler
#   CCFLAGS -------> Extra flags to use while compiling
#
#   OUTPUT_FOLDER -> Absolute path to the folder where binaries will be built
#
#   COMMON_INC ----> Absolute path to the folder containing common (to all
#                    sub-projects) header files
#
#   FACTORY_LIB ---> Absolute path to the "factory library" *.a file 
#
#   MKDIR ---------> Tool to create a directory
#

FACTORY_DIRECTORY := factory

LIB               := $(FACTORY_LIB)
SRC               := $(wildcard src_independent/*.c)
SRC               += $(wildcard src_independent/extensions/*/*.c)
OBJ               := $(patsubst %.c,$(OUTPUT_FOLDER)/tmp/$(FACTORY_DIRECTORY)/%.o,$(SRC))

INTERNAL_INC      := src_independent interfaces
INTERNAL_INC      += $(sort $(dir $(wildcard interfaces/extensions/*/)))
EXTERNAL_INC      := $(COMMON_INC)

HDR               := $(shell find $(INTERNAL_INC) $(EXTERNAL_INC) -name *.h)


################################################################################
# Targets
################################################################################

.PHONY: all
all: $(LIB)


$(LIB) : $(OBJ)
	$(AR) -rc $@ $^


$(OBJ) : $(OUTPUT_FOLDER)/tmp/$(FACTORY_DIRECTORY)/%.o : %.c $(HDR)
	$(foreach directory, $(sort $(dir $(wildcard $(SRC)))), $(MKDIR) $(OUTPUT_FOLDER)/tmp/$(FACTORY_DIRECTORY)/$(directory);)
	$(CC) $(CCFLAGS) -c $(addprefix -I,$(INTERNAL_INC) $(EXTERNAL_INC)) $< -o $@


.PHONY: unit_tests
unit_tests:
	$(MAKE) -C unit_tests all


.PHONY: clean
clean:
	rm -rf $(LIB)
	rm -rf $(OUTPUT_FOLDER)/tmp/$(FACTORY_DIRECTORY)
	$(MAKE) -C unit_tests clean

