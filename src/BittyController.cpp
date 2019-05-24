#include <Arduino.h>
#include <SoftwareSerial.h>
#include "BittyController.h"

#define BUFLEN 80
static char bittyBuf[BUFLEN + 1] = {0};

static void hd_bittyCheckResponse(SoftwareSerial &sSerial) 
{
  delay(30);
  int i = 0;
  while (sSerial.available() && i < BUFLEN)
  {
    bittyBuf[i++] = sSerial.read();
  }
  if (i > 0)
  {
    bittyBuf[i] = '\0';
  }
}


// Length in bytes of Bitty messages (including the opcode)
byte bittyLen[9] = {0, 2, 3, 3, 2, 3, 2, 2, 7};
char bittyMsg[7] = {0};

bool hd_bittyControllerHasEvent(SoftwareSerial &sSerial)
{
  hd_bittyCheckResponse(sSerial);
  char c = bittyBuf[0];
  if (c > 0 && c <= 8 && strlen(bittyBuf) == bittyLen[c])
  {
    memcpy(bittyMsg, bittyBuf, bittyLen[c]);
    bittyBuf[0] = '\0';
    return true;
  }
  return false;
}

bool hd_bittyControllerEvent(String event)
{
  if (event == "Dpad")
    return bittyMsg[0] == 1;
  if (event == "Touchpad motion")
    return bittyMsg[0] == 2;
  if (event == "Touchpad control")
    return bittyMsg[0] == 3;
  if (event == "General control")
    return bittyMsg[0] == 4;
  if (event == "Sampling Control")
    return bittyMsg[0] == 6;
  if (event == "Button")
    return bittyMsg[0] == 7;
  if (event == "Pin")
    return bittyMsg[0] == 8;
  return false;
}


bool hd_bittyControllerDpad(String dpad, String button, int pressed)
{
  if (bittyMsg[0] != 1)
    return false;
  int d = bittyMsg[1];
  if (d < 1 || d > 16)
    return false;
  if (pressed && d % 2 != 1)
    return false;
  if (dpad == "left") {
    if (bittyMsg[1] > 8)
      return false;
  } else if (bittyMsg[1] < 9) {
    return false;
  }
  d = ((d - 1) % 8)/2;
  switch (d)
  {
    case 0:
      return (button == "top");
    case 1:
      return (button == "bottom");
    case 2:
      return (button == "left");
    case 3:
      return (button == "right");
    }
}


int hd_bittyControllerMotionSpeed()
{
  if (bittyMsg[0] != 2)
    return 0;
  return (int) bittyMsg[1];
}

int hd_bittyControllerMotionDirection()
{
  if (bittyMsg[0] != 2)
    return 0;
  return (int) bittyMsg[2];
}


bool hd_bittyControllerTouchpad(int touched)
{
  if (bittyMsg[0] != 3)
    return false;
  return bittyMsg[2] == touched;
}


bool hd_bittyControllerGeneral(int pressed)
{
  if (bittyMsg[0] != 4)
    return false;
  return bittyMsg[2] == pressed;
}


int hd_bittyControllerButton()
{
  if (bittyMsg[0] != 7)
    return -1;
  return (int) bittyMsg[1];
}
