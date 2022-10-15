#include<LiquidCrystal.h>
#include<Keypad.h>
int desplazamiento_abajo = 0;
int desplazamiento_arriba = 0;
int linea = 1;
bool presionado = false;
const byte ROW_NUM = 4; //four rows
const byte COLUMN_NUM = 4; //four columns
char botones[ROW_NUM][COLUMN_NUM] = {
   {'1','2','3','A'},
   {'4','5','6', 'B'},
   {'7','8','9', 'C'},
   {'#','0','*', 'D'}
};
// Letra A desplazamiento hacia arriba 
// Letra B desplazamiento hacia abajo
// Letra D retroceder al menu principal
LiquidCrystal lcd(8,9,10,11,12,13);
void setup(){
  Serial.begin(9600);
  lcd.begin(16,2);
  cabecera_menu_1();
}
void loop(){
  desplazamiento_abajo = digitalRead(2);
  desplazamiento_arriba = digitalRead(3);
  funcion_desplazamiento_abajo();
}
  
void funcion_desplazamiento_abajo(){
     if (desplazamiento_abajo == 1 && presionado != true ){
      if(linea <= 2){
        cabecera_menu_1();
        if(linea == 1){
          lcd.setCursor(15, 0);
          lcd.print("<");
        }
        else{
          lcd.setCursor(15, 0);
          lcd.print(" ");
          lcd.setCursor(15, 1);
          lcd.print("<");
          }
        linea = linea + 1;
        }
        else{
          lcd.clear();
          cabecera_menu_2();
          if(linea == 3){
            lcd.setCursor(15, 0);
            lcd.print("<");
          }
          else{
            lcd.setCursor(15, 0);
            lcd.print(" ");
            lcd.setCursor(15, 1);
            lcd.print("<");
            }
          if(linea < 4)
            linea = linea + 1;
        }
       
      presionado = true;
       
    }
    if(desplazamiento_abajo == 0){
         
        presionado = false;
      }
   
  }


  
void cabecera_menu_1(){
    lcd.setCursor(0,0);
    lcd.print("1-INFO");
    lcd.setCursor(0,1);
    lcd.print("2-STAR");
  }
void cabecera_menu_2(){
    lcd.setCursor(0,0);
    lcd.print("4-EDIT");
    lcd.setCursor(0,1);
    lcd.print("5-REST");
  }
  
// Menu 
// 1 - INFORMACION
// 2 - INICIAR 
// 3 - EDITAR
// 4 - RESTABLECER
