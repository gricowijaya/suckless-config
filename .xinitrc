#!/bin/sh

userresources=$HOME/.Xresources
usermodmap=$HOME/.Xmodmap
sysresources=/etc/X11/xinit/.Xresources
sysmodmap=/etc/X11/xinit/.Xmodmap


# merge in defaults and keymaps

if [ -f $sysresources ]; then







    xrdb -merge $sysresources

fi

if [ -f $sysmodmap ]; then
    xmodmap $sysmodmap
fi

if [ -f "$userresources" ]; then







    xrdb -merge "$userresources"

fi

if [ -f "$usermodmap" ]; then
    xmodmap "$usermodmap"
fi

# start some nice programs

if [ -d /etc/X11/xinit/xinitrc.d ] ; then
 for f in /etc/X11/xinit/xinitrc.d/?*.sh ; do
  [ -x "$f" ] && . "$f"
 done
 unset f
fi

## USING THE XTERM
# twm &
# xclock -geometry 50x50-1+1 &
# xterm -geometry 80x50+494+51 &
# xterm -geometry 80x20+494-0 &
# exec xterm -geometry 80x66+0+0 -name login

# swap super with alt
# setxkbmap -option altwin:swap_alt_win

## USING XFCE4
# exec startxfce4

## Dynamic wallpaper
# cursewall &

## Animated Wallpaper
# paperview $HOME/.local/src/paperview/wallpaper/town 5 &

## Dynamic Animated Wallpaper
# curseanimwall &

# wallpaper
# feh --bg-fill $HOME/.local/src/wallpaper/934006.jpg  &

## DWM
# export _JAVA_AWT_WM_NONREPARENTING=1
# increasemousetrackpoint &
# statusbar &
# nm-applet & # to start the network applet
# firefox &
# telegram-desktop &
# discord --start-minimized &
# st & # uncomment to auto start st
# picom & # should be turn off to use the animated wallpaper
# startdwm
# exec dwm

