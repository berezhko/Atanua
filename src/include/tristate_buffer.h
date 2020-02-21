#ifndef TRISTATE_BUFFER_H
#define TRISTATE_BUFFER_H

class Vtristate_buffer;

class TristateBuffer: public Chip
{
    Pin mInputPin;  // Input pin for this chip
    Pin mEnablePin;  // Enable pin for this chip
    Pin mOutputPin; // Output pin for this chip
    int mTexture;

    Vtristate_buffer *mTsb;
public:
    TristateBuffer(); // Ctor
    virtual ~TristateBuffer(); // DCtor

    virtual void render(int aChipId);
    virtual void update(float aTick);
};

#endif
