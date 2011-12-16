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
    
    char* version(void);			// get the library version
    
    void listen(void);
    
    bool isReleased() const {return released_;}
    bool isPressed() const {return pressed_;}
    
    bool onChange() const {return changed_;}
    bool onPress() const {return justPressed_;}
    bool onRelease() const {return justReleased_;}
        
    unsigned int getDebounceDelay(void);
    void setDebounceDelay(unsigned int);
    void clearDebounceDelay(void);
    
    bool onDoubleClick();
    
    unsigned int getDoubleClickDelay(void) {return doubleClickDelay_;}
    void setDoubleClickDelay(unsigned int);
    
    // FIXME This code would not work if you call this method twice
    bool onPressAsToggle();
    // FIXME This code would not work if you call this method twice
    bool onReleaseAsToggle();
     
    bool isHold();
    
    unsigned int getHoldDelay(void);
    void setHoldDelay(unsigned int);
    
    unsigned int getPressCount(void) const {return pressCount_;}
    void clearPressCount(void);    
    unsigned int getReleaseCount(void) const {return releaseCount_;}
    void clearReleaseCount(void);
    
    bool isNthPress(unsigned int moduloByMe) const;
    bool isNthRelease(unsigned int moduloByMe) const;
    
  private:
    int myPin_;
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

