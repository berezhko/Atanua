all:
	cd src; make -C chipverilog; make all
clean:
	cd src; make -C chip cleanverilog; make clean
