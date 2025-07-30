## Arduino Stepper Motor Control

This sketch allows you to control a stepper motor via serial commands.

### Commands
- `u` → Move Up
- `d` → Move Down
- `s` → Stop

### Customization
- `STEPS_TO_MOVE`: Total steps per command
- `STEP_DELAY`: Speed control (µs between steps)

### Connections
- `STEP_PIN = 12`
- `DIR_PIN = 14`
- `ENABLE_PIN = 13`
