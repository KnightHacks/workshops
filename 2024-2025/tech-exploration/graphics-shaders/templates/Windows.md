## Window Template Setup

Navigate to https://www.msys2.org/ and install the exe. Once that is done, type this command in, and it should be on the site as well:

```
pacman -S mingw-w64-ucrt-x86_64-gcc
```


Once that is finished, go to windows search bar, type "edit environment variables" and hit enter.


Navigate to Path, double-click, then the edit environment variable will pop up.

Hit new, navigate to msys64 then ucrt64 then bin, hit done, and it should be added to your path! Now hit ok on everything and it should be saved, then run the windows template on main.cpp with CMD + SHIFT + B and it should compile! Execute it like a normal exe.