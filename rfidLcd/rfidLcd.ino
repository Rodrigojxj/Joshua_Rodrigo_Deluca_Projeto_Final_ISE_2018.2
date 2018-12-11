#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>
 
#define SS_PIN 10
#define RST_PIN 9
double valor_parcial=0;
int enable=0;
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
 
LiquidCrystal lcd(6, 7, 5, 4, 3, 2); 
 
char st[20];
 
void setup() 
{
  Serial.begin(9600);   // Inicia a serial
  SPI.begin();      // Inicia  SPI bus
  mfrc522.PCD_Init();   // Inicia MFRC522
  Serial.println("Aproxime o seu cartao do leitor...");
  Serial.println();
  //Define o número de colunas e linhas do LCD:  
  lcd.begin(16, 2); 
  mensagemIdle(); 
}
 
void loop() 
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Mostra UID na serial
  Serial.print("UID da tag :");
  String conteudo= "";
  byte letra;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Produto: ");
  conteudo.toUpperCase();

if (enable)
{
  if (conteudo.substring(1) == "D5 95 56 A3") //UID 1 - Chaveiro
  {
    valor_parcial += 8.47;
    Serial.println("Leite -> R$8,47");
    Serial.println();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Produto:");
    lcd.setCursor(0,1);
    lcd.print("Leite R$8,47");
    lcd.setCursor(0,1);
    delay(3000);
    mensageminicial();
  }
  if (conteudo.substring(1) == "98 90 90 B9") //UID 2 - Chaveiro
  {
   valor_parcial += 2.34;
    Serial.println("Arroz -> R$2,34");
    Serial.println();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Produto:");
    lcd.setCursor(0,1);
    lcd.print("Arroz R$2,34");
    lcd.setCursor(0,1);
    delay(3000);
    mensageminicial();
  }
  if (conteudo.substring(1) == "56 C0 B7 73") //UID 3 - Chaveiro
  {
    valor_parcial += 4.10;
    Serial.println("Macarrao -> R$4,10");
    Serial.println();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Produto:");
    lcd.setCursor(0,1);
    lcd.print("Macarrao R$4,10");
    lcd.setCursor(0,1);
    delay(3000);
    mensageminicial();
  }
  if (conteudo.substring(1) == "FA 8B 17 A3") //UID 4 - Chaveiro
  {
    valor_parcial += 6.49;
    Serial.println("Coca Cola 2L -> R$6,49");
    Serial.println();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Produto:");
    lcd.setCursor(0,1);
    lcd.print("Coca Cola R$6,49");
    lcd.setCursor(0,1);
    delay(3000);
    mensageminicial();
  }
  if (conteudo.substring(1) == "10 0D 95 79") //UID 5 - Chaveiro
  {
    valor_parcial += 4.59;
    Serial.println("Toddy -> R$4,59");
    Serial.println();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Produto:");
    lcd.setCursor(0,1);
    lcd.print("Toddy R$4,59");
    lcd.setCursor(0,1);
    delay(3000);
    mensageminicial();
  }
  if (conteudo.substring(1) == "7D 6D 17 A3") //UID 6 - Chaveiro
  {
    valor_parcial += 14.98;
    Serial.println("Pizza -> R$14,98");
    Serial.println();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Produto:");
    lcd.setCursor(0,1);
    lcd.print("Pizza R$14,98");
    lcd.setCursor(0,1);
    delay(3000);
    mensageminicial();
  }
  if (conteudo.substring(1) == "55 BC 06 88") //UID 7 - Chaveiro
  {
    valor_parcial += 10.99;
    Serial.println("Melancia -> R$10,99");
    Serial.println();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Produto:");
    lcd.setCursor(0,1);
    lcd.print("Melancia R$10,99");
    lcd.setCursor(0,1);
    delay(3000);
    mensageminicial();
  }
}
 
  if (conteudo.substring(1) == "C9 7D A7 89") // - Cartao
  {
    if (enable == 1)
    {
      enable=0;
      Serial.println("Compra Finalizada");
      Serial.println();
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Compra Finalizada");
      lcd.setCursor(0,1);
      lcd.print("Total:R$");
      lcd.print(valor_parcial);
      delay(3000);
      valor_parcial = 0.00;
      mensagemIdle();
    }else
    {
      enable=1;
      Serial.println("Iniciaram as compras");
      Serial.println();
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Seja Bem Vindo");
      lcd.setCursor(0,1);
      lcd.print("Boas Compras");
      delay(3000);
      mensageminicial();
    }
    
  }

}
void mensageminicial()
{
  lcd.clear();
  lcd.print("Valor da Compra:");  
  lcd.setCursor(0,1);
  lcd.print("R$"); 
  lcd.print(valor_parcial);  
}

void mensagemIdle()
{
  lcd.clear();
  lcd.print("----------------");  
  lcd.setCursor(0,1);
  lcd.print("----------------"); 
}
