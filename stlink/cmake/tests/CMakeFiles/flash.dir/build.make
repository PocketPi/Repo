# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/peter/Repo/stlink

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/peter/Repo/stlink/cmake

# Include any dependencies generated for this target.
include tests/CMakeFiles/flash.dir/depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/flash.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/flash.dir/flags.make

tests/CMakeFiles/flash.dir/flash.c.o: tests/CMakeFiles/flash.dir/flags.make
tests/CMakeFiles/flash.dir/flash.c.o: ../tests/flash.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/peter/Repo/stlink/cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object tests/CMakeFiles/flash.dir/flash.c.o"
	cd /home/peter/Repo/stlink/cmake/tests && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/flash.dir/flash.c.o   -c /home/peter/Repo/stlink/tests/flash.c

tests/CMakeFiles/flash.dir/flash.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/flash.dir/flash.c.i"
	cd /home/peter/Repo/stlink/cmake/tests && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/peter/Repo/stlink/tests/flash.c > CMakeFiles/flash.dir/flash.c.i

tests/CMakeFiles/flash.dir/flash.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/flash.dir/flash.c.s"
	cd /home/peter/Repo/stlink/cmake/tests && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/peter/Repo/stlink/tests/flash.c -o CMakeFiles/flash.dir/flash.c.s

tests/CMakeFiles/flash.dir/flash.c.o.requires:

.PHONY : tests/CMakeFiles/flash.dir/flash.c.o.requires

tests/CMakeFiles/flash.dir/flash.c.o.provides: tests/CMakeFiles/flash.dir/flash.c.o.requires
	$(MAKE) -f tests/CMakeFiles/flash.dir/build.make tests/CMakeFiles/flash.dir/flash.c.o.provides.build
.PHONY : tests/CMakeFiles/flash.dir/flash.c.o.provides

tests/CMakeFiles/flash.dir/flash.c.o.provides.build: tests/CMakeFiles/flash.dir/flash.c.o


tests/CMakeFiles/flash.dir/__/src/tools/flash_opts.c.o: tests/CMakeFiles/flash.dir/flags.make
tests/CMakeFiles/flash.dir/__/src/tools/flash_opts.c.o: ../src/tools/flash_opts.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/peter/Repo/stlink/cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object tests/CMakeFiles/flash.dir/__/src/tools/flash_opts.c.o"
	cd /home/peter/Repo/stlink/cmake/tests && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/flash.dir/__/src/tools/flash_opts.c.o   -c /home/peter/Repo/stlink/src/tools/flash_opts.c

tests/CMakeFiles/flash.dir/__/src/tools/flash_opts.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/flash.dir/__/src/tools/flash_opts.c.i"
	cd /home/peter/Repo/stlink/cmake/tests && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/peter/Repo/stlink/src/tools/flash_opts.c > CMakeFiles/flash.dir/__/src/tools/flash_opts.c.i

tests/CMakeFiles/flash.dir/__/src/tools/flash_opts.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/flash.dir/__/src/tools/flash_opts.c.s"
	cd /home/peter/Repo/stlink/cmake/tests && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/peter/Repo/stlink/src/tools/flash_opts.c -o CMakeFiles/flash.dir/__/src/tools/flash_opts.c.s

tests/CMakeFiles/flash.dir/__/src/tools/flash_opts.c.o.requires:

.PHONY : tests/CMakeFiles/flash.dir/__/src/tools/flash_opts.c.o.requires

tests/CMakeFiles/flash.dir/__/src/tools/flash_opts.c.o.provides: tests/CMakeFiles/flash.dir/__/src/tools/flash_opts.c.o.requires
	$(MAKE) -f tests/CMakeFiles/flash.dir/build.make tests/CMakeFiles/flash.dir/__/src/tools/flash_opts.c.o.provides.build
.PHONY : tests/CMakeFiles/flash.dir/__/src/tools/flash_opts.c.o.provides

tests/CMakeFiles/flash.dir/__/src/tools/flash_opts.c.o.provides.build: tests/CMakeFiles/flash.dir/__/src/tools/flash_opts.c.o


# Object files for target flash
flash_OBJECTS = \
"CMakeFiles/flash.dir/flash.c.o" \
"CMakeFiles/flash.dir/__/src/tools/flash_opts.c.o"

# External object files for target flash
flash_EXTERNAL_OBJECTS =

tests/flash: tests/CMakeFiles/flash.dir/flash.c.o
tests/flash: tests/CMakeFiles/flash.dir/__/src/tools/flash_opts.c.o
tests/flash: tests/CMakeFiles/flash.dir/build.make
tests/flash: libstlink.a
tests/flash: /usr/lib/x86_64-linux-gnu/libusb-1.0.so
tests/flash: tests/CMakeFiles/flash.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/peter/Repo/stlink/cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable flash"
	cd /home/peter/Repo/stlink/cmake/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/flash.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/flash.dir/build: tests/flash

.PHONY : tests/CMakeFiles/flash.dir/build

tests/CMakeFiles/flash.dir/requires: tests/CMakeFiles/flash.dir/flash.c.o.requires
tests/CMakeFiles/flash.dir/requires: tests/CMakeFiles/flash.dir/__/src/tools/flash_opts.c.o.requires

.PHONY : tests/CMakeFiles/flash.dir/requires

tests/CMakeFiles/flash.dir/clean:
	cd /home/peter/Repo/stlink/cmake/tests && $(CMAKE_COMMAND) -P CMakeFiles/flash.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/flash.dir/clean

tests/CMakeFiles/flash.dir/depend:
	cd /home/peter/Repo/stlink/cmake && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/peter/Repo/stlink /home/peter/Repo/stlink/tests /home/peter/Repo/stlink/cmake /home/peter/Repo/stlink/cmake/tests /home/peter/Repo/stlink/cmake/tests/CMakeFiles/flash.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/flash.dir/depend

