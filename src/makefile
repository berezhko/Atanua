all: atanua

atanua-cpp-src = \
./core/fileio.cpp \
./core/AtanuaConfig.cpp \
./core/BoxStitchingInformation.cpp \
./chip/and8chip.cpp \
./chip/or8chip.cpp \
./chip/nand8chip.cpp \
./chip/nor8chip.cpp \
./core/slidingaverage.cpp \
./chip/switchchip.cpp \
./chip/16segchip.cpp \
./chip/ledgrid.cpp \
./chip/box.cpp \
./chip/extpin.cpp \
./chip/chip7489.cpp \
./chip/audiochip.cpp \
./chip/7segchip.cpp \
./chip/and3chip.cpp \
./chip/andchip.cpp \
./basecode/angelcodefont.cpp \
./core/basechipfactory.cpp \
./chip/buttonchip.cpp \
./chip/stepper.cpp \
./chip/chip309.cpp \
./chip/chip27xx.cpp \
./chip/chip74193.cpp \
./chip/chip74165.cpp \
./chip/chip74192.cpp \
./core/chip.cpp \
./chip/chip2051.cpp \
./chip/chip7400.cpp \
./chip/chip7402.cpp \
./chip/chip7404.cpp \
./chip/chip7408.cpp \
./chip/chip7410.cpp \
./chip/chip74138.cpp \
./chip/chip74139.cpp \
./chip/chip74151.cpp \
./chip/chip74154.cpp \
./chip/chip74163.cpp \
./chip/chip74164.cpp \
./chip/chip74181.cpp \
./chip/chip74191.cpp \
./chip/chip74195.cpp \
./chip/chip7420.cpp \
./chip/chip74240.cpp \
./chip/chip74241.cpp \
./chip/chip74244.cpp \
./chip/chip74245.cpp \
./chip/chip74283.cpp \
./chip/chip7432.cpp \
./chip/chip7447.cpp \
./chip/chip74574.cpp \
./chip/chip7473.cpp \
./chip/chip7474.cpp \
./chip/chip7485.cpp \
./chip/chip7486.cpp \
./chip/chip7490.cpp \
./chip/clockchip.cpp \
./chip/dchip.cpp \
./chip/dflipflop.cpp \
./chip/dxchip.cpp \
./chip/extrapin.cpp \
./core/fileutils.cpp \
./chip/jkchip.cpp \
./chip/jkflipflop.cpp \
./chip/label.cpp \
./chip/ledchip.cpp \
./chip/logicprobe.cpp \
./core/main.cpp \
./basecode/mersennetwister.cpp \
./chip/muxchip.cpp \
./chip/nand3chip.cpp \
./chip/nandchip.cpp \
./core/nativefunctions.cpp \
./core/net.cpp \
./chip/nor3chip.cpp \
./chip/norchip.cpp \
./chip/notchip.cpp \
./chip/or3chip.cpp \
./chip/orchip.cpp \
./core/pin.cpp \
./core/pluginchip.cpp \
./core/pluginchipfactory.cpp \
./chip/sedchip.cpp \
./chip/serchip.cpp \
./core/simutils.cpp \
./chip/srchip.cpp \
./chip/srflipflop.cpp \
./chip/srnegchip.cpp \
./chip/staticlevelchip.cpp \
./chip/tchip.cpp \
./chip/tflipflop.cpp \
./basecode/toolkit.cpp \
./core/wire.cpp \
./chip/xorchip.cpp \
./tinyxml_2_5_3/tinyxml/tinystr.cpp \
./tinyxml_2_5_3/tinyxml/tinyxml.cpp \
./tinyxml_2_5_3/tinyxml/tinyxmlerror.cpp \
./tinyxml_2_5_3/tinyxml/tinyxmlparser.cpp

verilog-v-src = \
./chipverilog/andverilog.v \
./chipverilog/orverilog.v \
./chipverilog/twolatchverilog.v \
./chipverilog/ffverilog.v


atanua-c-src = \
8051/core.c \
8051/disasm.c \
8051/opcodes.c \
stb/stb_image.c \
stb/stb_image_write.c \
glee/GLee.c

verilog-cpp-src = $(verilog-v-src:.v=.cpp)
atanua-obj = $(atanua-cpp-src:.cpp=.o) $(atanua-c-src:.c=.o) $(verilog-cpp-src:.cpp=.o)
verilog-obj = $(addprefix ./chipverilog/, $(addprefix V, $(notdir $(verilog-v-src:.v=__ALL.a)))) ./chipverilog/verilated.o

CXX = g++
CC = gcc

CXXFLAGS = \
-O0 \
-g \
-I/usr/include/c++/7 \
-Itinyxml_2_5_3/tinyxml \
-I/usr/include/gtk-3.0 \
-I/usr/include/cairo \
-I/usr/include/glib-2.0 \
-I/usr/lib/glib-2.0/include \
-I/usr/include/pango-1.0 \
-I/usr/lib/gtk-3.0/include \
-I/usr/include/atk-1.0 \
-I/usr/lib64/glib-2.0/include \
-I/usr/include/gdk-pixbuf-2.0 \
-Iinclude \
-I.



atanua: $(atanua-obj)
	$(CXX) `pkg-config --cflags gtk+-3.0` `pkg-config --cflags glib-2.0` -o $@ $(atanua-obj) $(verilog-obj) -L. -ldl -lSDLmain -lSDL -lGL -lGLU `pkg-config --libs gtk+-3.0` `pkg-config --libs glib-2.0` $(CXXFLAGS)

clean:
	rm $(atanua-obj) atanua

test:
	echo $(verilog-obj)
