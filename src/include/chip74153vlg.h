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
#ifndef CHIP74153VLG_H
#define CHIP74153VLG_H

class Vchip74153vlg;

class Chip74153vlg : public Chip
{
    Pin mInputPinG1; // Input Enable pin G1
    Pin mInputPinG2; // Input Enable pin G2
    Pin mInputPinD1[4]; // Input Data pin D1
    Pin mInputPinD2[4]; // Input Data pin D2
    Pin mInputPinS[2]; // Input Select ping
    Pin mOutputPinY[2]; // Output pin Y1, Y2
    int mTexture;

    Vchip74153vlg *chipImpl;
public:
    Chip74153vlg(); // Ctor
    virtual ~Chip74153vlg(); // DCtor

    virtual void render(int aChipId);
    virtual void update(float aTick);
};

#endif
