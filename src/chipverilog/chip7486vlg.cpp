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
#include "chip7486vlg.h"
#include "Vchip7486vlg.h"
#include <verilated.h>
#include <vector>


Chip7486vlg::Chip7486vlg()
{
    set(0,0,4,2,"Quad 2-input XOR Gate");
    float xpos = 0.15 + 0.54;
    mPin.push_back(&mInputPinA[0]);
    mInputPinA[3].set(xpos, 0, this, "Pin 13:B4"); xpos += 0.54;
    mPin.push_back(&mInputPinB[0]);
    mInputPinB[3].set(xpos, 0, this, "Pin 12:A4"); xpos += 0.54;
    mPin.push_back(&mOutputPin[0]);
    mOutputPin[3].set(xpos , 0, this, "Pin 11:Y4"); xpos += 0.54;

    mPin.push_back(&mInputPinA[1]);
    mInputPinA[2].set(xpos, 0, this, "Pin 10:B3"); xpos += 0.54;
    mPin.push_back(&mInputPinB[1]);
    mInputPinB[2].set(xpos, 0, this, "Pin 9:A3"); xpos += 0.54;
    mPin.push_back(&mOutputPin[1]);
    mOutputPin[2].set(xpos, 0, this, "Pin 8:Y3"); xpos += 0.54;

    xpos = 0.15;
    mPin.push_back(&mInputPinA[2]);
    mInputPinA[0].set(xpos, 1.5, this, "Pin 1:A1"); xpos += 0.54;
    mPin.push_back(&mInputPinB[2]);
    mInputPinB[0].set(xpos, 1.5, this, "Pin 2:B1"); xpos += 0.54;
    mPin.push_back(&mOutputPin[2]);
    mOutputPin[0].set(xpos , 1.5, this, "Pin 3:Y1"); xpos += 0.54;

    mPin.push_back(&mInputPinA[3]);
    mInputPinA[1].set(xpos, 1.5, this, "Pin 4:A2"); xpos += 0.54;
    mPin.push_back(&mInputPinB[3]);
    mInputPinB[1].set(xpos, 1.5, this, "Pin 5:B2"); xpos += 0.54;
    mPin.push_back(&mOutputPin[3]);
    mOutputPin[1].set(xpos, 1.5, this, "Pin 6:Y2"); xpos += 0.54;

    mTexture = load_texture("data/chip_14pin.png");

    chipImpl = new Vchip7486vlg;
}

void Chip7486vlg::render(int aChipId)
{
    drawtexturedrect(mTexture,mX,mY,mW,mH,0xffffffff);
    fn.drawstring("7486 VLG",mX+0.6,mY+0.6,0x5fffffff,0.75);
}

void Chip7486vlg::update(float aTick) 
{
    const char invalid = 1;
    const char valid = 0;
    vector<char> pinstate;

    chipImpl->a = 0;
    chipImpl->b = 0;
    for (int i = 0; i < 4; i++) {
        if (mInputPinA[i].mNet == NULL ||
            mInputPinB[i].mNet == NULL) {

            pinstate.push_back(invalid);
        } else if (mInputPinA[i].mNet->mState == NETSTATE_INVALID ||
                   mInputPinB[i].mNet->mState == NETSTATE_INVALID) {

            pinstate.push_back(invalid);
        } else {
            chipImpl->a |= ((mInputPinA[i].mNet->mState == NETSTATE_HIGH) << i);
            chipImpl->b |= ((mInputPinB[i].mNet->mState == NETSTATE_HIGH) << i);

            pinstate.push_back(valid);
        }
    }

    chipImpl->eval();

    for (int i = 0; i < 4; i++) {
        int mask = (1 << i);

        if (pinstate[i] == valid)
            mOutputPin[i].setState((chipImpl->out & mask) ? PINSTATE_WRITE_HIGH : PINSTATE_WRITE_LOW);
        else
            mOutputPin[i].setState(gConfig.mPropagateInvalidState);

    }
}

Chip7486vlg::~Chip7486vlg()
{
    chipImpl->final();
    delete chipImpl;
}    
