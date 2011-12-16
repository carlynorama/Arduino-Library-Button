/*
	Button.h - - Button library for Wiring/Arduino - Version 0.1
	
	Original library 		(0.1) by Carlyn Maw.
	
 */

// ensure this library description is only included once
#ifndef Button_h
#define Button_h

// include types & constants of Wiring core API
#include "WProgram.h"

class Button {
  public:
    Button(int myPin, bool myMode);
    Button(int myBit, bool myMode, unsigned char *myRegister);
    
    char* version(void);			// get the library version
    unsigned char getRegisterValue(void);
    
    void listen(void);
    
    bool isReleased(bool refreshPinData = false);
    bool isPressed(bool refreshPinData = false);
    
    bool onChange(bool refreshPinData = false);
    bool onPress(bool refreshPinData = false);
    bool onRelease(bool refreshPinData = false);
        
    unsigned int getDebounceDelay(void);
    void setDebounceDelay(unsigned int);
    void clearDebounceDelay(void);
    
    bool onDoubleClick(bool refreshPinData = false);
    
    unsigned int getDoubleClickDelay(void);
    void setDoubleClickDelay(unsigned int);
    
    bool onPressAsToggle(bool refreshPinData = false);
    bool onReleaseAsToggle(bool refreshPinData = false);
     
    bool isHold(bool refreshPinData = false);
    
    unsigned int getHoldDelay(void);
    void setHoldDelay(unsigned int);
    
    unsigned int getPressCount(void);
    void clearPressCount(void);    
    unsigned int getReleaseCount(void);
    void clearReleaseCount(void);
    
    bool isNthPress(unsigned int moduloByMe);
    bool isNthRelease(unsigned int moduloByMe);
    
  private:
    int myPin_;
    int myBit_;
    unsigned char *myRegister_;
    unsigned char registerValue_;
    bool type_;  //direct pin or shift register
    bool mode_;  //HIGH == pressed (1) or LOW == pressed (0)
    
    bool lastState_;
    bool currentState_;
    
    bool debounced_;
    bool lastDebouncedState_;
    bool currentDebouncedState_;
    unsigned long int debounceTimerStartTime_;
    unsigned int debounceDelay_;
    
    bool pressed_;
    bool released_;
    
    bool changed_;
    bool justPressed_;
    bool justReleased_;
    unsigned int pressCount_;
    unsigned int releaseCount_;
   
    unsigned int doubleClickDelay_;
    unsigned int holdDelay_;
    
    bool pToggleFlag_;
    bool rToggleFlag_;
    
    unsigned long int lastPressTime_;
    unsigned long int currentPressTime_;
    unsigned long int lastReleaseTime_;
    unsigned long int currentReleaseTime_;
    
    unsigned long int currentTime_;
};

#endif

