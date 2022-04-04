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

## Session Calibration Example
Session calibration is performed everytime time device is started. It
compensates for the mounting angle of the sensor once it is on the person's
back. To perform the calibration:-

1. Take X and Y axis measurements. Either single readings or an average. These
   values must be stored for use in step 4.
2. Pass these readings to the get_calibration_angle() function. Save this angle
   value for use in step 4.
3. Collect your data set.
4. Each X or Y axis value needs to be passed into either get_corrected_x() or
   get_corrected_y(). These return the corrected values using the angle
   measured in step 2.

## Step Calculation Example
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

If excessive integration error is present it might be better to use linear
regression to improve the data. The method to use linear regression is the same
execpt:

     step_t my_step = calculate_step_linreg(500, 0.01, 1.1, y-data);
