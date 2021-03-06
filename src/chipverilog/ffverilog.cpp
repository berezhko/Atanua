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
#include "ffverilog.h"
#include "Vffverilog.h"
#include "verilated.h"


FFVerilog::FFVerilog()
{
    set(0,0,5,5,NULL);
    mPin.push_back(&mInputPinD);
    mInputPinD.set(0, 1.25, this, "Data");
    mPin.push_back(&mClockPin);
    mClockPin.set(0, 3.25, this, "Clock");

    mPin.push_back(&mInputPinS);
    mInputPinS.set(2.25, 0, this, "Set");
    mPin.push_back(&mInputPinR);
    mInputPinR.set(2.25, 4.5, this, "Reset");

    mPin.push_back(&mOutputPinA);
    mOutputPinA.set(4.5, 1.25, this, "Output");
    mPin.push_back(&mOutputPinB);
    mOutputPinB.set(4.5, 3.25, this, "Inverted output");
    mTexture = load_texture("data/d_flipflop.png");
    mState = 0;
    mClock = 0;

	mInputPinD.mReadOnly = 1;
	mInputPinR.mReadOnly = 1;
	mInputPinS.mReadOnly = 1;

    myff = new Vffverilog("Flipflop");
}

void FFVerilog::render(int aChipId)
{
	if (gBlackBackground)
	    drawtexturedrect(mTexture,mX,mY,8,8,0xffffffff);
	else
		drawtexturedrect(mTexture,mX,mY,8,8,0xff000000);
}

void FFVerilog::update(float aTick) 
{
    // Let's make SR pins optional, but still validated
    if (mInputPinD.mNet == NULL || mInputPinR.mNet == NULL ||
        mClockPin.mNet == NULL || mInputPinS.mNet == NULL)
    {
        mOutputPinA.setState(gConfig.mPropagateInvalidState);
        mOutputPinB.setState(gConfig.mPropagateInvalidState);
        return;
    }

    if (mClockPin.mNet->mState == NETSTATE_INVALID ||
        mInputPinD.mNet->mState == NETSTATE_INVALID ||
        mInputPinS.mNet->mState == NETSTATE_INVALID ||
        mInputPinR.mNet->mState == NETSTATE_INVALID)
    {
        mOutputPinA.setState(gConfig.mPropagateInvalidState);
        mOutputPinB.setState(gConfig.mPropagateInvalidState);
        return;
    }

    myff->clk = (mClockPin.mNet->mState == NETSTATE_HIGH);
    myff->data = (mInputPinD.mNet->mState == NETSTATE_HIGH);
    myff->s = (mInputPinS.mNet->mState == NETSTATE_HIGH);
    myff->r = (mInputPinR.mNet->mState == NETSTATE_HIGH);

    myff->eval();

    mOutputPinA.setState(myff->out ? PINSTATE_WRITE_HIGH : PINSTATE_WRITE_LOW);
    mOutputPinB.setState(myff->invout ? PINSTATE_WRITE_HIGH : PINSTATE_WRITE_LOW);
}

FFVerilog::~FFVerilog()
{
    myff->final();
    delete myff;
}    
