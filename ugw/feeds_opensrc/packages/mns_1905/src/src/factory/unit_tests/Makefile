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
#   COMMON_LIB ----> Absolute path to the "common library" *.a file
#   COMMON_INC ----> Absolute path to the folder containing common (to all
#                    sub-projects) header files

#   FACTORY_LIB   -> Absolute path to the "factory library" *.a file 
#   FACTORY_INC   -> Absolute path to the folder containing the "factory
#                    library" header files
#
#   MKDIR ---------> Tool to create a directory
#
UNIT_TESTS_DIRECTORY := factory/unit_tests

UNITS := 1905_tlv_forging
UNITS += 1905_tlv_parsing
UNITS += 1905_cmdu_forging
UNITS += 1905_cmdu_parsing
UNITS += 1905_alme_forging
UNITS += 1905_alme_parsing
UNITS += lldp_tlv_parsing
UNITS += lldp_payload_forging
UNITS += lldp_payload_parsing

UNITS += extensions/bbf/bbf_tlv_forging
UNITS += extensions/bbf/bbf_tlv_parsing

EXE  := $(addprefix $(OUTPUT_FOLDER)/UNITTEST_, $(UNITS))
SRC  := $(addsuffix .c, $(UNITS))
OBJ  := $(addprefix $(OUTPUT_FOLDER)/tmp/$(UNIT_TESTS_DIRECTORY)/, $(addsuffix .o, $(UNITS)))


INTERNAL_INC := . $(sort $(dir $(wildcard extensions/*/)))
EXTERNAL_INC := $(COMMON_INC) $(FACTORY_INC)

HDR := $(shell find $(INTERNAL_INC) $(EXTERNAL_INC) -name "*.h")

SHARED_SRC := $(wildcard *test_vectors.c)
SHARED_SRC += $(wildcard extensions/*/*test_vectors.c)
SHARED_OBJ := $(addprefix $(OUTPUT_FOLDER)/tmp/$(UNIT_TESTS_DIRECTORY)/,$(patsubst %.c,%.o,$(SHARED_SRC)))
SHARED_HDR := $(patsubst %.c,%.h,$(SHARED_SRC))

#LDFLAGS += -fdata-sections -ffunction-sections -Wl,--gc-sections

TESTS      := $(addprefix UNITTEST_,$(basename $(UNITS)))

################################################################################
# Targets
################################################################################

.PHONY: all
all: $(TESTS) 


.PHONY: $(TESTS)
$(TESTS) : UNITTEST_% : $(OUTPUT_FOLDER)/UNITTEST_%
	$<


$(EXE) : $(OUTPUT_FOLDER)/UNITTEST_% : $(OUTPUT_FOLDER)/tmp/$(UNIT_TESTS_DIRECTORY)/%.o $(SHARED_OBJ) $(COMMON_LIB) $(FACTORY_LIB)
	$(foreach directory, $(UNITS), $(MKDIR) $(OUTPUT_FOLDER)/UNITTEST_$(shell dirname $(directory);))
	$(CC) $(LDFLAGS) $^ -o $@

$(OBJ) : $(OUTPUT_FOLDER)/tmp/$(UNIT_TESTS_DIRECTORY)/%.o : %.c 
	$(foreach directory, $(sort $(dir $(wildcard $(SRC)))), $(MKDIR) $(OUTPUT_FOLDER)/tmp/$(UNIT_TESTS_DIRECTORY)/$(directory);)
	$(CC)  $(CCFLAGS) -c $(addprefix -I,$(INTERNAL_INC) $(EXTERNAL_INC)) $< -o $@;


$(SHARED_OBJ) : $(OUTPUT_FOLDER)/tmp/$(UNIT_TESTS_DIRECTORY)/%.o : %.c $(SHARED_HDR)
	$(foreach directory, $(sort $(dir $(wildcard $(SHARED_SRC)))), $(MKDIR) $(OUTPUT_FOLDER)/tmp/$(UNIT_TESTS_DIRECTORY)/$(directory);)
	$(CC)  $(CCFLAGS) -c $(addprefix -I,$(INTERNAL_INC) $(EXTERNAL_INC)) $< -o $@;


.PHONY: clean
clean:
	rm -f $(EXE)
	rm -rf $(OUTPUT_FOLDER)/UNITTEST_*
	rm -rf $(OUTPUT_FOLDER)/tmp/UNITTEST_*
	rm -rf $(OUTPUT_FOLDER)/tmp/$(UNIT_TESTS_DIRECTORY)
