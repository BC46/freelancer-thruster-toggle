# VC6 makefile

BIN_DIR = bin
INCLUDE_DIR = include
OBJ_DIR = obj
RC_DIR = rc
SRC_DIR = src
DEF_DIR = def

RC_FILE = $(RC_DIR)\main.rc
CPP_FILES = $(SRC_DIR)\*.cpp
DEF_FILE = $(DEF_DIR)\common.def

RES_FILE = $(OBJ_DIR)\main.RES
OBJ_FILES = $(OBJ_DIR)\*.obj
LIB_FILE = $(OBJ_DIR)\common.lib

OUTPUT_FILE = $(BIN_DIR)\thruster_toggle.dll

CXX_FLAGS = /c /GX /O2 /nologo /W3 /WX /LD /MD
LD_FLAGS = /DLL /FILEALIGN:512 /NOLOGO /RELEASE
LIB_FLAGS = /NOLOGO /MACHINE:IX86

$(OUTPUT_FILE): $(OBJ_DIR) $(RES_FILE) $(LIB_FILE) $(RC_FILE) $(DEF_FILE) $(INCLUDE_DIR)\common.h $(CPP_FILES) $(OBJ_FILES)
    link $(OBJ_FILES) $(LIB_FILE) $(RES_FILE) $(LD_FLAGS) /OUT:$(OUTPUT_FILE)

{$(SRC_DIR)}.cpp{$(OBJ_DIR)}.obj::
    $(CPP) $(CXX_FLAGS) $< -I$(INCLUDE_DIR) /Fo./$(OBJ_DIR)/

$(RES_FILE): $(RC_FILE)
    rc /fo $(RES_FILE) $(RC_FILE)

$(LIB_FILE): $(DEF_FILE) $(INCLUDE_DIR)\common.h
    lib $(LIB_FLAGS) /def:$(DEF_FILE) /name:COMMON /out:$(LIB_FILE)

$(OBJ_DIR):
    if not exist $(OBJ_DIR) mkdir $(OBJ_DIR)

# Dependencies
$(INCLUDE_DIR)\common.h: $(DEF_FILE)
$(SRC_DIR)\config_reader.cpp: $(INCLUDE_DIR)\config_reader.h $(INCLUDE_DIR)\common.h
$(SRC_DIR)\hook_manager.cpp: $(INCLUDE_DIR)\hook_manager.h $(INCLUDE_DIR)\utils.h
$(SRC_DIR)\hooks.cpp: $(INCLUDE_DIR)\hooks.h
$(SRC_DIR)\main.cpp: $(INCLUDE_DIR)\main.h $(INCLUDE_DIR)\utils.h $(INCLUDE_DIR)\hooks.h $(INCLUDE_DIR)\hook_manager.h $(INCLUDE_DIR)\config_reader.h
$(SRC_DIR)\utils.cpp: $(INCLUDE_DIR)\utils.h
