# ******************************************************************************** #
#       Copyright (c) 2016                                                         #
#       Lantiq Beteiligungs-GmbH & Co. KG                                          #
#       Lilienthalstrasse 15, 85579 Neubiberg, Germany                             #
#       For licensing information, see the file 'LICENSE' in the root folder of    #
#        this software module.                                                     #
# *******************************************************************************  #

# urlfilterd source Makefile
PKG_NAME := urlfilterd 
 
bins := urlfilterd

urlfilterd_sources := urlfilter.c
urlfilterd_ldflags := -lubox -lnetfilter_queue -lnfnetlink 

include make.inc
