void Edit_Values()
{
  lcd.clear();
  while (1)
  {
    TECLA = teclado.getKey();
    if (TECLA == 'A')
    {
      if (linea <= 2)
      {
        linea = linea + 1;
        lcd.clear();
      }
    }
    else if (TECLA == 'B')
    {
      if (linea >= 1)
      {
        linea = linea - 1;
        lcd.clear();
      }
    }
    if (identificador == 0)
    {
      if (linea == 0)
      {
        lcd.setCursor(0, 0);
        lcd.print("1- TEMPERATURA");
        lcd.setCursor(0, 1);
        lcd.print("2- VELOCIDADES");
        lcd.setCursor(15, 0);
        lcd.print("<");
        if (TECLA == '#')
        {
          identificador = 1;
          memset(valor_char, ' ', dimension);
          lcd.clear();
        }
      }
      if (linea == 1)
      {
        lcd.setCursor(0, 0);
        lcd.print("1- TEMPERATURA");
        lcd.setCursor(0, 1);
        lcd.print("2- VELOCIDADES");
        lcd.setCursor(15, 1);
        lcd.print("<");
        if (TECLA == '#')
        {
          identificador = 2;
          memset(valor_char, ' ', dimension);
          lcd.clear();
        }
      }
      if (linea == 2)
      {
        lcd.setCursor(0, 0);
        lcd.print("3- PID");
        lcd.setCursor(0, 1);
        lcd.print("4- MOTOR");
        lcd.setCursor(15, 0);
        lcd.print("<");
        if (TECLA == '#')
        {
          identificador = 3;
          memset(valor_char, ' ', dimension);
          allow = false;
          lcd.clear();
        }
      }
      if (linea == 3)
      {
        lcd.setCursor(0, 0);
        lcd.print("3- PID");
        lcd.setCursor(0, 1);
        lcd.print("4- MOTOR");
        lcd.setCursor(15, 1);
        lcd.print("<");
        if (TECLA == '#')
        {
          identificador = 4;
          lcd.clear();
        }
      }
    }
    if (identificador != 0)
    {
      if (identificador == 1)
      {
        lcd.setCursor(0, 0);
        lcd.print("Temperatura:");
        get_valor();
        if (TECLA == 'D')
        {
          identificador = 0;
          lcd.clear();
        }
      }
      else if (identificador == 2)
      {
        lcd.setCursor(0, 0);
        lcd.print("New speed:");
        get_valor();
        if (TECLA == 'D')
        {
          identificador = 0;
          lcd.clear();
        }
      }
      else if (identificador == 3)
      {
        if (TECLA == 'A')
        {
          if (linea_2 <= 1)
          {
            linea_2 = linea_2 + 1;
            lcd.clear();
          }
        }
        else if (TECLA == 'B')
        {
          if (linea_2 >= 1)
          {
            linea_2 = linea_2 - 1;
            lcd.clear();
          }
        }
        if (identificador_2 == 0)
        {
          switch (linea_2)
          {
          case 0:
            lcd.setCursor(0, 0);
            lcd.print("1- New kp");
            lcd.setCursor(15, 0);
            lcd.print("<");
            lcd.setCursor(0, 1);
            lcd.print("2- New ki");
            if (TECLA == '#' && allow != false)
            {
              identificador_2 = 1;
              memset(valor_char, ' ', dimension);
              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print("VALUE KP:");
              get_valor_pid();
            }
            allow = true;
            break;
          case 1:
            lcd.setCursor(0, 0);
            lcd.print("1- New kp");
            lcd.setCursor(15, 1);
            lcd.print("<");
            lcd.setCursor(0, 1);
            lcd.print("2- New ki");
            if (TECLA == '#')
            {
              identificador_2 = 2;
              memset(valor_char, ' ', dimension);
              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print("VALUE KI:");
              get_valor_pid();
            }
            break;
          case 2:
            lcd.setCursor(0, 0);
            lcd.print("3- New kd");
            lcd.setCursor(15, 0);
            lcd.print("<");
            if (TECLA == '#')
            {
              identificador_2 = 3;
              memset(valor_char, ' ', dimension);
              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print("VALUE KD:");
              get_valor_pid();
            }
            break;
          }
        }
        if (TECLA == 'D')
        {
          identificador = 0;
          linea = 2;
          lcd.clear();
        }
      }
    }
    else if (identificador == 4)
    {
      lcd.setCursor(0, 0);
      lcd.print("MOTORES");
      if (TECLA == 'D')
      {
        memset(valor_char, ' ', dimension);
        identificador = 0;
        lcd.clear();
      }
    }
    if (TECLA == 'D')
    {
      lcd.clear();
      break;
    }
  }
}

void get_valor()
{
  i = 0;
  while (1)
  {
    TECLA = teclado.getKey();
    if (isdigit(TECLA) && i < dimension || TECLA == '.')
    {
      valor_char[i] = TECLA;
      lcd.setCursor(i, 1);
      lcd.print(valor_char[i]);
      i = i + 1;
    }
    if (TECLA == '#')
    {
      if (identificador == 1)
      {
        last_set_temperature = set_temperature;
        set_temperature = atof(valor_char);
        lcd.clear();
        identificador = 0;
        break;
      }
      if (identificador == 2)
      {
        last_set_velocidad_fan = Velocidad_fan;
        Velocidad_fan = atof(valor_char);
        lcd.clear();
        identificador = 0;
        break;
      }
    }
    if (TECLA == 'D')
    {
      identificador = 0;
      lcd.clear();
      TECLA = ' ';
      break;
    }
  }
}
void get_valor_pid()
{
  i = 0;
  while (1)
  {
    TECLA = teclado.getKey();
    if (isdigit(TECLA) && i < 6 || TECLA == '.')
    {
      valor_char[i] = TECLA;
      lcd.setCursor(i, 1);
      lcd.print(valor_char[i]);
      i = i + 1;
    }
    if (TECLA == '#')
    {
      if (identificador_2 == 1)
      {
        last_kp = Kp;
        Kp = atof(valor_char);
      }
      else if (identificador_2 == 2)
      {
        last_ki = Ki;
        Ki = atof(valor_char);
      }
      else if (identificador_2 == 3)
      {
        last_kd = Kd;
        Kd = atof(valor_char);
      }
      lcd.clear();
      identificador_2 = 0;
      break;
    }
    if (TECLA == 'D')
    {
      identificador_2 = 0;
      lcd.clear();
      TECLA = ' ';
      break;
    }
  }
}
