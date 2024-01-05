# inspection-sys-AI-Arduino
Inspection system for a conveyor belt in a manufacture system using computer vision. The model was trained in Teachable Machine and it connects with an Arduino Leonardo board.

The code is based in the following Google project: https://experiments.withgoogle.com/tiny-sorter/view

This Arduino code controls a simple system with a conveyor belt, a good box, and a bad box. The system reads color information from a serial input and takes action based on the received color code. The color codes 1 and 2 correspond to the good and bad boxes, respectively. The system also checks the state of a robot using an input pin to determine whether it should take any action. The code is documented with comments to explain the purpose of each section and the actions performed in different scenarios.
