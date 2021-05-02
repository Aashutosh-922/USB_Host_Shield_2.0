/*
 Example sketch for the Switch Pro Bluetooth library - developed by Kristian Sloth Lauszus
 For more information visit the Github repository: github.com/felis/USB_Host_Shield_2.0 or
 send me an e-mail: lauszus@gmail.com
 */

#include <SwitchProBT.h>
#include <usbhub.h>

// Satisfy the IDE, which needs to see the include statement in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

USB Usb;
//USBHub Hub1(&Usb); // Some dongles have a hub inside
BTD Btd(&Usb); // You have to create the Bluetooth Dongle instance like so

/* You can create the instance of the SwitchProBT class in two ways */
// This will start an inquiry and then pair with the Switch Pro controller - you only have to do this once
// You will need to press the Sync button next to the USB connector to put the controller into pairing mode.
SwitchProBT SwitchPro(&Btd, PAIR);

// After that you can simply create the instance like so and then press a button on the device
//SwitchProBT SwitchPro(&Btd);

uint16_t lastMessageCounter = -1;
uint32_t home_timer;

void setup() {
  Serial.begin(115200);
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); // Halt
  }
  Serial.print(F("\r\nSwitch Pro Bluetooth Library Started"));
}

void loop() {
  Usb.Task();

  if (SwitchPro.connected() && lastMessageCounter != SwitchPro.getMessageCounter()) {
    lastMessageCounter = SwitchPro.getMessageCounter();

    if (SwitchPro.getAnalogHat(LeftHatX) > 5000 || SwitchPro.getAnalogHat(LeftHatX) < -5000 ||
        SwitchPro.getAnalogHat(LeftHatY) > 5000 || SwitchPro.getAnalogHat(LeftHatY) < -5000 ||
        SwitchPro.getAnalogHat(RightHatX) > 5000 || SwitchPro.getAnalogHat(RightHatX) < -5000 ||
        SwitchPro.getAnalogHat(RightHatY) > 5000 || SwitchPro.getAnalogHat(RightHatY) < -5000) {
      Serial.print(F("\r\nLeftHatX: "));
      Serial.print(SwitchPro.getAnalogHat(LeftHatX));
      Serial.print(F("\tLeftHatY: "));
      Serial.print(SwitchPro.getAnalogHat(LeftHatY));
      Serial.print(F("\tRightHatX: "));
      Serial.print(SwitchPro.getAnalogHat(RightHatX));
      Serial.print(F("\tRightHatY: "));
      Serial.print(SwitchPro.getAnalogHat(RightHatY));
    }

    // Hold the HOME button for 1 second to disconnect the controller
    // This prevents the controller from disconnecting when it is reconnected,
    // as the HOME button is sent when it reconnects
    if (SwitchPro.getButtonPress(HOME)) {
      if (millis() - home_timer > 1000)
        SwitchPro.disconnect();
    } else
      home_timer = millis();

    if (SwitchPro.getButtonClick(HOME))
      Serial.print(F("\r\nHome"));
    if (SwitchPro.getButtonClick(CAPTURE))
      Serial.print(F("\r\nCapture"));
    if (SwitchPro.getButtonClick(LEFT)) {
      /*SwitchPro.setLedOff();
      SwitchPro.setLedOn(LED1);*/
      Serial.print(F("\r\nLeft"));
    }
    if (SwitchPro.getButtonClick(RIGHT)) {
      /*SwitchPro.setLedOff();
      SwitchPro.setLedOn(LED3);*/
      Serial.print(F("\r\nRight"));
    }
    if (SwitchPro.getButtonClick(DOWN)) {
      /*SwitchPro.setLedOff();
      SwitchPro.setLedOn(LED4);*/
      Serial.print(F("\r\nDown"));
    }
    if (SwitchPro.getButtonClick(UP)) {
      /*SwitchPro.setLedOff();
      SwitchPro.setLedOn(LED2);*/
      Serial.print(F("\r\nUp"));
    }

    if (SwitchPro.getButtonClick(PLUS))
      Serial.print(F("\r\nPlus"));
    if (SwitchPro.getButtonClick(MINUS))
      Serial.print(F("\r\nMinus"));

    if (SwitchPro.getButtonClick(A))
      Serial.print(F("\r\nA"));
    if (SwitchPro.getButtonClick(B)) {
      //SwitchPro.setRumbleToggle();
      Serial.print(F("\r\nB"));
    }
    if (SwitchPro.getButtonClick(X))
      Serial.print(F("\r\nX"));
    if (SwitchPro.getButtonClick(Y))
      Serial.print(F("\r\nY"));

    if (SwitchPro.getButtonClick(L))
      Serial.print(F("\r\nL"));
    if (SwitchPro.getButtonClick(R))
      Serial.print(F("\r\nR"));
    if (SwitchPro.getButtonClick(ZL))
      Serial.print(F("\r\nZL"));
    if (SwitchPro.getButtonClick(ZR))
      Serial.print(F("\r\nZR"));
    if (SwitchPro.getButtonClick(L3))
      Serial.print(F("\r\nL3"));
    if (SwitchPro.getButtonClick(R3))
      Serial.print(F("\r\nR3"));
  }
}
