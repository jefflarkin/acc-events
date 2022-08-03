CC=nvc
FC=nvfortran
PIC=-fpic
FFLAGS=-fast -acc=gpu -Minfo=accel

test: libacctool.so laplace2d.parallel.f90 jacobi.f90
	$(FC) $(FFLAGS) -o test laplace2d.parallel.f90 jacobi.f90
	ACC_PROFLIB="./libacctool.so" ./test

testcolor: libacctoolcolor.so laplace2d.parallel.f90 jacobi.f90
	$(FC) $(FFLAGS) -o test laplace2d.parallel.f90 jacobi.f90
	ACC_PROFLIB="./libacctoolcolor.so" ./test

libacctool.so: acc_data_migrate_tool.o
	$(CC) -shared -o $@ -Wl,-soname=$@ -Wl,--whole-archive $< -Wl,--no-whole-archive

libacctoolcolor.so: acc_data_migrate_tool_color.o
	$(CC) -shared -o $@ -Wl,-soname=$@ -Wl,--whole-archive $< -Wl,--no-whole-archive

acc_data_migrate_tool.o: acc_data_migrate_tool.c
	$(CC) $(PIC) -c $<

acc_data_migrate_tool_color.o: acc_data_migrate_tool_color.c
	$(CC) $(PIC) -c $<

.PHONY: clean
clean:
	rm -f *.o *.mod *.so core test
