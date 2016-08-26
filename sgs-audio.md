sgs-audio
---------
the SGScript audio system

- supported formats: uncompressed WAV, OGG
- streaming support for .ogg files
- additional features:
 - pitch shifting
 - volume fading
 - volume groups
 - 3D sound support
 - suspension of processing (pause)
- compiles on Windows / Linux

Usage
-----

- create the sound system with `sgs_audio_create()`
- create emitters, `load()` sounds into them, configure the sound system
- `play()` the created emitters

Testing
-------

- the sound system requires OpenAL to be installed (Windows/Linux) or the OpenAL.dll and wrap_oal.dll files to be otherwise available for immediate loading (Windows only)
- run `sgsvm audio-test.sgs` from the `bin` directory to do a test run
