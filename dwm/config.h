#include <X11/XF86keysym.h>
/* See LICENSE file for copyright and license details. */
static const char *upvol[]   = { "amixer", "set", "Master", "10%+",     NULL };
static const char *downvol[] = { "amixer", "set", "Master", "10%-",     NULL };
static const char *mutevol[] = { "amixer", "set", "Master", "toggle", NULL };
static const char *upbright[] = { "brightnessctl", "s", "-n", "100+", NULL };
static const char *downbright[] = { "brightnessctl", "s", "-n", "100-", NULL };

/* appearance */
static const unsigned int borderpx  = 5;        /* border pixel of windows */
static const unsigned int gappx     = 4;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means no top bar */
static const int extrabar           = 1;        /* 0 means no bottom bar */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;   	/* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 2;     /* 0 means no systray */
/* static const char *fonts[]          = { "FiraCode Nerd Font:pixelsize=18:antialias=true:autohint=true:size=16", "JoyPixels:pixelsize=11:antialias=true:autohint=true"}; */
/* static const char dmenufont[]       = "FiraCode Nerd Font:size=16"; */
static const char *fonts[]          = { "mononoki Nerd Font Mono:pixelsize=19:antialias=true:autohint=true:size=16", "JoyPixels:pixelsize=11:antialias=true:autohint=true"};
static const char dmenufont[]       = "mononoki Nerd Font Mono:size=16";
static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#005577";
static char selbgcolor[]            = "#005577";
static const char statussep         = ';';      /* separator between statuses */
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

/* tagging */
// static const char *tags[] = { ">_", "", "", "", ""};
static const char *tags[] = { "一", "二", "三", "四", "五"};
/* static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7"}; */

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class                instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "TelegramDesktop",    NULL,     NULL,           1 << 1,         0,          0,           0,        -1 },
	{ "mattermost-desktop", NULL,     NULL,           1 << 1,         0,          0,           0,        -1 },
	{ "whatsdesk",          NULL,     NULL,           1 << 1,         0,          0,           0,        -1 },
	{ "obs",                NULL,     NULL,           0,              1,          0,           0,        -1 },
	{ "Lutris",             NULL,     NULL,           0,              1,          0,           0,        -1 },
	{ "firefox",   		      NULL,     NULL,           1 << 2,         0,          0,          -1,        -1 },
	{ "qutebrowser",   		  NULL,     NULL,           1 << 2,         0,          0,          -1,        -1 },
	{ "St",                 NULL,     NULL,           0,              0,          1,           0,        -1 },
	{ NULL,                 NULL,     "Event Tester", 0,              0,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

#include "fibonacci.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
 	{ "[\\]",      dwindle },
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
 	{ "[@]",      spiral },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont};
static const char *termcmd[]  = { "st", NULL };

#include "shiftview.c"
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_g,      togglebar,      {0} },
	{ MODKEY,                       XK_f,	     zoom,           {0} },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_s,      incnmaster,     {.i = +1 } },
	{ MODKEY,		                    XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_w,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_e,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_r,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY|ShiftMask,             XK_r,  	   togglefloating, {0} },
	{ MODKEY,                       XK_t,  	   setlayout,      {0} },
	{ MODKEY,                       XK_n,  	   shiftview,      {.i = +1} },
	{ MODKEY,                       XK_b,  	   shiftview,      {.i = -1} },
	{ MODKEY,                       XK_space,  spawn,          {.v = dmenucmd } },
	{ MODKEY,			                  XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,			                  XK_minus,  setgaps,	       {.i = -1 } },
	{ MODKEY,			                  XK_equal,  setgaps,	       {.i = +1 } },
	{ MODKEY|ShiftMask,		          XK_equal,  setgaps,	       {.i =  0 } },
  /* { MODKEY,                       XK_F5,     xrdb,           {.v = NULL } }, */
  /* { MODKEY,                       XK_F1,     spawn,          {.v = mutevol } }, */ 
  /* { MODKEY,                       XK_F2,     spawn,          {.v = downvol } }, */ 
  /* { MODKEY,                       XK_F3,     spawn,          {.v = upvol   } }, */ 
  /* { MODKEY|ShiftMask,             XK_b,      toggleextrabar, {0} }, */
  /* // { MODKEY,                       XK_F4,     xrdb,           {.v = NULL } }, *1/ */
  /* { MODKEY,                       XK_F5,     spawn,          {.v = downbright } }, */
  /* { MODKEY,                       XK_F6,     spawn,          {.v = upbright } }, */
	{ 0,                       XK_F1,     spawn,          {.v = mutevol } },
	{ 0,                       XK_F2,     spawn,          {.v = downvol } },
	{ 0,                       XK_F3,     spawn,          {.v = upvol   } },
	/* { 0|ShiftMask,             XK_b,      toggleextrabar, {0} }, */
  /* { 0,                       XK_F4,     xrdb,           {.v = NULL } }, */
	{ 0,                       XK_F5,     spawn,          {.v = downbright } },
	{ 0,                       XK_F6,     spawn,          {.v = upbright } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,		XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkExBarLeftStatus,   0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkExBarMiddle,       0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkExBarRightStatus,  0,              Button2,        spawn,          {.v = termcmd } },
};

