#include "USB.h"
#include "USBHID.h"
#include <Preferences.h>

// Configuration
#define POT_PIN        4
#define CAL_BTN_PIN    0
#define LED_PIN        -1
#define INVERT_AXIS    false
#define DEADZONE_LOW   0.02f
#define DEADZONE_HIGH  0.02f
#define OVERSAMPLE     16
#define FILTER_ALPHA   0.25f
#define CAL_DURATION   5000
#define SEND_PERIOD_MS 2
#define DEBUG_SERIAL   false

// HID
static const uint8_t hidReportDescriptor[] = {
  0x05, 0x01,
  0x09, 0x04,
  0xA1, 0x01,
  0x85, 0x01,
  0x09, 0x32,
  0x15, 0x00,
  0x27, 0xFF, 0xFF, 0x00, 0x00,
  0x75, 0x10,
  0x95, 0x01,
  0x81, 0x02,
  0xC0
};

class HandbrakeHID : public USBHIDDevice {
public:
  HandbrakeHID() {
    static bool initialized = false;
    if (!initialized) {
      initialized = true;
      hid.addDevice(this, sizeof(hidReportDescriptor));
    }
  }
  void begin() { hid.begin(); }
  uint16_t _onGetDescriptor(uint8_t *buffer) {
    memcpy(buffer, hidReportDescriptor, sizeof(hidReportDescriptor));
    return sizeof(hidReportDescriptor);
  }
  bool send(uint16_t value) { return hid.SendReport(1, &value, sizeof(value)); }
private:
  USBHID hid;
};

HandbrakeHID handbrake;
Preferences prefs;

int rawMin = 0;
int rawMax = 4095;
float filtered = 0;
uint16_t lastSent = 0xFFFF;
uint32_t lastSend = 0;

// Fonctions
int readPot() {
  uint32_t sum = 0;
  for (int i = 0; i < OVERSAMPLE; i++) sum += analogRead(POT_PIN);
  return sum / OVERSAMPLE;
}

void setLed(bool on) {
  if (LED_PIN >= 0) digitalWrite(LED_PIN, on ? HIGH : LOW);
}

void loadCalibration() {
  prefs.begin("handbrake", true);
  rawMin = prefs.getInt("min", 0);
  rawMax = prefs.getInt("max", 4095);
  prefs.end();
  if (rawMax - rawMin < 100) { rawMin = 0; rawMax = 4095; }
}

void saveCalibration() {
  prefs.begin("handbrake", false);
  prefs.putInt("min", rawMin);
  prefs.putInt("max", rawMax);
  prefs.end();
}

void runCalibration() {
  int lo = 4095, hi = 0;
  uint32_t start = millis();
  while (millis() - start < CAL_DURATION) {
    int v = readPot();
    if (v < lo) lo = v;
    if (v > hi) hi = v;
    setLed((millis() / 150) % 2);
    delay(2);
  }
  setLed(false);
  if (hi - lo > 300) {
    rawMin = lo;
    rawMax = hi;
    saveCalibration();
  }
  filtered = readPot();
}

uint16_t computeAxis(float raw) {
  float n = (raw - rawMin) / float(rawMax - rawMin);
  n = constrain(n, 0.0f, 1.0f);
  if (n < DEADZONE_LOW) n = 0;
  else if (n > 1.0f - DEADZONE_HIGH) n = 1;
  else n = (n - DEADZONE_LOW) / (1.0f - DEADZONE_LOW - DEADZONE_HIGH);
  if (INVERT_AXIS) n = 1.0f - n;
  return (uint16_t)(n * 65535.0f);
}

void setup() {
#if DEBUG_SERIAL
  Serial.begin(115200);
#endif
  pinMode(CAL_BTN_PIN, INPUT_PULLUP);
  if (LED_PIN >= 0) pinMode(LED_PIN, OUTPUT);

  analogReadResolution(12);
  analogSetPinAttenuation(POT_PIN, ADC_11db);

  loadCalibration();
  filtered = readPot();

  handbrake.begin();
  USB.productName("DIY Handbrake");
  USB.manufacturerName("GLOXIOU");
  USB.begin();
}

void loop() {
  if (digitalRead(CAL_BTN_PIN) == LOW) {
    delay(30);
    if (digitalRead(CAL_BTN_PIN) == LOW) runCalibration();
  }

  filtered += FILTER_ALPHA * (readPot() - filtered);

  if (millis() - lastSend >= SEND_PERIOD_MS) {
    lastSend = millis();
    uint16_t axis = computeAxis(filtered);
    if (axis != lastSent) {
      if (handbrake.send(axis)) lastSent = axis;
#if DEBUG_SERIAL
      Serial.printf("raw=%.0f  axis=%u  (min=%d max=%d)\n", filtered, axis, rawMin, rawMax);
#endif
    }
  }
}