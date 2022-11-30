/*
 * This is a program for an extructor filament created in ULSA university for
 * re-use plastic material to then use in a 3D printed.
 *
 * Autors: Ana Arce
 *         Brandon Bravo
 *         Veronica Castillo
 *         Daniel Centeno
 *         David Santana
 *         Anielka Rosales
 *         Wilhem Rojas
 *
 * Version: 1.2.0
 *
 * Pin used:
 *
 * KeyPad Pines:
 *    for rows =  22, 23, 24, 25
 *    for column = 26, 27, 28, 29
 *
 * LCD 16x2 with I2C communication model pines:
 *    for SDA = 20
 *    for SCL = 21
 *
 *    This information of these pines are in "wire" library, more info: https://www.arduino.cc/en/Reference/Wire
 *
 *Big Steeper motor (Extructor motor)
 *
 *  for motor direction = 2
 *  for signal motor = 3
 *
 *Medium Steeper motor
 *
 *
 *
 *
 *Termistor
 *
 *  for termistor = A0
 *
 *PWM Output signal pin
 *
 *    for PWM_pin = 5
 *
 */

//#include <LiquidCrystal.h> //DESCARGAR LIBRERÍA:https://github.com/ELECTROALL/Codigos-arduino/blob/master/LiquidCrystal_I2C.zip
// LiquidCrystal lcd(22,24,26,28,30,32); // si no te sale con esta direccion  puedes usar (0x3f,16,2) || (0x27,16,2)  ||(0x20,16,2)
//#include <LiquidCrystal_I2C.h>
// LiquidCrystal_I2C lcd(0x3f,16,2);  //sometimes the adress is not 0x3f. Change to 0x27 if it dosn't work.

/*
#include "DFRobot_LCD.h"

const int colorR = 255;
const int colorG = 0;
const int colorB = 0;

DFRobot_LCD lcd(16,2);  //16 characters and 2 lines of show*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>


// Crear el objeto lcd  dirección  0x3F y 16 columnas x 2 filas
LiquidCrystal_I2C lcd(0x27, 16, 2); //
const int row_num = 4;
const int column_num = 4;
char keys[row_num][column_num] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'.', '0', '#', 'D'}};
byte pin_rows[row_num] = {22, 23, 24, 25};
byte pin_column[column_num] = {26, 27, 28, 29};
Keypad teclado = Keypad(makeKeymap(keys), pin_rows, pin_column, 4, 4);

//**********************************************************************************************************************************
// Variables used to control keypad and menu
const int dimension = 16;
char TECLA;
char VARIABLE[dimension];
byte INDICE = 0;
float Valor = 0;
int d_y = 1;
int Last_d_y = d_y;

//*********************************************************************************************************************************
// PID Values
const float Constant = 0.2086;
int Termistor_Pin = A0;
float set_temperature = 200;
float Temperature = 0;
float PID_error = 0;
float previous_error = 0;
float elapsedTime, Time, timePrev;
float PID_Signal = 0;
float last_set_temperature = 0;
int max_PWM = 255;
int PWM_pin = 5;

//***********************************************************************************************************************************
unsigned long Inicial_Time_Termistor = 0, Final_Time_Termistor = 0;
unsigned long Delay_Time_Termistor = 1000; // 1 Second delay
unsigned long Differential_Termistor = 0;

//************************************************************************************************************************************
// PID contants
float Kp = 90, P = 0;
float Ki = 30, I = 0;
float Kd = 80, D = 0;
float last_kp = 0;
float last_ki = 0;
float last_kd = 0;
unsigned long Inicial_Time_LCD = 0, Final_Time_Time = 0;
unsigned long Delay_Time_LCD = 500; 
unsigned long Differential_LCD = 0; 

//**********************************************************************************************************************************
// Indicate process is start or stop
boolean Star_Process_Value = false;

//**********************************************************************************************************************************
// Funtion edit_values
byte identificador = 0;
byte identificador_2 = 0;
byte linea = 0;
byte linea_2 = 0;
int i = 0;
char valor_char[dimension];
//**********************************************************************************************************************************

void setup()
{
  // Inicializar el LCD
  lcd.init();
  // Encender la luz de fondo.
  lcd.backlight();
  Serial.begin(9600);

  Wire.begin();
  
  // Print a message to the LCD.
  delay(1000);
  for (int i = 0; i <= 15; i++)
  {
    VARIABLE[i] = 0;
  }
}
void loop()
{
  main_Process();
  Star_Process();
}
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
         lcd.print("Temp:");
         lcd.print(set_temperature);
         lcd.setCursor(10, 0);
         lcd.print("/");
         lcd.print(Temperature);
         lcd.setCursor(8,1);
         lcd.print("   "); 
         if(Temperature >= (set_temperature-10)&& Star_Process_Value == true){ 
            lcd.setCursor(0, 1);        
            lcd.print("Motor: ON");
         }
         else {       
            lcd.setCursor(0, 1);   
            lcd.print("Motor: OFF");
        }


      }
      Star_Process();
   }
}
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
    if (TECLA == 'B')
    {
        if (d_y < 4)
        {
            d_y += 1;
        }
    }
    else if (TECLA == 'A')
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
void Star_Off()
{

  int Slave_Value = 0;
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
        
        int Slave_Value = 1;
        Serial.println(Slave_Value);
        Wire.beginTransmission(1);
        Wire.write(Slave_Value);
        Wire.endTransmission();
        Star_Process_Value = true;
        lcd.clear();
        break;
      }
      else if (TECLA == 'D')
      {
        lcd.clear();
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
        
        Slave_Value = 0;

        Wire.beginTransmission(1);
        Wire.write(Slave_Value);
        Wire.endTransmission();

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

void Edit_Values(){
  lcd.clear();
  while(1){
    Star_Process();
    TECLA = teclado.getKey();
    if (TECLA == 'B'){
      	lcd.clear();
        linea = linea + 1;
    }
    if (TECLA == 'A'){
      	lcd.clear();
        linea = linea - 1;
    }
    if (TECLA == 'D')
    {
      	lcd.clear();
        break;
    }
    if(linea == 0){
        linea = 1;
    }
    if (linea == 3)
    {
        linea = 2;
    }
    
    if(identificador == 0){
        switch (linea)
        {
            case 1:
                lcd.setCursor(0,0);
                lcd.print("1- Temperature ");
                lcd.setCursor(15,0);
                lcd.print("<");
                lcd.setCursor(0,1);
                lcd.print("2- PID ");
                if(TECLA == '#'){
                    identificador = 1;
                    lcd.clear();
                }
                else if(TECLA == '1'){
                  	identificador = 1;
                  	lcd.clear();
                }
          		else if(TECLA == '2'){
                  	identificador = 2;
                  	lcd.clear();
                }
                break;
            case 2:
                lcd.setCursor(0,0);
                lcd.print("1- Temperature ");
                lcd.setCursor(0,1);
                lcd.print("2- PID ");
                lcd.setCursor(15,1);
                lcd.print("<");
                if(TECLA == '#' || TECLA == '2'){
                    identificador = 2;
                    lcd.clear();
                }
          		else if(TECLA == '1'){
                  	identificador = 1;
                  	lcd.clear();
                }
          		else if(TECLA == '2'){
                  	identificador = 2;
                  	lcd.clear();
                }
                break;
        }
    }
    else if(identificador != 0){
        Star_Process();
        switch (identificador)
        {
            case 1:
                lcd.setCursor(0,0);
                lcd.print("New Temperature:");
                lcd.setCursor(0,1);
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
                        last_set_temperature = set_temperature;
                        set_temperature = atof(valor_char);
                        lcd.clear();
                        identificador = 0;
                      	memset(valor_char, ' ', dimension);
                      	i = 0;
                        break;
                    }
                  	if (TECLA == 'D')
                    {
                        
                        lcd.clear();
                        identificador = 0;
                      	memset(valor_char, ' ', dimension);
                        i = 0;
                        break;
                    }
                }
                break;
            case 2:
                if(TECLA == 'B'){
                    linea_2 = linea_2 + 1;
                }
                if(TECLA == 'A'){
                    linea_2 = linea_2 - 1;
                }
                if(linea_2 == 4){
                    linea_2 = 3;
                }
                if(linea_2 == 0){
                    linea_2 = 1;
                }
          		if(TECLA == 'D'){
                  lcd.clear();                           
                  identificador = 0;                                  
              	} 
                switch (linea_2)
                {
                    case 1:
                        lcd.setCursor(0,0);
                        lcd.print("1- KP");
                        lcd.setCursor(15,0);
                        lcd.print('<');
                        lcd.setCursor(0,1);
                        lcd.print("2- KI");
                        if(TECLA == '#'){
                            lcd.clear();
                            identificador_2 = 1;
                          	lcd.setCursor(0,0);
                          	lcd.print("New KP:");
                            get_valor_pid();
                        }
                        break; 
                    case 2:
                        lcd.setCursor(0,0);
                        lcd.print("1- KP");
                        lcd.setCursor(15,1);
                        lcd.print('<');
                        lcd.setCursor(0,1);
                        lcd.print("2- KI");     
                        if(TECLA == '#'){
                            lcd.clear();                           
                            identificador_2 = 2;
                          	lcd.setCursor(0,0);
                          	lcd.print("New KI:");
                            get_valor_pid();
                        }                                      
                        break;
                    case 3:
                        lcd.setCursor(0,0);
                        lcd.print("3- KD");
                        lcd.setCursor(15,0);
                        lcd.print('<'); 
                        if(TECLA == '#'){
                            lcd.clear();                           
                            identificador_2 = 3; 
                          	lcd.setCursor(0,0);
                          	lcd.print("New KD:");
                            get_valor_pid();
                        }                                          
                        break;
                }	
        }
    }
}
}
void get_valor_pid(){
        while(1){
            Star_Process()
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
                switch(identificador_2){
                    case 1:
                        last_kp = Kp;
                        Kp = atof(valor_char);
                        lcd.clear();                  		
                        break;
                    case 2:
                        last_ki = Ki;
                        Ki = atof(valor_char);                  		
                        lcd.clear();                  		
                        break;
                    case 3:
                        last_kd = Kd;
                        Kd = atof(valor_char);                  		
                        lcd.clear();                  		
                        break;
                }
              memset(valor_char, ' ', dimension);
              i = 0;
              identificador_2 = 0;
              break;
            } 
            if(TECLA == 'D'){
                identificador_2 = 0;
               	memset(valor_char, ' ', dimension);
                lcd.clear();
                i = 0;
                break;
            }      
        }    
    
}
