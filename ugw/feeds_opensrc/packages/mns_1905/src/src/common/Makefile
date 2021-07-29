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
#   PLATFORM      -> Possible values: "linux"
#   OUTPUT_FOLDER -> Absolute path to the folder where binaries will be built
#
#   COMMON_LIB ----> Absolute path to the "common library" *.a file
#
#   MKDIR ---------> Tool to create a directory
#

LIB := $(COMMON_LIB)

COMMON_DIRECTORY := common

SRC_INDEPENDENT  := $(wildcard src_independent/*.c)
SRC_PLATFORM     := $(wildcard src_$(PLATFORM)/*.c)

OBJ_INDEPENDENT  := $(patsubst %.c,$(OUTPUT_FOLDER)/tmp/$(COMMON_DIRECTORY)/%.o,$(SRC_INDEPENDENT))
OBJ_PLATFORM     := $(patsubst %.c,$(OUTPUT_FOLDER)/tmp/$(COMMON_DIRECTORY)/%.o,$(SRC_PLATFORM))

INTERNAL_INC_INDEPENDENT := src_independent interfaces
INTERNAL_INC_PLATFORM    := src_$(PLATFORM) interfaces

EXTERNAL_INC     :=

HDR_INDEPENDENT  := $(shell find $(INTERNAL_INC_INDEPENDENT) $(EXTERNAL_INC) -name *.h)
HDR_PLATFORM     := $(shell find $(INTERNAL_INC_PLATFORM)    $(EXTERNAL_INC) -name *.h)


################################################################################
# Targets
################################################################################

.PHONY: all
all: $(LIB)


$(LIB) : $(OBJ_INDEPENDENT) $(OBJ_PLATFORM)
	$(AR) -rc $@ $^


$(OBJ_INDEPENDENT) : $(OUTPUT_FOLDER)/tmp/$(COMMON_DIRECTORY)/%.o : %.c $(HDR_INDEPENDENT)
	$(foreach directory, $(sort $(dir $(wildcard $(SRC_INDEPENDENT)))), $(MKDIR) $(OUTPUT_FOLDER)/tmp/$(COMMON_DIRECTORY)/$(directory);)
	$(CC) $(CCFLAGS) -c $(addprefix -I,$(INTERNAL_INC_INDEPENDENT) $(EXTERNAL_INC)) $< -o $@

$(OBJ_PLATFORM)    : $(OUTPUT_FOLDER)/tmp/$(COMMON_DIRECTORY)/%.o : %.c $(HDR_PLATFORM)
	$(foreach directory, $(sort $(dir $(wildcard $(SRC_PLATFORM)))), $(MKDIR) $(OUTPUT_FOLDER)/tmp/$(COMMON_DIRECTORY)/$(directory);)
	$(CC) $(CCFLAGS) -c $(addprefix -I,$(INTERNAL_INC_PLATFORM) $(EXTERNAL_INC)) $< -o $@


.PHONY: clean
clean:
	rm -rf $(LIB)
	rm -rf $(OUTPUT_FOLDER)/tmp/$(COMMON_DIRECTORY)

