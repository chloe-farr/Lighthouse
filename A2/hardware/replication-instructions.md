# Steps to Replicate

% TODO: Add step by step pictures

## Build 3D Model

Laser cut the arch and vehicle using the SVG files provided in the project repository (\laser_cut). These files are properly scaled, so material thickness is preserved regardless of scaling applied in your software. Be aware that joint sizes will be affected if the file is scaled non-uniformly, which can interfere with assembly.


1. Laser cut the arch and vehicle using the SVG files provided in the project repository.
    - Glue the thin arcs (two stacked) to the inner side of each arch engraved with angle markers. These act as rails and barriers for the vehicle’s wheels.
2. Glue together noninvasive parts before wiring. Use Gorilla Glue (in small amounts, applied carefully) unless another adhesive is explicitly stated. Take your time when gluing. These steps pose the highest risk to the integrity of the wood, and error will likely require a new frame to be cut.
    - Glue LEGO axles to the laser-cut chassis piece. Do not attach wheels until the very end, as doing so early can stress and damage the wood.
    - Glue axle supports to the short edges of the wooden chassis piece.
3. Adhere neodymium magnets to the engraved divots on the outer six pieces of the vehicle housing. Do not glue magnets to the chassis or shelf. 
    - Check magnet polarity carefully before gluing to ensure corresponding faces attract. 

    **CAUTION:** Neodymium magnets are extremely powerful. Do not place anything fragile between two magnets. Keep them away from the MPU6050 sensor, as they can interfere with its readings.

## Wire Microelectronics

Wire electronic components according to the wiring schematic. 

*Notes:*
- To ensure jumper wires aren’t defective, use a multimeter’s continuity or resistance mode before making any connections (during breadboard testing or committing to solder).
- Test connections with a breadboard and male header pins shipped with the electronic components. 
- You will remove the male header pins from NodeMCU prior to soldering, as it reduces its footprint within the vehicle. Only do this once all connections have been tested with the breadboard, as testing is challenging once they are removed.
- Before soldering, put small pieces of heat shrink (5-10mm as space allows) somewhere along the wire sheathing. They should remain on the wire once soldered on both ends.
- When soldering, apply solder when connecting, use desoldering pump when removing solder.
- Melt heat shrink (can use heat from soldering iron -- don't touch the two together-- heat gun, or blow dryer).
- Label wires or use color-coded heat shrink for clarity in case of future troubleshooting.
- To test code, open any referenced .ino files in the Arduino IDE. Connect your board, and port, and set the Serial Monitor Baud to mach that in the script's `setup()` function.
    

1. Connect the MPU6050 to the NodeMCU.
2. Connect NodeMCU to your computer via USB. Proceed once Serial Monitor displays `Board is alive!` on loop.
3. Unplug and disconnect NodeMCU from all power/data sources and other components. Desolder male pins from the board. Solder connections and retest to ensure the board remains functional. If it no longer 
4. Connect NodeMCU and MPU. Don’t reverse SDA/SCL.
5. Confirm recognition of both the NodeMCU and MPU6050 by uploading [test_MCU.ino](../A2/code/test_MCU_MPU.ino) to your NodeMCU from the Arduino IDE. This tests whether the board is properly functioning. readings are successfully displayed via the Serial Monitor. 
> The following steps are theoretical and untested due to failure at this stage during development.
6. On the boost converter, adjust the small brass screw counterclockwise to set output to 5V. Use a multimeter in DC voltage mode to confirm. The prototype’s boost converter shipped with an 11.12V default.
7. Connect the LiPo battery, charger board, boost converter, and MPU. Use the multimeter to verify successful voltage delivery, then test manually.
8. Solder connections and retest.
9. Connect the LED strip to the NodeMCU. 
> **Do not** do this until all prior steps are verified. The LED draws more current than the USB connection can safely provide. It should only be powered via the LiPo battery (3.7V, 320mAh). Attempting to run the LEDs on USB power may damage components.
10. Solder connections and retest.
    - Upload [test_helios_connections.ino](../A2/code/test_helios_connections.ino) to the NodeMCU. This verifies that all connections are working while powered via the battery setup.
    - Upload [test_helios_system.ino](../A2/code/test_helios_system.ino) to the NodeMCU to begin running the full system.

## Adhere Microelectronics

Once all components are successfully connected and operational, affix them inside the vehicle housing. Choose your adhesive medium based on desired permanence. For temporary installation, mini zip ties or double-sided foam tape are sufficient. For a more secure hold, use hot glue. Avoid permanent adhesives as they will hinder future repairs.

Insert and glue the chassis perpendicularly into the back piece of the vehicle frame using the tongue-and-groove joint. Attach the two long sides to the back piece at 90°. Attach the remaining sides magnetically. Finally, add the wheels, bracing all sides to prevent joint stress.

Move the car along the arch manually to test the LED strip’s behavior. As the vehicle ascends, the LED should transition in both brightness and color temperature. At the apex (solar noon), the two central LEDs should be lit. Upon descent, the LED should shift toward the strip’s end closest to the base of the arch, simulating sunset.

At this stage, begin debugging and refining the logic that maps angular IMU data to solar-referenced LED output.