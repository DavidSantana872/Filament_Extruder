void main_Process()
{
    if (Last_d_y != d_y)
    {
        lcd.clear();
        Last_d_y = d_y;
    }
    if (d_y == 1)
    {
        lcd.setCursor(0, 0);
        lcd.print("1- Information <");
        lcd.setCursor(0, 1);
        lcd.print("2- Start        ");
    }
    else if (d_y == 2)
    {
        lcd.setCursor(0, 0);
        lcd.print("1- Information");
        lcd.setCursor(0, 1);
        lcd.print("2- Start       <");
    }
    else if (d_y == 3)
    {
        lcd.setCursor(0, 0);
        lcd.print("2- Start        ");
        lcd.setCursor(0, 1);
        lcd.print("3- Edit Values <");
    }
    else if (d_y == 4)
    {
        lcd.setCursor(0, 0);
        lcd.print("3- Edit Values  ");
        lcd.setCursor(0, 1);
        lcd.print("4- Reset Value <");
    }
    TECLA = teclado.getKey();
    if (TECLA == 'A')
    {
        if (d_y < 4)
        {
            d_y += 1;
        }
    }
    else if (TECLA == 'B')
    {
        if (d_y > 1)
        {
            d_y -= 1;
        }
    }
    else if ((TECLA == '#' && d_y == 1) || TECLA == '1')
    {
        Information();
    }
    else if ((TECLA == '#' && d_y == 2) || TECLA == '2')
    {
        Star_Off();
    }
    else if ((TECLA == '#' && d_y == 3) || TECLA == '3')
    {
        Edit_Values();
    }
    else if ((TECLA == '#' && d_y == 3) || TECLA == '4')
    {
        // Reset_System();
    }
    Star_Process();
}
