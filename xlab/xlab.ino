volatile unsigned int encoder = 0;
volatile unsigned int copyOfEncoder =0;
const byte encoder1 = 2;
const byte encoder2 = 3;
const int deltaSteps = 8400;


void setup() {
  Serial.begin(115200);  //Initialize the serial connection
  pinMode(encoder1, INPUT); //Set the pins the encoder is connected to as inputs
  pinMode(encoder2, INPUT); //Set the pins the encoder is connected to as inputs
  digitalWrite(encoder1,HIGH); // internal pull up resistor
  digitalWrite(encoder2,HIGH); // internal pull up resistor
  md.init(); // Initialize the motor driver
  md.flipM1(false); // Set motor driection
  md.enableDrivers(); // Enable the motor driver
}

void loop() {
  noInterrupts();
  copyOfEncoder = encoder;
  interrupts();
  turnMotor();
  Serial.println(copyOfEncoder);
}

void turnMotor(){
  
  if(copyOfEncoder >= deltaSteps){
    md.setM1Speed(0);
  }else{
    md.setM1Speed(400);
  }
}

void encoderISR(){
    if (bitRead(PORTD, 2) == bitRead(PORTD, 3) ) {
         encoder += 1;
    }
    else encoder -= 1;
}
