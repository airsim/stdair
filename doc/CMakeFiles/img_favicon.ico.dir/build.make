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

# Utility rule file for img_favicon.ico.

doc/CMakeFiles/img_favicon.ico: doc/html/favicon.ico

doc/html/favicon.ico: doc/html/index.html
doc/html/favicon.ico: doc/images/favicon.ico
	$(CMAKE_COMMAND) -E cmake_progress_report /home/localoriuser/dev/sim/stdair/stdairgit/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Copying image '/home/localoriuser/dev/sim/stdair/stdairgit/doc/images/favicon.ico' into '/home/localoriuser/dev/sim/stdair/stdairgit/doc/html'..."
	cd /home/localoriuser/dev/sim/stdair/stdairgit/doc && /usr/bin/cmake -E copy /home/localoriuser/dev/sim/stdair/stdairgit/doc/images/favicon.ico /home/localoriuser/dev/sim/stdair/stdairgit/doc/html/favicon.ico

doc/html/index.html: doc/doxygen_html.cfg
doc/html/index.html: doc/tutorial/tutorial.doc
doc/html/index.html: doc/local/documentation.doc
doc/html/index.html: doc/local/users_guide.doc
doc/html/index.html: doc/local/index.doc
doc/html/index.html: doc/local/help_wanted.doc
doc/html/index.html: doc/local/installation.doc
doc/html/index.html: doc/local/authors.doc
doc/html/index.html: doc/local/features.doc
doc/html/index.html: doc/local/test.doc
doc/html/index.html: doc/local/linking.doc
doc/html/index.html: doc/local/copyright.doc
doc/html/index.html: doc/local/codingrules.doc
doc/html/index.html: doc/local/verification.doc
doc/html/index.html: doc/local/howto_release.doc
doc/html/index.html: doc/local/stdair_footer.html
doc/html/index.html: doc/local/stdair_header.html
	$(CMAKE_COMMAND) -E cmake_progress_report /home/localoriuser/dev/sim/stdair/stdairgit/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating documentation with Doxygen, from '/home/localoriuser/dev/sim/stdair/stdairgit/doc/doxygen_html.cfg'..."
	cd /home/localoriuser/dev/sim/stdair/stdairgit/doc && /usr/bin/doxygen /home/localoriuser/dev/sim/stdair/stdairgit/doc/doxygen_html.cfg

img_favicon.ico: doc/CMakeFiles/img_favicon.ico
img_favicon.ico: doc/html/favicon.ico
img_favicon.ico: doc/html/index.html
img_favicon.ico: doc/CMakeFiles/img_favicon.ico.dir/build.make
.PHONY : img_favicon.ico

# Rule to build all files generated by this target.
doc/CMakeFiles/img_favicon.ico.dir/build: img_favicon.ico
.PHONY : doc/CMakeFiles/img_favicon.ico.dir/build

doc/CMakeFiles/img_favicon.ico.dir/clean:
	cd /home/localoriuser/dev/sim/stdair/stdairgit/doc && $(CMAKE_COMMAND) -P CMakeFiles/img_favicon.ico.dir/cmake_clean.cmake
.PHONY : doc/CMakeFiles/img_favicon.ico.dir/clean

doc/CMakeFiles/img_favicon.ico.dir/depend:
	cd /home/localoriuser/dev/sim/stdair/stdairgit && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/localoriuser/dev/sim/stdair/stdairgit /home/localoriuser/dev/sim/stdair/stdairgit/doc /home/localoriuser/dev/sim/stdair/stdairgit /home/localoriuser/dev/sim/stdair/stdairgit/doc /home/localoriuser/dev/sim/stdair/stdairgit/doc/CMakeFiles/img_favicon.ico.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : doc/CMakeFiles/img_favicon.ico.dir/depend
