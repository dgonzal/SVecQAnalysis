# Package information
LIBRARY = SVecQAnalysis
OBJDIR  = obj
DEPDIR  = $(OBJDIR)/dep
SRCDIR  = src
INCDIR  = include

USERLDFLAGS += $(shell root-config --libs) -lMinuit 

# Include the generic compilation rules
include $(SFRAME_DIR)/SFrameTools/Makefile.defs


