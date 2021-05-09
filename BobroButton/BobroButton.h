#pragma once
#include "Arduino.h"

#define HOLDING_MODE_SIGNAL 2 
#define ERROR_CODE 3

#define SINGLE_MODE 1
#define TRIGGER_MODE 2

class Button {
private:

    byte defaultPin_ = 2;
    byte pin_;

    
    boolean button_; //the data out of pin goes into this variable 
    byte buttonMode_; //button mode: single or trigger
    boolean isHoldingMode_ = 0;

    //timers
    unsigned long rattleTimer_; //anti rattle timer - таймер против дребезга контактов
    unsigned long holdingTimer_;
    
    //time
    //delay for anti rattle 
    const byte rattleDelay_ = 250;
    //the time to holding button for 
    unsigned int holdingTime_ = 2000;

    //flags
    boolean flag_ = 0;
   
    boolean trigger_ = 0;
    boolean isButtonPressed_ = 0;

    //functions
    byte getPinNumber();
    
public:

    Button();
    Button(byte pin);
    ~Button();

    byte checkClick();
    boolean checkHoldingClick();

    void setSingleMode();
    void setTriggerMode();
    //void setHoldingMode();

    //add checking holding button 
    void addHoldingMode();
    void addHoldingMode(int holdingTime);

    /*
    set the time (in milliseconds) holding a button pressed 
    to get HIGH value after this time is over.
    установка вренмени (в миллисекундах) удерживания кнопки нажатой, 
    по истечение которого функция checkHoldingClick() вернет высокое значение.
    */
    void setHoldingModeTime(int holdingTime);

    //позволяет сменить пин подключенной к ардуино кнопки с помощью оператора равно
    Button& operator = (byte pin);


};


