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

# Utility rule file for pdf.

doc/CMakeFiles/pdf: doc/latex/refman.pdf

doc/latex/refman.pdf: doc/html/index.html
doc/latex/refman.pdf: doc/latex/refman.tex
	$(CMAKE_COMMAND) -E cmake_progress_report /home/localoriuser/dev/sim/stdair/stdairgit/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating PDF Reference Manual ('refman.pdf')..."
	cd /home/localoriuser/dev/sim/stdair/stdairgit/doc && /usr/bin/cmake -E chdir /home/localoriuser/dev/sim/stdair/stdairgit/doc/latex pdflatex -interaction batchmode refman.tex || echo First\ PDF\ generation\ done.
	cd /home/localoriuser/dev/sim/stdair/stdairgit/doc && /usr/bin/cmake -E chdir /home/localoriuser/dev/sim/stdair/stdairgit/doc/latex makeindex -q refman.idx
	cd /home/localoriuser/dev/sim/stdair/stdairgit/doc && /usr/bin/cmake -E chdir /home/localoriuser/dev/sim/stdair/stdairgit/doc/latex pdflatex -interaction batchmode refman.tex || echo Second\ PDF\ generation\ done.

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

pdf: doc/CMakeFiles/pdf
pdf: doc/latex/refman.pdf
pdf: doc/html/index.html
pdf: doc/CMakeFiles/pdf.dir/build.make
.PHONY : pdf

# Rule to build all files generated by this target.
doc/CMakeFiles/pdf.dir/build: pdf
.PHONY : doc/CMakeFiles/pdf.dir/build

doc/CMakeFiles/pdf.dir/clean:
	cd /home/localoriuser/dev/sim/stdair/stdairgit/doc && $(CMAKE_COMMAND) -P CMakeFiles/pdf.dir/cmake_clean.cmake
.PHONY : doc/CMakeFiles/pdf.dir/clean

doc/CMakeFiles/pdf.dir/depend:
	cd /home/localoriuser/dev/sim/stdair/stdairgit && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/localoriuser/dev/sim/stdair/stdairgit /home/localoriuser/dev/sim/stdair/stdairgit/doc /home/localoriuser/dev/sim/stdair/stdairgit /home/localoriuser/dev/sim/stdair/stdairgit/doc /home/localoriuser/dev/sim/stdair/stdairgit/doc/CMakeFiles/pdf.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : doc/CMakeFiles/pdf.dir/depend

