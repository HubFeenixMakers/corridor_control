# Fan Control

Trying to decide which fan to use and how to control it.

# Test

Basic maths says even some 80, but definitely 92mm PC fans should move enough
air in a standard 15m2 room, ie change the room air in 2 hours.

Since lower rpm usually means quieter, we are also testing 120mm.

## List of fans

All tested fans are on the quiet side. Some have it in the name, but they are
all under 20db under full load. Some have pwm control built in, which i am
thinking is less relevant than i thought.

In my setup i am testing with a Pi Pico and measuring with a **telephone**
(Sound Meter), from about 50cm and 2m. Not too accurate, but ok, ambient at
6-9db.
15m2 at 2.5 m height is about 20m3 / h for compliance.

Fan      |  mm  |  V  | mA  | Wire | rpm  | m3  | db | 40cm | 1m  | Notes
---------|------|-----|-----|------|------|-----|----|------|-----|-----
Zephyr   |  60  |  12 | 110 |  3   | 2000 | 17  | 18 |  10  | 16  | Notes
Zephyr   |  80  |  12 | 160 |  3   | 1400 | 47  | 14 |  40  | 13  | Notes
Zephyr   |  92  |  12 | 140 |  3   | 1300 | 57  | 14 |  45  | 14  | Notes
Zephyr   | 120  |  12 | 180 |  4   | 1400 | 81  | 15 | 50cm | 2m  | Zapped

## Conclusions

So far the fans ahve been surprisingly quiet. At close proximity the phone seems to pick up the air movement as noise. It was a scenario created to distinguish
the leels better, it would be impossible to get this close. An average real life
distance would be 2-3m, but at that distance all the fans a are too quiet to
measure (a good thing!)

# Decisions
