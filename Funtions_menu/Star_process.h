void Star_Process()
{
  // Delay time to clean the screen and show the new values.
  Differential_Termistor = Inicial_Time_Termistor - Final_Time_Termistor;
  Inicial_Time_Termistor = millis();
  if (Differential_Termistor >= Delay_Time_Termistor)
  {
    Final_Time_Termistor = Inicial_Time_Termistor;
    Temperature = analogRead(Termistor_Pin);
    Temperature = Temperature * Constant;
  }

  if (Star_Process_Value == true)
  {
    // Calculate the error between the setpoint and the real value
    PID_error = set_temperature - Temperature + 6;
    // Calculate the P value
    P = 0.01 * Kp * PID_error;
    // Calculate the I value in a range on +-6
    I = 0.01 * I + (Ki * PID_error);
    // For derivative we need real time to calculate speed change rate
    timePrev = Time;
    Time = millis();
    elapsedTime = (Time - timePrev) / 1000;
    // Now we can calculate the D Value
    D = 0.01 * Kd * ((PID_error - previous_error) / elapsedTime);
    // Calculate the final PID value is the sum of P+I+D
    PID_Signal = P + I + D;
    // We define PWM range between 0 and 255
    if (PID_Signal < 0)
    {
      PID_Signal = 0;
    }
    if (PID_Signal > max_PWM)
    {
      PID_Signal = max_PWM;
    }
    // Now we can write the PWM signal to the mosfet on digital pin D5
    analogWrite(PWM_pin, PID_Signal);
    previous_error = PID_error; // Remember to store the previous error for next loop.
  }
  else
  {
    // Apagar todo
    PID_Signal = 0;
  }
}
