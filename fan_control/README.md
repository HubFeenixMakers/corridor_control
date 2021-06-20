# Testing platforio and esp

## Rationale

I notices that i have to start smaller, make test.

Also, while python was great, the library handling was (really) _bad_ .

Since PlatformIO finally allows to add code to git and share it i chose that
over plain Arduino.

And the Basic is such an unbeatable package of esp, power supply, relay and case.
Even with ce mark. So here we go...

## File structure

This whole directory is a PlatformIO project. Testing . . .

I am not sure what parts are machine specific and thus have to be left out.

## Esp

Or to be precise a SonOff Basic v1.3 is the target.

I have this wired with an UNO as a programmer according to https://www.youtube.com/watch?v=qOztsbEfg1g
This just bridges the uno and uses its usb chip to pass the programm on.
The net says a usb to TTL programmer is the "normal" way, just have not bought one.

## Code

The actual code i am trying to write will use the Basic to switch a Fan.

I will add 2 DHT22 in a case like this https://www.thingiverse.com/thing:4852992

The sketch will simply compare temeratures and switch the relay on/off
