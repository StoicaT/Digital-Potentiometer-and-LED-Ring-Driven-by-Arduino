# Digital-Potentiometer-and-LED-Ring-Driven-by-Arduino
This project aims to experiment with the digital control of a digital potentiometer type M62429 and an RGB LED ring. This is done by an Arduino Nano, which reads a Rotary Encoder.
The position of the Rotary Encoder gives the factor of division (attenuation) of the digital potentiometer but also the number of LEDs lit (as well as their color), thus making a visual estimate of the signal level.

The applications are in the audio field, for a sound control without potentiometric noises and a fast estimation of the sound level. Thus, for large attenuations the color of the LEDs is blue, for medium attenuations it will be green, and for small attenuations it will be red. For intermediate values, two colors can be displayed simultaneously.

For those interested in software, the routines of rotary encoder reading, LED ring control and serial communication with the digital potentiometer may be of interest. The software will be described in more details.
More details about the project at:
https://www.instructables.com/id/Digital-Potentiometer-and-LED-Ring-Driven-by-Ardui/
