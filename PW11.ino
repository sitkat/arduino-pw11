#include <SPI.h>

#define lathchPin 4 //линия синхронизации данных, защелка (LCHCLK)
#define clockPin 7 //линия тактирования (SFTCLK)
#define dataPin 8 //линия передачи данных(SDI)

uint32_t number;
String str;

const byte SEGMENT_MAP[] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0X80, 0X90};
const byte SEGMENT_SELECT[] = {0xF1, 0xF2, 0xF4, 0xF8};

void setup() {
  SPI.begin();
  Serial.begin(9600);

  pinMode(lathchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void loop() {
  if (Serial.available () > 0)
  {
    str = Serial.readString();
    if (atoui(str.c_str(), &number)) {
    if (number >= 0 && number <= 9) {
        WriteNumberToSegment(3, (byte)number);
      }
      else
        Serial.println("Введите 1 цифру");
    }
    else Serial.println("Ошибка ввода");
    }
}

void WriteNumberToSegment(byte Segment, byte Value)
{
  digitalWrite(lathchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, SEGMENT_MAP[Value]);
  shiftOut(dataPin, clockPin, MSBFIRST, SEGMENT_SELECT[Segment] );
  digitalWrite(lathchPin, HIGH);
}
