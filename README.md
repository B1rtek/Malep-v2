# Malep-v2
An image screwing up utility

This program takes an image, splits it into parts and outputs it based on the sequence you provide.

## How to use this awful thing

You open the console, go to the directory where you downloaded it, and type
```shell
$ Malep_v2
```
If you happen to have any images in supported formats in that directory (bmp, png, tga, jpg, gif, psd, hdr, pic), a list of those files will be printed out in the console, for example:
```
1: 22i8gsd3v4u61crop.png
2: 245_08022022.png
3: 24_27052021.png
Choose a file from the list:
```
You choose the file by entering a number next to the file that you're interested in "editing". Next step is entering the base sequence:
```
Name this image: maple
```
This will split the image into *n* equal parts, where *n* is the amount of valid characters in the sequence you entered (letters from a to z). You'll see the list of generated characters to use:
```
Generated characters:
m a p l e
```
In case your base sequence has a letter that occurs more than one time, every occurrence after the first one will have a number appended to it, like this:
```
Name this image: cinnamon
Generated characters:
c i n n1 a m o n2
```
The next step is to enter a new sequence, on which the new image will be based. You don't have to enter any spaces between characters, writing like this is just fine:
```
Write down the name of the new image using the generated characters: mon2cinn1a
New image sequence:
m o n2 c i n n1 a
```
Now the magic happens. The source image that was split into parts is used to create a new image based on the new sequence. Every part of the image has a symbol attached to it, which it got from the base sequence. The new sequence is just a list of these segments in any order you want. You can use every segments as many times as you want, whether it's 9000 or 0. After the image gets assembled, you'll see a message:
```
New image was saved to <original name of the file>Malep.png
```
or nothing if it failed for some reason. So, for example, this image:<br>
<img src="https://github.com/B1rtek/Malep-v2/blob/master/cinnamon.png" alt="Cinnamon" width="400"/><br>
With a base sequence `cinnamon` and a new sequence `m o n2 c i n n1 a` comes out as this:<br>
<img src="https://github.com/B1rtek/Malep-v2/blob/master/cinnamonMalep.png" alt="MonCinna" width="400"/><br>
An extreme (and extremely stupid) example of what you can do with this program is this:<br>
<img src="https://github.com/B1rtek/Malep-v2/blob/master/maple.png" alt="Maple" width="400"/><br>
With a base sequence `maple` and a new sequence 
```
Lorem ipsum dolor sit amet, consectetur adipiscing elit. Donec aliquam justo nec justo rutrum, vitae malesuada nisl efficitur. Cras in fermentum dui. Mauris luctus facilisis eros faucibus consectetur. Sed vel faucibus magna, non laoreet nisl. Praesent id molestie ligula, et laoreet enim. Donec pellentesque tempor ex, eu commodo diam lobortis cursus. In efficitur, ligula vel semper cursus, arcu nisi elementum orci, ac mollis justo orci a sem. Maecenas sed lacinia neque. Nunc sagittis sed libero ut scelerisque. Phasellus a nulla non diam porttitor tincidunt. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. Integer a tristique enim. Morbi sed elementum magna, sit amet dignissim neque. Etiam commodo erat lacinia augue faucibus euismod ac vel magna. Maecenas pretium, dui in aliquam lacinia, velit turpis scelerisque mauris, pharetra sodales lacus ligula ut nisl.
```
it comes out as this monstrosity:  
   ![I don't even know](https://github.com/B1rtek/Malep-v2/blob/master/mapleMalep.png)  
Yeah... Have fun :)

## Compiling

This program requires CMake to compile, the version of CMake doesn't really matter so if you have an outdated version you can change it to 3.11 or higher in the CMakeLists.txt. Since dependencies are handled by FetchContent, you don't have to do anything, just:
```shell
$ mkdir build
$ cd build
$ cmake ..
$ make
```
And you're good to go. 
