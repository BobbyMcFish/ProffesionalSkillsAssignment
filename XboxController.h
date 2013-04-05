#include <Windows.h>
#include <Xinput.h>
#define WIN32_LEAN_AND_MEAN
#pragma comment(lib, "XInput.lib")

// XBOX Controller Class Definition
class CXBOXController
{
private:
    XINPUT_STATE controllerState;
    int controllerNum;
public:
    CXBOXController(int playerNumber);
    XINPUT_STATE GetState();
    bool IsConnected();
    void Vibrate(int leftVal = 0, int rightVal = 0);
};
