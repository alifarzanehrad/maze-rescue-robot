void compas_calibrate (void)
    {
    lcd_clear();
    lcd_putsf("increase-> calibrate");

    lcd_gotoxy(0,2);
    lcd_putsf("decrease-> fac reset");


    while(increase==1 && decrease==1 && previouse_page==1 && next_page==1);
    if(!increase)          // cmps calibration  
        {  
        #asm("cli");
        i2c_start();
        i2c_write(0xC0);
        i2c_write(0);
        i2c_write(0xf0);
        i2c_stop();
        delay_ms(40);

        i2c_start();
        i2c_write(0xC0);
        i2c_write(0);
        i2c_write(0xf5);
        i2c_stop();
        delay_ms(40);

        i2c_start();
        i2c_write(0xC0);
        i2c_write(0);
        i2c_write(0xf7);
        i2c_stop();
        delay_ms(400);
        
        motor(30,30,-30,-30);

        lcd_clear();
        lcd_puts("Now robot will rotate");
        lcd_gotoxy(0,1);
        lcd_puts("press enter when cmp didn't blink");
        while(enter==1);
        while(enter==0);
        motor(0,0,0,0);
        
        i2c_start();
        i2c_write(0xC0);
        i2c_write(0);
        i2c_write(0xf8);
        i2c_stop();
        delay_ms(500);
        
        
        }
    else if (decrease==0)    // factory reset
        {
        while (decrease==0);
        lcd_clear();
        lcd_putsf("factory rst.");
        i2c_start();
        i2c_write(0xC0);
        i2c_write(0);
        i2c_write(0x20);
        i2c_stop();
        delay_ms(20);
        lcd_putsf(".");
        
        i2c_start();
        i2c_write(0xC0);
        i2c_write(0);
        i2c_write(0x2A);
        i2c_stop();
        delay_ms(20);
        lcd_putsf(".");

        i2c_start();
        i2c_write(0xC0);
        i2c_write(0);
        i2c_write(0x60);
        i2c_stop();
        delay_ms(20);
        lcd_putsf(".");
        
        delay_ms(300);
        lcd_clear();
        lcd_putsf("factory reset Done");
        lcd_puts("press enter for exit");
        while(enter==1);
        while(enter==0);
        }
    }
    
