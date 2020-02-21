#ifdef _WIN32
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "../plugin/atanua_dll_interface.h"

static const char plugin_name[]="plugin test";
static const int chipcount = 1;

/* Get the number of chips this DLL/interface supports */
ATANUADLLEXPORT void ATANUACALL getatanuadllinfo(atanuadllinfo *aDllInfo)
{
    /* DLL interface version. Set to ATANUA_PLUGIN_DLL_VERSION. Set to -1 if in error. */
    aDllInfo->mDllVersion = ATANUA_PLUGIN_DLL_VERSION;   
    /* Number of chips provided by this DLL */
    aDllInfo->mChipCount = chipcount;    
    /* Pointers to chip names. These may not point to stack! */
    aDllInfo->mChipName = new const char*[chipcount]; 
    /* Category numbers for chips. May be NULL. Categories are 0=dont care, 1=base, 2=chip, 3=I/O */
    aDllInfo->mChipCategory = new int[chipcount]; 

    aDllInfo->mChipName[0] = plugin_name;
    aDllInfo->mChipCategory[0] = 2;
}

/* create a chip */
ATANUADLLEXPORT int ATANUACALL create(chipinfostruct *aChipInfo, const char *aChipname)
{
    if (strcmp(aChipname, plugin_name) != 0)
        return 0; // unknown chip

    /* Number of pins for the structure */
    aChipInfo->mPinCount = 3;     

    /* Pin output data states. See pinmodes enum. */
    aChipInfo->mPinOutput = new int[3];   
    aChipInfo->mPinOutput[0] = PINSTATE_READ;
    aChipInfo->mPinOutput[1] = PINSTATE_READ;
    aChipInfo->mPinOutput[2] = PINSTATE_HIGHZ;

    /* Pin input data states. See netstates enum. */
    aChipInfo->mPinInput = new int[3];    

    aChipInfo->mWidth = 2;      /* Chip width */
    aChipInfo->mHeight = 2;     /* Chip height */

    /* Pin coordinates in relation to the chip. Two floats per pin. */
    aChipInfo->mPinCoordinates = new float[3*2]; 
    aChipInfo->mPinCoordinates[0*2+0] = 0.75f; // pin 1: top center
    aChipInfo->mPinCoordinates[0*2+1] = 0.0f;
    aChipInfo->mPinCoordinates[1*2+0] = 0.0f; // pin 2: left edge
    aChipInfo->mPinCoordinates[1*2+1] = 1.0f;
    aChipInfo->mPinCoordinates[2*2+0] = 1.5f; // pin 3: right edge
    aChipInfo->mPinCoordinates[2*2+1] = 1.0f;

    /* Texture filename. Can be NULL. */
    aChipInfo->mTextureFilename = NULL; 

    /* Chip name rendered at the center of the chip */
    aChipInfo->mChipName = "P";        

    /* Chip tooltip. Can be NULL. */
    aChipInfo->mTooltip = "Simple Relay";         

    /* Tooltips for the pins. Can be NULL. */
    aChipInfo->mPinTooltips = new const char*[3];
    aChipInfo->mPinTooltips[0] = "Switch";
    aChipInfo->mPinTooltips[1] = "Input";
    aChipInfo->mPinTooltips[2] = "Output";

    /* Number of bytes in persistent data store. Can be 0. */
    aChipInfo->mPersistentDataCount = 0;     

    /* Pointer to the persistent data store. Can be NULL. */
    aChipInfo->mPersistentDataPtr = NULL; 

    /* User pointer for storing other chip-related data. */
    aChipInfo->mUserPtr = NULL;        
    return 1;
}

/* Update a chip */
ATANUADLLEXPORT void ATANUACALL update(chipinfostruct *aChipInfo, float aTick)
{
    if (aChipInfo->mPinInput[0] != NETSTATE_HIGH)
    {
        aChipInfo->mPinOutput[2] = PINSTATE_HIGHZ;
        return;
    }
    switch (aChipInfo->mPinInput[1])
    {
    case NETSTATE_LOW:
        aChipInfo->mPinOutput[2] = PINSTATE_WRITE_LOW;
        break;
    case NETSTATE_HIGH:
        aChipInfo->mPinOutput[2] = PINSTATE_WRITE_HIGH;
        break;
    default:
        aChipInfo->mPinOutput[2] = PINSTATE_HIGHZ;
    }
    return;
}

/* Render and/or handle key input. Return 0 to let Atanua render the chip. */
ATANUADLLEXPORT int ATANUACALL render(chipinfostruct *aChipInfo, int aKey)
{
    int i;
    static int testcycle = 0;
    static int rendermode = 0;
    if (aKey == 'u')
    {
        if (testcycle == 0)
        {
            aChipInfo->mAsyncCall = ATANUA_ASYNC_CALL_STORE_UNDO;
            testcycle = 1; // make sure we don't do this over and over again
        }
        return 0;
    }
    if (aKey == 'q')
    {
        if (testcycle == 0)
        {
            aChipInfo->mAsyncCall = ATANUA_ASYNC_CALL_OKCANCEL;
            aChipInfo->mAsyncCallParam = "ok/cancel test";
            testcycle = 1; 
        }
        else
        {
            if (testcycle == 1)
            {
                if (aChipInfo->mAsyncCallReturn != NULL)
                {
                    // do something
                }
                testcycle = 2; // make sure we don't do this over and over again
            }
        }
        return 0;
    }
    if (aKey == 'o')
    {
        if (testcycle == 0)
        {
            aChipInfo->mAsyncCall = ATANUA_ASYNC_CALL_OPENFILE;
            aChipInfo->mAsyncCallParam = "openfile test";
            aKey = 0;
            testcycle = 1;
        }
        else
        {
            if (testcycle == 1)
            {
                if (aChipInfo->mAsyncCallReturn != NULL)
                {
                    fclose((FILE*)aChipInfo->mAsyncCallReturn);
                }
                testcycle = 2; // make sure we don't do this over and over again
            }
        }
        return 0;
    }
    if (aKey == 's')
    {
        if (testcycle == 0)
        {
            aChipInfo->mAsyncCall = ATANUA_ASYNC_CALL_OPENFILE;
            aChipInfo->mAsyncCallParam = "savefile test";
            aKey = 0;
            testcycle = 1;
        }
        else
        {
            if (testcycle == 1)
            {
                if (aChipInfo->mAsyncCallReturn != NULL)
                {
                    fclose((FILE*)aChipInfo->mAsyncCallReturn);
                }
                testcycle = 2; // make sure we don't do this over and over again
            }
        }
        return 0;
    }
    testcycle = 0;
#ifdef _WIN32
    if (aKey == 'm')
    {
        rendermode = (rendermode + 1) % 2;
    }

    int tick = GetTickCount();
#endif

    switch (rendermode)
    {
#ifdef _WIN32
    case 1:
        glBegin(GL_TRIANGLE_STRIP);
        glColor4f(1,0,0,1);
            glVertex3f(-0.5,-0.5,0);
            glVertex3f(-0.5,0.5,0);
        glColor4f(0,1,1,1);
            glVertex3f(0.5,-0.5,0);
            glVertex3f(0.5,0.5,0);
        glEnd();
        glColor4f(0,0,0,0.6f);
        glBegin(GL_TRIANGLE_STRIP);
        for (i = 0; i < 11; i++)
        {
            glVertex3f(-0.5f+(i/10.0f),-0.2f+sinf((i*100+tick) * 0.00329857f)*0.3f,0);
            glVertex3f(-0.5f+(i/10.0f),0.2f+sinf((i*100+tick) * 0.00329857f)*0.3f,0);
        }
        glEnd();
        return 1;
        break;
#endif
    default:
        // Let Atanua handle rendering
        return 0;
    }
}

/* Called when chip is being destroyed. */
ATANUADLLEXPORT void ATANUACALL cleanup(chipinfostruct *aChipInfo)
{   
    // Free the bits that we allocated. 
    // Atanua has no idea how we allocated these - could be globals, for instance.
    delete[] aChipInfo->mPinOutput;   
    delete[] aChipInfo->mPinInput;    
    delete[] aChipInfo->mPinCoordinates; 
    delete[] aChipInfo->mPinTooltips;
    return;
}
