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
#ifndef CHIPMARSOHOD_H
#define CHIPMARSOHOD_H

class Vmarsohod;

class ChipMarsohod : public Chip
{
    Pin pin[14];
    int mTexture;

    Vmarsohod *chipImpl;
    const char * pins_label[14] = {"Clk", "Key0", "Key1", "Led0", "Led1", "Led2", "Led3", "Led4", "Led5", "Led6", "Led7", "Led8", "Led9", "Led10"};
public:
    ChipMarsohod(); // Ctor
    virtual ~ChipMarsohod(); // DCtor

    virtual void render(int aChipId);
    virtual void update(float aTick);
};

#endif
