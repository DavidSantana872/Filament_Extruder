void Information()
{
   lcd.clear();
   while (1)
   {
      TECLA = teclado.getKey();
      if (TECLA == 'D')
      {
         break;
      }
      // Delay time to clean the screen and show the new values.
      Differential_LCD = Inicial_Time_LCD - Final_Time_Time;
      Inicial_Time_LCD = millis();
      if (Differential_LCD >= Delay_Time_LCD)
      {
         Final_Time_Time = Inicial_Time_LCD;
         lcd.setCursor(0, 0);
         lcd.print("Temp: ");
         lcd.print(Temperature);
         lcd.setCursor(0, 1);
         lcd.print("Fan Velo: ");
         lcd.print(Velocidad_fan);
      }
      Star_Process();
   }
}
