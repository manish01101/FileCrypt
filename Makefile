# Compiler
CXX = g++

# Compiler flags (added -arch arm64 for Apple Silicon)
CXXFLAGS = -std=c++17 -g -Wall -arch arm64 -I. -Isrc/app/encryptDecrypt -Isrc/app/fileHandling -Isrc/app/processes

# Targets
MAIN_TARGET = encrypt_decrypt
CRYPTION_TARGET = cryption

# Source files
MAIN_SRC = main.cpp \
           src/app/processes/ProcessManagement.cpp \
           src/app/fileHandling/IO.cpp \
           src/app/fileHandling/ReadEnv.cpp \
           src/app/encryptDecrypt/Cryption.cpp

CRYPTION_SRC = src/app/encryptDecrypt/CryptionMain.cpp \
               src/app/encryptDecrypt/Cryption.cpp \
               src/app/fileHandling/IO.cpp \
               src/app/fileHandling/ReadEnv.cpp

# Object files (changed from `.o` to `build/*.o` for better organization)
BUILD_DIR = build
MAIN_OBJ = $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(MAIN_SRC))
CRYPTION_OBJ = $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(CRYPTION_SRC))

# Default build target
all: $(MAIN_TARGET) $(CRYPTION_TARGET)

# Build executables
$(MAIN_TARGET): $(MAIN_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(CRYPTION_TARGET): $(CRYPTION_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compile .cpp to .o (ensuring build directory exists)
$(BUILD_DIR)/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean all compiled files
clean:
	rm -rf $(BUILD_DIR) $(MAIN_TARGET) $(CRYPTION_TARGET)

.PHONY: clean all
