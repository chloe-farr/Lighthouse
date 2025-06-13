# /code
This directory contains Arduino sketches used to test and validate subsystem connectivity for the Helios sun simulation subproject of Lighthouse, and scripts to prepare data.

Note that only partial mapping has been implemented due to electronics issues, but the pipeline is designed and documented.

## Pipeline
- Obtain roll angle from IMU via NodeMCU (ESP8266), where the NodeMCU acts as a Wi-Fi Access Point (AP)
- Convert roll angle to solar elevation
- Map solar elevation to a clock time (calendar day), assuming a fixed geographic location
- Interpolate meteorological dataset based on the derived time to extract relevant values (radiation, temperature)
- Estimate illuminance or color temperature using extracted values
- Map illuminance or color temperature to RGB
    - Will use the kelvin-rgb Python library to convert color temperature to RGB

## Scripts
- (test_MCU_MPU.ino)[./test_MCU_MPU.ino]: Verifies MCU and IMU (MPU model) serial connection.
- (test_MCU_MPU_LED.ino)[./test_MCU_MPU_LED.ino]: Stub for LED test integration; checks MCU → LED output.
- [nc_converter.py](./nc_converter.py): Converts .nc data to binary data in csv format.
    - `python nc_converter.py <path_to_nc_file> var1,var2,var3`
    - e.g. `python nc_converter.py ../data/cesar_surface_radiation_lb1_t10_v1.0_202502.nc SWD,TSLWU`

## Planned Scripts
- test_helios_system.ino: Placeholder for full simulation logic using IMU roll angle.
- imu_to_elevation.py (or .ino): Converts roll angle to solar elevation.
- elevation_to_dataset.py: Retrieves matching solar radiation value from dataset.
- radiation_to_rgb.py: Maps radiation to approximate color temperature, then to RGB.
    - will use the [kelvin-rgb](https://github.com/esemeniuc/kelvin_rgb) python library to convert color temperature to RGB. 

