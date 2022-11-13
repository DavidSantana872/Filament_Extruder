/*
 * This is a program for an extructor filament created in ULSA university for
 * re-use plastic material to then use in a 3D printed.
 *
 * Autors: Ana Arce
 *         Daniel Centeno
 *         Issac Palacios
 *         David Santana
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

// Externs Funtions
#include <Edit_values.h>
#include <Information_process.h>
#include <Star_process.h>
#include <Start_off.h>

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
int PID_values_fixed = 0;


//**********************************************************************************************************************************
// Indicate process is start or stop
boolean Star_Process_Value = false;

//**********************************************************************************************************************************
// Funtion edit_values
byte identificador = 0;
byte identificador_2 = 0;
byte linea = 0;
byte linea_2 = 0;
bool allow = false;
int i = 0;
int line_var_two = 0;
char valor_char[dimension];
float Velocidad_fan = 0;
float last_set_velocidad_fan = 0;

void setup()
{
  // Inicializar el LCD
  lcd.init();
  // Encender la luz de fondo.
  lcd.backlight();
  Serial.begin(9600);
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
