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


### Bigscreen

Bigscreen makes your linux-based HTPC work more like a TV.

- TV-like OSD
- Volume Control (mute/unmute, volume up/down)
- Sleep Timer

Ideas:
- custom remote key remapping
- handle OS media keys
- brightness / night mode


#### Platform Support

| Platform | Support |
| ------- | ------ |
| Linux | ✅ |
| Mac | _Coming Soon_ |
| Windows | _Coming Soon_ |

#### Remotes

I used an [FLIRC](https://flirc.tv/products/flirc-usb-receiver) USB receiver along with a IR remote (I used this [replacement remote](https://www.amazon.com/dp/B096XLHVS7) for a Roku TV). The FLIRC GUI app allows you map IR codes to any key combination you need. 

The Bigscreen app responds to the following global hot keys:

| Action | Hot Key |
| ------ | ------- |
| `Ctrl` + `Shift` + `1` | Mute/Unmute |
| `Ctrl` + `Shift` + `2` | Volume Up |
| `Ctrl` + `Shift` + `3` | Volume Down |
| `Ctrl` + `Shift` + `4` | Sleep Timer +30m |

If you are using another type of remote, or a keyboard. You can try and remap the key events of the device to these global hot keys using a tool like `xmodmap`. 

_(More remote documentation coming soon!)_

#### Compiling From Source

Bigscreen is built using the Qt5 development framework.

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