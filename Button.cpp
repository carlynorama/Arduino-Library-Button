/*
  Button.h - Button library for Wiring/Arduino
  (cc) 2007 Carlyn Maw .  Some rights reserved.
  
  Created 13 Apr 2007
  Version 0.1
*/

// include this library's description file
#include "Button.h"

Button::Button(int myPin, bool mode)    
    : type_(0)
    , mode_(mode)
    , myBit_(myPin_)
    , myPin_(myPin_)
    , myRegister_(0)

    , registerValue_(0)
    
    , lastState_(0)
    , currentState_(0)
    
    , debounced_(1)
    , lastDebouncedState_(0)
    , currentDebouncedState_(0)
    , debounceTimerStartTime_(0)
    , debounceDelay_(30)
    
    , pressed_(0)
    , released_(1)
  
    , changed_(0)
    , justPressed_(0)
    , justReleased_(0)
    , pressCount_(0)
    , releaseCount_(0)
    
    , doubleClickDelay_(400)
    , holdDelay_(1500)
    
    , pToggleFlag_(0) //starts in off
    , rToggleFlag_(1) //starts in off
    
    , lastPressTime_(0)
    , currentPressTime_(0)
    , lastReleaseTime_(0)
    , currentReleaseTime_(0) {

    pinMode(myPin_, INPUT);
}

Button::Button(int myBit, bool mode, unsigned char *myRegister)
    : type_(1)
    , mode_(mode)
    , myBit_(myBit_)
    , myPin_(myBit_)  
    , myRegister_(myRegister)

    , registerValue_(255)
    
    , lastState_(0)
    , currentState_(0)
    
    , debounced_(1)
    , lastDebouncedState_(0)
    , currentDebouncedState_(0)
    , debounceTimerStartTime_(0)
    , debounceDelay_(30)
    
    , pressed_(0)
    , released_(1)
  
    , changed_(0)
    , justPressed_(0)
    , justReleased_(0)
    , pressCount_(0)
    , releaseCount_(0)
    
    , doubleClickDelay_(400)
    , holdDelay_(1500)
    
    , pToggleFlag_(0) //starts in off
    , rToggleFlag_(1) //starts in off
    
    , lastPressTime_(0)
    , currentPressTime_(0)
    , lastReleaseTime_(0)
    , currentReleaseTime_(0)
{}

// Public Methods //////////////////////////////////////////////////////////////
// Functions available in Wiring sketches, this library, and other libraries

//---------////////////////////MAIN LOOP / LISTENER ///////////--------------//

void Button::listen(void){
    currentTime_ = millis();
  
    if(!type_) {
        currentState_ = digitalRead(myPin_);
    } else {
        registerValue_ = *myRegister_;
  	currentState_ = registerValue_ & (1 << myBit_);
    }
  
    if (currentState_ != lastState_) {
        debounced_ = false;
        debounceTimerStartTime_ = currentTime_;
    } else if ((currentTime_ - debounceTimerStartTime_) > debounceDelay_) {
        debounced_ = true;
    }
  
    if (debounced_) {
        lastDebouncedState_ = currentDebouncedState_;
        currentDebouncedState_ = currentState_;
    }
  
    if (currentDebouncedState_ == mode_) {
        pressed_ = true;
        released_ = false;
        justReleased_ = false;
    } else {
        pressed_ = false;
        released_ = true;
        justPressed_ = false;
    }
  
    if (lastDebouncedState_ != currentDebouncedState_) {
        changed_ = true;
    } else {
        changed_ = false;
        justPressed_ = false;
        justReleased_ = false;
    }
  
    if (changed_ && pressed_) {
        justPressed_ = true;
        pressCount_ ++;
        lastPressTime_ = currentPressTime_;
        currentPressTime_ = currentTime_;
        justReleased_ = false;
    } else if(changed_ && released_){
        justPressed_ = false;
        justReleased_ = true;
        releaseCount_ ++;
        lastReleaseTime_ = currentReleaseTime_;
        currentReleaseTime_ = currentTime_;
    } else if(!changed_) { //added no effect...
        justPressed_ = false; //added no effect...
        justReleased_ = false; //added no effect...
    } else if (released_) { //added no effect...
        justPressed_ = false; //added no effect...
    } else if (pressed_) { //added no effect...
        justReleased_ = false; //added no effect...
    }
	
    //wrap up the funtion
    lastState_ = currentState_;
}
  
 //----------------------------------------------------------- END LISTENER
 
 // -------------------------------------------------------//// DEBOUNCE /// 
 
unsigned int Button::getDebounceDelay(void) {
    return debounceDelay_;
}

void Button::setDebounceDelay(unsigned int newDebounceDelay) {
    debounceDelay_ = newDebounceDelay;
}

void Button::clearDebounceDelay(void){
    setDebounceDelay(0);
}
  
 // -------------------------------------------------------//// UP OR DOWN /// 
  
bool Button::isReleased(bool refreshPinData){  
    if (refreshPinData) {
        listen();
  	return released_;
    }
    return released_;
}

bool Button::isPressed(bool refreshPinData){
    if (refreshPinData) {
        listen();
    } 
    return pressed_;
}    

 // -------------------------------------------------------//// COUNTS /// 
 
unsigned int Button::getPressCount(void) {
    return pressCount_;
}

void Button::clearPressCount(void){
    pressCount_ = 0;
}
 
unsigned int Button::getReleaseCount(void) {
    return pressCount_;
}

void Button::clearReleaseCount(void){
    releaseCount_ = 0;
}
  
 // -------------------------------------------------------////   EVENTS   /// 
  
bool Button::onChange(bool refreshPinData){
    if (refreshPinData) {
        listen();
    }
    return changed_;
}
  
bool Button::onPress(bool refreshPinData){
    if (refreshPinData) {
        listen();
    }
    return justPressed_;
}
    
bool Button::onRelease(bool refreshPinData){
    if (refreshPinData) {
        listen();
    }
    return justReleased_;
}

 //---------------------------------------------------- TOGGLES 
 
bool Button::onPressAsToggle(bool refreshPinData){
    if (refreshPinData) {
        listen();    
    }

    if (justPressed_) {
        pToggleFlag_ = !pToggleFlag_;
    }
    return pToggleFlag_;
}
 
bool Button::onReleaseAsToggle(bool refreshPinData){
    if (refreshPinData) {
        listen();    
    }

    if (justReleased_) {
        rToggleFlag_ = !rToggleFlag_;
    }
    return rToggleFlag_;
}

 //------------------------------------------------------- DOUBLE CLICK
 
bool Button::onDoubleClick(bool refreshPinData){
    if (refreshPinData) {
        listen();    
    }
    return(justReleased_ && (currentReleaseTime_ - lastReleaseTime_) <= doubleClickDelay_);
}

unsigned int Button::getDoubleClickDelay(void) {
    return doubleClickDelay_;
}

void Button::setDoubleClickDelay(unsigned int newDoubleClickDelay) {
    doubleClickDelay_ = newDoubleClickDelay;
}

 //---------------------------------------------------------------- HOLDING

bool Button::isHold(bool refreshPinData){
    if (refreshPinData) {
        listen();    
    }
    return pressed_ && (currentTime_ - currentPressTime_) > holdDelay_;
}
 
unsigned int Button::getHoldDelay(void) {
    return holdDelay_;
}

void Button::setHoldDelay(unsigned int newHoldDelay) {
    holdDelay_ = newHoldDelay;
}

 //----------------------------------------------------------- isNTH Sillyness

bool Button::isNthPress(unsigned int moduloByMe) {
    return pressCount_ % moduloByMe == 0;
}


bool Button::isNthRelease(unsigned int moduloByMe) {
    return releaseCount_ % moduloByMe == 0;
}

 // -------------------------------------------------------////    ADMIN   /// 
unsigned char Button::getRegisterValue(void){
    return registerValue_;
}

char* Button::version(void) {
    return "0.1";
}
