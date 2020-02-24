/*
Atanua Real-Time Logic Simulator
Copyright (c) 2008-2014 Jari Komppa

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.
Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
claim that you wrote the original software. If you use this software
in a product, an acknowledgment in the product documentation would be
appreciated but is not required.

2. Altered source versions must be plainly marked as such, and must not be
misrepresented as being the original software.

3. This notice may not be removed or altered from any source
distribution.
*/
#include "atanua.h"
#include "chip74153vlg.h"
#include "Vchip74153vlg.h"
#include <verilated.h>
#include <vector>


Chip74153vlg::Chip74153vlg()
{
    set(0,0,4.54,2.25,"Two 4->1 Multiplexers Gate");

    float xpos = 0.15 + 0.54;
    mPin.push_back(&mInputPinG2);
    mInputPinG2.set(xpos, 0, this, "Pin 15:/G2"); xpos += 0.54;
    mPin.push_back(&mInputPinS[0]);
    mInputPinS[0].set(xpos, 0, this, "Pin 14:S0"); xpos += 0.54;
    mPin.push_back(&mInputPinD2[3]);
    mInputPinD2[3].set(xpos, 0, this, "Pin 13:2D3"); xpos += 0.54;
    mPin.push_back(&mInputPinD2[2]);
    mInputPinD2[2].set(xpos, 0, this, "Pin 12:2D2"); xpos += 0.54;
    mPin.push_back(&mInputPinD2[1]);
    mInputPinD2[1].set(xpos, 0, this, "Pin 11:2D1"); xpos += 0.54;
    mPin.push_back(&mInputPinD2[0]);
    mInputPinD2[0].set(xpos, 0, this, "Pin 10:2D0"); xpos += 0.54;
    mPin.push_back(&mOutputPinY[1]);
    mOutputPinY[1].set(xpos, 0, this, "Pin 9:2Y"); xpos += 0.54;

    xpos = 0.15;

    mPin.push_back(&mInputPinG1);
    mInputPinG1.set(xpos, 1.75, this, "Pin 1:/G1"); xpos += 0.54;
    mPin.push_back(&mInputPinS[1]);
    mInputPinS[1].set(xpos, 1.75, this, "Pin 2:S1"); xpos += 0.54;
    mPin.push_back(&mInputPinD1[3]);
    mInputPinD1[3].set(xpos, 1.75, this, "Pin 3:1D3"); xpos += 0.54;
    mPin.push_back(&mInputPinD1[2]);
    mInputPinD1[2].set(xpos, 1.75, this, "Pin 4:1D2"); xpos += 0.54;
    mPin.push_back(&mInputPinD1[1]);
    mInputPinD1[1].set(xpos, 1.75, this, "Pin 5:1D1"); xpos += 0.54;
    mPin.push_back(&mInputPinD1[0]);
    mInputPinD1[0].set(xpos, 1.75, this, "Pin 6:1D0"); xpos += 0.54;
    mPin.push_back(&mOutputPinY[0]);
    mOutputPinY[0].set(xpos, 1.75, this, "Pin 7:1Y"); xpos += 0.54;

    mTexture = load_texture("data/chip_16pin.png");

    chipImpl = new Vchip74153vlg;
}

void Chip74153vlg::render(int aChipId)
{
    drawtexturedrect(mTexture,mX,mY,mW,mH,0xffffffff);
    fn.drawstring("74153 VLG",mX+0.6,mY+0.6,0x5fffffff,0.75);
}

#include "checknet.h"

void Chip74153vlg::update(float aTick) 
{
    vector<CheckNet::State> pinstate;

    chipImpl->d[0] = 0;
    chipImpl->d[1] = 0;
    chipImpl->en = 0;
    chipImpl->s = 0;

    CheckNet check1;
    check1.add(mInputPinG1.mNet);
    check1.add(mInputPinD1[0].mNet);
    check1.add(mInputPinD1[1].mNet);
    check1.add(mInputPinD1[2].mNet);
    check1.add(mInputPinD1[3].mNet);
    check1.add(mInputPinS[0].mNet);
    check1.add(mInputPinS[1].mNet);

    pinstate.push_back(check1());
    if (pinstate.back() == CheckNet::valid) {
        chipImpl->en |= ((mInputPinG1.mNet->mState == NETSTATE_HIGH) << 0);
        for (int i = 0; i < 4; i++) {
            chipImpl->d[0] |= ((mInputPinD1[i].mNet->mState == NETSTATE_HIGH) << i);
        }
        for (int i = 0; i < 2; i++) {
            chipImpl->s |= ((mInputPinS[i].mNet->mState == NETSTATE_HIGH) << i);
        }
    }

    CheckNet check2;
    check2.add(mInputPinG2.mNet);
    check2.add(mInputPinD2[0].mNet);
    check2.add(mInputPinD2[1].mNet);
    check2.add(mInputPinD2[2].mNet);
    check2.add(mInputPinD2[3].mNet);
    check2.add(mInputPinS[0].mNet);
    check2.add(mInputPinS[1].mNet);

    pinstate.push_back(check2());
    if (pinstate.back() == CheckNet::valid) {
        chipImpl->en |= ((mInputPinG2.mNet->mState == NETSTATE_HIGH) << 1);
        for (int i = 0; i < 4; i++) {
            chipImpl->d[1] |= ((mInputPinD2[i].mNet->mState == NETSTATE_HIGH) << i);
        }
        for (int i = 0; i < 2; i++) {
            chipImpl->s |= ((mInputPinS[i].mNet->mState == NETSTATE_HIGH) << i);
        }
    }

    chipImpl->eval();

    for (int i = 0; i < 2; i++) {
        int mask = (1 << i);
        int aState = gConfig.mPropagateInvalidState;

        if (pinstate[i] == CheckNet::valid) {
            aState = (chipImpl->y & mask) ? PINSTATE_WRITE_HIGH : PINSTATE_WRITE_LOW;
        }
        mOutputPinY[i].setState(aState);
    }
}

Chip74153vlg::~Chip74153vlg()
{
    chipImpl->final();
    delete chipImpl;
}


