# Trigger Box
## General Description
The EEG Dual Audio Trigger Box (shown below) detects if either of the two audio inputs rises suddenly by more than a certain voltage step, generating a pulse on the corresponding trigger outputs, which are then fed into the corresponding trigger inputs of a Biosemi EEG system. Two LED indicators are lit for as long as the trigger output pulse for the corresponding channel is on (1 and 2 correspond to the left and right audio channels, respectively).
(insert image)
## Operating principle
As soon as a rising edge is detected on the input, a 50ms pulse going from 0 to 1 V is generated on its corresponding output. (this means that the signal applied to the input has to show a rising edge). When triggered, inputs become inactive for 100ms. The delay between input and output rising edges is typically between 20 and 24μs (see table below). For now, it isn’t recommended to trigger both inputs at once since it would increase the delay to about 7ms on either output (though it seems to mostly concern output 2).
(insert delay table)
## Code and wiring
Code was written in C language using PlatformIO with an Arduino Nano (ATmega328P). The program is interrupt based and works as follows:
-	Each time a rising edge is detected on the input, the corresponding interrupt routine is called and sets its related output to HIGH (+5V).
-	Interrupts also trigger a timer that will count for 50ms, duration after which the output is reset to LOW (0V).
-	Since both interrupts cannot be executed at the same time, latency is increased in the event of both inputs being triggered at once.
Down below is a diagram showing how the board and external components are wired up. A voltage divider is applied on both output pins to comply with the voltage input range of the Biosemi Analog Input Box (which allows -1 to +1V)
(insert image)
# Future Version
Only two I/O pairs are physically available on the device. So far, the combination of the two (triggering both inputs simultaneously) has been used as 3rd condition in experiments, which isn’t ideal since it increases latency as mentioned above. In the next version, more I/O will be added to the box to facilitate the implementation of new conditions.
