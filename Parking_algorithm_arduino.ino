#include <Servo.h>
Servo myservo;

#define back_right_ir 6
#define front_right_ir 7
#define back_ir 9
#define echoPin 12
#define trigPin 13
#define rightforward 4
#define leftforward 2
#define rightbackward 3
#define leftbackward 5

int flag=0;
int time=0;
int parked=0;
char income=0;
int blueon=0;
void setup() {
  // put your setup code here, to run once:
  // myservo.attach(8);
  // ############################

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(front_right_ir,INPUT);
  pinMode(back_right_ir,INPUT);
  
  pinMode(8, OUTPUT);
  // ###############################
  pinMode(9, INPUT);
  pinMode(11, OUTPUT);

  // #######################
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // ######################

  Serial.begin(9600);
}

void loop() {

  if(Serial.available()>0)
  {
    income=Serial.read();
    // if(income=='O')
    // {
    //   blueon=1;
    // }
    if(income=='F')
    {
      // blueon=0;
      // Stop();
      forward();
    }
    // if(income=='A'){
    //   blueon=2;
    // }
    if(income=='B')
    {
      back();
    }
    if(income=='S') Stop();
    if(income=='R') right();
    if(income=='L') left();
  }
  if(blueon==2){
    if(find_distance()<20){
    Serial.println(find_distance());
      Stop();
      buz();
      buz();
      buz();
      
      // delay(5000);
    }
    else{
      forward();
   }
  }
  // put your main code here, to run repeatedly:

  // if(find_distance<15){
  //   Stop();
  // }
  if(blueon==1)
  {
    if(flag==6){
    buz();
    Stop();
  }
  if(flag==5){
    if((digitalRead(back_ir))){
      back();
      delay(100);
      goto lb;
    }
    else{
      buz();
      Stop();
      delay(5000);
      flag=6;
    }
  }
  else if(flag==4){
    if(digitalRead(front_right_ir)==0 && digitalRead(back_right_ir)==1){
      left();
      delay(50);
    }
    else if(digitalRead(front_right_ir)==1 && digitalRead(back_right_ir)==0){
      right();
      delay(50);
    }
    flag=5;
    goto lb;
  }
  else if(flag==3){
    buz();
    Stop();
    delay(1000);
    flag=4;
    goto lb;
  }
  else if(flag==2){
    if(digitalRead(front_right_ir)==0 || digitalRead(back_right_ir)==0){
      flag=3;
      Stop();
      goto lb;
    }
    else if((digitalRead(back_ir))){
      back();
      delay(100);
      goto lb;
    }
    right();
    delay(500);
    left();
    delay(500);
    goto lb;
  }
  // if(parked==1){
  //   buz();
  //   Stop();
  //   goto lb;
  // }
  int front_right_ir_reading=!(digitalRead(front_right_ir));
  int back_right_ir_reading=!(digitalRead(back_right_ir));
  if(front_right_ir_reading==1 && back_right_ir_reading==1 && flag==0){
    forward();
    delay(100);
    flag=0;
    goto lb;
  }
  else if(front_right_ir_reading==1 && back_right_ir_reading==0 && flag==0){
    forward();
    delay(100);
    flag=0;
    goto lb;
  }
  else if(front_right_ir_reading==0 && back_right_ir_reading==1 && flag==0){
    forward();
    delay(100);
    flag=1;
    goto lb;
  }
  else if(front_right_ir_reading==0 && back_right_ir_reading==0 && flag==0){
    forward();
    delay(100);
    goto lb;
  }
  else if(front_right_ir_reading==0 && back_right_ir_reading==0 && flag==1){
    flag=2;
    Stop();
    right();
    delay(500);
    left();
    delay(500);
    Stop();
  }
  
  lb:
  int pppp=1;
  // Serial.println("Hello");
  }
}

void back() {
  digitalWrite(5,HIGH);
  digitalWrite(3,HIGH);
  digitalWrite(2,LOW);
  digitalWrite(4,LOW);      
  delay(10);
}

void forward() {
  digitalWrite(4,HIGH);
  digitalWrite(2,HIGH);
  digitalWrite(3,LOW);
  digitalWrite(5,LOW);
  delay(10);
}

void left() {
  digitalWrite(2,LOW);
  // digitalWrite(3,HIGH);
  digitalWrite(4,HIGH);
  digitalWrite(5,LOW);
  delay(10);
}

void right() {
  // digitalWrite(5,HIGH);
  digitalWrite(4,LOW);
  digitalWrite(3,LOW);
  digitalWrite(2,HIGH);
  delay(10);
}

void Stop() {
  digitalWrite(2,0);
  digitalWrite(5,0);
  digitalWrite(3,0);
  digitalWrite(4,0);
}

void buz(){
  digitalWrite(11, HIGH);
  delay(50);
  digitalWrite(11,0);
  delay(50);
}

int find_distance(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  int duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;
  return distance;
}

void park(){
  right();
  delay(1200);
  forward();
  delay(500);
  left();
  delay(1050);
  // back();
  // delay(150);
  parked=1;
  Stop();
}
