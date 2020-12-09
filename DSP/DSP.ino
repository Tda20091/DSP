#include <stdio.h>
#include <stdlib.h>
#include <LiquidCrystal.h>
#include <IRremote.h>

//IR Stuff
int RECV_PIN = 11;

IRrecv irrecv(RECV_PIN);
decode_results results;

//LCD
LiquidCrystal lcd(0,1,3,4,5,6);

//INPUT
const int button = A0;            // GPIO 8 for the button
const int button1= A1;
const int button2= A2;

//FLAG
int ledflag1=1;                   // LED status flag
int ledflag2=1;
int ledflag3=1;

//Output PIN
int buzz = 2;
int relPin = 13;
int relPin1= 12;

void setup() {
  pinMode(button,INPUT);         // define button as an input 
  pinMode(button1,INPUT);
  pinMode(button2,INPUT);

  pinMode(buzz, OUTPUT);
  pinMode(relPin, OUTPUT);
  pinMode(relPin1,OUTPUT);
  
  lcd.begin(16,2);
  
//  Serial.begin(9600);
//  Serial.println("IR Enable in");
  irrecv.enableIRIn(); // Start the receiver
//  Serial.println("IR Enable in");
}

void loop() {
  
//~~~~~~~~~~~~~IR REMOTE STUFF~~~~~~~~~~~~
  
  if (irrecv.decode(&results))
  {
    unsigned int value = results.value;
//    Serial.println(value);
      switch(value)
      {
        case 2295:
        
   if(ledflag1==1&&ledflag2==1&&ledflag3==1)
   {  
     digitalWrite(relPin1, HIGH);

     delay(1000);
        
      ledflag1=0;
     
     digitalWrite(relPin1, LOW);
     lcd.setCursor(0,0);
     lcd.print("Water Level:100%");     
   }
    else if(ledflag1==0&&ledflag2==1&&ledflag3==1)
   {   
     digitalWrite(relPin1, HIGH);

     delay(1000);        
        
     ledflag2=0;
      
     digitalWrite(relPin1, LOW);      
     lcd.setCursor(0,0);  
     lcd.print("Water Level:75%");
   }
     else if(ledflag1==0&&ledflag2==0&&ledflag3==1)  
   {      
     digitalWrite(relPin1, HIGH);

     delay(1000);
        
     ledflag3=0;
       
     digitalWrite(relPin1, LOW);       
     lcd.setCursor(0,0);
     lcd.print("Water Level:50%");       
   } 
   
        break;
        
        case 12495:
        
   if(ledflag1==1&&ledflag2==1&&ledflag3==1)
   {

  lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Water Level:100%");
     
    digitalWrite(relPin, LOW);
    digitalWrite(buzz,LOW);    
    delay(1000);
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~     
         
   }else if(ledflag1==0&&ledflag2==1&&ledflag3==1){
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Water Level:75%");
     
    digitalWrite(relPin, HIGH);
    digitalWrite(buzz,LOW);    
    delay(1000);
     
    ledflag1=1;
     
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Water Level:100%");    
    digitalWrite(relPin, LOW);
    digitalWrite(buzz,LOW);    
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~     
   }else if(ledflag1==0&&ledflag2==0&&ledflag3==1){
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Water Level:50%");
     
    digitalWrite(relPin, HIGH);
    digitalWrite(buzz,LOW);    
    delay(1000);  
    
    ledflag2=1;
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Water Level:75%");
     
    digitalWrite(relPin, HIGH);
    digitalWrite(buzz,LOW);    
    delay(1000);
     
    ledflag1=1;
     
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Water Level:100%");    
    digitalWrite(relPin, LOW);
    digitalWrite(buzz,LOW);
       
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~           
   }else if(ledflag1==0&&ledflag2==0&&ledflag3==0){ 

//    lcd.clear();
//    lcd.setCursor(0,0);
//    lcd.print("Water Level:25%");
     
    digitalWrite(relPin, HIGH);
    delay(1000);
   
    ledflag3=1;
     
    lcd.clear();     
    lcd.setCursor(0,0);
    lcd.print("Water Level:50%");
     
    digitalWrite(relPin, HIGH);
    digitalWrite(buzz,LOW);     
    delay(1000);  
    
    ledflag2=1;
     
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Water Level:75%");
     
    digitalWrite(relPin, HIGH);
    digitalWrite(buzz,LOW);     
    delay(1000);
     
    ledflag1=1;
     
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Water Level:100%");    
    digitalWrite(relPin, LOW);
    digitalWrite(buzz,LOW); 
   }  

        break;
      }
    irrecv.resume();
  }  
  
//~~~~~~~~~~~SENSOR~~~~~~~~~~~
  if (digitalRead(button)==HIGH){ 
    if (ledflag1==1) {             
      ledflag1=0;                  
      }                            
    else {                        
      ledflag1=1;                  
    }
  delay(1500);                    // wait a sec for the 
  }                               // hardware to stabilize

  if (digitalRead(button1)==HIGH){ // if button is pressed
    if (ledflag2==1) {             // and the status flag is LOW
      ledflag2=0;                  // make status flag HIGH
      }                           // 
    else {                        // otherwise...
      ledflag2=1;                  // make status flag LOW
    }
  delay(1500);                    // wait a sec for the 
  }                               // hardware to stabilize

  if (digitalRead(button2)==HIGH){ // if button is pressed
    if (ledflag3==1) {             // and the status flag is LOW
      ledflag3=0;                  // make status flag HIGH
      }                           // 
    else {                        // otherwise...
      ledflag3=1;                  // make status flag LOW
    }
  delay(1500);                    // wait a sec for the 
  }                               // hardware to stabilize


   if(ledflag1==1&&ledflag2==1&&ledflag3==1)
   {
    digitalWrite(buzz, LOW);
    digitalWrite(relPin,LOW);
    lcd.setCursor(0,0);
    lcd.print("Water Level:100%");

   }else if(ledflag1==0&&ledflag2==1&&ledflag3==1){
    digitalWrite(buzz, LOW);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Water Level:75%");
   }else if(ledflag1==0&&ledflag2==0&&ledflag3==1){
    digitalWrite(buzz, LOW);     
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Water Level:50%");
      
   }else if(ledflag1==0&&ledflag2==0&&ledflag3==0){
    digitalWrite(buzz, HIGH);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Water Level:25%");
    lcd.setCursor(0,2);
    lcd.print("Please Refill"); 
   }  
}      
