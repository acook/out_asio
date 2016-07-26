-------------------------------------------------- -------
  out_asio (dll) .dll (dll version) Ver. 0.67 (2006/10/4)
-------------------------------------------------- -------


* This plug-in

  WINAMP5 is ASIO output plug-in for.

  To use this plug-in, sound card that supports ASIO 2.1
  De driver is required.

  ---------------------------------
    ASIO Technology by Steinberg.
    http://www.steinberg.net/
  ---------------------------------


* Characteristic

- Light loads because the output without going through the Windows.
- Raw data because it does not pass through the Windows of the mixer is output as it is.
  (Depending on the make of the sound card and the ASIO driver, but in general is Lisa
  Data processing such as sampling is not carried out. )
Latency is small.


* And supported data format

Sound format
    Int8, Int16, Int24, Int32, Float32, Float64

Device format
    Int16MSB, Int24MSB, Int32MSB,
    Float32MSB, Float64MSB,
    Int32MSB16, Int32MSB24,
    Int16LSB, Int24LSB, Int32LSB,
    Float32LSB, Float64LSB,
    Int32LSB16, Int32LSB24

Sampling frequency
    Depending on the device

• Number of channels
    Depending on the device


* How to install

· WINAMP5 is in the bottom of the folder that is installed Plugins folder
  Please do the area just out_asio (dll) .dll to da.

• In the option setting WINAMP5 ASIO output plug-in (dll version) the selection
  Please be 択.
  (WINAMP5 - Options - Preferences ... - Plug-ins - Output dialog
  - Output plug-ins)


* Option settings

    Device:
      (Standard = top)

    Priority of the thread:
      Normal
      Above normal
      Highest
      Time critical
      (Standard = Time critical)

    Buffer size:
      0 to 63
      (Standard = 7)

    Shifting the output channels:
      0-99
      (Standard = 0)

      For example, set to 0 (standard), the
        Input channel 0 -> Output channel 0
        Input channel 1 -> Output channel 1
      Now, if set to 1,
        Input channel 0 -> Output channel 1
        Input channel 1 -> Output channel 2
      It will be.

    Gapless mode (to seamlessly between songs):
      Not to gapless mode = Do not check
      To gapless mode = check
      (Standard = unchecked)

    To convert one channel of data into two channels:
      Do not convert = Do not check
      To = check to convert
      (Standard = checked)

    Using direct monitor (using the direct monitoring function of the sound source
                                                             To):
      Do not use = Do not check
      To = check to use
      (Standard = unchecked)

    Resampling - Enable (to enable the re-sampling):
      Not enable = Do not check
      To = check to enable
      (Standard = unchecked)

      Sound format after resampling will be Float64.

    Resampling - the priority of the thread (resampling thread Yu
                                                             Sakido):
      Normal
      Above normal
      Highest
      Time critical
      (Standard = Highest)

    Targeted at the time of sample rate (resampling - resampling
                                               Tsu To sample rate):
      11025Hz ~ 192000Hz
      (Standard = 88200Hz)

    Resampling - Quality:
      Low
      Normal
      High
      Top
      Ultra
      (Standard = Top)

      If you want to sound out when you increase the quality, increase the buffer size
      please.

  Since the standard value was set according to my environment, the optimum value by environment differences
  I think that will come I.


* Ver. 0.67

And change the design of the configuration dialog.

* Ver. 0.66.2

• When the gapless mode has stopped playing in the effective state, ASIO driver
  Was not to unload.

* Ver. 0.65.1

And change the wait method of synchronization objects.

* Ver. 0.64

Resampling - Add the Ultra in quality.
  If you want to sound out when you increase the quality, increasing the buffer size Shiteku
  Please.

* Ver. 0.63

- Change the string manipulation functions to those of a secure type.

* Ver. 0.62.1

And change the processing of the hook in the procedure of the main window.

* Ver. 0.61.2

Resampling - add a Normal to quality.

* Ver. 0.60

- Change the compiler in Visual C ++ Ver. 8.0.50727.42.

* Ver. 0.59.2

And change the standard of the priority of the resampling thread to Highest.
  Priority seems to be too low in the Above normal ....

* Ver. 0.58

- Gapless mode change option settings during a performance stop in the enabled state
  When it, Fixed settings has not been reflected.

* Ver. 0.57a

- A little faster up-sampling of the SSRC.
And change the standard of the priority of the resampling thread Above normal.
  Priority seems to be too low in Normal ....
Change or the compiler in Visual C ++ Ver. 8.0.50215.44 Beta2.

* Ver. 0.56

And change the standard of the priority of the resampling thread to Normal.
  When the priority is high, because the environment there was a noise may come out lower want
  did.

* Ver. 0.55

- Change the compiler to Intel C ++ Ver. 9.0.019.

* Ver. 0.54

- Fixed a bug related to SSRC downsampling.
  For more information,
  http://www.hydrogenaudio.org/forums/index.php?showtopic=34320
  Please refer to.
- Change the compiler to Intel C ++ Ver. 8.1.028.

* Ver. 0.53a

And change the ASIO SDK to Ver. 2.1. (It does not correspond to the DSD.)
- Change the compiler to Intel C ++ Ver. 8.1.026.

* Ver. 0.52

• When you change the option set during a performance, to reflect the immediate settings
  I was in.
- It was to be able to change the settings of the ASIO driver during a performance.

* Ver. 0.51

And change the process to hook the main window.

* Ver. 0.50a

Change the timing to close the device.
  Depending on the environment, there was not the data is output to the end.

* Ver. 0.49

In · Ver. 0.48, the ability to convert one channel of data into two channels
  Fixed did not work properly.

* Ver. 0.48

And change the process of shifting the output channel.
- Change the compiler to Intel C ++ Ver. 8.1.022.

* Ver. 0.47

- Change the compiler to Intel C ++ Ver. 8.1.019.

* Ver. 0.46

In · WINAMP Ver. 5.04, the gapless mode did not work properly
  Fix.
- Change the compiler to Intel C ++ Ver. 8.0.052.

* Ver. 0.45

- Change the compiler to Intel C ++ Ver. 8.0.050.

* Ver. 0.44

- While sound is after playing the end of the environment be a (short loop state)
  Fix was there.

* Ver. 0.43

- Change the compiler to Intel C ++ Ver. 8.0.049.

* Ver. 0.42

- Change the compiler to Intel C ++ Ver. 8.0.048.

* Ver. 0.41

- Change the compiler to Intel C ++ Ver. 8.0.047.

* Ver. 0.40d

• In extremely small data, Fixed could not start playing.

* Ver. 0.39

Resampling continuous playing and using the gapless mode with a valid state
  It was when, Fixed GetOutputTime had advanced earlier than the original playing time.
  The second song later, the movement of the music and Visualization had shifted.

* Ver. 0.38

When resampling is enabled, it has been able to output the data immediately before the performance ends is
  Fixed did not.
  Ver. 0.35 change, it so can not output data just before the play ends is
  Incorrectly me.

* Ver. 0.37

When resampling is enabled, return Open return value (max latency) to generous
  It was so.
  Actual latency is greater than the max latency and Visualization of the dynamic
  Kiga is so funny. (WINAMP5 is, Visual use this return value
  We expect or not than has secured a buffer for ization. I
  Oh, the actual latency using the GetOutputTime and GetWrittenTime
  It seems to be calculated. )
  Really to calculate properly the latency of the SSRC, return what was added to it
  As Will is good to to but, SSRC of records at the time the Open is called
  Because it is not possible to calculate the latency, appropriately latency of generous (2000ms)
  Death was to return by adding.

* Ver. 0.36

And modify the calculation of how it was wrong of the maximum latency.
  Because ASIO is a double buffer,

  ASIOGetLatencies (& InputLatency, & OutputLatency);
  MaxLatency = OutputLatency * 2;

  But it is the maximum latency ....
And change the method of calculating the WrittenTime.

* Ver. 0.35

Resampling is reduce the load at the time of effectiveness.
• The re-sampling so as to run in a different thread, set the priority of the thread
  It was to be constant.

* Ver. 0.34

• When you use the DSP plug-ins, Fixed could not start playing.

* Ver. 0.33

Change the method of calculating · OutputTime and WrittenTime.
  OutputTime is, it has to be calculated taking into account the latency of the device
  It was. The operation of the Visualization is I think that was smoothly.
  WrittenTime, has to be calculated taking into account the latency of the SSRC.
  It uses the QueryPerformanceCounter API to calculate the latency.
  In an environment in which this API is not available, use the timeGetTime API as an alternative
  Then, but at that time you will not be able to calculate the exact latency. (TimeG
  Because of the poor accuracy of etTime. )

* Ver. 0.32a

And change the method of calculating the OutputTime and WrittenTime when you seek.

* Ver. 0.31

And change the method of calculating the latency.

* Ver. 0.30

The first time you play the · WINAMP5 after startup, Fixed a fall.

* Ver. 0.29b

• When you seek to the end of the song, it Fixed a thing that locks up.

* Ver. 0.28c

Change or the compiler in Visual C ++ .NET Ver. 7.1.3091.

* Ver. 0.27c

Of the device format Int16MSB, Int24MSB, Int32MSB, Float32MSB, F
  loat64MSB, Int32MSB16, corresponding to Int32MSB24.

* Ver. 0.26i

And responding to Float32 of sound format.

* Ver. 0.25

Resampling is continuously played using a gapless mode with a valid state,
  When the sound format is switched between songs, the operation was funny
  Fix.

* Ver. 0.24a

And change the timing of when the play started.

* Ver. 0.23

And retaining the clipping processing of resampling process the final stage, only in the final output stage,
  It was to be the clipping processing.

* Ver. 0.22

And responding to Float64 of sound format.
  When the conventional (Int delivery),

  Input plug-in operation (Float) ->
  Input plug-in output (Int) ->
  Output plug-in input (Int) ->
  Resampling (Float) ->
  Output plug-in output (Int)

  Since it had been converted, but I was there is a possibility that the error is accumulated at the time of integer conversion,
  By passing the data in Float64,

  Input plug-in operation (Float) ->
  Input plug-in output (Float) ->
  Output plug-in input (Float) ->
  Resampling (Float) ->
  Output plug-in output (Int)

  It becomes a path that, you can minimize the integer conversion.

  However, input plug-ins that can output Float64 format, the current
  Jae, in_mpg123.dll Ver. 1.18y ot34 only does not exist later.
- Change the sound format to Float64 after resampling.

* Ver. 0.21

When resampling is enabled, it has been able to output the data immediately before the performance ends is
  Fixed did not.
  A buffer for resampling was flushed with the tail end of the data stream
  Because did not.
  However, in the gapless mode it does not have this fix. Final for each song
  When you flush the re-sampling buffer at the end, the next music convex smoothly
  Because it does not want Do not ....
When the resampling was seeking an effective state, this the performance would be stopped
  Fixed a door.

* Ver. 0.20c

Resampling - to abolish the high-speed mode, and to be able to select a quality.
  Conventional high-speed mode of Low, quality-oriented mode is equivalent to High.
  In the Top setting, it will consume a lot of CPU time. CPU resources of a decoder
  If you like the sound out with vinegar conflict occurs, the priority of the present plug-in thread
  Please try to reduce the degree.
And change the standard of the thread priority of the Highest.

* Ver. 0.19

Resampling - change the parameters of the quality-oriented mode.

* Ver. 0.18

· The SSRC library expanded so that it can be output in 32bit precision, resampling
  The data after ing and to output at 32bit.

* Ver. 0.17

• When resampling is enabled, the number ms performance data backward (high-speed mode),
  Fixed a few tens of ms was not (quality-oriented mode) shift.
  It was the failure of the SSRC library you are using. Using the same library
  Mr. and are Peter of the output plug-in resampling module
  Also it seems to have the same symptoms in Le.

* Ver. 0.16a

- The calculation method of the latency when the resampling was seek a valid state
  Change.

* Ver. 0.15

- Speeding up the operation speed when resampling is enabled.
When resampling is enabled, Starring in the case where the number of channels has been changed in the middle of
  Fixed was not able to do so.
When resampling is enabled, the there was a case of noise when you seek out
  Modify.
- - Change the default settings in the resampling Fast mode] to quality-oriented mode.

* Ver. 0.14

And distributing provisions to the LGPL, publish the source file.
· SSRC that Shibata-san has been created (high-quality sampling rate converter) the tower
  Mounting.
  When the sampling rate after the input data and the re-sampling of the same, SSRC
  It does not pass through.
  So far, the number of bits after the re-sampling is 24bit, dither is disabled solid
  It has been constant.
  Order to improve the calculation accuracy, the output bits of the decoder side is the highest precision (32bit)
  More had been would be good.
- Change the compiler in Visual C ++ .NET Ver. 7.1.2235 Beta.
  The compiler processor specific optimization options for Pentium4, Athlon
  It has changed. (New feature of Visual C ++ 7.1.)

* Ver. 0.13

• When converting from a floating-point type to an integer type, close to the value after the decimal point is the best (middle
  Changed to round to the nearest even number) in the case of. (Previously it was rounded off.)

* Ver. 0.12

And change the standard of the buffer size to 7.

* Ver. 0.11

• In gapless mode, sampling rate tea from a previous performance data
  When the tunnel number has changed, Fixed delay calculation of VIS data was funny.

* Ver. 0.10

- It was to be able to play in gapless.
  In such as when a continuous performance from the CD, because between the song will not break is useful.
  Conditions that can be played without interruption, formerly of the performance data and the sampling rate
  - The number of channels is only the same time. The number of bits does not have to be changed.
  When using this mode, better to leave the buffer size to larger
  It would be nice.

  (Note) ASIO Device even when the playing end state finished playing the song until the last
         Chair will remain in the open position. Applications This is the time of the next song start playing
         So you do not cut, is to deliberately leave open the device.
         If you want to close the device, press the stop button by playing again or,
         Please exit the WINAMP5.

And expand the maximum of the buffer size to 63.

* Ver. 0.09

Sound Format -> a little fast device format conversion routine
  Of.

* Ver. 0.08

· Ver. 0.07 Int24 of sound format was not handled properly
  Fixed.

* Ver. 0.07

· Bit depth drop the - when (32bit> 24bit, etc.), the following calculation result decimal point
  It was to be rounded off.

* Ver. 0.06

- From the beginning until the buffer size of the ASIO driver was not able to output
  Fix.

* Ver. 0.05a

• The output channel was as shifting.
  For example, set to 0 (standard), the
    Input channel 0 -> Output channel 0
    Input channel 1 -> Output channel 1
  Now, if set to 1,
    Input channel 0 -> Output channel 1
    Input channel 1 -> Output channel 2
  It will be.
And change the standard of the thread priority of the Time critical.

* Ver. 0.04

- Playing for the thread of the callback routine through the window procedure
  Cease to have been calling, call via the user-mode asynchronous procedure
  It was so put out.
  This was difficult to sound out than conventional.
And change the standard of the buffer size to 3. (Because it was less likely to sound out.)
And reducing the maximum of the buffer size to 31.

* Ver. 0.03

· 1 channel data is converted into two channels and can be output.
  When you play one channel of data to enable this feature, the second Chang
  It will also ensure that the data of the first channel is output from the panel.
And change the standard of the buffer size to 15. (Out_asio.dll is cnv_pcmasio.wac
  Since the structurally easy sound interruption as compared with. )
And expand the maximum of the buffer size to 63.

* Ver. 0.02b

And modify Int8 of it was not able to play normally of sound format.
· The (ASIO driver of the buffer size * 4 * (buffer size + 1)) Writ
  e () when you did not divisible by data size per once, Do not able to start playing
  Modify the bought was for.

* Ver. 0.01

First version.


* How to compile

  Please compile read the out_asio.sln in Visual C ++ 8.0.

  Included binary was compiled with Visual C ++ Ver. 8.0.50727.42.


* Other

  Distribution provisions will follow the LGPL.

  When it was sound interruption occurs, the priority and the buffer of the process threads
  Please try to the adjustment of the size. Adjustment of the buffer size to the ASIO driver
  If you find there is a section function, please try to adjust even more of there.

  When the buffer size of the ASIO driver is small too, at the start playing
  You may not be able to. Buffer of such ASIO output plug-ins such time
  Please try to increase the Asaizu.

  SSRC that Shibata-san has been developed tower (high quality sampling rate converter)
  It has been mounting. Thanks to Shibata's Developer.


  Oda-chan
  Web: http://otachan.com/
