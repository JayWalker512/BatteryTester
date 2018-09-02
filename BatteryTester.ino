#define CONTROL_PIN 5
#define SENSE_PIN A5
#define DEFAULT_CURRENT_LIMIT 100

/* This assumes the sense pin is measuring the voltage
 * across a 1 Ohm shunt resistor.
 */
float convertSenseToMa(int sensedValue) {
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
  float currentCurrent = convertSenseToMa(avgAnalogRead(SENSE_PIN));
  //float currentCurrent = (float)avgAnalogRead(SENSE_PIN);
  if (currentCurrent < 0.1f) {
    currentControlValue = (currentControlValue + 1) % 255;
  }

  if (currentCurrent > 0.1f) {
    currentControlValue = (currentControlValue - 1) % 255;
  }

  Serial.print("Current: ");
  Serial.print(currentCurrent, DEC);
  Serial.print(" Control: ");
  Serial.print(currentControlValue, DEC);
  Serial.println("");
  delay(100);
}


