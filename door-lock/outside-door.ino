#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
int led_rojo = 10;
int led_verde = 11;


// TECLADO MATRICIAL
const byte filas = 4;
const byte columnas = 4;

char hexaKeys[filas][columnas] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[filas] = {2, 3, 4, 5};
byte colPins[columnas] = {6, 7, 8, 9};

Keypad keypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, filas, columnas);
String pass = "";
String cadena = "";
// LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin (9600);
  pinMode (led_verde, OUTPUT);
  pinMode (led_rojo, OUTPUT);
  lcd.init ();
  lcd.backlight ();
}

void loop() {
  limpiar ();
  // ENVIAR CLAVE
  char  key = keypad.getKey();                  // lee tecla presionada
  if (key) {                                    // pregunta si hay tecla presionada
    pass += key;                                // almacena en array tecla presiona
    if (key == '#') {                           // cuando el inice llega a 4
      Serial.print (pass);
      lcd.setCursor (7, 0);
      lcd.print (pass);
      lcd.print ("    ");
      pass = "";
      limpiar ();
    }
  }
  // LECTOR RESPUESTA
  while (Serial.available() > 0) {
    char caracter = Serial.read();
    cadena += caracter;
    if (caracter == '.') {
      if (cadena == "correcto.") {             // si la respuesta es correcta
        digitalWrite (led_verde, HIGH);        // enciende el led verde
        lcd.setCursor (0, 1);
        lcd.print    ("Clave correcta  ");     // nos dice q la clave es correcta
        delay (2000);
        digitalWrite (led_verde, LOW);
        lcd.setCursor (0, 1);
        lcd.print    ("                ");    // limpiamos el lcd
        lcd.setCursor (7, 0);
        lcd.print ("         ");              // limpia clave ingresada lcd
        limpiar ();
      }
      if (cadena == "error.") {
        digitalWrite (led_rojo, HIGH);
        lcd.setCursor (0, 1);
        lcd.print    ("Clave incorrecta");
        delay (2000);
        digitalWrite (led_rojo, LOW);
        lcd.setCursor (0, 1);
        lcd.print    ("                ");    // limpiamos el lcd
        lcd.setCursor (7, 0);
        lcd.print ("         ");              // limpia clave ingresada lcd
        limpiar();
      }
      if (cadena == "listo.") {
        digitalWrite (led_verde, HIGH);
        digitalWrite (led_rojo, HIGH);
        delay (2000);
        digitalWrite (led_verde, LOW);
        digitalWrite (led_rojo, LOW);
      }
      cadena = "";
    }
  }
}


void limpiar() {
  lcd.setCursor(0, 0);
  lcd.print("CLAVE :");
  lcd.setCursor(9, 0);
}
