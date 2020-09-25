# EkoParty - Advanced Fuzzing Workshop

## Requirements

All you need for the workshop is:
- A running Linux system with an internet connection
- Latest version of AFL++ installed on the system (https://github.com/AFLplusplus/AFLplusplus#building-and-installing-afl). You can download AFL++ source code at https://github.com/AFLplusplus/AFLplusplus/releases.

### Virtual machine

You also can find an **.OVF virtual machine** with everything already set up for the workshop [here](https://drive.google.com/file/d/1UydxinlwKD847JHdbenO5gv7Xy7p3vJO/view?usp=sharing)

- VM credentials: fuzz/fuzz

After booting the VM, open a terminal and go to 
	```Desktop -> WORKSHOP -> Fuzz 0 -> unrtf```

Then, type:

	afl-fuzz -i ./tests -o afl-output  -- ./bin/unrtf --verbose -P ./lib/unrtf/ @@

If all it's ok, you'll be able to see a lot of AFL crashes :)

## Rules

- It's a CTF-style hands-on workshop.
- There will be 3 different challenges. The goal is to find a reproducible bug on each of them.
- We're looking for exploitable vulnerabilities. In order to be the winner of a challenge, you must provide a crash/PoC. "Theoretical bugs" or code warnings are not welcome, sorry.
- Challenges are intended to be solved by fuzzing, but creative approaches will be encouraged.
- During the workshop you will be able to ask me any questions you might have (via a private message). Please don't share solutions while the challenge is live.
- I will give you some hints and tips before and during the challenge.
- After each challenge, I will show my solution and I will explain it to you.
- There may be more than one correct solution.


### Awards

The winner of each challenge will receive a coupon to spend in [GitHub Shop](https://github.myshopify.com/). Second place will also be awarded.

YOU CAN SEND ME THE CRASHES TO MY TWITTER ACCOUNT [@nosoynadiemas](https://twitter.com/Nosoynadiemas)

## Fuzz Challenge 1 - ESIF (Extremely Stupid Image Format) [40 minutes]

WILL BE MADE PUBLIC ON Sep 25, 17:30 ART

Build:

    gcc EkoParty1.c -o EkoParty1 -w -lcrypto -lssl

Run:

    ./EkoParty1 example.ESIF output.ppm

## Fuzz Challenge 2 - Crazy HTTP server [50 minutes]

Build:

    gcc EkoParty2.c -o EkoParty2 -w -lz

Run (must be run as root):

    ./EkoParty2

## Fuzz Challenge 3 - Check your grammar
