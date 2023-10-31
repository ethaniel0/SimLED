# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.27.7/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.27.7/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/ethanhorowitz/CLionProjects/SimLED/Tests

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/ethanhorowitz/CLionProjects/SimLED/Tests/build

# Include any dependencies generated for this target.
include Graphics/CMakeFiles/Graphics.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include Graphics/CMakeFiles/Graphics.dir/compiler_depend.make

# Include the progress variables for this target.
include Graphics/CMakeFiles/Graphics.dir/progress.make

# Include the compile flags for this target's objects.
include Graphics/CMakeFiles/Graphics.dir/flags.make

Graphics/CMakeFiles/Graphics.dir/GraphicsUtils.cpp.o: Graphics/CMakeFiles/Graphics.dir/flags.make
Graphics/CMakeFiles/Graphics.dir/GraphicsUtils.cpp.o: /Users/ethanhorowitz/CLionProjects/SimLED/Graphics/GraphicsUtils.cpp
Graphics/CMakeFiles/Graphics.dir/GraphicsUtils.cpp.o: Graphics/CMakeFiles/Graphics.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/ethanhorowitz/CLionProjects/SimLED/Tests/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object Graphics/CMakeFiles/Graphics.dir/GraphicsUtils.cpp.o"
	cd /Users/ethanhorowitz/CLionProjects/SimLED/Tests/build/Graphics && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT Graphics/CMakeFiles/Graphics.dir/GraphicsUtils.cpp.o -MF CMakeFiles/Graphics.dir/GraphicsUtils.cpp.o.d -o CMakeFiles/Graphics.dir/GraphicsUtils.cpp.o -c /Users/ethanhorowitz/CLionProjects/SimLED/Graphics/GraphicsUtils.cpp

Graphics/CMakeFiles/Graphics.dir/GraphicsUtils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Graphics.dir/GraphicsUtils.cpp.i"
	cd /Users/ethanhorowitz/CLionProjects/SimLED/Tests/build/Graphics && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/ethanhorowitz/CLionProjects/SimLED/Graphics/GraphicsUtils.cpp > CMakeFiles/Graphics.dir/GraphicsUtils.cpp.i

Graphics/CMakeFiles/Graphics.dir/GraphicsUtils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Graphics.dir/GraphicsUtils.cpp.s"
	cd /Users/ethanhorowitz/CLionProjects/SimLED/Tests/build/Graphics && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/ethanhorowitz/CLionProjects/SimLED/Graphics/GraphicsUtils.cpp -o CMakeFiles/Graphics.dir/GraphicsUtils.cpp.s

Graphics/CMakeFiles/Graphics.dir/StripElement.cpp.o: Graphics/CMakeFiles/Graphics.dir/flags.make
Graphics/CMakeFiles/Graphics.dir/StripElement.cpp.o: /Users/ethanhorowitz/CLionProjects/SimLED/Graphics/StripElement.cpp
Graphics/CMakeFiles/Graphics.dir/StripElement.cpp.o: Graphics/CMakeFiles/Graphics.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/ethanhorowitz/CLionProjects/SimLED/Tests/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object Graphics/CMakeFiles/Graphics.dir/StripElement.cpp.o"
	cd /Users/ethanhorowitz/CLionProjects/SimLED/Tests/build/Graphics && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT Graphics/CMakeFiles/Graphics.dir/StripElement.cpp.o -MF CMakeFiles/Graphics.dir/StripElement.cpp.o.d -o CMakeFiles/Graphics.dir/StripElement.cpp.o -c /Users/ethanhorowitz/CLionProjects/SimLED/Graphics/StripElement.cpp

Graphics/CMakeFiles/Graphics.dir/StripElement.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Graphics.dir/StripElement.cpp.i"
	cd /Users/ethanhorowitz/CLionProjects/SimLED/Tests/build/Graphics && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/ethanhorowitz/CLionProjects/SimLED/Graphics/StripElement.cpp > CMakeFiles/Graphics.dir/StripElement.cpp.i

Graphics/CMakeFiles/Graphics.dir/StripElement.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Graphics.dir/StripElement.cpp.s"
	cd /Users/ethanhorowitz/CLionProjects/SimLED/Tests/build/Graphics && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/ethanhorowitz/CLionProjects/SimLED/Graphics/StripElement.cpp -o CMakeFiles/Graphics.dir/StripElement.cpp.s

Graphics/CMakeFiles/Graphics.dir/Button.cpp.o: Graphics/CMakeFiles/Graphics.dir/flags.make
Graphics/CMakeFiles/Graphics.dir/Button.cpp.o: /Users/ethanhorowitz/CLionProjects/SimLED/Graphics/Button.cpp
Graphics/CMakeFiles/Graphics.dir/Button.cpp.o: Graphics/CMakeFiles/Graphics.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/ethanhorowitz/CLionProjects/SimLED/Tests/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object Graphics/CMakeFiles/Graphics.dir/Button.cpp.o"
	cd /Users/ethanhorowitz/CLionProjects/SimLED/Tests/build/Graphics && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT Graphics/CMakeFiles/Graphics.dir/Button.cpp.o -MF CMakeFiles/Graphics.dir/Button.cpp.o.d -o CMakeFiles/Graphics.dir/Button.cpp.o -c /Users/ethanhorowitz/CLionProjects/SimLED/Graphics/Button.cpp

Graphics/CMakeFiles/Graphics.dir/Button.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Graphics.dir/Button.cpp.i"
	cd /Users/ethanhorowitz/CLionProjects/SimLED/Tests/build/Graphics && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/ethanhorowitz/CLionProjects/SimLED/Graphics/Button.cpp > CMakeFiles/Graphics.dir/Button.cpp.i

Graphics/CMakeFiles/Graphics.dir/Button.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Graphics.dir/Button.cpp.s"
	cd /Users/ethanhorowitz/CLionProjects/SimLED/Tests/build/Graphics && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/ethanhorowitz/CLionProjects/SimLED/Graphics/Button.cpp -o CMakeFiles/Graphics.dir/Button.cpp.s

# Object files for target Graphics
Graphics_OBJECTS = \
"CMakeFiles/Graphics.dir/GraphicsUtils.cpp.o" \
"CMakeFiles/Graphics.dir/StripElement.cpp.o" \
"CMakeFiles/Graphics.dir/Button.cpp.o"

# External object files for target Graphics
Graphics_EXTERNAL_OBJECTS =

Graphics/libGraphics.a: Graphics/CMakeFiles/Graphics.dir/GraphicsUtils.cpp.o
Graphics/libGraphics.a: Graphics/CMakeFiles/Graphics.dir/StripElement.cpp.o
Graphics/libGraphics.a: Graphics/CMakeFiles/Graphics.dir/Button.cpp.o
Graphics/libGraphics.a: Graphics/CMakeFiles/Graphics.dir/build.make
Graphics/libGraphics.a: Graphics/CMakeFiles/Graphics.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/ethanhorowitz/CLionProjects/SimLED/Tests/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX static library libGraphics.a"
	cd /Users/ethanhorowitz/CLionProjects/SimLED/Tests/build/Graphics && $(CMAKE_COMMAND) -P CMakeFiles/Graphics.dir/cmake_clean_target.cmake
	cd /Users/ethanhorowitz/CLionProjects/SimLED/Tests/build/Graphics && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Graphics.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Graphics/CMakeFiles/Graphics.dir/build: Graphics/libGraphics.a
.PHONY : Graphics/CMakeFiles/Graphics.dir/build

Graphics/CMakeFiles/Graphics.dir/clean:
	cd /Users/ethanhorowitz/CLionProjects/SimLED/Tests/build/Graphics && $(CMAKE_COMMAND) -P CMakeFiles/Graphics.dir/cmake_clean.cmake
.PHONY : Graphics/CMakeFiles/Graphics.dir/clean

Graphics/CMakeFiles/Graphics.dir/depend:
	cd /Users/ethanhorowitz/CLionProjects/SimLED/Tests/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/ethanhorowitz/CLionProjects/SimLED/Tests /Users/ethanhorowitz/CLionProjects/SimLED/Graphics /Users/ethanhorowitz/CLionProjects/SimLED/Tests/build /Users/ethanhorowitz/CLionProjects/SimLED/Tests/build/Graphics /Users/ethanhorowitz/CLionProjects/SimLED/Tests/build/Graphics/CMakeFiles/Graphics.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : Graphics/CMakeFiles/Graphics.dir/depend

