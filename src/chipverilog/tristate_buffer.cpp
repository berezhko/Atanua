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
#include "tristate_buffer.h"
#include "Vtristate_buffer.h"
#include "verilated.h"


TristateBuffer::TristateBuffer()
{
    set(0,0,4,2,NULL);
    mPin.push_back(&mInputPin);
    mInputPin.set(0, 0.75, this, "Input");

    mPin.push_back(&mEnablePin);
    mEnablePin.set(2, 0.75, this, "Enable");
 
    mPin.push_back(&mOutputPin);
    mOutputPin.set(3.5, 0.75, this, "Output");
    mTexture = load_texture("data/tsb.png");

	mInputPin.mReadOnly = 1;
    mTsb = new Vtristate_buffer("TSB");
}

void TristateBuffer::render(int aChipId)
{
	if (gBlackBackground)
	    drawtexturedrect(mTexture,mX,mY,mW,mH,0xffffffff);
	else
		drawtexturedrect(mTexture,mX,mY,mW,mH,0xff000000);
}

#include <stdio.h>

void TristateBuffer::update(float aTick) 
{
    if (mInputPin.mNet == NULL || mEnablePin.mNet == NULL) {
        mOutputPin.setState(gConfig.mPropagateInvalidState);
        return;
    }

    mTsb->e = (mEnablePin.mNet->mState == NETSTATE_HIGH);
    mTsb->x = (mInputPin.mNet->mState == NETSTATE_HIGH);

    mTsb->eval();
    printf("x = %d, e = %d, y = %d\n", mTsb->x, mTsb->e, mTsb->y);

    switch (mTsb->y) {
    case 1:
        mOutputPin.setState(PINSTATE_WRITE_HIGH);
        break;
    case 0:
        mOutputPin.setState(PINSTATE_WRITE_LOW);
        break;
    default:
        mOutputPin.setState(PINSTATE_HIGHZ);
    }
}    


TristateBuffer::~TristateBuffer()
{
    mTsb->final();
    delete mTsb;
}
