# acc-events - Examples for using the OpenACC Profiling Events API

The purpose of this repository is to provide a demonstration of how to write
simple tools using the OpenACC Events API (formerly Profiling Interface).
Nothing in this repository is intended for production use, use at your own risk.

## Examples

1. acc_data_migrate_tool.c - Will print to the console whenever data is
implicitly copied to or from the device. Useful for identifying data structures
that should be added to explicit data clauses. **NOTE:** As-written this tool
can be ***very*** verbose.  
2. acc_data_migrate_tool_color.c - Same as
acc_data_migrate_tool.c, but prints with ANSI colors.

## Build

The included Makefile provides examples for building both `libacctool.so` and
`libacctoolcolor.so` using the NVIDIA compilers. Options should be adapted when
used with other compilers. 

## Usage

The included Makefile demonstrates how to use the two libraries with an included
sample application. More generally, to use with an arbitrary executable simply
set set `ACC_PROFLIB="<path to lib.so>"` when running the executable.

## Recommendations

Printing to the console from the profiling library may introduce a significant
overhead and result in a large amount of output. It is likely a better practice
to record details to memory or a database (sqlite, for instance) and print only
periodically or at the very end, unless the output is needed immediately for
your specific use case.