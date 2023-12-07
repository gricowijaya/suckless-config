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

# swap super with alt
# setxkbmap -option altwin:swap_alt_win

# USING XFCE4
# alsactl init
# increasemousetrackpoint &
# xrandr --scale '1.14x1.14'
# exec startxfce4

# DWM
feh --bg-fill $HOME/.local/src/wallpaper/934006.jpg  &
export _JAVA_AWT_WM_NONREPARENTING=1
alsactl init
increasemousetrackpoint &
statusbar &
nm-applet &
xrandr --scale '1.14x1.14'
dunst &
exec dwm
discord --start-minimized &

# startdwm

# Dynamic wallpaper
# cursewall &

# Animated Wallpaper
# paperview $HOME/.local/src/paperview/wallpaper/town 5 &

# Dynamic Animated Wallpaper
# curseanimwall &
# picom & # should be turn off to use the animated wallpaper

