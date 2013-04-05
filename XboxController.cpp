#include "XboxController.h"

CXBOXController::CXBOXController(int playerNumber)
{
    // Set the Controller Number
    controllerNum = playerNumber - 1;
}

XINPUT_STATE CXBOXController::GetState()
{
    // Zeroise the state
    ZeroMemory(&controllerState, sizeof(XINPUT_STATE));

    // Get the state
    XInputGetState(controllerNum, &controllerState);

    return controllerState;
}

bool CXBOXController::IsConnected()
{
    // Zeroise the state
    ZeroMemory(&controllerState, sizeof(XINPUT_STATE));

    // Get the state
    DWORD Result = XInputGetState(controllerNum, &controllerState);

    if(Result == ERROR_SUCCESS)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void CXBOXController::Vibrate(int leftVal, int rightVal)
{
    // Create a Vibraton State
    XINPUT_VIBRATION Vibration;

    // Zeroise the Vibration
    ZeroMemory(&Vibration, sizeof(XINPUT_VIBRATION));

    // Set the Vibration Values
    Vibration.wLeftMotorSpeed = leftVal;
    Vibration.wRightMotorSpeed = rightVal;

    // Vibrate the controller
    XInputSetState(controllerNum, &Vibration);
}
