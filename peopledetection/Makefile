#@Author Dr. Ing. Koen Gilissen
#
#Make 
#	build: build  OUTPUT
#	run: run the  OUTPUT
#	clean: remove OUTPUT 
#	all: clean->build->run
#Make OUT=foo -->  an executable 'foo' will be build/run/cleaned
#Make S=code.cpp --> code.cpp will be build 
#


#--->> Build Settings<---#
OUTPUT:=program
BUILDDIR := .
#------------------------#

UNAME_S := $(shell uname -s)
PWD_S := $(shell pwd)

ifndef OUT
	OUTPUT:= program
else
	OUTPUT:= $(OUT)
endif 

ifndef S
	SOURCE:= main.cpp
else
	SOURCE:= $(S)
endif

# Compiler Settings
ifeq ($(UNAME_S),Darwin)
  CC := clang++ -arch x86_64 #default compiler for iOS & OSX + google
else
  CC := g++
endif

CFLAGS:=-ggdb `pkg-config --cflags --libs opencv4`

#Tasks 

all: clean build run

build: $(SOURCE)
	@date
	@echo "[INFO]: Running in $(PWD_S)"
	@echo "[INFO]: Building for architecture $(UNAME_S)"
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) $(SOURCE) -o $(BUILDDIR)/$(OUTPUT)

run: 
	./$(OUTPUT)

clean:
	@echo "[INFO]: Cleaning $(BUILDDIR)/$(OUTPUT)"
	rm -fr $(BUILDDIR)/$(OUTPUT)
