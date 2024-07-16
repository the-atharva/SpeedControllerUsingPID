#include <cmath>
#define MODE RISING

//80Mhz clock
const uint8_t input_pin = 13; //ip from ir sensor
//for tachometer
#define TIME micros()
#define C2S 1000000
#define MODE RISING
const int correction_factor = 1.14;
const double max_dt = (1e+7) - 1;
volatile long long interrupt_time_duration = max_dt;
volatile long long prev_time = 0;
//for lpf
double filtered_speed = 0;
double prev_speed = 0;

//pid parameters
const double Kp = 1000;
const double Ki = 10; 
const double Kd = 4.5;  

//pid variables
double integral_error = 0;
double last_error = 0;

//pwm parameters
const uint8_t channel = 1;
//f * 2^(resolution) <= 80MHz
const uint16_t pwm_freq = 100;     
const uint8_t pwm_res = 10;
const int max_duty_cycle = (int)(pow(2, pwm_res) - 1); 

//set speed
float target_speed = 1;


//output pin
const uint8_t output_pin = 26;

void setup() {
  Serial.begin(115200);
  pinMode(input_pin, INPUT); //ir senson
  attachInterrupt(digitalPinToInterrupt(input_pin), tachometer, MODE); //interrupt
  //pwm setup
  ledcSetup(channel, pwm_freq, pwm_res);
  ledcAttachPin(output_pin, channel);
}

void loop() {
  long long time_duration = max_dt;
  noInterrupts();
  time_duration = interrupt_time_duration;
  interrupts();
  double curr_speed = (C2S/correction_factor)/((double)time_duration);
  double dt = (double)time_duration/(C2S/correction_factor);
  curr_speed = constrain(curr_speed, 0.85*target_speed, 1.15*target_speed);
  filtered_speed = curr_speed;
  //actual pid implementation
  double error = target_speed - filtered_speed;
  if(dt != max_dt)
    integral_error += error * dt;   // Calculate integral and derivative terms
  double derivative_error = (error - last_error)/dt;
  double pid = Kp * error + Ki * integral_error + Kd * derivative_error;
  pid = fabs(pid);
  ledcWrite(channel, constrain(pid, 0, max_duty_cycle));

  last_error = error;   // Update last error for the next loop

  Serial.print(dt);
  Serial.print(",");
  Serial.print(filtered_speed);
  Serial.print(",");
  Serial.print(target_speed);
  // Serial.print(",");
  // Serial.print(pid);
  Serial.println();
  delay(200);
}

void tachometer(){
  long long curr_time = TIME; //time since code began
  interrupt_time_duration = (curr_time - prev_time);
  prev_time = curr_time;
}



