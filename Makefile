CXX = g++
CXXFLAGS = -std=c++17
TARGET = netxlang

# OS Detection
ifeq ($(OS),Windows_NT)
    EXE = .exe
    RM = del /Q
    FIX_PATH = $(subst /,\,$(1))
else
    EXE =
    RM = rm -f
    FIX_PATH = $(1)
endif

all: $(TARGET)$(EXE)

$(TARGET)$(EXE): main.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET)$(EXE) main.cpp

clean:
	$(RM) $(TARGET)$(EXE)

test: all
	.$(FIX_PATH)/$(TARGET)$(EXE) examples/full_features.nxl
