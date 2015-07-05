harbour-ambience-tohkbd2
======

### Shortly 
* When TOHKBD base is attached to the phone for very first time
  * NFC ID is read by ```tohd``` and subbmitted to Jolla Store
  * Store install required packages automatically
  * During installation, EEPROM contents of TOHKBD are compared to certain vid/pid, and if they match, daemon is started
* After this, everytime TOHKBD base is attached to the phone, EEPROM contents are checked by udev rule, which starts daemon
* When daemon is started it creates a uinput device which is used to send key-events to system
* When the keyboard part is connected to the base, interrupt is generated which triggers followig sequence:
  * power-up keyboard and check can we communicate over I2C with keyboard chip. If comms test fails, shutdown keyboard.
  * send SW_KEYPAD_SLIDE event (keypad opened), which is registered by mce to turn display on
  * Show a notification that keyboard is connected
  * Change virtual keyboard layout to minimal (done through tohkbd2-user daemon which writes/reads dconf)
  * Force screen orientation to landscape
* Keyboard presense is checked every 2 secs. If comms test fails:
  * shutdown keyboard
  * send SW_KEYPAD_SLIDE event (keypad closed)
  * show notification that keyboard is removed
  * change virtual keyboard layout back to what it was before connecting keyboard
* When key is pressed on keyboard:
  * Interrupt is generated
  * daemon reads input report from keyboard chip over I2C and processes it
  * If a valid key was pressed, this is sent by uinput device to the system
  * some of keys have special function, like starting a application. these are processed in the daemon.
  

### Installing ... dont
But if you really want to:
 * either install the SDK and deploy your own RPM built from this branch 
 * or build it on your phone, but its a lot of work to set up the phone to build stuff, little bit of help is there:   
https://together.jolla.com/question/63393/compile-qt-app-inside-jolla/?page=1#63464
 * And install keymaps/scandic.qmap in place of /usr/share/qt5/keymaps/boston.qmap and restart lipstick or reboot

### References:

* TCA8424 datasheet: http://www.ti.com/lit/ds/symlink/tca8424.pdf
* TCA8424 evaluation module user's guide: www.ti.com/lit/ug/scdu004/scdu004.pdf

