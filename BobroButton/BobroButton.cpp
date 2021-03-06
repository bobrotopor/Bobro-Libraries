#include "BobroButton.h"

Button::Button() 
{
    pin_ = defaultPin_;
    pinMode(pin_, INPUT_PULLUP);
    buttonMode_ = SINGLE_MODE;
}
Button::Button(byte pin) 
{
    pin_ = pin;
    pinMode(pin_, INPUT_PULLUP);
    buttonMode_ = SINGLE_MODE;
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
    buttonMode_ = SINGLE_MODE;
}
void Button::setTriggerMode()
{
    flag_ = 0;
    buttonMode_ = TRIGGER_MODE;
}    
void Button::addHoldingMode() 
{

    isHoldingMode_ = 1;
}

void Button::setHoldingModeTime(int holdingTime) 
{
    holdingTime_ = holdingTime;
}

byte Button::checkClick()
{
    
    button_ = !digitalRead(pin_);
    if (buttonMode_ == SINGLE_MODE)
    {
        if (button_ == 1 && flag_ == 0 && millis() - rattleTimer_ > rattleDelay_) {
            rattleTimer_ = millis();
            flag_ = 1;
            
            //запомнинаем значение таймера
            if (isButtonPressed_ == 0 && isHoldingMode_) { 
                holdingTimer_ = millis();
                isButtonPressed_ = 1;
            }
    
        }
            
        if (button_ == 0 && flag_ == 1) {
            
            flag_ = 0;

            //сбрасываем значение таймера на 0 в случае отпускания кнопки
            if (isHoldingMode_) {
                holdingTimer_ = 0;
                isButtonPressed_ = 0;
            }
            
        }

        if (millis()-holdingTimer_ > holdingTime_ && flag_ == 1 && isHoldingMode_) 
            return HOLDING_MODE_SIGNAL;

        return flag_;
    }

    if (buttonMode_ == TRIGGER_MODE)
    {
        if (button_ == 1 && flag_ == 0 && millis() - rattleTimer_ > rattleDelay_) {
            rattleTimer_ = millis();
            flag_ = 1;
            trigger_ = !trigger_;

            //запомнинаем значение таймера
            if (isButtonPressed_ == 0 && isHoldingMode_) { 
                holdingTimer_ = millis();
                isButtonPressed_ = 1;
            }


        }

        if (button_ == 0 && flag_ == 1) {
            
            flag_ = 0;

            //сбрасываем значение таймера на 0 в случае отпускания кнопки
            if (isHoldingMode_) {
                holdingTimer_ = 0;
                isButtonPressed_ = 0;
            }
            
        }


        if (millis()-holdingTimer_ > holdingTime_ && flag_ == 1 && isHoldingMode_) 
            return HOLDING_MODE_SIGNAL;
        
        
        return trigger_;
    }


    
    return ERROR_CODE;
}

Button &Button::operator=(byte pin)
{
    this->pin_ = pin;
    return *this;
}

