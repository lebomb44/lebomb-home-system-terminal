//const int rxPin  = 2;
const int ledPin = 13;

// variables will change
int rxState = 0;
word fifo_buff[256];
byte fifo_in = 0;
byte fifo_out = 0;

word chaconStep = 0;
boolean chaconBitStream[64];
unsigned long chaconMsg;

void setup() {
  fifo_in = 0;
  fifo_out = 0;
  chaconStep = 0;
  // initialize the LED pin as an output
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  // initialize the pushbutton pin as an input
  Serial.begin(115200);
  TCNT1  = 0x0000;
  TCCR1A = 0x00;
  TCCR1C = 0x00;
  TCCR1B = 0x02;

  //EIMSK = 0x00;
  attachInterrupt(0, extInt0, CHANGE);
  //EICRA = 0x03;
  //EIMSK = 0x01;
}

void loop() {
  word dataU16 = 0;
  byte cBit = 0;

  if(fifo_out != fifo_in)
  {
    dataU16 = fifo_buff[fifo_out];
    fifo_out++;
    digitalWrite(ledPin, LOW);

    if((1 < chaconStep) && (chaconStep < 130))
    {
      if(0 == (chaconStep%2)) { if(chaconHigh(dataU16)) { chaconStep++; } else { Serial.print("BadHigh");Serial.print("-");Serial.println(dataU16); chaconStep = 0; } }
      else
      {
        if(chaconLowShort(dataU16)) { chaconBitStream[(chaconStep-3)/2] = false; chaconStep++; }
        else
        {
          if(chaconLowLong(dataU16)) { chaconBitStream[(chaconStep-3)/2] = true; chaconStep++; }
          else { Serial.print(chaconStep);Serial.print("-");Serial.println(dataU16); chaconStep = 0; }
        }
      }
    }
    if(1 == chaconStep) { if(chaconLowSync(dataU16)) { chaconStep++; } else { chaconStep = 0; } }
    if(0 == chaconStep) { if(chaconHigh(dataU16)) { chaconStep++; } }
  }
  if(129 < chaconStep)
  {
    for(cBit=0; cBit<32; cBit++)
    {
      /* Serial.print(chaconBitStream[2*cBit]); Serial.print(chaconBitStream[(2*cBit) + 1]); */
      if((false == chaconBitStream[2*cBit]) && (true == chaconBitStream[(2*cBit) + 1]))
      {
        bitClear(chaconMsg, cBit);
      }
      else
      {
        if((true == chaconBitStream[2*cBit]) && (false == chaconBitStream[(2*cBit) + 1]))
        {
          bitSet(chaconMsg, cBit);
        }
        else
        {
          /* Serial.print("Bad sequence-");Serial.print(cBit);Serial.print("=");Serial.print(chaconBitStream[2*cBit]);Serial.println(chaconBitStream[(2*cBit) +1]); */
          chaconStep = 0; return;
        }
      }
    }
    Serial.println();
    Serial.println(chaconMsg, HEX);
    Serial.print((0xF0000000 & chaconMsg) >> 28, HEX);Serial.print("-");
    Serial.print((0x08000000 & chaconMsg) >> 27, HEX);Serial.print("-");
    Serial.print((0x04000000 & chaconMsg) >> 26, HEX);Serial.print("-");
    Serial.print(0x03FFFFFF & chaconMsg, HEX);Serial.println();
    
    chaconStep = 0;
  }
}

boolean chaconHigh(word timeU16) {
  if((495 < timeU16) && (timeU16 < 640)) { return true; }
  else { return false; }
}

boolean chaconLowShort(word timeU16) {
  if((432 < timeU16) && (timeU16 < 650)) { return true; }
  else { return false; }
}

boolean chaconLowLong(word timeU16) {
  if((2340 < timeU16) && (timeU16 < 2860)) { return true; }
  else { return false; }
}

boolean chaconLowSync(word timeU16) {
  if((4815 < timeU16) && (timeU16 < 5585)) { return true; }
  else { return false; }
}

void extInt0(void) {
  word dataU16 = 0;

  dataU16 = TCNT1;
  TCNT1 = 0x0000;

  if((432 < dataU16) && (dataU16 < 5585))
  {
    digitalWrite(ledPin, HIGH);
    if(fifo_out != (fifo_in+1))
    {
      fifo_buff[fifo_in] = dataU16;
      fifo_in++;
    }
  }
}

