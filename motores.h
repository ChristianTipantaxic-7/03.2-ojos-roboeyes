
const int rele1A = 25;
const int rele1B = 26;

const int rele2A = 27;
const int rele2B = 14;

// Motor 1: izquierda del carrito
// Motor 2: derecha del carrito

void setup() {
  pinMode(rele1A, OUTPUT);
  pinMode(rele1B, OUTPUT);
  pinMode(rele2A, OUTPUT);
  pinMode(rele2B, OUTPUT);

  detener();
}

void motorIzquierdo(bool adelante) {
  digitalWrite(rele1A, adelante ? HIGH : LOW);
  digitalWrite(rele1B, adelante ? HIGH : LOW);
}

void motorDerecho(bool adelante) {
  digitalWrite(rele2A, adelante ? HIGH : LOW);
  digitalWrite(rele2B, adelante ? HIGH : LOW);
}

void detenerMotorIzquierdo() {
  digitalWrite(rele1A, HIGH);
  digitalWrite(rele1B, LOW);
}

void detenerMotorDerecho() {
  digitalWrite(rele2A, HIGH);
  digitalWrite(rele2B, LOW);
}

void detener() {
  detenerMotorIzquierdo();
  detenerMotorDerecho();
}

void adelante() {
  motorIzquierdo(true);
  motorDerecho(true);
}

void atras() {
  motorIzquierdo(false);
  motorDerecho(false);
}

void derecha() {
  motorIzquierdo(true);
  motorDerecho(false);
}

void izquierda() {
  motorIzquierdo(false);
  motorDerecho(true);
}

void loop() {
  adelante();
  delay(2000);

  detener();
  delay(700);

  atras();
  delay(2000);

  detener();
  delay(700);

  derecha();
  delay(1500);

  detener();
  delay(700);

  izquierda();
  delay(1500);

  detener();
  delay(1500);
}
