<!-- 
OLD Notes:
Build the app
```bash
gcc keyboard.c -o keyhog
```

```json
{
  // could use this to mute/unmute?
  "N": "mpv:cycle ao-mute",
  "N": "mpv:del ao-mute",
  "N": "mpv:set ao-mute yes",
}
```
 -->


### HTPC Utils

Stuff to make a HTPC linux system more like a TV. Built using qt5

- OSD / notifications
- volume control (mute/unmute)
- sleep timer

Ideas:
- custom key remapping (OS media keys)

#### Remote Codes
I used FLIRC along with a IR remote (I used one for a Roku TV). The FLIRC app allows you map IR codes to any key combination you need. This app listens for the following hotkeys:

| Action | Hot Key |
| ------ | ------- |
| `Ctrl` + `Shift` + `1` | Mute/Unmute |
| `Ctrl` + `Shift` + `2` | Volume Up |
| `Ctrl` + `Shift` + `3` | Volume Down |
| `Ctrl` + `Shift` + `4` | Sleep Timer +30m |

#### Compiling From Source

Install dependencies:

```bash
sudo apt install qt5-default qtbase5-private-dev
```

Note: Bigscreen also uses `amixer` to control the system volume. Most distros come with this program, but if you need to, you can install it with:
```bash
sudo apt install alsa-tools
```

Make project:

```bash
cd bigscreen
cmake .
make
```

Run the application:
```bash
./bigscreen
```

Global Hot Key Support:
https://github.com/hluk/qxtglobalshortcut/tree/master