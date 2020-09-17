 CPPFLAGS = -Wall -std=c++11 -g
 .PHONY: clean

avm.out: AVM.o AVM_Table.o AVM_MemCell.o AVM_main.cpp error_handler.o VMarg.o instruction.o execute_arithmetic.o execute_jumps.o execute_functions.o execute_nop.o execute_assign.o execute_tables.o execute_assign.o AVM_libfuncs.o
	g++ $(CPPFLAGS) AVM.o AVM_Table.o AVM_MemCell.o error_handler.o instruction.o VMarg.o AVM_main.cpp execute_arithmetic.o execute_jumps.o execute_functions.o execute_nop.o execute_tables.o execute_assign.o AVM_libfuncs.o -o avm.out 

AVM.o: AVM.cpp 
	g++ $(CPPFLAGS) -c AVM.cpp 

AVM_MemCell.o: AVM_MemCell.cpp
	g++ $(CPPFLAGS) -c AVM_MemCell.cpp

AVM_Table.o: AVM_Table.cpp 
	g++ $(CPPFLAGS) -c AVM_Table.cpp

instruction.o: instruction.cpp VMarg.cpp
	g++ $(CPPFLAGS) -c instruction.cpp	

VMarg.o: VMarg.cpp
	g++ $(CPPFLAGS) -c VMarg.cpp

error_handler.o: error_handler.cpp
	g++ $(CPPFLAGS) -c error_handler.cpp

execute_arithmetic.o: execute_arithmetic.cpp
	g++ $(CPPFLAGS) -c execute_arithmetic.cpp

execute_jumps.o: execute_jumps.cpp
	g++ $(CPPFLAGS) -c execute_jumps.cpp

execute_functions.o: execute_functions.cpp
	g++ $(CPPFLAGS) -c execute_functions.cpp

execute_nop.o: execute_nop.cpp
	g++ $(CPPFLAGS) -c execute_nop.cpp

execute_assign.o: execute_assign.cpp
	g++ $(CPPFLAGS) -c execute_assign.cpp

execute_tables.o: execute_tables.cpp
	g++ $(CPPFLAGS) -c execute_tables.cpp

AVM_libfuncs.o: AVM_libfuncs.cpp
	g++ $(CPPFLAGS) -c AVM_libfuncs.cpp

clean: 
	rm -f *.out *.o 