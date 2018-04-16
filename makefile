all:
	cd src; make -C chipverilog; make all
clean:
	cd src; make clean; make -C chipverilog clean; 
