# Compiler and tools
CXX = g++
CXXFLAGS = -Wall -std=c++17 -Iinclude -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lSDL2 -lSDL2main
NVCC = nvcc
NVCCFLAGS = -O3 -Iinclude 

# Directories
SRCDIR = src
INCDIR = include
OBJDIR = obj
RESOURCESDIR = resource

# Find all source files
SRCS = $(wildcard $(SRCDIR)/*.cpp $(SRCDIR)/*.cu)
OBJS = $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
OBJS += $(SRCS:$(SRCDIR)/%.cu=$(OBJDIR)/%.o)

# Executable
TARGET = VPWC

# Default rule
all: $(TARGET)

# Build executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

# Rule to compile .cpp files into .o files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to compile .cu files into .o files
$(OBJDIR)/%.o: $(SRCDIR)/%.cu | $(OBJDIR)
	$(NVCC) $(NVCCFLAGS) -c $< -o $@

# Create the object directory if it doesn't exist
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Clean rule
clean:
	rm -f $(OBJDIR)/*.o $(TARGET)

.PHONY: all clean
