#pragma once

#include "Arduino.h"

class Button {
private:

    byte defaultPin_ = 2;
    byte pin_;

    //
    boolean button_;
    byte buttonMode_;

    //timers
    unsigned long rattleTimer_; //таймер против дребезга контактов
    unsigned long holdingTimer_;

    //button modes
    const boolean singleMode_ = 0;
    const boolean triggerMode_ = 1;
    const boolean holdingMode_ = 2;
    
    //time
    //
    const byte rattleDelay_ = 250;
    //
    unsigned int holdingTime_ = 2000;

    //flags
    boolean flag_ = 0;
    boolean trigger_ = 0;
    boolean isButtonPressed_ = 0;

    //functions
    
    
public:

    Button();
    Button(byte pin);
    ~Button();

    byte getPinNumber();

    boolean checkClick();
    boolean checkHoldingClick();

    void setSingleMode();
    void setTriggerMode();
    void setHoldingMode();
    /*
    set the time (in milliseconds) holding a button pressed 
    to get HIGH value after this time is over.
    установка вренмени (в миллисекундах) удерживания кнопки нажатой, 
    по истечение которого функция checkHoldingClick() вернет высокое значение.
    */
    void setHoldingModeTime(int holdingTime);

    //позволяет сменить пин подключенной к ардуино кнопки с помощью оператора равно
    Button& operator = (byte pin)
    {
        this->pin_ = pin;
        return *this;
    }
};


