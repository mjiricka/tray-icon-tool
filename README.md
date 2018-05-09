# Tray utils

**ABANDONED PROJECT**

I wanted to do a program that would display following two things as tray icons:

 - Short custom string that could be set when invoking the app. (And also be
   updated the same way.)
    - Purpose: To display my current XKB keymap that is set by my custom Bash
      script.
 - Current master volume of Alsa mixer.

After some time I realized it would be much better to create a plugin into my
desktop panel instead of creating separate app. Moreover I found out GTK3 is ugly
library. This program probably contains memory leak, because I found GTK3
documentation confusing about deallocation responsibilities.

Moreover tray icons are deprecated in GTK3.

I also started a code for displaying the master volume, but I accidentally
deleted it :) So it is not even here. (Which is a pity, it took me some time
to create asynchronous code that would do that.)

But I will keep it here. Maybe it will serve as an inspiration for the panel
plugin one day.

