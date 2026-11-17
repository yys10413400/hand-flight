// Hand Flight - HC-SR04 거리 센서 → 시리얼 출력
// 배선 (Arduino Nano / Uno):
//   HC-SR04 VCC  -> 5V
//   HC-SR04 GND  -> GND
//   HC-SR04 TRIG -> D9
//   HC-SR04 ECHO -> D10
// 출력: 한 줄에 거리(cm) 하나, 예) "12.3\n"  (115200 baud)

const int TRIG_PIN = 9;
const int ECHO_PIN = 10;

void setup() {
  Serial.begin(115200);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

float readDistanceCm() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  // 25ms 타임아웃 ≈ 최대 4m
  unsigned long duration = pulseIn(ECHO_PIN, HIGH, 25000UL);
  if (duration == 0) return -1;          // 측정 실패
  return duration * 0.0343 / 2.0;        // 음속 343m/s
}

void loop() {
  float d = readDistanceCm();
  if (d > 0 && d < 200) {
    Serial.println(d, 1);
  }
  delay(30); // 약 30Hz
}
