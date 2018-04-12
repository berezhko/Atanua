all:
	cd src; make -C chipverilog; make all
clean:
	cd src; make -C chipverilog clean; make clean
