
#include <Keypad.h>
#include <LiquidCrystal.h>
#include <EEPROM.h>
LiquidCrystal liquid_crystal_display(9, 8, 7, 6, 5, 4);
char password[6];
char initial_password[6], new_password[6];
int i = 0;
int right_passpin = 10;
int wrong_passpin = 12;
char key_pressed = 0;
const byte rows = 4;
const byte columns = 4;
int counter = 0;
int wrongc = 0;
/*char hexaKeys[rows][columns] = {
  { '7', '4', '1', '#' },
  { '8', '5', '2', '0' },
  { '9', '6', '3', '=' },
  { '%', 'x', '-', '+' }
}; */
char hexaKeys[rows][columns] = {
{'1','4','7','*'},
{'2','5','8','0'},
{'3','6','9','#'},
{'A','B','C','D'}
};
byte row_pins[rows] = { A0, A1, A2, A3 };
byte column_pins[columns] = { A4, A5, 3, 2 };
Keypad keypad_key = Keypad(makeKeymap(hexaKeys), row_pins, column_pins, rows, columns); 

void setup() {
  pinMode(right_passpin, OUTPUT);
  pinMode(wrong_passpin, OUTPUT);
  liquid_crystal_display.begin(16, 2);
  liquid_crystal_display.print("     Welcome");
  liquid_crystal_display.setCursor(0, 1);
  liquid_crystal_display.print("Electronic Lock ");
  delay(2000);
  liquid_crystal_display.clear();
  liquid_crystal_display.print("Enter Password");
  liquid_crystal_display.setCursor(0, 1);
  /////////////////////////////////
 // for(int i=0;i==0;i++)
 //   {initialpassword();}  
  
}
void loop() {
  key_pressed = keypad_key.getKey();
  if (key_pressed == '#') {
    change();  //1
  }
  if (key_pressed) {
    password[i++] = key_pressed;
    liquid_crystal_display.print('*');
  }

  if (wrongc < 3) {
    if (i == 6) {
      delay(200);
      for (int j = 0; j < 6; j++) {
        initial_password[j] = EEPROM.read(j);
      }


      if (!(strncmp(password, initial_password, 6))) {
        liquid_crystal_display.clear();
        liquid_crystal_display.print("Pass Accepted");
        digitalWrite(right_passpin, HIGH);
        delay(2000);
        digitalWrite(right_passpin, LOW);
        liquid_crystal_display.setCursor(0, 1);
        liquid_crystal_display.print("Pres # to change");
        liquid_crystal_display.print(key_pressed);
        delay(2000);
        liquid_crystal_display.clear();
        i = 0;
        wrongc = 0;

      }

      else {
        digitalWrite(right_passpin, LOW);
        liquid_crystal_display.clear();
        liquid_crystal_display.print("Wrong Password");
        liquid_crystal_display.setCursor(0, 1);
        liquid_crystal_display.print("Pres # to Change");
        for(int l=0;l<3;l++)
          {
              digitalWrite(wrong_passpin, HIGH);
              digitalWrite(right_passpin, LOW);
              delay(500);
              digitalWrite(wrong_passpin, LOW);
              digitalWrite(right_passpin, LOW);
              delay(500);                                                  
          }        

        liquid_crystal_display.clear();
        liquid_crystal_display.print("Enter Password");
        liquid_crystal_display.setCursor(0, 1);
        i = 0;
        digitalWrite(right_passpin, LOW);
        digitalWrite(wrong_passpin, LOW);        
        wrongc++;
      }
    }

  }


  else {
    locked();
    wrongc = 0;
  }
}
int k = 0;
void change() {
  int j = 0;
  liquid_crystal_display.clear();
  liquid_crystal_display.print("Current Password");
  liquid_crystal_display.setCursor(0, 1);
  while (j < 6) {
    char key = keypad_key.getKey();
    if (key) {
      new_password[j++] = key;
      liquid_crystal_display.print(key);
    }
    key = 0;
  }
  delay(200);

  if ((strncmp(new_password, initial_password, 6))) {
    liquid_crystal_display.clear();
    digitalWrite(wrong_passpin, HIGH);
    liquid_crystal_display.setCursor(0, 0);            
    liquid_crystal_display.print("Wrong Password");
    liquid_crystal_display.setCursor(0, 1);
    liquid_crystal_display.print("Try Again");
    delay(1000);
    digitalWrite(wrong_passpin, LOW);
    j = 0;
    if(k < 3) {
      k++;
       
      change();
      
         
    }
    if(k!=0){
         k=0;     
         }

  }
   else

  {
  digitalWrite(right_passpin, HIGH);    

    delay(2000) ;
    digitalWrite(right_passpin, LOW);
    j = 0;
    liquid_crystal_display.clear();
    liquid_crystal_display.print("New Password:");
    liquid_crystal_display.setCursor(0, 1);
    while (j < 6) {
      char key = keypad_key.getKey();
      if (key) {
        initial_password[j] = key;
        liquid_crystal_display.print(key);
        EEPROM.write(j, key);
        j++;
      }
    }
    delay(1000);    
    liquid_crystal_display.clear();    
    liquid_crystal_display.print("Pass Changed");
    delay(1000);
  }
  liquid_crystal_display.clear();
  liquid_crystal_display.print("Enter Password");
  liquid_crystal_display.setCursor(0, 1);
  key_pressed = 0;
}
/////////////////////////////////////////////
// void initialpassword()
// {
// for(int j=0 ;j<6 ;j++)
//  EEPROM.write(j, j+49);
     
// for(int j=0 ;j<6 ;j++)
//   initial_password[j]=EEPROM.read(j);
// }
/////////////////////////////////////////////

void locked() {
  liquid_crystal_display.clear();
  liquid_crystal_display.setCursor(0, 0);

  for (int i = 0; i < 5; i++) {
    digitalWrite(right_passpin, HIGH);
    digitalWrite(wrong_passpin, HIGH);

    liquid_crystal_display.println("  Safe  Locked  ");
    liquid_crystal_display.setCursor(6, 1);
    liquid_crystal_display.print(" WAIT           ");
    delay(1000);

    digitalWrite(wrong_passpin, LOW);
    digitalWrite(right_passpin, LOW);
    liquid_crystal_display.clear();
    delay(1000);
  }
    
  liquid_crystal_display.clear();
  digitalWrite(wrong_passpin, LOW);

  digitalWrite(right_passpin, LOW);
    
  liquid_crystal_display.println("  Safe  Locked  ");
  liquid_crystal_display.setCursor(6, 1);
  delay(3000);      
setup();
}