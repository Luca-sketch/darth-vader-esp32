#pragma once

// ================================
// Marcha Imperial - Buzzer Passivo
// Pino: GPIO 27 (livre na CYD)
// ================================

#define BUZZER_PIN 27

#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F4  349
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS4 415
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_E4  330
#define NOTE_C4  262
#define REST     0

static int melody[] = {
  NOTE_A4,4, NOTE_A4,4, NOTE_A4,4, NOTE_F4,-8, NOTE_C5,16,
  NOTE_A4,4, NOTE_F4,-8, NOTE_C5,16, NOTE_A4,2,
  NOTE_E5,4, NOTE_E5,4, NOTE_E5,4, NOTE_F5,-8, NOTE_C5,16,
  NOTE_A4,4, NOTE_F4,-8, NOTE_C5,16, NOTE_A4,2,
  NOTE_A5,4, NOTE_A4,-8, NOTE_A4,16, NOTE_A5,4, NOTE_GS5,-8, NOTE_G5,16,
  NOTE_DS5,16, NOTE_D5,16, NOTE_DS5,8, REST,8, NOTE_A4,8, NOTE_DS5,4, NOTE_D5,-8, NOTE_CS5,16,
  NOTE_C5,16, NOTE_B4,16, NOTE_C5,16, REST,8, NOTE_F4,8, NOTE_GS4,4, NOTE_F4,-8, NOTE_A4,-16,
  NOTE_C5,4, NOTE_A4,-8, NOTE_C5,16, NOTE_E5,2,
  NOTE_A5,4, NOTE_A4,-8, NOTE_A4,16, NOTE_A5,4, NOTE_GS5,-8, NOTE_G5,16,
  NOTE_DS5,16, NOTE_D5,16, NOTE_DS5,8, REST,8, NOTE_A4,8, NOTE_DS5,4, NOTE_D5,-8, NOTE_CS5,16,
  NOTE_C5,16, NOTE_B4,16, NOTE_C5,16, REST,8, NOTE_F4,8, NOTE_GS4,4, NOTE_F4,-8, NOTE_A4,-16,
  NOTE_A4,4, NOTE_F4,-8, NOTE_C5,16, NOTE_A4,2,
};

// Music status
static int _tempo       = 120;
static int _notes       = sizeof(melody) / sizeof(melody[0]) / 2;
static int _wholenote   = (60000 * 4) / 120;
static int _noteIndex   = 0;
static unsigned long _nextNoteTime = 0;
static bool _noteOn     = false;
static int _noteDuration = 0;

void imperialSetup() {
  pinMode(BUZZER_PIN, OUTPUT);
}

void imperialTick() {
  unsigned long agora = millis();

  if (!_noteOn && agora >= _nextNoteTime) {
    if (_noteIndex >= _notes * 2) {
      // Reinicia depois de 3s de pausa
      _noteIndex = 0;
      _nextNoteTime = agora + 3000;
      return;
    }

    int divider = melody[_noteIndex + 1];
    if (divider > 0) {
      _noteDuration = _wholenote / divider;
    } else {
      _noteDuration = _wholenote / abs(divider);
      _noteDuration *= 1.5;
    }

    tone(BUZZER_PIN, melody[_noteIndex], _noteDuration * 0.9);
    _noteOn = true;
    _nextNoteTime = agora + _noteDuration;
    _noteIndex += 2;

  } else if (_noteOn && agora >= _nextNoteTime) {
    noTone(BUZZER_PIN);
    _noteOn = false;
    _nextNoteTime = agora;
  }
}