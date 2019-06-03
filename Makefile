CXX ?= g++

# path #
SRC_PATH = src
INCLUDE_PATH = include
BUILD_PATH = build
BIN_PATH = $(BUILD_PATH)/bin

# executable # 
BIN_NAME = PiranhasClientCPP

# extensions #
SRC_EXT = cpp
INCLUDES_EXT = hpp

# code lists #
# Find all source files in the source directory, sorted by
# most recently modified
SOURCES = $(shell find $(SRC_PATH) -maxdepth 8 -name '*.$(SRC_EXT)' | sort -k 1nr | cut -f2-)
INCLUDES = $(shell find $(INCLUDE_PATH) -maxdepth 8 -name '*.$(INCLUDES_EXT)' | sort -k 1nr | cut -f2-)
# Set the object file names, with the source directory stripped
# from the path, and the build path prepended in its place
OBJECTS = $(SOURCES:$(SRC_PATH)/%.$(SRC_EXT)=$(BUILD_PATH)/%.o)
# Set the dependency files that will be used to add header dependencies
DEPS = $(OBJECTS:.o=.d)

# flags #
COMPILE_FLAGS = -std=c++14 -Wall -Wextra -Ofast
COMPILE_FLAGS_DEBUG = -std=c++14 -Wall -Wextra -g -Og
INCLUDES = -I include/ -I include/Logic/ -I include/Search/ -I include/Search/MoveOrdering -I include/Search/Heuristics -I include/Search/Helpers/ -I include/Search/MCTS/ -I include/Search/Minimax -I include/Search/Negamax/ -I include/Search/NullMoveSearch/ -I include/Evaluation/ -I include/Client/ -I include/Piranhas/ -I include/Piranhas/Communication/ -I include/PugiXmlAdditions/ -I /usr/local/include -I /usr/lib/
# Space-separated pkg-config libraries used by this project
LIBS = -static -L /usr/lib/ -lboost_system -lboost_thread -lpthread -lboost_program_options
LIBS_DEBUG = -static -L /usr/lib/ -lboost_system -lboost_thread -lpthread -lboost_program_options

.PHONY: default_target
default_target: debug

.PHONY: debug
debug: export CXXFLAGS := $(CXXFLAGS) $(COMPILE_FLAGS_DEBUG)
debug: dirs
	@$(MAKE) all_Debug

.PHONY: release
release: export CXXFLAGS := $(CXXFLAGS) $(COMPILE_FLAGS)
release: dirs
	@$(MAKE) all

.PHONY: dirs
dirs:
	@echo "Creating directories"
	@mkdir -p $(dir $(OBJECTS))
	@mkdir -p $(BIN_PATH)

.PHONY: clean
clean:
	@echo "Deleting $(BIN_NAME) symlink"
	@$(RM) $(BIN_NAME)
	@echo "Deleting directories"
	@$(RM) -r $(BUILD_PATH)
	@$(RM) -r $(BIN_PATH)

# checks the executable and symlinks to the output
.PHONY: all
all: $(BIN_PATH)/$(BIN_NAME)
	@echo "Making symlink: $(BIN_NAME) -> $<"
	@$(RM) $(BIN_NAME)
	@ln -s $(BIN_PATH)/$(BIN_NAME) $(BIN_NAME)

# Creation of the executable
$(BIN_PATH)/$(BIN_NAME): $(OBJECTS)
	@echo "Linking: $@"
	$(CXX) $(OBJECTS) $(LIBS) -o $@

# Add dependency files, if they exist
-include $(DEPS)

# Source file rules
# After the first compilation they will be joined with the rules from the
# dependency files to provide header dependencies
$(BUILD_PATH)/%.o: $(SRC_PATH)/%.$(SRC_EXT)
	@echo "Compiling: $< -> $@"
	$(CXX) $(CXXFLAGS) $(INCLUDES) -MP -MMD -c $< -o $@

.PHONY: all_Debug
all_Debug: $(BIN_PATH)/$(BIN_NAME)
	@echo "Making symlink: $(BIN_NAME) -> $<"
	@$(RM) $(BIN_NAME)
	@ln -s $(BIN_PATH)/$(BIN_NAME) $(BIN_NAME)

# Creation of the executable
$(BIN_PATH)/$(BIN_NAME): $(OBJECTS)
	@echo "Linking: $@"
	$(CXX) $(OBJECTS) $(LIBS_DEBUG) -o $@

# Add dependency files, if they exist
-include $(DEPS)

# Source file rules
# After the first compilation they will be joined with the rules from the
# dependency files to provide header dependencies
$(BUILD_PATH)/%.o: $(SRC_PATH)/%.$(SRC_EXT)
	@echo "Compiling: $< -> $@"
	$(CXX) $(CXXFLAGS) $(INCLUDES) -MP -MMD -c $< -o $@