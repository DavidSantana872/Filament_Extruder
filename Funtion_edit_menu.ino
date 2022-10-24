float speed_fan;
int line_var_two = 0;
int nivel_menu = 0;
int nivel_menu_2 = 0;
char Temperature_char[5];
char Velocidad_char[5];
int Velocidad_fan = 0;
int last_set_velocidad_fan = 0;
int i = 0;



void Edit_Values(){

    line_var_two = 0;

    nivel_menu = 0;

    while(1){


// Valores desplazamiento 
//*******************************************************************

        TECLA = teclado.getKey();

        if(TECLA == 'A'){

            if(line_var_two >= 0 && line_var_two <= 2){

                line_var_two = line_var_two + 1; 

            } 
        }

        if(TECLA == 'B'){

            if(line_var_two >= 0 && line_var_two <= 2){

                line_var_two = line_var_two - 1;
            }   
        }

        if(line_var_two == 4){

            line_var_two = 3;

        }

        if(line_var_two == -1){

            line_var_two = 0;

        }

//******************************************************************

        // MAIN MENU OPTIONS EDIT

        if(nivel_menu == 0){

            switch(line_var_two){

                case 0:

                    lcd.setCursor(0,0);
                    lcd.print("1- TEMPERATURA");
                    lcd.setCursor(15,0);
                    lcd.print("<");
                    lcd.setCursor(0,1);
                    lcd.print("2- VELOCIDAD");
                    asignacion_submenu(1);
                    break;

                case 1:

                    lcd.setCursor(0,0);
                    lcd.print("1- TEMPERATURA");
                    lcd.setCursor(15,1);
                    lcd.print("<");
                    lcd.setCursor(0,1);
                    lcd.print("2- VELOCIDAD");
                    asignacion_submenu(2);
                    break;

                case 2:

                    lcd.setCursor(0,0);
                    lcd.print("3- PID");
                    lcd.setCursor(15,0);
                    lcd.print("<");
                    lcd.setCursor(0,1);
                    lcd.print("4- MOTORES");
                    asignacion_submenu(3);
                    break;

                case 3:

                    lcd.setCursor(0,0);
                    lcd.print("3- PID");
                    lcd.setCursor(15,1);
                    lcd.print("<");
                    lcd.setCursor(0,1);
                    lcd.print("4- MOTORES");
                    asignacion_submenu(4);
                    break;

            }

            if(TECLA == 'D'){
        
                break;
        
            }

        }
//****************************************************************

        // SUBMENU, SOLO ACCEDEMOS CUANDO SE PRECIONO ENTER EN EL MENU ANTERIOR

        else{

            switch(nivel_menu){

                // submenu temperatura

                case 1:

                    // salvamos la temperatura antes de cambiarla "ALMACENAR EN EEPROM"
                    last_set_temperature = Temperature;
                    i = 0;
                    lcd.setCursor(0,0);
                    lcd.print("Temperatura:");

                    while(1){            
                        //----------------------------------
                        // Star_Process(); 
                        //----------------------------------
                        // Arreglo para salvar en forma de caracter la temperatura nueva
                        TECLA = teclado.getKey();

                        if(isdigit(TECLA) && i < 5 || TECLA == '.'){

                            Temperature_char[i] = TECLA;

                            lcd.setCursor(i,1);

                            lcd.print(Temperature_char[i]);

                            i = i + 1;

                        }

                        if(TECLA == "D"){

                            // si cancela el cambio de temperatura --> regresamos a sus valores normales

                            Temperature = last_set_temperature;

                            last_set_temperature = 0:

                            // si decide salir no seguimos accediento a este submenu

                            nivel_menu = 0;
                
                            break;

                        }

                        if(TECLA == "#"){

                            Temperature = 12;

                        //  Convertir el arreglo en flotante
                        //  Temperature = atof(Temperature_char);

                            nivel_menu = 0;
                
                            break;

                        }

                    }

                    break;

                // submenu velocidad fa

                case 2:

                    i = 0;
                    lcd.setCursor(0,0);
                    lcd.print("VELOCIDAD FAN");
                    while(1){
                        //----------------------------------
                        // Star_Process(); 
                        //----------------------------------
                        TECLA = teclado.getKey();

                        if(isdigit(TECLA) && i < 5 || TECLA == '.'){

                                Velocidad_char[i] = TECLA;
                                
                                lcd.setCursor(i,1);

                                lcd.print(Velocidad_char[i]);

                                i = i + 1;

                            }

                        if(TECLA == "D"){

                            // si cancela el cambio de temperatura --> regresamos a sus valores normales

                            Velocidad_fan = last_set_velocidad_fan;

                            last_set_velocidad_fan = 0:

                            // si decide salir no seguimos accediento a este submenu

                            nivel_menu = 0;

                            break;

                        }

                        if(TECLA == "#"){

                            Velocidad_fan = 100;

                        //  Convertir el arreglo en flotante
                        //  Velocidad_fan = atof(Velocidad_char);

                            nivel_menu = 0;

                            break;

                        }

                    }

                    break;
                
                // submenu PID

                case 3:
                    line_var_two = 0;
                    nivel_menu = 0;
                    // send to eeprom
                    last_kp = kp;
                    last_ki = ki;
                    last_kd = Kd;
                    while(1){

                        TECLA = teclado.getKey();

                        if(TECLA == 'A'){

                            if(line_var_two >= 0 && line_var_two <= 2){

                                line_var_two = line_var_two + 1;  

                            } 

                        }

                        if(TECLA == 'B'){

                            if(line_var_two >= 0 && line_var_two <= 2){

                                line_var_two = line_var_two - 1;

                            }   

                        }

                        if(line_var_two == 4){

                            line_var_two = 3;

                        }

                        if(line_var_two == -1){

                            line_var_two = 0;

                        }
                        
                        if(nivel_menu_2 == 0){

                            switch(line_var_two){

                                case 0:
                                    lcd.setCursor(0,0);
                                    lcd.print("1- KP");
                                    lcd.setCursor(15,0);
                                    lcd.print("<");
                                    lcd.setCursor(0,1);
                                    lcd.print("2- KI");
                                    asignacion_submenu_2(1);
                                    break;
                                case 1:
                                    lcd.setCursor(0,0);
                                    lcd.print("1- KP");
                                    lcd.setCursor(0,1);
                                    lcd.print("2- KI");
                                    lcd.setCursor(15,1);
                                    lcd.print("<");
                                    asignacion_submenu_2(2);
                                    break;
                                case 2:
                                    lcd.setCursor(0,0);
                                    lcd.print("3- KD");
                                    lcd.setCursor(15,0);
                                    lcd.print("<");
                                    lcd.setCursor(0,1);
                                    lcd.print("  ");
                                    asignacion_submenu_2(3);
                                    break;

                            }
                            if(TECLA == 'D'){

                                line_var_two = 0;

                                nivel_menu_2 = 0;

                                nivel_menu = 0;

                                break;

                            }
                        }

                        else{

                            switch(line_var_two){

                                case 1:
                                    lcd.setCursor(0,0);
                                    lcd.print("- VALOR KP:");
                                    cambio_de_valor();
                                    break;
                                case 2:
                                    lcd.setCursor(0,0);
                                    lcd.print("- VALOR KI:"); 
                                    cambio_de_valor();                                  
                                    break;
                                case 3:
                                    lcd.setCursor(0,0);
                                    lcd.print("- VALOR KD:");
                                    cambio_de_valor();
                                    break;
                            
                            }
                            if(TECLA == 'D'){

                                line_var_two = 0;

                            }

                        }

                    break;

                // submenu velocidad motores
                case 4:

                    break;
                    }
        }
}


void cambio_de_valor(){
    i = 0;
    while(1){

        //----------------------------------
        // Star_Process(); 
        //----------------------------------

        TECLA = teclado.getKey();
        if(isdigit(TECLA) && i < 5 || TECLA == '.'){
            Velocidad_char[i] = TECLA;
            i = i + 1;
        }
        if(TECLA == "D"){
            // cancelado
            // dependendiendo la variable editada cacelamos
            if(line_var_two == 1){
                kp = last_kp;
                last_kp = 0;
            }
            else if(line_var_two == 2){
                ki = last_ki;
                last_ki = 0;
            }
            else if(line_var_two == 3){
                last_kd = 0;
                kd = last_kd;
            }
            
            break;
        }
        if(TECLA == "#"){
            //aceptado
            /*
            if(line_var_two == 1){}
                kp = atof(Velocidad_char);
            }
            else if(line_var_two == 2){
                ki = atof(Velocidad_char);
            }
            else if(line_var_two == 3){
                kd = atof(Velocidad_char);
            }
            */
            break;
        }
    }

}
// funcion para asignar el siguien opcion del menu

void asignacion_submenu(int x){
    TECLA = teclado.getKey();
    if(TECLA == '#'){
        nivel_menu = x;
    }
}


void asignacion_submenu_2(int x){
    TECLA = teclado.getKey();
    if(TECLA == '#'){
        nivel_menu_2 = x;
    }
}
/// a desplazamiento vertical negatico
// b desplazamiento vertical positivo