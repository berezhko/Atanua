#include "atanua.h"
#include "marsohod.h"
#include "Vmarsohod.h"
#include <verilated.h>
#include <vector>


ChipMarsohod::ChipMarsohod()
{
    set(0,0,4.54,2.25,"Marsohod Schoolmips process");

    float xpos = 0.15 + 0.54;
    float ypos = 0.;
    for (int i = 0; i < 14; i++) {
        if (i == 7) {
            xpos = 0.15;
            ypos = 1.75;
        }
        mPin.push_back(&pin[i]);
        pin[i].set(xpos, ypos, this, pins_label[i]); xpos += 0.54;
    }

    mTexture = load_texture("data/chip_14pin.png");

    chipImpl = new Vmarsohod;
}

void ChipMarsohod::render(int aChipId)
{
    drawtexturedrect(mTexture,mX,mY,mW,mH,0xffffffff);
    fn.drawstring("Marsohod",mX+0.6,mY+0.6,0x5fffffff,0.75);
}

#include "checknet.h"

void ChipMarsohod::update(float aTick) 
{
    CheckNet::State pinstate = CheckNet::invalid;

    chipImpl->CLK100MHZ = 0;
    chipImpl->KEY0 = 0;
    chipImpl->KEY1 = 0;

    // Check state for input pins
    CheckNet check;
    for (int i = 0; i < 3; i++) {
        check.add(pin[i].mNet);
    }
    pinstate = check();

    if (pinstate == CheckNet::valid) {
        chipImpl->CLK100MHZ |= (pin[0].mNet->mState == NETSTATE_HIGH);
        chipImpl->KEY0 |= (pin[1].mNet->mState == NETSTATE_HIGH);
        chipImpl->KEY1 |= (pin[2].mNet->mState == NETSTATE_HIGH);
    }

    chipImpl->eval();

    // Define state for output pins
    for (int i = 3; i < 14; i++) {
        int mask = (1 << (i-3));

        if (pinstate == CheckNet::valid) {
            pin[i].setState((chipImpl->LED & mask) ? PINSTATE_WRITE_HIGH : PINSTATE_WRITE_LOW);
        } else {
            pin[i].setState(gConfig.mPropagateInvalidState);
        }
    }
}

ChipMarsohod::~ChipMarsohod()
{
    chipImpl->final();
    delete chipImpl;
}


