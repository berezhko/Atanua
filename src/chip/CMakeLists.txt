add_library(chip SHARED "")

target_sources(chip
  PRIVATE
16segchip.cpp
7segchip.cpp
and3chip.cpp
and8chip.cpp
andchip.cpp
audiochip.cpp
box.cpp
buttonchip.cpp
chip2051.cpp
chip27xx.cpp
chip309.cpp
chip7400.cpp
chip7402.cpp
chip7404.cpp
chip7408.cpp
chip7410.cpp
chip74138.cpp
chip74139.cpp
chip74151.cpp
chip74154.cpp
chip74163.cpp
chip74164.cpp
chip74165.cpp
chip74181.cpp
chip74191.cpp
chip74192.cpp
chip74193.cpp
chip74195.cpp
chip7420.cpp
chip74240.cpp
chip74241.cpp
chip74244.cpp
chip74245.cpp
chip74283.cpp
chip7432.cpp
chip7447.cpp
chip74574.cpp
chip7473.cpp
chip7474.cpp
chip7485.cpp
chip7486.cpp
chip7489.cpp
chip7490.cpp
clockchip.cpp
dchip.cpp
dflipflop.cpp
dxchip.cpp
extpin.cpp
extrapin.cpp
jkchip.cpp
jkflipflop.cpp
label.cpp
ledchip.cpp
ledgrid.cpp
logicprobe.cpp
muxchip.cpp
nand3chip.cpp
nand8chip.cpp
nandchip.cpp
nor3chip.cpp
nor8chip.cpp
norchip.cpp
notchip.cpp
or3chip.cpp
or8chip.cpp
orchip.cpp
sedchip.cpp
serchip.cpp
srchip.cpp
srflipflop.cpp
srnegchip.cpp
staticlevelchip.cpp
stepper.cpp
switchchip.cpp
tchip.cpp
tflipflop.cpp
xorchip.cpp
  )

target_include_directories(chip
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
  )
