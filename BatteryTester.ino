#define CONTROL_PIN 5
#define SENSE_PIN A5
#define DEFAULT_CURRENT_LIMIT 0.1f

bool testStarted = false;
long elapsedTestTime = 0;
float ampSeconds = 0;

/* This assumes the sense pin is measuring the voltage
 * across a 1 Ohm shunt resistor.
 */
float convertSenseToA(int sensedValue) {
  //10-bit ADC, 5 volt reference
  return ((float)sensedValue / 1024.0f) * 5.0f; 
  //return (float)sensedValue;
}

int avgAnalogRead(int pin) {
  int sum = 0;
  const int readings = 100;
  for (int i = 0; i < readings; i++) {
    sum += analogRead(pin);
  }
  return sum/readings;
}

void setup() {
  // put your setup code here, to run once:
  pinMode(CONTROL_PIN, OUTPUT);
  analogWrite(CONTROL_PIN, 0);

  Serial.begin(9600);
  Serial.print("Battery tester started...");  
}

void loop() {
  static int currentControlValue = 0; //starts at 0
  analogWrite(CONTROL_PIN, currentControlValue); 

  //adjust the value up until we get to DEFAULT_CURRENT_LIMIT
  float currentCurrent = convertSenseToA(avgAnalogRead(SENSE_PIN));
  if (currentCurrent < DEFAULT_CURRENT_LIMIT) {
    currentControlValue = (currentControlValue + 1) % 255;
  }

  if (currentCurrent > DEFAULT_CURRENT_LIMIT) {
    currentControlValue = (currentControlValue - 1) % 255;
  }



  static long lastSampleTimestamp = 0;
  if (currentCurrent > DEFAULT_CURRENT_LIMIT && testStarted == false) {
    testStarted = true;
    elapsedTestTime = 0;
    lastSampleTimestamp = millis();
    ampSeconds = 0;
    Serial.println("Test started...");
  }

  long currentTimestamp = millis();
  if (currentTimestamp > lastSampleTimestamp + 1000) {
    long elapsedSampleTime = currentTimestamp - lastSampleTimestamp;
    elapsedTestTime += elapsedSampleTime;

    float sampleDuration = elapsedSampleTime / 1000.0f;
    ampSeconds += (sampleDuration * currentCurrent);

    lastSampleTimestamp = currentTimestamp;

    if (testStarted) {
      Serial.print("Amp Seconds consumed: ");
      Serial.print(ampSeconds, DEC);
      Serial.println("");
    } else {
      Serial.print("Current: ");
      Serial.print(currentCurrent, DEC);
      Serial.print(" Control: ");
      Serial.print(currentControlValue, DEC);
      Serial.println("");
    }
  }

  
  delay(100);
}


