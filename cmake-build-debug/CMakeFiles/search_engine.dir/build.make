# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/rayaanirani/Desktop/Search-Engine

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/rayaanirani/Desktop/Search-Engine/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/search_engine.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/search_engine.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/search_engine.dir/flags.make

CMakeFiles/search_engine.dir/main.cpp.o: CMakeFiles/search_engine.dir/flags.make
CMakeFiles/search_engine.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/rayaanirani/Desktop/Search-Engine/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/search_engine.dir/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/search_engine.dir/main.cpp.o -c /Users/rayaanirani/Desktop/Search-Engine/main.cpp

CMakeFiles/search_engine.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/search_engine.dir/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/rayaanirani/Desktop/Search-Engine/main.cpp > CMakeFiles/search_engine.dir/main.cpp.i

CMakeFiles/search_engine.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/search_engine.dir/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/rayaanirani/Desktop/Search-Engine/main.cpp -o CMakeFiles/search_engine.dir/main.cpp.s

CMakeFiles/search_engine.dir/DocumentParser.cpp.o: CMakeFiles/search_engine.dir/flags.make
CMakeFiles/search_engine.dir/DocumentParser.cpp.o: ../DocumentParser.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/rayaanirani/Desktop/Search-Engine/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/search_engine.dir/DocumentParser.cpp.o"
	/Applications/Xcode.app/Contents/Developer/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/search_engine.dir/DocumentParser.cpp.o -c /Users/rayaanirani/Desktop/Search-Engine/DocumentParser.cpp

CMakeFiles/search_engine.dir/DocumentParser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/search_engine.dir/DocumentParser.cpp.i"
	/Applications/Xcode.app/Contents/Developer/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/rayaanirani/Desktop/Search-Engine/DocumentParser.cpp > CMakeFiles/search_engine.dir/DocumentParser.cpp.i

CMakeFiles/search_engine.dir/DocumentParser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/search_engine.dir/DocumentParser.cpp.s"
	/Applications/Xcode.app/Contents/Developer/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/rayaanirani/Desktop/Search-Engine/DocumentParser.cpp -o CMakeFiles/search_engine.dir/DocumentParser.cpp.s

CMakeFiles/search_engine.dir/IndexHandler.cpp.o: CMakeFiles/search_engine.dir/flags.make
CMakeFiles/search_engine.dir/IndexHandler.cpp.o: ../IndexHandler.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/rayaanirani/Desktop/Search-Engine/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/search_engine.dir/IndexHandler.cpp.o"
	/Applications/Xcode.app/Contents/Developer/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/search_engine.dir/IndexHandler.cpp.o -c /Users/rayaanirani/Desktop/Search-Engine/IndexHandler.cpp

CMakeFiles/search_engine.dir/IndexHandler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/search_engine.dir/IndexHandler.cpp.i"
	/Applications/Xcode.app/Contents/Developer/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/rayaanirani/Desktop/Search-Engine/IndexHandler.cpp > CMakeFiles/search_engine.dir/IndexHandler.cpp.i

CMakeFiles/search_engine.dir/IndexHandler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/search_engine.dir/IndexHandler.cpp.s"
	/Applications/Xcode.app/Contents/Developer/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/rayaanirani/Desktop/Search-Engine/IndexHandler.cpp -o CMakeFiles/search_engine.dir/IndexHandler.cpp.s

CMakeFiles/search_engine.dir/ResearchDocument.cpp.o: CMakeFiles/search_engine.dir/flags.make
CMakeFiles/search_engine.dir/ResearchDocument.cpp.o: ../ResearchDocument.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/rayaanirani/Desktop/Search-Engine/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/search_engine.dir/ResearchDocument.cpp.o"
	/Applications/Xcode.app/Contents/Developer/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/search_engine.dir/ResearchDocument.cpp.o -c /Users/rayaanirani/Desktop/Search-Engine/ResearchDocument.cpp

CMakeFiles/search_engine.dir/ResearchDocument.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/search_engine.dir/ResearchDocument.cpp.i"
	/Applications/Xcode.app/Contents/Developer/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/rayaanirani/Desktop/Search-Engine/ResearchDocument.cpp > CMakeFiles/search_engine.dir/ResearchDocument.cpp.i

CMakeFiles/search_engine.dir/ResearchDocument.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/search_engine.dir/ResearchDocument.cpp.s"
	/Applications/Xcode.app/Contents/Developer/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/rayaanirani/Desktop/Search-Engine/ResearchDocument.cpp -o CMakeFiles/search_engine.dir/ResearchDocument.cpp.s

CMakeFiles/search_engine.dir/QueryProcessor.cpp.o: CMakeFiles/search_engine.dir/flags.make
CMakeFiles/search_engine.dir/QueryProcessor.cpp.o: ../QueryProcessor.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/rayaanirani/Desktop/Search-Engine/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/search_engine.dir/QueryProcessor.cpp.o"
	/Applications/Xcode.app/Contents/Developer/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/search_engine.dir/QueryProcessor.cpp.o -c /Users/rayaanirani/Desktop/Search-Engine/QueryProcessor.cpp

CMakeFiles/search_engine.dir/QueryProcessor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/search_engine.dir/QueryProcessor.cpp.i"
	/Applications/Xcode.app/Contents/Developer/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/rayaanirani/Desktop/Search-Engine/QueryProcessor.cpp > CMakeFiles/search_engine.dir/QueryProcessor.cpp.i

CMakeFiles/search_engine.dir/QueryProcessor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/search_engine.dir/QueryProcessor.cpp.s"
	/Applications/Xcode.app/Contents/Developer/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/rayaanirani/Desktop/Search-Engine/QueryProcessor.cpp -o CMakeFiles/search_engine.dir/QueryProcessor.cpp.s

CMakeFiles/search_engine.dir/porter2_stemmer.cpp.o: CMakeFiles/search_engine.dir/flags.make
CMakeFiles/search_engine.dir/porter2_stemmer.cpp.o: ../porter2_stemmer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/rayaanirani/Desktop/Search-Engine/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/search_engine.dir/porter2_stemmer.cpp.o"
	/Applications/Xcode.app/Contents/Developer/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/search_engine.dir/porter2_stemmer.cpp.o -c /Users/rayaanirani/Desktop/Search-Engine/porter2_stemmer.cpp

CMakeFiles/search_engine.dir/porter2_stemmer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/search_engine.dir/porter2_stemmer.cpp.i"
	/Applications/Xcode.app/Contents/Developer/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/rayaanirani/Desktop/Search-Engine/porter2_stemmer.cpp > CMakeFiles/search_engine.dir/porter2_stemmer.cpp.i

CMakeFiles/search_engine.dir/porter2_stemmer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/search_engine.dir/porter2_stemmer.cpp.s"
	/Applications/Xcode.app/Contents/Developer/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/rayaanirani/Desktop/Search-Engine/porter2_stemmer.cpp -o CMakeFiles/search_engine.dir/porter2_stemmer.cpp.s

# Object files for target search_engine
search_engine_OBJECTS = \
"CMakeFiles/search_engine.dir/main.cpp.o" \
"CMakeFiles/search_engine.dir/DocumentParser.cpp.o" \
"CMakeFiles/search_engine.dir/IndexHandler.cpp.o" \
"CMakeFiles/search_engine.dir/ResearchDocument.cpp.o" \
"CMakeFiles/search_engine.dir/QueryProcessor.cpp.o" \
"CMakeFiles/search_engine.dir/porter2_stemmer.cpp.o"

# External object files for target search_engine
search_engine_EXTERNAL_OBJECTS =

search_engine: CMakeFiles/search_engine.dir/main.cpp.o
search_engine: CMakeFiles/search_engine.dir/DocumentParser.cpp.o
search_engine: CMakeFiles/search_engine.dir/IndexHandler.cpp.o
search_engine: CMakeFiles/search_engine.dir/ResearchDocument.cpp.o
search_engine: CMakeFiles/search_engine.dir/QueryProcessor.cpp.o
search_engine: CMakeFiles/search_engine.dir/porter2_stemmer.cpp.o
search_engine: CMakeFiles/search_engine.dir/build.make
search_engine: CMakeFiles/search_engine.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/rayaanirani/Desktop/Search-Engine/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable search_engine"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/search_engine.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/search_engine.dir/build: search_engine
.PHONY : CMakeFiles/search_engine.dir/build

CMakeFiles/search_engine.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/search_engine.dir/cmake_clean.cmake
.PHONY : CMakeFiles/search_engine.dir/clean

CMakeFiles/search_engine.dir/depend:
	cd /Users/rayaanirani/Desktop/Search-Engine/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/rayaanirani/Desktop/Search-Engine /Users/rayaanirani/Desktop/Search-Engine /Users/rayaanirani/Desktop/Search-Engine/cmake-build-debug /Users/rayaanirani/Desktop/Search-Engine/cmake-build-debug /Users/rayaanirani/Desktop/Search-Engine/cmake-build-debug/CMakeFiles/search_engine.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/search_engine.dir/depend

