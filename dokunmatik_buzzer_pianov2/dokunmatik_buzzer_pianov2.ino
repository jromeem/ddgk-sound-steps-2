#define MHD_R  0x2B
#define NHD_R 0x2C
#define NCL_R   0x2D
#define FDL_R 0x2E
#define MHD_F 0x2F
#define NHD_F 0x30
#define NCL_F 0x31
#define FDL_F 0x32
#define ELE0_T  0x41
#define ELE0_R  0x42
#define ELE1_T  0x43
#define ELE1_R  0x44
#define ELE2_T  0x45
#define ELE2_R  0x46
#define ELE3_T  0x47
#define ELE3_R  0x48
#define ELE4_T  0x49
#define ELE4_R  0x4A
#define ELE5_T  0x4B
#define ELE5_R  0x4C
#define ELE6_T  0x4D
#define ELE6_R  0x4E
#define ELE7_T  0x4F
#define ELE7_R  0x50
#define ELE8_T  0x51
#define ELE8_R  0x52
#define ELE9_T  0x53
#define ELE9_R  0x54
#define ELE10_T 0x55
#define ELE10_R 0x56
#define ELE11_T 0x57
#define ELE11_R 0x58
#define FIL_CFG 0x5D
#define ELE_CFG 0x5E
#define GPIO_CTRL0  0x73
#define GPIO_CTRL1  0x74
#define GPIO_DATA 0x75
#define GPIO_DIR  0x76
#define GPIO_EN   0x77
#define GPIO_SET  0x78
#define GPIO_CLEAR  0x79
#define GPIO_TOGGLE 0x7A
#define ATO_CFG0  0x7B
#define ATO_CFGU  0x7D
#define ATO_CFGL  0x7E
#define ATO_CFGT  0x7F

// Global Constants
#define TOU_THRESH  0x06
#define REL_THRESH  0x0A

#include "Adafruit_MPR121.h"
#include "notes.h"
#include <Wire.h>
#include <Audio.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// sequence with 23 notes
float tones[24] = {note_c4, note_d4, note_e4, note_f4, note_g4, note_a4, note_b4,
                   note_c5, note_d5, note_e5, note_f5, note_g5, note_a5, note_b5,
                   note_c6, note_d6, note_e6, note_f6, note_g6, note_a6, note_b6,
                   note_c7, note_d7, note_e7
                  };

int irqpin = 2;
int speaker = 3;
//int tones[] = {1700, 1519, 1432, 1275, 1136, 1014, 956, 851, 758, 716, 636, 568 };
int Cur_tone = 0;

Adafruit_MPR121 cap = Adafruit_MPR121();
Adafruit_MPR121 cap2 = Adafruit_MPR121();

boolean touchStates[12];
boolean touchStates2[12];

// GUItool: begin automatically generated code
AudioSynthWaveformSineModulated sine_fm2;       //xy=123.28571319580078,385.1428527832031
AudioSynthWaveform       waveform1;      //xy=218,470
AudioSynthWaveformSineModulated sine_fm1;       //xy=271.8571472167969,385.4285888671875
AudioMixer4              mixer2;         //xy=444,454
AudioEffectEnvelope      envelope1;      //xy=608.4284973144531,453.4285888671875
//AudioEffectDelay         delay1;         //xy=770,614
AudioMixer4              mixer1;         //xy=771,471.5714416503906
AudioAnalyzePeak         peak1;          //xy=921,321
AudioOutputAnalog        dac1;           //xy=1001.4285659790039,486.8571300506592
AudioConnection          patchCord1(sine_fm2, sine_fm1);
AudioConnection          patchCord2(waveform1, 0, mixer2, 1);
AudioConnection          patchCord3(sine_fm1, 0, mixer2, 0);
AudioConnection          patchCord4(mixer2, envelope1);
AudioConnection          patchCord5(envelope1, 0, mixer1, 0);
//AudioConnection          patchCord6(delay1, 0, mixer1, 1);
AudioConnection          patchCord6(mixer1, dac1);
AudioConnection          patchCord7(mixer1, peak1);
//AudioConnection          patchCord9(mixer1, delay1);
// GUItool: end automatically generated code



void setup() {
  pinMode(irqpin, INPUT);
  //  pinMode(speaker, OUTPUT);
  //  digitalWrite(irqpin, HIGH);

  //  Serial.begin(57600);
  //  Serial.begin(9600);
  //  Wire.begin();

  mpr121_setup();

  AudioMemory(75);
  sine_fm1.amplitude(1);
  //  waveform1.begin(1, 440, WAVEFORM_SQUARE);
  mixer2.gain(0, .7);
  mixer2.gain(1, .3);
  //  envelope1.attack(1);
  //  envelope1.release(5);
  mixer1.gain(0, 1);
  mixer1.gain(1, 0);

}

void loop() {
  readTouchInputs();

  if (   (touchStates[0] == 1) || (touchStates[1] == 1) ||
         (touchStates[2] == 1) || (touchStates[3] == 1) ||
         (touchStates[4] == 1) || (touchStates[5] == 1) ||
         (touchStates[6] == 1) || (touchStates[7] == 1) ||
         (touchStates[8] == 1) || (touchStates[9] == 1) ||
         (touchStates[10] == 1) || (touchStates[11] == 1)

         ||

         (touchStates2[0] == 1) || (touchStates2[1] == 1) ||
         (touchStates2[2] == 1) || (touchStates2[3] == 1) ||
         (touchStates2[4] == 1) || (touchStates2[5] == 1) ||
         (touchStates2[6] == 1) || (touchStates2[7] == 1) ||
         (touchStates2[8] == 1) || (touchStates2[9] == 1) ||
         (touchStates2[10] == 1) || (touchStates2[11] == 1))
  {

    Serial.println("we touched");
    if (touchStates[0] == 1)
    {
      Cur_tone = tones[0];
    }
    if (touchStates[1] == 1)
    {
      Cur_tone = tones[1];
    }
    if (touchStates[2] == 1)
    {
      Cur_tone = tones[2];
    }
    if (touchStates[3] == 1)
    {
      Cur_tone = tones[3];
    }
    if (touchStates[4] == 1)
    {
      Cur_tone = tones[4];
    }
    if (touchStates[5] == 1)
    {
      Cur_tone = tones[5];
    }
    if (touchStates[6] == 1)
    {
      Cur_tone = tones[6];
    }
    if (touchStates[7] == 1)
    {
      Cur_tone = tones[7];
    }
    if (touchStates[8] == 1)
    {
      Cur_tone = tones[8];
    }
    if (touchStates[9] == 1)
    {
      Cur_tone = tones[9];
    }
    if (touchStates[10] == 1)
    {
      Cur_tone = tones[10];
    }
    if (touchStates[11] == 1)
    {
      Cur_tone = tones[11];
    }

    if (touchStates2[0] == 1)
    {
      Cur_tone = tones[12];
    }
    if (touchStates2[1] == 1)
    {
      Cur_tone = tones[13];
    }
    if (touchStates2[2] == 1)
    {
      Cur_tone = tones[14];
    }
    if (touchStates2[3] == 1)
    {
      Cur_tone = tones[15];
    }
    if (touchStates2[4] == 1)
    {
      Cur_tone = tones[16];
    }
    if (touchStates2[5] == 1)
    {
      Cur_tone = tones[17];
    }
    if (touchStates2[6] == 1)
    {
      Cur_tone = tones[18];
    }
    if (touchStates2[7] == 1)
    {
      Cur_tone = tones[19];
    }
    if (touchStates2[8] == 1)
    {
      Cur_tone = tones[20];
    }
    if (touchStates2[9] == 1)
    {
      Cur_tone = tones[21];
    }
    if (touchStates2[10] == 1)
    {
      Cur_tone = tones[22];
    }
    if (touchStates2[11] == 1)
    {
      Cur_tone = tones[23];
    }

    //    freq_out1 = seq23[seq_step1];
    sine_fm1.frequency(Cur_tone);
    envelope1.noteOff();
    //    digitalWrite(speaker, HIGH);
    //    delayMicroseconds(Cur_tone);
    //    envelope1.noteOff();
    //    digitalWrite(speaker, LOW);
    //    delayMicroseconds(Cur_tone);
    //    tone(23, Cur_tone);

  }
  else //in case no button is pressed , close the piezo
  {
    //    Serial.println("we done?");
    //    envelope1.noteOff();
    //    digitalWrite(speaker, LOW);
  }
}

void readTouchInputs() {

  // check 1
  if (!checkInterrupt()) {
    //    Serial.println("hellso world");
    Wire.requestFrom(0x5A, 2);

    byte LSB = Wire.read();
    byte MSB = Wire.read();

    uint16_t touched = ((MSB << 8) | LSB);

    for (int i = 0; i < 12; i++) {
      if (touched & (1 << i)) {

        if (touchStates[i] == 0) {
          Serial.print(i);
          Serial.println(".Pin Dokulundu");

        } else if (touchStates[i] == 1) {
        }

        touchStates[i] = 1;
      } else {
        if (touchStates[i] == 1) {
          Serial.print(i);
          Serial.println(".Pin Cekildi");

        }
        touchStates[i] = 0;
      }
    }
  }

  // check 2
  if (!checkInterrupt()) {
    //    Serial.println("hellso world");
    Wire.requestFrom(0x5B, 2);

    byte LSB = Wire.read();
    byte MSB = Wire.read();

    uint16_t touched = ((MSB << 8) | LSB);

    for (int i = 0; i < 12; i++) {
      if (touched & (1 << i)) {

        if (touchStates2[i] == 0) {
          Serial.print(i);
          Serial.println(".Pin Dokulundu");

        } else if (touchStates2[i] == 1) {
        }

        touchStates2[i] = 1;
      } else {
        if (touchStates2[i] == 1) {
          Serial.print(i);
          Serial.println(".Pin Cekildi");

        }
        touchStates2[i] = 0;
      }
    }
  }
}

void mpr121_setup(void) {
  Serial.println("finding?");
  if (!cap.begin(0x5A)) {
    delay(5000);
    Serial.println("MPR121 not found, check wiring?");
    while (1);
  }
  Serial.println("MPR121 found!");

  if (!cap.begin(0x5B)) {
    delay(5000);
    Serial.println("MPR121 2 not found, check wiring?");
    while (1);
  }
  Serial.println("MPR121 2 found!");
  //  set_register(0x5A, ELE_CFG, 0x00);
  //
  //  set_register(0x5A, MHD_R, 0x01);
  //  set_register(0x5A, NHD_R, 0x01);
  //  set_register(0x5A, NCL_R, 0x00);
  //  set_register(0x5A, FDL_R, 0x00);
  //
  //  set_register(0x5A, MHD_F, 0x01);
  //  set_register(0x5A, NHD_F, 0x01);
  //  set_register(0x5A, NCL_F, 0xFF);
  //  set_register(0x5A, FDL_F, 0x02);
  //
  //  set_register(0x5A, ELE0_T, TOU_THRESH);
  //  set_register(0x5A, ELE0_R, REL_THRESH);
  //  set_register(0x5A, ELE1_T, TOU_THRESH);
  //  set_register(0x5A, ELE1_R, REL_THRESH);
  //  set_register(0x5A, ELE2_T, TOU_THRESH);
  //  set_register(0x5A, ELE2_R, REL_THRESH);
  //  set_register(0x5A, ELE3_T, TOU_THRESH);
  //  set_register(0x5A, ELE3_R, REL_THRESH);
  //  set_register(0x5A, ELE4_T, TOU_THRESH);
  //  set_register(0x5A, ELE4_R, REL_THRESH);
  //  set_register(0x5A, ELE5_T, TOU_THRESH);
  //  set_register(0x5A, ELE5_R, REL_THRESH);
  //  set_register(0x5A, ELE6_T, TOU_THRESH);
  //  set_register(0x5A, ELE6_R, REL_THRESH);
  //  set_register(0x5A, ELE7_T, TOU_THRESH);
  //  set_register(0x5A, ELE7_R, REL_THRESH);
  //  set_register(0x5A, ELE8_T, TOU_THRESH);
  //  set_register(0x5A, ELE8_R, REL_THRESH);
  //  set_register(0x5A, ELE9_T, TOU_THRESH);
  //  set_register(0x5A, ELE9_R, REL_THRESH);
  //  set_register(0x5A, ELE10_T, TOU_THRESH);
  //  set_register(0x5A, ELE10_R, REL_THRESH);
  //  set_register(0x5A, ELE11_T, TOU_THRESH);
  //  set_register(0x5A, ELE11_R, REL_THRESH);
  //  set_register(0x5A, FIL_CFG, 0x04);
  //  set_register(0x5A, ELE_CFG, 0x0C);
  //  set_register(0x5A, ELE_CFG, 0x0C);
}

boolean checkInterrupt(void) {
  //  Serial.println("what is this");
  return digitalRead(irqpin);
}

void set_register(int address, unsigned char r, unsigned char v) {
  Wire.beginTransmission(address);
  Wire.write(r);
  Wire.write(v);
  Wire.endTransmission();
}
