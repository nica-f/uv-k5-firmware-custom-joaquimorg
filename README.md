# UV-K5 Open Radio Firmware

## ..... Work in PROGRESS .....

## Open implementation of the Quansheng UV-K5/K6/5R firmware

This is a very customized version of DualTachyon's open firmware found [here](https://github.com/DualTachyon/uv-k5-firmware) ... a cool achievement !

> [!WARNING]  
> *Use this firmware at your own risk (entirely). There is absolutely no guarantee that it will work in any way shape or form on your radio(s), it may even brick your radio(s), in which case, you'd need to buy another radio.*

> [!WARNING]
> *After some unfortunate incidents by users I'm going to put this warning and disclaimer up. DO NOT attempt to transmit without the proper precautions in place. Transmitting 5W of RF energy centimetres away from a PC can LITERALLY destroy it, it's almost like an EMP at that distance. Get your antenna away from the PC.*

Anyway, have fun.


## Credits

Many thanks to various people on Telegram for putting up with me during this effort and helping:

* [egzumer](https://github.com/egzumer/uv-k5-firmware-custom)
* [DualTachyon](https://github.com/DualTachyon)
* [Mikhail](https://github.com/fagci)
* [@Matoz](https://github.com/spm81)
* [OneOfEleven](https://github.com/OneOfEleven)


## Other sources of information

[ludwich66 - Quansheng UV-K5 Wiki](https://github.com/ludwich66/Quansheng_UV-K5_Wiki/wiki)<br>
[amnemonic - tools and sources of information](https://github.com/amnemonic/Quansheng_UV-K5_Firmware)

## License

Copyright 2023 Dual Tachyon
https://github.com/DualTachyon

Copyright 2024 joaquim.org
https://github.com/joaquimorg

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.

## Example changes/updates

<p float="left">
  <img src="/images/image1.png" width=300 />
  <img src="/images/image2.png" width=300 />
  <img src="/images/image3.png" width=300 />
</p>

Video showing the AM fix working ..

<video src="/images/AM_fix.mp4"></video>

<video src="https://github.com/OneOfEleven/uv-k5-firmware-custom/assets/51590168/2a3a9cdc-97da-4966-bf0d-1ce6ad09779c"></video>

# My changes to the main branch

- Changes to Spectrum :
  - Frequency Presets
  - Frequency in Bold
  - Show channel name

<p float="left">
  <img src="/images/spectrum_v2.jpg" width=300 />
</p>

- Main display

<p float="left">
  <img src="/images/main_v2.jpg" width=300 />
  <img src="/images/main_8_v2.jpg" width=300 />
</p>

- Messenger, send and receive short text messages, write with T9 keyboard.

<p float="left">
  <img src="/images/msg_1.jpg" width=300 />
  <img src="/images/msg_2.jpg" width=300 />
</p>

Keys :

- "*" - Change keyboard, Upper case, Lower case, Numeric.
- "0" - Space, except in numeric mode.
- "F" - Backspace
- "(Long press) F" - Clear all messages
- "UP" - Recalls last sent message
- "M" - Transmits message in the frequency of active VFO.
- "Exit" - Close application

<p float="left">
<img src="/images/UV-K5 - keypad - T9.jpg" width=600 />
</p>
