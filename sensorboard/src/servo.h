#ifndef _STARDUST_SERVO_h
#define _STARDUST_SERVO_h
#include <std_msgs/UInt8.h>
#include <Servo.h> 
#include <math.h>

namespace stardust
{
  class Servomotor
  {
    private:
  
      const byte pin;
      const byte init_position;
      Servo servo;
      ros::Subscriber<std_msgs::UInt8, Servomotor> sub_position;

    public :

      Servomotor(const char *_topic_name,
        const byte _pin, const byte _init_position):
          pin(_pin),
	  init_position(_init_position),
          sub_position(_topic_name, &Servomotor::updatePWM, this ) { }
    
      void setup(ros::NodeHandle *nh)
      {
        nh->subscribe(sub_position);
       
        servo.attach(pin);
        servo.write(init_position);
      }

      void updatePWM(const std_msgs::UInt8& msg) {
        servo.write(msg.data);
      }
  };
}
#endif
