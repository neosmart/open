# `open` for Windows

macOS users are accustomed to the convenience of being able to use `open` from the command line to explore a directory or launch a program with its default handler. `open` for Windows provides the same convenience, and is particularly useful under Windows 10 and WSL.

## It's like double-clicking from the command line

At its heart, `open` is a convenient way to tell Windows to launch a file or open a folder the same way it would if you had double-clicked on it in Windows Explorer.

## Installation

Just copy `open.exe` to a directory in your `PATH` and call it from the command line (under WSL/bash or from cmd):

```
open mydoc.docx # launches Microsoft Word to edit the file
open . # launches Windows explorer, open to this direcctory
open foo.exe # runs foo.exe
open bar.png # launches default photo viewer
open https://neosmart.net/ # navigates to URL in default browser
open foo.bar # shows the "open with" dialog as .bar is not a known extension
```

## License and Copyright

`open` is released as open source to the public under the terms of the MIT Public License. `open` is developed and maintained by Mahmoud Al-Qudsi of NeoSmart Technologies. <mqudsi@neosmart.net>.

