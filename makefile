# VC6 makefile

BIN_DIR = bin
INCLUDE_DIR = include
OBJ_DIR = obj
RC_DIR = rc
SRC_DIR = src

RC_FILE = $(RC_DIR)\main.rc
CPP_FILES = $(SRC_DIR)\*.cpp

RES_FILE = $(OBJ_DIR)\main.RES
OBJ_FILES = $(OBJ_DIR)\*.obj

OUTPUT_FILE = $(BIN_DIR)\thruster_toggle.dll

CXX_FLAGS = /c /GX /O2 /nologo /W3 /WX /LD /MD
LD_FLAGS = /DLL /FILEALIGN:512 /NOLOGO /RELEASE

$(OUTPUT_FILE): $(OBJ_DIR) $(BIN_DIR) $(RC_FILE) $(RES_FILE) $(CPP_FILES) $(OBJ_FILES)
    link $(OBJ_FILES) $(RES_FILE) $(LD_FLAGS) /OUT:$(OUTPUT_FILE)

{$(SRC_DIR)}.cpp{$(OBJ_DIR)}.obj::
    $(CPP) $(CXX_FLAGS) $< -I$(INCLUDE_DIR) /Fo./$(OBJ_DIR)/

$(RES_FILE): $(RC_FILE)
    rc /fo $(RES_FILE) $(RC_FILE)

$(BIN_DIR):
    if not exist $(BIN_DIR) mkdir $(BIN_DIR)

$(OBJ_DIR):
    if not exist $(OBJ_DIR) mkdir $(OBJ_DIR)

# Dependencies
$(SRC_DIR)\hook_manager.cpp: $(INCLUDE_DIR)\hook_manager.h $(INCLUDE_DIR)\utils.h
$(SRC_DIR)\hooks.cpp: $(INCLUDE_DIR)\hooks.h
$(SRC_DIR)\main.cpp: $(INCLUDE_DIR)\main.h $(INCLUDE_DIR)\utils.h $(INCLUDE_DIR)\hooks.h $(INCLUDE_DIR)\hook_manager.h
$(SRC_DIR)\utils.cpp: $(INCLUDE_DIR)\utils.h
