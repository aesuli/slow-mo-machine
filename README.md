# Slow Motion Machine

A slow motion machine. Works by combining the action of an electromagnet that makes an object vibrate and a high frequency flickering light that "freezes" the motion.

Inspired to the [timeframe](https://github.com/cubic-print/timeframe) from Cubic Print.

I put in my machine four controls that allow me to set:

* the frequency of the electromagnet (to better find a resonating frequency for the object you place in the machine).
* the duty cycle of the electromagnet (intensity of the oscillation).
* the phase shift of the LEDs (speed of the slow motion effect).
* the duty duty cycle of the LEDs (intensity of light).

See it in action:
* Video 1: [![Video 1](https://img.youtube.com/vi/maoMhYfvcu0/0.jpg)](https://www.youtube.com/watch?v=maoMhYfvcu0)
* Video 2: [![Video 2](https://img.youtube.com/vi/vIDryuApn_g/0.jpg)](https://www.youtube.com/watch?v=vIDryuApn_g)
* Early prototype: [![Early prototype](https://img.youtube.com/vi/UeeFFY5VJrM/0.jpg)](https://www.youtube.com/watch?v=UeeFFY5VJrM)

---

The box.slvs file is a [Solvespace](http://solvespace.com) 3D model that I made to sketch my idea of the enclosing box.
Then [Cristina Galeotti](http://www.officinegaleotti.it/) ([fb page](https://www.facebook.com/OfficineGaleotti/)) optimized the model to make it printable.
The STL file are made by her.

<img src="box2_solvespace.jpg"  alt="Box" width="70%" />

---

BOM:


 * 1 Arduino Nano
 * 4 10k potentiometers
 * 2 1k resistors
 * 1 1N4001 diode
 * 2 NPN transistors
 * 1 LED strip (NOT programmable ones, which are slow)
 * 1 electromagnet

---

Circuit schema:

<img src="circuit.jpg"  alt="Circuit schema" width="70%" />

---

PCB:

<img src="pcb.jpg"  alt="pcb" width="70%" />

---

Oscillator with circuit on breadboard:

<img src="internals.jpg"  alt="Oscillator with circuit on breadboard" width="40%" />


