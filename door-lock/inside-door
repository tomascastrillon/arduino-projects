#include <EEPROM.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
// TECLADO MATRICIAL
const byte filas = 4;
const byte columnas = 4;

char keys[filas][columnas] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};

const byte rowPins[filas] = { 2, 3, 4, 5 };
const byte columnPins[columnas] = { 6, 7, 8, 9 };
Keypad keypad = Keypad(makeKeymap(keys), rowPins, columnPins, filas, columnas);
char pass = "";                                          // variable pass es cadena
char newpass = "";                                      
char password = "3398#";                                 //contraseña inicial
int i;
// LCD
LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup() {
  Serial.begin(9600);                                      //abrir puerto serial
  lcd.init ();
  lcd.backlight ();
}


void loop() {
  // CAMBIO CONTRASEÑA
  char key = keypad.getKey();
  if (key) {
    newpass +=  key;                                          //sumador de caracteres, almacena en codigo
    if (key == '#') {                                        // tecla presionada igual a numeral
      password = newpass;                                   // lo almacena en password
      // EEPROM
      char code[6]= {password};
      for (i=0; i<6;i++)
      {
        EEPROM.write(i,code[i]);
      }
      Serial.print ("listo.");                               // imprime listo en puerto serial
      lcd.setCursor (0,0);
      lcd.print ("NUEVA CLAVE: ");
      lcd.setCursor (14,0);
      lcd.print (newpass);
      lcd.setCursor (0,1);
      lcd.print ("  Clave cambiada");
      delay (2500);
      lcd.setCursor (0,0);
      lcd.print ("                    ");
      lcd.setCursor (0,1);
      lcd.print ("                    ");
      newpass = "";                                           // vacia la variable codigo
    }
  }
  // VERIFICACION CLAVE INGRESADA
  while (Serial.available() > 0) {
    char caracter = Serial.read();                           // lee el puerto serial
    pass += caracter;
    if (caracter == '#') {                                  //cuando el caracter es #
       
      if (pass == code) {                                       // compara pass con password
        Serial.print("correcto.");                          // si pass es correcto imprime
      }
      else  {
        Serial.print("error.");                             // si la contraseña es incorrecta
      }
      pass = "";                                           //vaciamos variable pass
    }
  }
}
