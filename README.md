# Gait Analysis Library
This library will estimate four gait parameters when given a dataset of
vertical acceleration values (m/s^2).

The four parameters estimated are:

* Step Length (m)
* Cadence (step/min)
* Total time (s)
* Gait speed (m/s)

## Dataset criteria
The collected data must be from an accelerometer mounted close to the patient's
L5 vertebrae. The sensor should be pre calibrated against a 90 degree block.
Only data from the vertical axis is required.

## Installation
Simply copy both the gait_func.c and gait_func.h files to the same 
directory as the Arduino script.

## Usage
Include the library header near the top of the Arduino script:

     #include "gait_func.h"

## Example
The following pseudocode demonstrates how to use the library functions. The
example data is collected at 100Hz for 5 seconds. Therefore n = 500 and ts
(sample time) = 0.01. The value of l is the height of the sensor from the
ground and is set as 1.1m in this example.

     float y-data[500] = vertical_acceleration_data();
     step_t my_step = calculate_step(500, 0.01, 1.1, y-data);

     Serial.println(my_step.length);
     Serial.println(my_step.cadence);
     Serial.println(my_step.time);
     Serial.println(my_step.gait_time);
