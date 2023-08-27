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


## Bigscreen

### _Remote control your HTPC like a pro!_

- **TV-like OSD**<br />Mimicks the on screen display of a TV
- **Minimal Remote Friendly**<br />Works great with small streaming remotes
- **Control System Volume**<br />Easily change the system volume, mute, and unmute.
- **Sleep Timer**<br />Send the suspend or shutdown command with a timer

<img src="https://github.com/dudewheresmycode/bigscreen/assets/3523761/802483a5-3ed9-414b-ae98-afc0558ef041" width="360" alt="Screenshot Muted" title="Screenshot Muted" />
<img src="https://github.com/dudewheresmycode/bigscreen/assets/3523761/22aa4b99-1343-4f07-90cb-f35773bdeb7e" width="360" alt="Screenshot Volume" title="Screenshot Volume" />

--- 

Note: Bigscreen was built primarily for use with the [Plex HTPC](https://support.plex.tv/articles/htpc-getting-started/) app, but will work for any HTPC setup.

Ideas:
- custom remote key remapping
- handle OS media keys
- brightness / night mode


#### Platform Support

| Platform | Support | System Audio Control |
| ------- | ------ | --- |
| Linux | ✅ | ASLA (Pulse) |
| Mac | _Coming Soon_ | ? |
| Windows | _Coming Soon_ | ? |

#### Remotes

I used an [FLIRC](https://flirc.tv/products/flirc-usb-receiver) USB receiver along with a IR remote (I used this [replacement remote](https://www.amazon.com/dp/B096XLHVS7) for a Roku TV). The FLIRC GUI app allows you map IR codes to any key combination you need. 

The Bigscreen app responds to the following global hot keys:

| Action | Hot Key |
| ------ | ------- |
| `Ctrl` + `Shift` + `1` | Mute/Unmute |
| `Ctrl` + `Shift` + `2` | Volume Up |
| `Ctrl` + `Shift` + `3` | Volume Down |
| `Ctrl` + `Shift` + `4` | Sleep Timer +30m |

If you are using another type of remote, or a keyboard. You can try and remap the key events of the device to the above global hot keys using a tool like `xmodmap`. 

_(More remote documentation coming soon!)_

#### Compiling From Source

Bigscreen is built using the Qt5 development framework.

Install dependencies:

```bash
sudo apt install qt5-default qtbase5-private-dev
```

---

> Note: Bigscreen also uses `amixer` to control the system volume. Most distros come with this program, but if you need to, you can install it with `sudo apt install alsa-tools`

---

#### qxtglobalshortcut
Bigscreen also depends on the [`qxtglobalshortcut`](https://github.com/hluk/qxtglobalshortcut/tree/master) library to bind to the global hot keys. You'll need to follow the instructions to build and install that on your development machine.

```bash
cd ~/
git clone https://github.com/hluk/qxtglobalshortcut
cd qxtglobalshortcut
cmake -DCMAKE_INSTALL_PREFIX=/usr/local .
make install
```

Next, clone the repo and build it:

```bash
cd ~/
git clone https://github.com/dudewheresmycode/bigscreen
cd bigscreen
cmake .
make
```

Run the application:
```bash
./bigscreen
```
