#include "BobroButton.h"

Button::Button() 
{
    pin_ = defaultPin_;
    pinMode(pin_, INPUT_PULLUP);
}
Button::Button(byte pin) 
{
    pin_ = pin;
    pinMode(pin_, INPUT_PULLUP);
}

Button::~Button() 
{

}

byte Button::getPinNumber() 
{
    return pin_;
}

void Button::setSingleMode()
{
    flag_ = 0;
    buttonMode_ = singleMode_;
}
void Button::setTriggerMode()
{
    flag_ = 0;
    buttonMode_ = triggerMode_;
}    
void Button::setHoldingMode() 
{
    flag_ = 0;
    buttonMode_ = holdingMode_;
}

void Button::setHoldingModeTime(int holdingTime) 
{
    holdingTime_ = holdingTime;
}

boolean Button::checkClick()
{
    
    button_ = !digitalRead(pin_);
    if (buttonMode_ == singleMode_)
    {
        if (button_ == 1 && flag_ == 0 && millis() - rattleTimer_ > rattleDelay_) {
            rattleTimer_ = millis();
            flag_ = 1;
            
        }
            
        if (button_ == 0 && flag_ == 1) {
            
            flag_ = 0;
            
        }    

        return flag_;
    }

    if (buttonMode_ == triggerMode_)
    {
        if (button_ == 1 && flag_ == 0 && millis() - rattleTimer_ > rattleDelay_) {
            rattleTimer_ = millis();
            flag_ = 1;
            trigger_ = !trigger_;
        }

        if (button_ == 0 && flag_ == 1) {
            
            flag_ = 0;
            
        }

        return trigger_;
    }
    return button_;
}

boolean Button::checkHoldingClick()
{
    button_ = !digitalRead(pin_);
    if (buttonMode_ == holdingMode_) 
    {
        if (button_ == 1 && flag_ == 0 && millis() - rattleTimer_ > rattleDelay_) {
            
            flag_ = 1;
            
            if (isButtonPressed_ == 0) {
                holdingTimer_ = millis();
                isButtonPressed_ = 1;
            }
        }
        //restart function
        if (button_ == 0 && flag_ == 1) {
            
            flag_ = 0;
            isButtonPressed_ = 0;

        }
        
        
        if (millis()-holdingTimer_ > holdingTime_ && flag_ == 1) 
            return 1;  
        
        else 
            return 0;

    }
    else 
    {
        Serial.println("error: holding mode wasn't be set");
        return 0;
    }
        
}

//operators
//void Button::operator = (byte pin);



// boolean Button::getTriggerValue() 
// {
//     if (buttonMode_ == singleMode_)
//     {
//         return button_;
//     }
//     if (buttonMode_ == triggerMode_)
//     {
//         return button_;
//     }
// }
