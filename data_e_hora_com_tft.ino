#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_TFTLCD.h> // Hardware-specific library

//Definicao de cores
#define BLACK           0x0000
#define BLUE            0x001F
#define RED             0xF800
#define GREEN           0x07E0
#define CYAN            0x07FF
#define MAGENTA         0xF81F
#define YELLOW          0xFFE0
#define WHITE           0xFFFF

//CS, CD, WR, RD, RESET
Adafruit_TFTLCD tft(A3, A2, A1, A0, A4);

int segundo, minuto, hora, dia, mes, ano;
unsigned long UtlTime;

//Declaração das constantes

//Variável que conterá os estados do botão (0 LOW, 1 HIGH).
int estadoBotao = 1;

void setup(void)
{
  pinMode(LED_BUILTIN, OUTPUT);

  UtlTime = 0;
  minuto = 0;
  hora = 0;

  Serial.begin(9600);
  tft.reset();
  delay(500);
  //tft.begin(0x9341) //Use esta linha para o controlador 9341
  tft.begin(0x9325);

  tft.setTextColor(WHITE);
  tft.fillScreen(BLACK);

  //tft.setRotation(3); //Use esta linha para o controlador 9341
  // left, top, larg,alt, x

  tft.setTextSize(3);
  tft.setCursor(170, 210);
  tft.setRotation(1);
  tft.fillRoundRect(136, 205, 180, 30, 1,  BLACK);

  tft.print(hora);
  tft.print(":");
  tft.print(minuto);

  digitalWrite(LED_BUILTIN, LOW); //Botão não pressionado, apaga o led.
}

void loop()
{


  if (millis() - UtlTime < 0)
  {
    UtlTime = millis();
  }
  else
  {
    segundo = int((millis() - UtlTime) / 1000);
  }

  if (segundo > 59)
  {
    segundo = 0;
    //tft.setRotation(3); //Use esta linha para o controlador 9341
    // left, top, larg,alt, x


    minuto++;
    UtlTime = millis();
    if (minuto > 59)
    {
      hora++;
      minuto = 0;
      if (hora > 23)
      {
        dia++;
        hora = 0;

        if (mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12)
        {
          if (dia > 31)
          {
            dia = 1;
            mes++;
            if (mes > 12)
            {
              ano++;
              mes = 1;
            }
          }
        }
        else if (mes == 2)
        {
          if (ano % 400 == 0)
          {
            if (dia > 29)
            {
              dia = 1;
              mes++;
            }
          }
          else if ((ano % 4 == 0) && (ano % 100 != 0))
          {
            if (dia > 29)
            {
              dia = 1;
              mes++;
            }
          }
          else
          {
            if (dia > 28)
            {
              dia = 1;
              mes++;
            }
          }
        }
        else
        {
          if (dia > 30)
          {
            dia = 1;
            mes++;
          }
        }
      }
    }
    tft.setTextSize(3);
    tft.setCursor(170, 210);
    tft.setRotation(1);
    tft.fillRoundRect(136, 205, 180, 30, 1,  BLACK);

    tft.print(hora);
    tft.print(":");
    tft.print(minuto);

  }



  if (hora >= 8 && hora <= 16) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
  } else {
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);
  }

  delay(100);

}


