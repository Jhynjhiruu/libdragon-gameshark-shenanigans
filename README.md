This tool can dump the contents of an N64 cartridge made with modern Libdragon via digital video.

Compiling it will produce a file called `fw.bin`. Flash that to a GameShark or Action Replay using SharkSaver64, then put the game you want to dump onto the GameShark and put the GameShark in your N64.

You'll need an HDMI-modded N64 or a clone with HDMI out, as well as a way to capture HDMI at high quality. Once everything is set up, turn on the N64, which will boot to a black screen. Start recording HDMI, then press the A button on controller 1. You should see a lot of rapidly flickering images.

After about 1 minute 40 seconds, the pixels on the screen will turn green. At this point, the dump is complete. Stop the recording.

Now, run the video file through the other half of this tool to produce your dump.

# Building

Good luck!

# Licence

Most of the code in the src/bootloader directory is taken from Libdragon. I realised after I'd finished this tool that the entirety of src/bootloader is unnecessary and it'll work just fine without it. Oh well.
