# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canoncical targets will work.
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

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/localoriuser/dev/sim/stdair/stdairgit

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/localoriuser/dev/sim/stdair/stdairgit

# Utility rule file for man.

man/CMakeFiles/man: man/man1/stdair-config.1
man/CMakeFiles/man: man/man3/stdair-library.3

man/man1/stdair-config.1: man/doxygen_man1.cfg
man/man1/stdair-config.1: man/stdair.doc
man/man1/stdair-config.1: man/stdair-config.doc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/localoriuser/dev/sim/stdair/stdairgit/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating section 1 manual pages with Doxygen, from '/home/localoriuser/dev/sim/stdair/stdairgit/man/doxygen_man1.cfg'..."
	cd /home/localoriuser/dev/sim/stdair/stdairgit/man && /usr/bin/doxygen /home/localoriuser/dev/sim/stdair/stdairgit/man/doxygen_man1.cfg

man/man3/stdair-library.3: man/doxygen_man3.cfg
man/man3/stdair-library.3: man/stdair-library.doc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/localoriuser/dev/sim/stdair/stdairgit/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating section 3 manual pages with Doxygen, from '/home/localoriuser/dev/sim/stdair/stdairgit/man/doxygen_man3.cfg'..."
	cd /home/localoriuser/dev/sim/stdair/stdairgit/man && /usr/bin/doxygen /home/localoriuser/dev/sim/stdair/stdairgit/man/doxygen_man3.cfg

man: man/CMakeFiles/man
man: man/man1/stdair-config.1
man: man/man3/stdair-library.3
man: man/CMakeFiles/man.dir/build.make
.PHONY : man

# Rule to build all files generated by this target.
man/CMakeFiles/man.dir/build: man
.PHONY : man/CMakeFiles/man.dir/build

man/CMakeFiles/man.dir/clean:
	cd /home/localoriuser/dev/sim/stdair/stdairgit/man && $(CMAKE_COMMAND) -P CMakeFiles/man.dir/cmake_clean.cmake
.PHONY : man/CMakeFiles/man.dir/clean

man/CMakeFiles/man.dir/depend:
	cd /home/localoriuser/dev/sim/stdair/stdairgit && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/localoriuser/dev/sim/stdair/stdairgit /home/localoriuser/dev/sim/stdair/stdairgit/man /home/localoriuser/dev/sim/stdair/stdairgit /home/localoriuser/dev/sim/stdair/stdairgit/man /home/localoriuser/dev/sim/stdair/stdairgit/man/CMakeFiles/man.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : man/CMakeFiles/man.dir/depend

