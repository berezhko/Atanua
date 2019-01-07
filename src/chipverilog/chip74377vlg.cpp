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
#include "chip74377vlg.h"
#include "Vchip74377vlg.h"
#include <verilated.h>
#include <vector>


Chip74377vlg::Chip74377vlg()
{
    set(0,0,5.7,2.8,"8bit Enableable Register");
    mPin.push_back(&mOutputPinQ[7]);
    mPin.push_back(&mInputPinD[7]);
    mPin.push_back(&mInputPinD[6]);
    mPin.push_back(&mOutputPinQ[6]);
    mPin.push_back(&mOutputPinQ[5]);
    mPin.push_back(&mInputPinD[5]);
    mPin.push_back(&mInputPinD[4]);
    mPin.push_back(&mOutputPinQ[4]);
    mPin.push_back(&mInputPinClk);

    mPin.push_back(&mInputPinEn);
    mPin.push_back(&mOutputPinQ[0]);
    mPin.push_back(&mInputPinD[0]);
    mPin.push_back(&mInputPinD[1]);
    mPin.push_back(&mOutputPinQ[1]);
    mPin.push_back(&mOutputPinQ[2]);
    mPin.push_back(&mInputPinD[2]);
    mPin.push_back(&mInputPinD[3]);
    mPin.push_back(&mOutputPinQ[3]);

    float xpos = 0.15 + 0.54;
    mOutputPinQ[7].set(xpos, 0.15, this, "Pin 19:Q7"); xpos += 0.54;    
    mInputPinD[7].set(xpos,  0.15, this, "Pin 18:D7"); xpos += 0.54;
    mInputPinD[6].set(xpos,  0.15, this, "Pin 17:D6"); xpos += 0.54;    
    mOutputPinQ[6].set(xpos, 0.15, this, "Pin 16:Q6"); xpos += 0.54;    
    mOutputPinQ[5].set(xpos, 0.15, this, "Pin 15:Q5"); xpos += 0.54;
    mInputPinD[5].set(xpos,  0.15, this, "Pin 14:D5"); xpos += 0.54;
    mInputPinD[4].set(xpos,  0.15, this, "Pin 13:D4"); xpos += 0.54;
    mOutputPinQ[4].set(xpos, 0.15, this, "Pin 12:Q4"); xpos += 0.54;
    mInputPinClk.set(xpos,   0.15, this, "Pin 11:Clk"); xpos += 0.54;

    xpos = 0.15;

    mInputPinEn.set(xpos,    2.1, this, "Pin 1:/En"); xpos += 0.54;
    mOutputPinQ[0].set(xpos, 2.1, this, "Pin 2:Q0"); xpos += 0.54;
    mInputPinD[0].set(xpos,  2.1, this, "Pin 3:D0"); xpos += 0.54;
    mInputPinD[1].set(xpos,  2.1, this, "Pin 4:D1"); xpos += 0.54;
    mOutputPinQ[1].set(xpos, 2.1, this, "Pin 5:Q1"); xpos += 0.54;
    mOutputPinQ[2].set(xpos, 2.1, this, "Pin 6:Q2"); xpos += 0.54;
    mInputPinD[2].set(xpos,  2.1, this, "Pin 7:D2"); xpos += 0.54;
    mInputPinD[3].set(xpos,  2.1, this, "Pin 8:D3"); xpos += 0.54;
    mOutputPinQ[3].set(xpos, 2.1, this, "Pin 9:Q3"); xpos += 0.54;
    
    mTexture = load_texture("data/chip_20pin.png");

    chipImpl = new Vchip74377vlg;
}

void Chip74377vlg::render(int aChipId)
{
    drawtexturedrect(mTexture,mX,mY,mW,mH,0xffffffff);
    fn.drawstring("74377 VGL",mX+0.6,mY+1,0x5fffffff,0.75);
}

#include "checknet.h"

void Chip74377vlg::update(float aTick) 
{
    chipImpl->d = 0;
    chipImpl->en = 0;
    chipImpl->clk = 0;

    CheckNet check;
    check.add(mInputPinEn.mNet);
    check.add(mInputPinClk.mNet);
    for (int i = 0; i < 8; i++) {
        check.add(mInputPinD[i].mNet);
    }

    bool pinstate = check();
    if (pinstate == CheckNet::valid) {
        for (int i = 0; i < 8; i++) {
            chipImpl->d |= ((mInputPinD[i].mNet->mState == NETSTATE_HIGH) << i);
        }
        chipImpl->en |= (mInputPinEn.mNet->mState == NETSTATE_HIGH);
        chipImpl->clk |= (mInputPinClk.mNet->mState == NETSTATE_HIGH);
    }

    chipImpl->eval();

    for (int i = 0; i < 8; i++) {
        int mask = (1 << i);

        if (pinstate == CheckNet::valid)
            mOutputPinQ[i].setState((chipImpl->q & mask) ? PINSTATE_WRITE_HIGH : PINSTATE_WRITE_LOW);
        else
            mOutputPinQ[i].setState(gConfig.mPropagateInvalidState);
    }
}

Chip74377vlg::~Chip74377vlg()
{
    chipImpl->final();
    delete chipImpl;
}

