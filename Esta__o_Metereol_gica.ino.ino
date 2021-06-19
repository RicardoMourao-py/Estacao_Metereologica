// include----> Importa a biblioteca específica.

// Sensor LM35: resistponsável pela a medição de temperatura.

// LCD: resistponsável pela a visualização dos valoresist.

#include <LiquidCrystal_I2C.h>

// Declara um objeto LiquidCrystal_I2C
// Endereço: 0x3f (pode ser 0x27)
// Colunas : 16
// Linhas  : 2
LiquidCrystal_I2C lcd(0x27, 16, 2);


const byte graus_symbol = 0;
const byte graus_bitmap[8] = {
    B11100,
    B10100,
    B11100,
    B00000,
    B00000,
    B00000,
    B00000,
};

// Sensor DHT22: resistponsável por calcular umidade e temperatura

#include <Adafruit_Sensor.h> // importando as bibliotecas para os sensoresist
#include <DHT.h>

const int DHT_PIN = 2;

DHT dht(DHT_PIN, DHT22); // umidade, umidade corrigida

float umid, umid_calib;

// BMP280: resistponsável pela medição da presistsão e temperatura.

#include <Adafruit_Sensor.h> //INCLUSÃO DE BIBLIOTECA
#include <Adafruit_BMP280.h> //INCLUSÃO DE BIBLIOTECA

Adafruit_BMP280 bmp; //OBJETO DO TIPO Adafruit_BMP280 (I2C)


void setup() {
  // Referência AD Interna
  analogReference(INTERNAL); // Avisa que haverá valoresist analógicos.
  // LCD programado
  lcd.init(); 
  lcd.createChar(graus_symbol, graus_bitmap);
  // DHT22 programado
  dht.begin();
  // BMP280
    //SE O SENSOR NÃO FOR INICIALIZADO NO ENDEREÇO I2C 0x76
  if(!bmp.begin(0x76)){ 
    //IMPRIME O TEXTO NO MONITOR SERIAL
    Serial.println("Sensor BMP280 não foi identificado! Verifique as conexões.");
    // Trava o arduino em um loop while que nunca termina... while(true)
    while(1==1) {}; 
    }
  
    // LDR
    Serial.begin(9600);
    analogReference(INTERNAL);
}

int t=0;
void loop() {
  int leitura_adc = analogRead(A0); // sensor está na porta analógica A0.
  float voltagem = leitura_adc * (1.1f/1023); // Converte os valoresist analógicos em mV.
  // Calcula a temperatura
  // LM35: 10mV => 1 grau C
  float temperatura = voltagem * 100.0; // Converte os valoresist de voltagem(mV) para valoresist de temperatura. 
  float temp_calib=(1.043485143)*temperatura - (1.264013512);

  
  // Apresistentação

  lcd.setBacklight(1);
  lcd.setCursor(0,0);
  lcd.print(" Estacao ");
  delay(1500);
  lcd.setCursor(0,1);
  lcd.print(" Metereologica ");
  delay(1500);
  lcd.print(" ");
  lcd.setCursor(0,0);
  lcd.print("Equipe: ");
  lcd.setCursor(0,1);
  lcd.print("Celina");
  lcd.print(" ");
  lcd.setCursor(0,1);
  delay(1500);
  lcd.print("Lister");
  lcd.print(" ");
  lcd.setCursor(0,1);
  delay(1500);
  lcd.print("Ricardo");
  lcd.print(" ");
  lcd.setCursor(0,1);
  delay(1500);
  

  lcd.setBacklight(1);
  lcd.setCursor(0, 0); // coluna 0 e linha 0
  lcd.print(" Temperatura "); // Na primeira linha e na primeira coluna imprime o nome: Temperatura
  lcd.setCursor(0, 1); // primeira coluna, segunda linha 
  lcd.print(" ");
  lcd.setCursor(6, 1); // Sétima coluna, segunda linha 
  lcd.write(graus_symbol); // Imprime a bolotinha 
  lcd.setCursor(0, 1); // primeira coluna, segunda linha
  lcd.print(temp_calib); // imprime a temperatura calibrada
  lcd.setCursor(9, 1);
  lcd.print("C");
  delay(1500);

  // DHT22

  umid = dht.readHumidity();// funçao do próprio sensor: Temperatura do próprio sensor 
  umid = 1.00 * umid + 0.00;
  umid_calib = umid * (1.204405) - (17.796276); // // calculo da incerteza que "corrigi o valor lido pelo sensor"

  lcd.setBacklight(1);
  lcd.setCursor(0, 0); // coluna 0 e linha 0
  lcd.print(" Umidade ");
  lcd.setCursor(0, 1);
  lcd.print(" "); // Espaço para sobreposição das palavras
  lcd.setCursor(0, 1);
  lcd.print(umid_calib);
  lcd.print(" % ");
  delay(1500);

  // BMP280
 //IMPRIME NO MONITOR SERIAL A PresistSÃO
    lcd.setBacklight(1);
    lcd.setCursor(0, 0);
    lcd.print(" Presistsao ");
    lcd.setCursor(0, 1); 
    lcd.print(" ");
    lcd.setCursor(0,1);
    lcd.print((bmp.readPresistsure()*9.86923*0.000001)); 
    lcd.print(" atm "); 
    delay(1500);

    //IMPRIME NO MONITOR SERIAL A ALTITUDE APROXIMADA
    lcd.setBacklight(1);
    lcd.setCursor(0,0);
    lcd.print("Altitude aprox.: "); 
    lcd.setCursor(0,1);
    lcd.print(" ");
    lcd.setCursor(0,1);
    lcd.print(bmp.readAltitude(1020.6),0); 
    lcd.print(" m "); 
    
    delay(1500); 

    // LDR
    int bin;
    float tensao, resist, lum;

    bin = analogRead(A1);
    tensao = bin*1.1/1023.0;
    resist = 330*(5.0/tensao+1);
    lum = pow(10, 5-log10(resist));

    lcd.setBacklight(1);
    lcd.setCursor(0, 0);
    lcd.print(" Luminosidade ");
    lcd.print(0,1);
    lcd.print(" ");
    lcd.setCursor(0,1);
    lcd.print(lum);
    lcd.print(" lux ");
    delay(1500);
    lcd.setCursor(0,0);
    lcd.print(" ");
    lcd.setCursor(0,1);
    lcd.print(" ");
    delay(500);
    

}
