# VC6 makefile

BIN_DIR = bin
INCLUDE_DIR = include
OBJ_DIR = obj
RC_DIR = rc
SRC_DIR = src

RC_FILE = $(RC_DIR)\main.rc
OBJ_FILES = $(OBJ_DIR)\main.obj $(OBJ_DIR)\utils.obj $(OBJ_DIR)\hooks.obj $(OBJ_DIR)\hook_manager.obj

RES_FILE = $(OBJ_DIR)\main.RES
CPP_FILES = $(SRC_DIR)\main.cpp $(SRC_DIR)\utils.cpp $(SRC_DIR)\hooks.cpp $(SRC_DIR)\hook_manager.cpp

OUTPUT_FILE = $(BIN_DIR)\thruster_toggle.dll

CXX_FLAGS = /c /GX /O2 /nologo /W3 /WX /LD /MD
LD_Flags = /DLL /FILEALIGN:512 /NOLOGO /RELEASE

all: clean_output $(OUTPUT_FILE) clean

$(OUTPUT_FILE): $(BIN_DIR) $(OBJ_FILES) $(RES_FILE)
    link $(OBJ_FILES) $(RES_FILE) $(LD_Flags) /OUT:$(OUTPUT_FILE)

$(OBJ_FILES): $(OBJ_DIR)
    cl $(CXX_FLAGS) $(CPP_FILES) -I$(INCLUDE_DIR) /Fo./$(OBJ_DIR)/

$(RES_FILE): $(OBJ_DIR)
    rc /fo $(RES_FILE) $(RC_FILE)

$(BIN_DIR):
    if not exist $(BIN_DIR) mkdir $(BIN_DIR)

$(OBJ_DIR):
    if not exist $(OBJ_DIR) mkdir $(OBJ_DIR)

clean_output:
    if exist $(OUTPUT_FILE) del $(OUTPUT_FILE)

clean:
    del $(OBJ_FILES) $(RES_FILE)
