#include <Arduino.h>

bool hd_bittyControllerHasEvent(SoftwareSerial &sSerial);
bool hd_bittyControllerEvent(String event);
bool hd_bittyControllerDpad(String dpad, String button, int pressed);
bool hd_bittyControllerTouchpad(int touched);
bool hd_bittyControllerGeneral(int pressed);
int hd_bittyControllerButton();
int hd_bittyControllerMotionSpeed();
int hd_bittyControllerMotionDirection();
