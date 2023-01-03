requirements:
Linux Machine

Dependencies:
sudo apt install libncurses-dev
sudo apt install libpthread-stubs0-dev
--or the default pthread library
sudo apt install libasound2-dev
sudo apt install libvorbis-dev
compile:
sh ./compile.sh


./playerradio

ncurses interface

features:

-manage as many playlists as you want
-ogg and wav format support(wav format only supports a fixed rate of 44100)(ogg supports any rate)
-full ogg support
-no mp3 support, mp3 sucks and ogg is better
-manager at what time which playlist will play
-skip next song option
-custom station ids for each individual playlist
-automatic shuffle with an algorithm that avoids repetition if possible
-all other software I know of for automated Radio Broadcasting is bloated and/or costs a lot of money in SUBSCRIPTIONS
-simple output to the soundcard
-manual Queue of songs to play
-toggleable microphone input
- sound effects(only gadzometer right now)

soon:
-turntables



-binary compiled on MX Linux OS
-took me several weeks of coding to get here
-written in C and C++



