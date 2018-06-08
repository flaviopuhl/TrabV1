/*
   The circuit:
 * LCD RS pin to digital pin 12 (8)
 * LCD Enable pin to digital pin 11 (9)
 * LCD D4 pin to digital pin 5 (4)
 * LCD D5 pin to digital pin 4 (5)
 * LCD D6 pin to digital pin 3 (6)
 * LCD D7 pin to digital pin 2 (7)
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
*/

// include the library code:
#include <LiquidCrystal.h>
#include <Button.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

Button UP = Button(8,BUTTON_PULLUP_INTERNAL);      
Button DOWN = Button(9,BUTTON_PULLUP_INTERNAL);
Button ENTER = Button(10,BUTTON_PULLUP_INTERNAL);

const int LEDA = A0;      	 // LED 1
const int LEDB = A1;      	 // LED 2
const int LEDC = A2;      	 // LED 3
const int LEDD = A3;      	 // LED 4

int LEDAtp = 1000;			 // tempo de acionamento do led
int LEDBtp = 1000;
int LEDCtp = 1000;
int LEDDtp = 1000;

int statusLEDA = 0;				
int statusLEDB = 0;
int statusLEDC = 0;
int statusLEDD = 0;

int autom = 1;			//automático=1   manual =0

int tempo = 0;

unsigned long currentMillis;
unsigned long previousMillisLEDA = 0;
unsigned long previousMillisLEDB = 0;
unsigned long previousMillisLEDC = 0;
unsigned long previousMillisLEDD = 0;

int buttonStateUP = 0;         // variable for reading the pushbutton status
int buttonStateDOWN = 0;
int buttonStateENTER = 0;

int Index=0;
int Menu = 0;

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  pinMode(LEDA, OUTPUT);
  pinMode(LEDB, OUTPUT);
  pinMode(LEDC, OUTPUT);
  pinMode(LEDD, OUTPUT);
  
  // initialize serial:
  Serial.begin(9600);
  Serial.setTimeout(0);
  while (!Serial) {} ;
  
}

void loop() {
    
  if(UP.uniquePress()){
    buttonStateUP = HIGH;}
    else{
    buttonStateUP = LOW;}

  if(DOWN.uniquePress()){
    buttonStateDOWN = HIGH;}
    else{
    buttonStateDOWN = LOW;}

  if(ENTER.uniquePress()){
    buttonStateENTER = HIGH;}
    else{
    buttonStateENTER = LOW;}
  
  tempo = analogRead(A5);					//leitura da entrada analogica
  tempo = map(tempo, 0, 1023, 1000, 9999);

  currentMillis = millis();					//leitura clock arduino
  
  	//Incrementa/decrementa index
      if (buttonStateUP == HIGH) {		
        Index++;}			
      if (buttonStateDOWN == HIGH) {
        Index--;}			
     
  	// Mantem Indexador dentro do limite de opcoes do menu
  	switch (Menu) {
    case 0:
      if (Index<=1){Index=Index;}
  		else{Index=1;}
      if (Index<=-1){Index=0;}
      break;	
	case 1:			
      if (Index<=4){Index=Index;}
  		else{Index=4;}
      if (Index<=-1){Index=0;}
      break;
    case 2:			
      if (Index<=5){Index=Index;}
  		else{Index=5;}
      if (Index<=-1){Index=0;}
      break;  
    }
  
  
    //Muda de menu
  	  	//Entra no menu CONFIGURAR
  		if (buttonStateENTER == HIGH && Index == 0 && Menu == 0){
            lcd.clear();
        	Index=0;
        	Menu=1;
        	Serial.println("Menu CONFIGURAR selecionado");}
        //Entra no menu AC.MANUAL
  	  	if (buttonStateENTER == HIGH && Index == 1 && Menu == 0){
            lcd.clear();
        	Index=0;
        	autom=0;	//Desabilita modo automatico
        	Menu=2;
        	Serial.println("Menu AC.MANUAL selecionado");
        	Serial.println("Modo de controle automatico desativado");}
        //Dentro do menu CONFIGURAR, volta para menu inicial
      	if (buttonStateENTER == HIGH && Index == 4 && Menu == 1){
            lcd.clear();
        	Index=0;
        	Menu=0;
        	Serial.println("Menu principal");}
  		//Dentro do menu AC.MANUAL, volta para menu inicial
 	    if (buttonStateENTER == HIGH && Index == 5 && Menu == 2){
            lcd.clear();
        	Index=0;
        	Menu=0;
        	Serial.println("Menu principal");}
  
  	//Aciona modo automático
  	  if (buttonStateENTER == HIGH && Index == 4 && Menu == 2){
            autom=1;
      		Serial.println("Modo de controle automático ATIVADO");}
  
  	//Grava valor do tempo na variável
  		if (buttonStateENTER == HIGH && Index == 0 && Menu == 1){
            LEDAtp=tempo;
        	Serial.print("Setup novo periodo Led A:");
        	Serial.println(LEDAtp);}
  
  		if (buttonStateENTER == HIGH && Index == 1 && Menu == 1){
            LEDBtp=tempo;
        	Serial.print("Setup novo periodo Led B:");
        	Serial.println(LEDBtp);}
  		
  		if (buttonStateENTER == HIGH && Index == 2 && Menu == 1){
            LEDCtp=tempo;
            Serial.print("Setup novo periodo Led C:");
        	Serial.println(LEDCtp);}
  		
  		if (buttonStateENTER == HIGH && Index == 3 && Menu == 1){
            LEDDtp=tempo;
            Serial.print("Setup novo periodo Led D:");
        	Serial.println(LEDDtp);}
 
  
  	// Define status do led no modo manual
  		if (buttonStateENTER == HIGH && Index == 0 && Menu == 2){
          digitalWrite(LEDA, !digitalRead(LEDA));  // toggle state;
  		  Serial.print("Ac. Manual Status Led A:");
          Serial.println(digitalRead(LEDA));}
  
  		if (buttonStateENTER == HIGH && Index == 1 && Menu == 2){
          digitalWrite(LEDB, !digitalRead(LEDB));  // toggle state;
  		  Serial.print("Ac. Manual Status Led B:");
          Serial.println(digitalRead(LEDB));}
  
  		if (buttonStateENTER == HIGH && Index == 2 && Menu == 2){
          digitalWrite(LEDC, !digitalRead(LEDC));  // toggle state;
  		  Serial.print("Ac. Manual Status Led C:");
          Serial.println(digitalRead(LEDC));}
  
  		if (buttonStateENTER == HIGH && Index == 3 && Menu == 2){
          digitalWrite(LEDD, !digitalRead(LEDD));  // toggle state;
		  Serial.print("Ac. Manual Status Led D:");
          Serial.println(digitalRead(LEDD));}
  
  	// Indica o status do led fora do modo manual
  		if (digitalRead(LEDA)==HIGH){statusLEDA=1;} else {statusLEDA=0;}
       
        if (digitalRead(LEDB)==HIGH){statusLEDB=1;} else {statusLEDB=0;}
  
        if (digitalRead(LEDC)==HIGH){statusLEDC=1;} else {statusLEDC=0;}
  
        if (digitalRead(LEDD)==HIGH){statusLEDD=1;} else {statusLEDD=0;}

  
  	// Controle automático
  		 
  if(autom==1){
    
  	if (currentMillis - previousMillisLEDA >= LEDAtp) {
    // save the last time you blinked the LED
    previousMillisLEDA = currentMillis;
    digitalWrite(LEDA, !digitalRead(LEDA));  // toggle state;
    		Serial.print("Automatico Status Led A:");
          	Serial.println(digitalRead(LEDA));
    }
    
    if (currentMillis - previousMillisLEDB >= LEDBtp) {
    // save the last time you blinked the LED
    previousMillisLEDB = currentMillis;
    digitalWrite(LEDB, !digitalRead(LEDB));  // toggle state;
    		Serial.print("Automatico Status Led B:");
          	Serial.println(digitalRead(LEDB));
    }
    
    if (currentMillis - previousMillisLEDC >= LEDCtp) {
    // save the last time you blinked the LED
    previousMillisLEDC = currentMillis;
    digitalWrite(LEDC, !digitalRead(LEDC));  // toggle state;
    		Serial.print("Automatico Status Led C:");
          	Serial.println(digitalRead(LEDC));
    }
    
    if (currentMillis - previousMillisLEDD >= LEDDtp) {
    // save the last time you blinked the LED
    previousMillisLEDD = currentMillis;
    digitalWrite(LEDD, !digitalRead(LEDD));  // toggle state;
    		Serial.print("Automatico Status Led D:");
          	Serial.println(digitalRead(LEDD));
    }
    
  }
 		
  
//Atualiza o LCD          

  if (Menu==0){
    lcd.setCursor(0, 0);
    if(statusLEDA==1){lcd.print("LD");} else{lcd.print("DL");}
    
    lcd.setCursor(3, 0);
    if(statusLEDB==1){lcd.print("LD");} else{lcd.print("DL");}
    
    lcd.setCursor(6, 0);
    if(statusLEDC==1){lcd.print("LD");} else{lcd.print("DL");}
    
    lcd.setCursor(9, 0);
    if(statusLEDD==1){lcd.print("LD");} else{lcd.print("DL");}
    
    switch(Index){
     case 0:
      		lcd.setCursor(0, 1);
            lcd.print("Configurar");
     break;
     
     case 1:
      		lcd.setCursor(0, 1);
            lcd.print("Ac. Manual  ");
     break;
    } 
  }
  
  
  if (Menu==1){
    		
    switch(Index){
     case 0:
      		lcd.setCursor(0, 0);
            lcd.print("LED A Tp: ");
      		lcd.setCursor(10, 0);
            lcd.print(LEDAtp);
      		lcd.setCursor(0, 1);
            lcd.print(tempo);
     break;
     
     case 1:
      		lcd.setCursor(0, 0);
            lcd.print("LED B Tp: ");
      		lcd.setCursor(10, 0);
            lcd.print(LEDBtp);
      		lcd.setCursor(0, 1);
            lcd.print(tempo);
     break;
      
     case 2:
      		lcd.setCursor(0, 0);
            lcd.print("LED C Tp: ");
      		lcd.setCursor(10, 0);
            lcd.print(LEDCtp);
      		lcd.setCursor(0, 1);
            lcd.print(tempo);
     break;
      
     case 3:
      		lcd.setCursor(0, 0);
            lcd.print("LED D Tp: ");
      		lcd.setCursor(10, 0);
            lcd.print(LEDDtp);
      		lcd.setCursor(0, 1);
            lcd.print(tempo);
     break;
      
     case 4:
      		lcd.setCursor(0, 0);
            lcd.print("Voltar     ");
      		lcd.setCursor(10, 0);
            lcd.print("           ");
      		lcd.setCursor(0, 1);
            lcd.print("           ");
     break;
    } 
  }
  
 if (Menu==2){
    lcd.setCursor(0, 0);
    if(statusLEDA==1){lcd.print("LD");} else{lcd.print("DL");}
    
    lcd.setCursor(3, 0);
    if(statusLEDB==1){lcd.print("LD");} else{lcd.print("DL");}
    
    lcd.setCursor(6, 0);
    if(statusLEDC==1){lcd.print("LD");} else{lcd.print("DL");}
    
    lcd.setCursor(9, 0);
    if(statusLEDD==1){lcd.print("LD");} else{lcd.print("DL");}
    		
    switch(Index){
     case 0:
      		lcd.setCursor(0, 1);
            lcd.print("LED A: ");
      		lcd.setCursor(9, 1);
      		if(digitalRead(LEDA)==HIGH){lcd.print("ON         ");}
                           else{lcd.print("OFF         ");}               
     break;
     
     case 1:
      		lcd.setCursor(0, 1);
            lcd.print("LED B: ");
      		lcd.setCursor(9, 1);
      		if(digitalRead(LEDB)==HIGH){lcd.print("ON         ");}
                           else{lcd.print("OFF         ");}
     break;
      
     case 2:
      		lcd.setCursor(0, 1);
            lcd.print("LED C: ");
      		lcd.setCursor(9, 1);
      		if(digitalRead(LEDC)==HIGH){lcd.print("ON         ");}
                           else{lcd.print("OFF         ");}
     break;
      
     case 3:
      		lcd.setCursor(0, 1);
            lcd.print("LED D: ");
      		lcd.setCursor(9, 1);
      		if(digitalRead(LEDD)==HIGH){lcd.print("ON         ");}
                           else{lcd.print("OFF         ");}
     break;
      
     case 4:
      		lcd.setCursor(0, 1);
            lcd.print("Automatico      ");
     break;
	
     case 5:
      		lcd.setCursor(0, 1);
            lcd.print("Voltar          ");
     break;
 
    
    } 
  }
  		

}
