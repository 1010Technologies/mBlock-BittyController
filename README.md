# mBlock-BittyController

An mBlock-based programming environment for the [Bitty Controller](http://www.bittysoftware.com). For use with [mBlock](http://www.mblock.cc).

## Install

To install, open **mBlock IDE**,
* From **Extensions** menu item
* Open **Manage Extensions** (short-cut *Ctrl+shift+T*)
* Click **Available** button and search for "*HyperDuino*"

The current version runs only in Arduino mode. In other words, you need to click **Upload to Arduino** button in **Arduino mode** to upload and run your program.

## Build and Upload

Instructions on creating extensions and adding blocks: http://download.makeblock.com/mblock/mblock_extension_guide.pdf

    zip --exclude \*.git\* \*.vscode\* -r bitty.zip mBlock-BittyController

To add the new extension to mBlock, visit http://www.mblock.cc/extensions