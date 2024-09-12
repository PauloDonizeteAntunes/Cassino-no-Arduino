#include <LiquidCrystal.h>


const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
const int backLight = 10;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
 
struct {
  int limite;
  char *nome;
} teclas[] = {
  {   50, "Direita " },
  {  150, "Cima    " },
  {  320, "Baixo   " },
  {  500, "Esquerda" },
  {  750, "Select  " },
  { 1024, "        " }  
};

byte rato[8] = {
  B01100,
  B00100,
  B01110,
  B01110,
  B01110,
  B10101,
  B01110,
  B00100,
};

byte estrela[8] = {
  B00000,
  B00100,
  B00100,
  B11111,
  B01110,
  B11011,
  B00000,
  B00000
};

byte caixaDeSom[8] = {
  B11111,
  B10001,
  B10101,
  B10001,
  B11111,
  B11111,
  B11001,
  B11111
};

byte casa[8] = {
  B00001,
  B00010,
  B00100,
  B01110,
  B11111,
  B01110,
  B11111,
  B00000
};

byte dinheiro[8] = {
  B00000,
  B00100,
  B01110,
  B10100,
  B01110,
  B00101,
  B01110,
  B00100
};
   int valor = 0;
   int saldo = 0;
   
void apostar(){
    lcd.clear();
    lcd.print("Aposta Validada");
    delay(1000);
    lcd.clear();

    
  int y;
  for ( y = 1; y < 11 ; y++) {

   long int sorte[3] = {random(0,4), random(0,4), random(0,4)};

    lcd.clear();

    lcd.setCursor(0,0);
    lcd.print("Tentaiva : ");
    lcd.print(y);

    lcd.setCursor(0,1);
    lcd.write(byte(sorte[0]));
    lcd.print("  ");
    delay(1000);
    lcd.write(byte(sorte[1]));
    lcd.print("  ");
    delay(1000);
    lcd.write(byte(sorte[2]));
    delay(1000);

    if(sorte[0] == sorte[1] && sorte[0] == sorte[2]) {
      
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Voce ganhou :");
    
      saldo = valor * 2;
      lcd.setCursor(0,1);
      lcd.print(saldo);
      delay(5000);

      setup();
      y = 20;
      
    };
}   

  if(y == 11){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Voce perdeu :");
    
    lcd.setCursor(0,1);
    lcd.print(valor);

    saldo = saldo-valor;
    
    delay(5000);
    setup();
  }
  
  };

 
// Iniciação
void setup() {
  
  pinMode(backLight, OUTPUT);
  lcd.createChar(0, rato);
  lcd.createChar(1, estrela);
  lcd.createChar(2, casa);
  lcd.createChar(3, dinheiro);
  lcd.createChar(4, caixaDeSom);
  digitalWrite(backLight, HIGH);


  lcd.begin(16, 2);
  lcd.print("--Sorte Do Gato-");
  lcd.setCursor(0,0);
  delay(2500);
  lcd.print("                ");
  lcd.setCursor(0,1);
  
  // Acende o backlight
  
 
}

// Laço principal
void loop() {
  static int teclaAnt = -1;   // última tecla detectada
    
  // Lê a tensão no pino A0
  int leitura = analogRead(A0);
 
  // Identifica a tecla apertada pela tensão lida
  int teclaNova;
  for (teclaNova = 0; ; teclaNova++) {
    if (leitura < teclas[teclaNova].limite) {
      break;
    }
  }
 
  


  // Atualiza a tela se pressionou uma nova tecla
  if (teclaNova != teclaAnt) {
    
    
    if (teclaNova == 1) {
      lcd.clear();
      valor++;

      lcd.setCursor(0, 0);
      lcd.print("Apostar : ");

      lcd.setCursor(0, 1);  
      lcd.print(valor);  
    }

    if (teclaNova == 2) {
      lcd.clear();
      valor--;
      if (valor <= 0) valor = 1;

      lcd.setCursor(0, 0);
      lcd.print("Apostar : ");

      lcd.setCursor(0, 1);   
      lcd.print(valor);  
    }

  if (teclaNova == 0) {
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("Validando aposta");

   lcd.setCursor(0,1);
   lcd.write(byte(0));
   lcd.print(" ");
   delay(1000);
   lcd.write(byte(1));// 
   lcd.print(" ");
   delay(1000);
   lcd.write(byte(2));// 
   lcd.print(" ");
   delay(1000);
   lcd.write(byte(3));
   lcd.print(" ");
   delay(1000);
   lcd.write(byte(4));// 
   lcd.print(" ");
   delay(1000);

   apostar();
   
  }

  if (teclaNova == 3) {
      lcd.clear();
    
      lcd.setCursor(0, 0);
      lcd.print("Saldo : ");
      lcd.setCursor(0, 1);  
      lcd.print(saldo);  
    }
    
    //lcd.print(teclas[teclaNova].nome);
    teclaAnt = teclaNova;
  }
 
  // Dá um tempo antes do próximo teste
  delay (50);
}
