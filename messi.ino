
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 5
#define RST_PIN 0
MFRC522 mfrc522(SS_PIN, RST_PIN);  

const uint8_t ROWS = 4;
const uint8_t COLS = 4;
char keys[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' },
};

uint8_t rowPins[ROWS] = { 13, 12, 14, 27 };
uint8_t colPins[COLS] = { 26, 25, 33, 35 };

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
LiquidCrystal_I2C LCD = LiquidCrystal_I2C(0x27, 16, 2);
 
char pass[7]="654322";
char ingresaPass[7];
int indice=0;
int pinbuzzer = 15;
int pinrelay = 32;
void setup() 
{
 pinMode(pinrelay, OUTPUT); 
pinMode(pinbuzzer, OUTPUT);
digitalWrite (pinbuzzer , LOW);
  Serial.begin(9600);   
  SPI.begin();      
  mfrc522.PCD_Init();  
  Serial.println("apoye la tarjeta...");
  Serial.println();
}
void loop() 
 {
  {
  char key = keypad.getKey();
  if (key) {
    
    ingresaPass[indice]=key;
   
    indice++;
    
    Serial.println(key);
    LCD. print(key);
  
  }
   if(indice==6){
    
    if(strcmp(pass,ingresaPass)==0){
      
      Serial.println("Acceso permitido");
      LCD.clear();
      LCD.setCursor(0, 0);
      LCD.println("Acceso permitido");
      digitalWrite (pinrelay , HIGH);
      delay(3000);
       LCD.clear();
       return ; 
    }
    
    else{
      
       LCD.clear();
        digitalWrite(pinbuzzer, HIGH );
      LCD.setCursor(0, 0);
      Serial.println("Acceso denegado");
       LCD.println("Acceso denegado");
    
      delay(3000);
      LCD.clear();
      return;
    }
    
    indice=0;
    delay(2500);
    LCD.clear();
  }
  
   
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  
  Serial.print("UID :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     //Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     //Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Mensaje : ");
  content.toUpperCase();
  if (content.substring(1) == "E3 8D 59 FA") 
  { 
    LCD.init();
  LCD.backlight();
    LCD.print("Acceso autorizado");
    delay(1100);
    Serial.println("Acceso aurtorizado");
    Serial.println();
    LCD.clear();
    delay(1000);
  }
     else   {
    digitalWrite(pinbuzzer , HIGH);
     LCD.print("Acceso denegado");
    Serial.println(" Acceso denegado");
    delay(3000);
    return;
  }
  
  Serial.begin(115200);
  LCD.init();
  LCD.backlight();
  LCD.print("bienvenido PEPE");
  LCD.setCursor(0, 1);
  LCD.print("DNI: 22567843");
  delay(2500);
     LCD.clear();
      LCD.setCursor(0, 0);
  LCD.print("ingrese la");
   LCD.setCursor(0, 1);
  LCD.print("contrasena:");
  delay(2500);
     LCD.clear();

 
 
  }
  return ;
}
 
