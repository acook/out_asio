# out_asio
This is the source code to a MediaMonkey/Winamp output plugin which talks directly to ASIO drivers. 

For more information see the README.en.txt or README.jp.txt files.

## Prerequisites 
Requires [Microsoft Visual Studio 2015](https://www.visualstudio.com/en-us/downloads/download-visual-studio-vs.aspx)
and a copy of the [ASIO SDK](http://www.steinberg.net/en/company/developers.html).

If your audio device doesn't have official ASIO drivers use [ASIO4ALL](http://www.asio4all.com/).

**NOTE!** The default configuration uses the AVX2 instruction set, remember to change it if you're building for older machines.

## Credits
- Created by: [おたちゃん](http://otachan.com)
- Updated for MSVS 2015 by: [Anthony M. Cook](http://anthonymcook.com)
- ASIO Technology by: [Steinberg](http://www.steinberg.net)
