# 🦾 Darth Vader ESP32 CYD

> *"I find your lack of RAM disturbing."*

A hobby project that puts Darth Vader on a tiny R$30 ESP32 display,
cycling through pop-art colors while playing the Imperial March on a passive buzzer.
Because why not.

## What it does

- Vader slides up from the bottom of the screen on startup
- Cycles through 5 pop-art color frames (blue, green, orange, purple, red)
- Plays the Imperial March on a passive buzzer — in sync with the animation
- Non-blocking music via `millis()` so the display never freezes

## Hardware

- ESP32-2432S028 aka **Cheap Yellow Display (CYD)**
- Passive buzzer (active buzzers won't work — they only beep)
- Two jumper wires

### Buzzer wiring

| Buzzer | ESP32 CYD |
|--------|-----------|
| `+`    | GPIO 27   |
| `-`    | GND       |

### TFT + Touch

Handled by `TFT_eSPI`. Touch initialized via VSPI:

| Function    | GPIO |
|-------------|------|
| Touch SCK   | 25   |
| Touch MISO  | 39   |
| Touch MOSI  | 32   |
| Touch CS    | 33   |
| Touch IRQ   | 36   |

Backlight → GPIO 21

## ⚠️ CYD display configuration

The CYD requires a specific `User_Setup.h` for `TFT_eSPI` **and** a
mandatory register fix after `tft.init()` — otherwise you get color
glitches and a noise band on the left edge of the screen.

See the comments in `darth-vader-esp32.ino` for the full setup.

## Image files

The Vader frames are pre-converted PNG images in **RGB565** format,
generated with a Python script (`converter_rgb565.py` included).

To create your own frames:

```bash
pip install Pillow
python converter_rgb565.py your_image.png VariableName 240 240
```

## Project structure
darth-vader-esp32/ 
├── darth-vader-esp32.ino # Main sketch 
├── Imperial.h # Imperial March — non-blocking 
├── converter_rgb565.py # Image conversion tool 
├── blue.h # Blue frame 
├── green.h # Green frame 
├── orange.h # Orange frame 
├── purple.h # Purple frame 
└── red.h # Red frame

##Libraries

Install via Arduino IDE Library Manager:

TFT_eSPI by Bodmer
XPT2046_Touchscreen by Paul Stoffregen

SPI is included with the ESP32 Arduino core.

May the Force be with your GPIO pins 🌌
