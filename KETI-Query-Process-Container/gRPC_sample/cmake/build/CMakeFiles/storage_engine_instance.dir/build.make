# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /root/workspace/ljs/git/KETI-Query-Process-Container/gRPC_sample

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/workspace/ljs/git/KETI-Query-Process-Container/gRPC_sample/cmake/build

# Include any dependencies generated for this target.
include CMakeFiles/storage_engine_instance.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/storage_engine_instance.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/storage_engine_instance.dir/flags.make

CMakeFiles/storage_engine_instance.dir/storage_engine_instance.cc.o: CMakeFiles/storage_engine_instance.dir/flags.make
CMakeFiles/storage_engine_instance.dir/storage_engine_instance.cc.o: ../../storage_engine_instance.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/workspace/ljs/git/KETI-Query-Process-Container/gRPC_sample/cmake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/storage_engine_instance.dir/storage_engine_instance.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/storage_engine_instance.dir/storage_engine_instance.cc.o -c /root/workspace/ljs/git/KETI-Query-Process-Container/gRPC_sample/storage_engine_instance.cc

CMakeFiles/storage_engine_instance.dir/storage_engine_instance.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/storage_engine_instance.dir/storage_engine_instance.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/workspace/ljs/git/KETI-Query-Process-Container/gRPC_sample/storage_engine_instance.cc > CMakeFiles/storage_engine_instance.dir/storage_engine_instance.cc.i

CMakeFiles/storage_engine_instance.dir/storage_engine_instance.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/storage_engine_instance.dir/storage_engine_instance.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/workspace/ljs/git/KETI-Query-Process-Container/gRPC_sample/storage_engine_instance.cc -o CMakeFiles/storage_engine_instance.dir/storage_engine_instance.cc.s

# Object files for target storage_engine_instance
storage_engine_instance_OBJECTS = \
"CMakeFiles/storage_engine_instance.dir/storage_engine_instance.cc.o"

# External object files for target storage_engine_instance
storage_engine_instance_EXTERNAL_OBJECTS =

storage_engine_instance: CMakeFiles/storage_engine_instance.dir/storage_engine_instance.cc.o
storage_engine_instance: CMakeFiles/storage_engine_instance.dir/build.make
storage_engine_instance: libss_grpc_proto.a
storage_engine_instance: /lib/libgrpc++_reflection.a
storage_engine_instance: /lib/libgrpc++.a
storage_engine_instance: /lib/libprotobuf.a
storage_engine_instance: /lib/libgrpc.a
storage_engine_instance: /lib/libz.a
storage_engine_instance: /lib/libcares.a
storage_engine_instance: /lib/libaddress_sorting.a
storage_engine_instance: /lib/libre2.a
storage_engine_instance: /lib/libabsl_raw_hash_set.a
storage_engine_instance: /lib/libabsl_hashtablez_sampler.a
storage_engine_instance: /lib/libabsl_hash.a
storage_engine_instance: /lib/libabsl_city.a
storage_engine_instance: /lib/libabsl_low_level_hash.a
storage_engine_instance: /lib/libabsl_statusor.a
storage_engine_instance: /lib/libabsl_bad_variant_access.a
storage_engine_instance: /lib/libgpr.a
storage_engine_instance: /lib/libupb.a
storage_engine_instance: /lib/libabsl_status.a
storage_engine_instance: /lib/libabsl_random_distributions.a
storage_engine_instance: /lib/libabsl_random_seed_sequences.a
storage_engine_instance: /lib/libabsl_random_internal_pool_urbg.a
storage_engine_instance: /lib/libabsl_random_internal_randen.a
storage_engine_instance: /lib/libabsl_random_internal_randen_hwaes.a
storage_engine_instance: /lib/libabsl_random_internal_randen_hwaes_impl.a
storage_engine_instance: /lib/libabsl_random_internal_randen_slow.a
storage_engine_instance: /lib/libabsl_random_internal_platform.a
storage_engine_instance: /lib/libabsl_random_internal_seed_material.a
storage_engine_instance: /lib/libabsl_random_seed_gen_exception.a
storage_engine_instance: /lib/libabsl_cord.a
storage_engine_instance: /lib/libabsl_bad_optional_access.a
storage_engine_instance: /lib/libabsl_cordz_info.a
storage_engine_instance: /lib/libabsl_cord_internal.a
storage_engine_instance: /lib/libabsl_cordz_functions.a
storage_engine_instance: /lib/libabsl_exponential_biased.a
storage_engine_instance: /lib/libabsl_cordz_handle.a
storage_engine_instance: /lib/libabsl_str_format_internal.a
storage_engine_instance: /lib/libabsl_synchronization.a
storage_engine_instance: /lib/libabsl_stacktrace.a
storage_engine_instance: /lib/libabsl_symbolize.a
storage_engine_instance: /lib/libabsl_debugging_internal.a
storage_engine_instance: /lib/libabsl_demangle_internal.a
storage_engine_instance: /lib/libabsl_graphcycles_internal.a
storage_engine_instance: /lib/libabsl_malloc_internal.a
storage_engine_instance: /lib/libabsl_time.a
storage_engine_instance: /lib/libabsl_strings.a
storage_engine_instance: /lib/libabsl_throw_delegate.a
storage_engine_instance: /lib/libabsl_int128.a
storage_engine_instance: /lib/libabsl_strings_internal.a
storage_engine_instance: /lib/libabsl_base.a
storage_engine_instance: /lib/libabsl_spinlock_wait.a
storage_engine_instance: /lib/libabsl_raw_logging_internal.a
storage_engine_instance: /lib/libabsl_log_severity.a
storage_engine_instance: /lib/libabsl_civil_time.a
storage_engine_instance: /lib/libabsl_time_zone.a
storage_engine_instance: /lib/libssl.a
storage_engine_instance: /lib/libcrypto.a
storage_engine_instance: CMakeFiles/storage_engine_instance.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/workspace/ljs/git/KETI-Query-Process-Container/gRPC_sample/cmake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable storage_engine_instance"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/storage_engine_instance.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/storage_engine_instance.dir/build: storage_engine_instance

.PHONY : CMakeFiles/storage_engine_instance.dir/build

CMakeFiles/storage_engine_instance.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/storage_engine_instance.dir/cmake_clean.cmake
.PHONY : CMakeFiles/storage_engine_instance.dir/clean

CMakeFiles/storage_engine_instance.dir/depend:
	cd /root/workspace/ljs/git/KETI-Query-Process-Container/gRPC_sample/cmake/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/workspace/ljs/git/KETI-Query-Process-Container/gRPC_sample /root/workspace/ljs/git/KETI-Query-Process-Container/gRPC_sample /root/workspace/ljs/git/KETI-Query-Process-Container/gRPC_sample/cmake/build /root/workspace/ljs/git/KETI-Query-Process-Container/gRPC_sample/cmake/build /root/workspace/ljs/git/KETI-Query-Process-Container/gRPC_sample/cmake/build/CMakeFiles/storage_engine_instance.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/storage_engine_instance.dir/depend

