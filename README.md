# Stegacito

Hide a File inside a PNG image. 
One pixel = One Byte of data.
You can hide in the image image_width x image_height - header_size(265) bytes.

For example a 800x480 image can have **800 x 480 - 265 = 383735 bytes** ----> **383.735** kilobytes

Pixel in the image are alterated, 3 bits in the Red and Green and 2 bits in the Blue. So the Red and Green will varry in a range of 0-7 and the Blue 0-3.

# Schema

### Data inside Pixel
```

Pixel = rrrrrddd gggggddd bbbbbbdd
             ^^^      ^^^       ^^
             |||      |||       ||
             _____________________
                   ||||||||
           Data  = dddddddd
```

### Header
```
|C1|C2|C3|C4|C5|VE|S1|S2|S3|S4|N1|..|N255|

C1-C5 = ControlKeys to check if it's using this software.
VE = Byte that contain the version number.
S1-S4 = Uint32 that is equal to the size of the file, max file = 4go
N1-N255 = Contain the filename.
```
