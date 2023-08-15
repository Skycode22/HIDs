# 𝕬𝖉𝖊𝖑𝖍𝖊𝖎𝖉 Plus

The Adelheid Plus is a fork of [Flookay's Adelheid case and PCB](https://github.com/floookay/adelheid).

![adelheid_plus_resized](https://user-images.githubusercontent.com/800930/150452003-4a898895-5934-4bcd-ba8f-0a1653da499b.jpg)
*Photo by yosoyjose*

Repository folders:

- `pcb`: KiCad files
- `pcb-mu`: KiCad files for Atmega32u4-MU chip (same pinout as Atmega32u4-AU, but smaller footprint)
- `case`: High profile case files
- `wrist-rest`: Wrist rest files

I modifed the pcb a bit to accept an Atmega32u4-MU since those seem to be in stock more often.

## Changes in this fork

- USB-C connector
- Option for 2U backspace
- Extra `B` key
- Option for rotary encoder at `F13` position
- Option for 2.25U left space + 1.25U modifier combo (requires modification to plate)

## Layout

[Keyboard-Layout-Editor](http://www.keyboard-layout-editor.com/#/gists/57b8a9ee4aeb89308701e20eda9b5dfc) 
![layout](https://user-images.githubusercontent.com/800930/150452424-d3dea0da-3d32-47d5-a4fc-80a83637e7d6.jpg)

## Firmware

See my Vial fork for the [firmware files](https://github.com/dcpedit/vial-qmk/tree/dcpedit/keyboards/dcpedit/adelheid_plus) on the [`dcpedit` branch](https://github.com/dcpedit/vial-qmk/tree/dcpedit).  I opted for Vial since it allows you to program the rotary encoder through their GUI: https://get.vial.today/