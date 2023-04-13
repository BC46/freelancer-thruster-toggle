# VC6 makefile

all: build clean

build: thruster_toggle.cpp thruster_toggle.res
	cl /GX /O2 /nologo /W4 /WX /LD /MD $** /link /filealign:512

clean:
	del *.obj *.RES