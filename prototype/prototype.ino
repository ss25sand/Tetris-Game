int ledPins[] = {3,5,6,9,10,11};
int buttonPin = 2;
int buttonState = 0;
int timer = 2000;

void setup() {
  // put your setup code here, to run once:
  for(int i = 0; i < 6; i++){
    pinMode(ledPins[i],OUTPUT);
  }
  pinMode(buttonPin,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  buttonState = digitalRead(buttonPin);
  
  if(buttonState == HIGH){
    for(int i = 0; i < 6; i++){
      digitalWrite(ledPins[i],HIGH);
      delay(timer);
    }
  }
  for(int i = 0; i < 6; i++){
    digitalWrite(ledPins[i],LOW);
  }
}
