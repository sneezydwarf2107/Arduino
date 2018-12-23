#include <SR04.h>
#include <Keypad.h>
#include <LiquidCrystal.h>
#include <EEPROM.h>

#define EchoSensor1 52
#define EchoSensor2 50
#define EchoSensor3 48
#define EchoSensor4 46
#define EchoSensor5 44
#define TriggerSensor1 53
#define TriggerSensor2 51
#define TriggerSensor3 49
#define TriggerSensor4 47
#define TriggerSensor5 45

SR04 sr04 = SR04(EchoSensor1,TriggerSensor1);


const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {33, 31, 29, 27}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {26, 28, 30, 32}; //connect to the column pinouts of the keypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

LiquidCrystal lcd(11, 12, 5, 4, 3, 2);

// Global Variables for the timesensetiev while loop (long max_wait is the time in mills, the while loop runs)
unsigned long time_since_last_reset = 0;
long max_wait = 20000;

void keypadtolcd(char Key){
  switch(Key){
    case '0':
      return;
    break;
    
    case '1':
      lcd.setCursor(9,1);
      lcd.print(1);
    
      delay(500);
      readsensor(Key);
    break;
    
    case '2':
      lcd.setCursor(9,1);
      lcd.print(2);
  
      delay(500);
      readsensor(Key);
    break;
    
    case '3':
      lcd.setCursor(9,1);
      lcd.print(3);
  
      delay(500);
      readsensor(Key);
    break;
    
    case '4':
      lcd.setCursor(9,1);
      lcd.print(4);
  
      delay(500);
      readsensor(Key);
    break;
    
    case '5':
      return;
    break;
    
    case '6':
      return;
    break;
    
    case '7':
      return;
    break;
    
    case '8':

    lcd.setCursor(9,1);
    lcd.print("8");

    delay(500);
    lcd.clear();
    read_eeprom();
    return;
    break;
    
    case '9':
    lcd.setCursor(9,1);
    lcd.print("9!");
    delay(500);
    lcd.clear();
    eeprom_up();
    return;
    break;
    
    case 'A':
      return;
    break;
    
    case 'B':
      return;
    break;
    
    case 'C':
      return;
    break;
    
    case 'D':
      lcd.setCursor(9,1);
      lcd.print("D");
  
      delay(500);
      readsensor(Key);
    break;
    
    case '*':
      return;
    break;
    
    case '#':
      return;
    break;
  }
}

void readsensor(char Key){
  long distance;
  switch(Key){
    case '0':
      
    break;

    case '1':
      lcd.clear();
      sr04 = SR04(EchoSensor1,TriggerSensor1);
      distance = 0;
      distance = sr04.Distance();
      //Serial.println(distance);
      //Serial.print("cm");
      distance = distance - 8;
      calcandprint1(distance, Key);
    break;

    case '2':
      lcd.clear();
      sr04 = SR04(EchoSensor2,TriggerSensor2);
      distance = 0;
      distance = sr04.Distance();
      //Serial.println(distance);
      //Serial.print("cm");
      distance = distance - 8;
      calcandprint2(distance,Key);
    break;
  
    case '3':
      lcd.clear();
      sr04 = SR04(EchoSensor3,TriggerSensor3);
      distance = 0;
      distance = sr04.Distance();
      //Serial.println(distance);
      //Serial.print("cm");
      distance = distance - 8;
      calcandprint2(distance, Key);
    break;
   
    case '4':
      lcd.clear();
      sr04 = SR04(EchoSensor4,TriggerSensor4);
      distance = 0;
      distance = sr04.Distance();
      //Serial.println(distance);
      //Serial.print("cm");
      distance = distance - 8;
      calcandprint2(distance, Key);
    break;
  
    case '5':
    break;
  
    case '6':
    break;
   
    case '7':
    break;
  
    case '8':
    break;
  
    case '9':
    break;
  
    case 'A':
    break;
  
    case 'B':
    break;
  
    case 'C':
    break;
  
    case 'D':
      lcd.clear();
      sr04 = SR04(EchoSensor5,TriggerSensor5);
      distance = 0;
      distance = sr04.Distance();
      //Serial.println(distance);
      //Serial.print("cm");
      calcandprint1(distance, Key);
    break;
  
    case '*':
    break;
  
    case '#':
    break;
  }
}

void calcandprint1(long distance, char Key){

  //Calculatin oil Amont left Tank 1 and 2

  double gesamt = 12500;
  double left = 0;
  double percent = 0;
  long left2 = 0;
  char secondKey = Key;
  
  left = ((((200 - distance)*300)*208)/1000);
  percent = (left/gesamt)*100;
  left2 = (long)left;
  
  lcd.clear();
  lcd.print("--> ");
  lcd.print(left2);
  lcd.print(" ");
  lcd.print("Liter");
  lcd.setCursor(0,1);
  lcd.print("--> ");
  lcd.print(percent);
  lcd.print(" ");
  lcd.print("%");

  //start timesensetiev while loop 
  time_since_last_reset = millis();
  while((millis() - time_since_last_reset) < max_wait && secondKey != 'A'){

    secondKey = customKeypad.getKey();
  
  }
  lcd.clear();
}

void calcandprint2(long distance, char Key){

  //Calculation oil Amount left Tanks 3-5

  double gesamt = 25000;
  double left = 0;
  double percent = 0;
  long left2 = 0;
  char secondKey = Key;
  
  left = ((((200 - distance)*600)*208)/1000);
  percent = (left/gesamt)*100;
  left2 = (long)left;
  
  lcd.clear();
  lcd.print("--> ");
  lcd.print(left2);
  lcd.print(" ");
  lcd.print("Liter");
  lcd.setCursor(0,1);
  lcd.print("--> ");
  lcd.print(percent);
  lcd.print(" ");
  lcd.print("%");

  //start timesensetiev while loop 
  time_since_last_reset = millis();
  while((millis() - time_since_last_reset) < max_wait && secondKey != 'A'){

    secondKey = customKeypad.getKey();
  
  }
  lcd.clear();
}

void eeprom_up(){
  lcd.clear();
  int tank_nummer = 0;
  lcd.setCursor(0,0);
  lcd.print("Aktuellen Tank");
  lcd.setCursor(0,1);
  lcd.print("eingeben:");

  bool running = true;
  while(running){
    char Key = customKeypad.getKey();
    
    if (Key){
  
      switch(Key){
        case 'A':
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Abbruch!");
          Key = '7';
          running = false;
          delay(2000);
          lcd.clear();
        break;
        
        case '1':
          lcd.setCursor(9,1);
          lcd.print(Key);
          tank_nummer = 1;
          EEPROM.put(0,tank_nummer);
          lcd.clear();
          lcd.print("Tank 1!");
          delay(2000);
          Key = '7';
          running = false;
        break;
        
        case '2':
          lcd.setCursor(9,1);
          lcd.print(Key);
          tank_nummer = 2;
          EEPROM.put(0,tank_nummer);
          lcd.clear();
          lcd.print("Tank 2!");
          delay(2000);
          Key = '7';
          running = false;
        break;
        
        case '3':
          lcd.setCursor(9,1);
          lcd.print(Key);
          tank_nummer = 3;
          EEPROM.put(0,tank_nummer);
          lcd.clear();
          lcd.print("Tank 3!");
          delay(2000);
          Key = '7';
          running = false;
        break;
        
        case '4':
          lcd.setCursor(9,1);
          lcd.print(Key);
          tank_nummer = 4;
          EEPROM.put(0,tank_nummer);
          lcd.clear();
          lcd.print("Tank 4!");
          delay(2000);
          Key = '7';
          running = false;
        break;

        default:
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Eingabe nicht");
          lcd.setCursor(0,1);
          lcd.print("zulaessig!");
          delay(2000);
          lcd.clear();
      }
    }
  }
}

void read_eeprom(){

  int tank_nummer = EEPROM.read(0);
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Entnahme aus");
  lcd.setCursor(0,1);
  lcd.print("Tank: ");
  lcd.print(tank_nummer);
  delay(7000);
  lcd.clear();
}

void setup() {

  //Deklaration pinMode Echo Pins to Input 
  pinMode(EchoSensor1,INPUT);
  pinMode(EchoSensor2,INPUT);
  pinMode(EchoSensor3,INPUT);
  pinMode(EchoSensor4,INPUT);
  pinMode(EchoSensor5,INPUT);

  //Deklaration pinMode Trigger Pins to Output
  pinMode(TriggerSensor1,OUTPUT);
  pinMode(TriggerSensor2,OUTPUT);
  pinMode(TriggerSensor3,OUTPUT);
  pinMode(TriggerSensor4,OUTPUT);
  pinMode(TriggerSensor5,OUTPUT);

  //Starting Serial for testing purposes
  //  Serial.begin(9600);

  //Setting up LCD with 16 colums and 2 rows
  lcd.begin(16, 2);
  read_eeprom();

}

void loop() {

  lcd.setCursor(0,0);
  lcd.print("Tanknummer");
  lcd.setCursor(0,1);
  lcd.print("eingeben:");
   
  char Key = customKeypad.getKey();
  
  if (Key){
    keypadtolcd(Key);
  } 
}
