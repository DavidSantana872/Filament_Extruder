void Star_Off()
{
  lcd.clear();
  if (Star_Process_Value == false)
  {
    while (1)
    {
      lcd.setCursor(0, 0);
      lcd.print("Press 1 to Star");
      lcd.setCursor(0, 1);
      lcd.print("Press D to back");
      TECLA = teclado.getKey();
      if (TECLA == '1')
      {
        // Comunicacion arduino esclavo
        // iniciar arduino esclavo
        Serial.write(0);
        Star_Process_Value = true;
        break;
      }
      else if (TECLA == 'D')
      {
        break;
      }
    }
  }
  else if (Star_Process_Value == true)
  {
    lcd.clear();
    while (1)
    {
      lcd.setCursor(0, 0);
      lcd.print("Press 1 to Stop");
      lcd.setCursor(0, 1);
      lcd.print("Press D to back");
      TECLA = teclado.getKey();
      if (TECLA == '1')
      {
        // Comunicacion arduino esclavo
        // apagar motor en esclavo
        Serial.write(2);
        Star_Process_Value = false;
        break;
      }
      else if (TECLA == 'D')
      {
        break;
      }
      Star_Process();
    }
  }
}
