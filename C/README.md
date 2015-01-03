# Terminal Interface for CODE2040 API Challenge

The code in this repository will produce a robust terminal-side application for the CODE2040 API Challenge.
I have added a bit of defensive programming to the source code and have made strongly tested functions. Further, I
have refined a lot of the mechanics. The limiting factor in execution will be the time to make and receive HTTP requests.
This is *not* ready for final production, but has enough defensive programming to be suitable for public use currently.
I still need to parse and handle bad json and bad responses (i.e. The server's answer for submitting the incorrect value).

## How To Use

1. Download the source files
2. Run `make`
3. Execute `./interface`
4. When prompted, either:
  * Enter your credentials (if you are a CODE2040 applicant)
  * Enter `a` for both questions to trigger my credentials

## Debugging and Individual Stages

There are also options to run each stage independently. You can run `make register`, `make stageI`, `make stageII`, 
`make stageIII`, and `make stageIV` to run each stage on its own. This is mostly for debugging though as it prints the
JSON in a less than ergonomic format currently. (Useful for debugging, not for aesthetics. Hence, the change in the
interface's display of the under-the-hood values).

## Current Bugs

**Updated 03 January 2015** There is currently 1 (one) known bug:

1. Most of the time, when executing Stage IV, my output will be off by an hour. This has not happened in my Python or 
JS versions. After some [research](http://stackoverflow.com/questions/310363/how-to-add-one-day-to-a-time-obtained-from-time)
This may be a problem with my cygwin's GCC, and not with my code itself. It seems that when a date causes a shift from one
DST value to the other, cygwin's GCC does not recognize it and keeps the older DST setting. As such, sometimes my output will
be off by an hour. I tested it briefly with an online IDE and indeed it ran fine on there. I'd like to have a better grasp
on this outcome though.
