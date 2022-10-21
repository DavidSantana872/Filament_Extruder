#include<LiquidCrystal.h>
LiquidCrystal lcd(8,9,10,11,12,13);
int desplazamiento_abajo = 0;
int desplazamiento_arriba = 0;
int linea = 0;
int salir = 0;
bool presionado = false;
bool presionado_2 = false;
int id = 0;

int enter = 0;
void setup() {
  // pines de lectura 
  Serial.begin(9600);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  lcd.begin(16,2);
  cabecera_menu_1();
}
void loop(){
    desplazamiento_abajo = digitalRead(2);
    desplazamiento_arriba = digitalRead(3);
    enter = digitalRead(4);
    salir = digitalRead(5);
    if(salir == 1 && presionado == false){
        linea = 0;
        id = 0;
        lcd.clear();
        presionado = true;
      }
    if(enter == 1){
        presionado = false;
      }

    if(linea <= 3 && linea >= 0){
        if( (desplazamiento_abajo == 1 && presionado == false) ){
              linea = linea + 1;
              presionado = true;
          }
        
        if(desplazamiento_abajo == 0){
              presionado = false;
          }

          
        if(desplazamiento_arriba == 1 && presionado_2 == false){
              linea = linea - 1;
              presionado_2 = true;
          }
        if (desplazamiento_arriba == 0){
              presionado_2 = false;
          }
      }
      if(linea == 4){
          linea = 3;
        }
      else if(linea == -1){
          linea = 0;
        }

    if(id == 0){
        switch(linea){
      case 0:
          cabecera_menu_1();
          lcd.setCursor(15,1);
          lcd.print(" ");
          lcd.setCursor(15,0);
          lcd.print("<");
          asignacion_id(1);
          break;
      case 1:
          cabecera_menu_1();
          lcd.setCursor(15,0);
          lcd.print(" ");
          lcd.setCursor(15,1);
          lcd.print("<");
          asignacion_id(2);
          break;
      case 2:
          cabecera_menu_2();
          lcd.setCursor(15,0);
          lcd.print("<");
          lcd.setCursor(15,1);
          lcd.print(" ");
          asignacion_id(3);
          break;
      case 3:
          cabecera_menu_2();
          lcd.setCursor(15,0);
          lcd.print(" ");
          lcd.setCursor(15,1);
          lcd.print("<");
          asignacion_id(4);
          break;
      }
      
      }
      switch(id){
      case 1:
          informacion();
          break;
      case 2:
          iniciar();
          break;
      case 3:
          editar();
          break;
      case 4:
          reiniciar();
          break;
      
      }
  }
void asignacion_id(int x){
    if (enter == 1 && presionado_2 == false){
        lcd.clear();
        id = x;
        presionado_2 = true;
      }
     if(enter == 1){
        presionado_2 = false;
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
void informacion(){
    lcd.setCursor(0,0);
    lcd.print("TEMP:");
    lcd.setCursor(6,0);
    lcd.print("80");
    lcd.setCursor(0,1);
    lcd.print("REPM:");
    lcd.setCursor(6,1);
    lcd.print("95");
  }
void iniciar(){
    lcd.setCursor(0,0);
    lcd.print("INICIANDO");
    lcd.setCursor(15,0);
    lcd.print("!");
    
  }
void editar(){
    lcd.setCursor(0,0);
    lcd.print("PID:");
    lcd.setCursor(6,0);
    lcd.print("00");
    
 }
void reiniciar(){
    lcd.setCursor(0,0);
    lcd.print("restableciendo!");
  }
// Menu 
// 1 - INFORMACION
// 2 - INICIAR 
// 3 - EDITAR
// 4 - RESTABLECER
