#include "GPIO.h" 
int main() 
{ 
// Open device file 13 on Linux file system 
GPIO gpio(13); 
// Generate PWM signal with 20ms period and 1.5ms on time. 
// Generate 400 periods, this will take 20ms * 400 iterations = 8s 
gpio.GeneratePWM(20000, 1500, 400); 
// Done 
return 0; 
}