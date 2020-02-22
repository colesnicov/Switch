#
# "main" pseudo-component makefile.
#
# (Uses default behaviour of compiling all source files in directory, adding 'include' to include path.)


COMPONENT_ADD_INCLUDEDIRS := . Switch SimplyAtomic
COMPONENT_SRCDIRS := . Switch SimplyAtomic
CXXFLAGS += -Wno-ignored-qualifiers