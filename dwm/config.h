#include <X11/XF86keysym.h>
/* See LICENSE file for copyright and license details. */
static const char *upvol[]               = { "amixer", "set", "Master", "10%+",     NULL };
static const char *downvol[]             = { "amixer", "set", "Master", "10%-",     NULL };
static const char *mutevol[]             = { "amixer", "set", "Master", "toggle", NULL };
static const char *upbright[]            = { "brightnessctl", "s", "-n", "100+", NULL };
static const char *downbright[]          = { "brightnessctl", "s", "-n", "100-", NULL };
static const char *ss[]                  = { "scrclip", "-s", "--file $HOME/Pictures/Screenshots", NULL};

/* appearance */
static const unsigned int borderpx       = 2;        /* border pixel of windows */
static const unsigned int gappx          = 1;        /* 1 gaps between windows */
static const unsigned int gappih         = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv         = 10;       /* vert inner gap between windows */
static const unsigned int gappoh         = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov         = 10;       /* vert outer gap between windows and screen edge */
static       int smartgaps               = 0;        /* 1 means no outer gap when there is only one window */
static const unsigned int snap           = 32;       /* snap pixel */
static const int swallowfloating         = 0;        /* 1 means swallow floating windows by default */
static const int showbar                 = 1;        /* 0 means no bar */
static const int topbar                  = 1;        /* 0 means no top bar */
static const int extrabar                = 0;        /* 0 means no bottom bar */
static const unsigned int systraypinning = 0;        /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft  = 0;        /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;        /* systray spacing */
static const int systraypinningfailfirst = 1;        /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray             = 1;        /* 0 means no systray */
static const char *fonts[]               = { "3270 Nerd Font Mono:pixelsize=20:antialias=true:autohint=true:size=16", "JoyPixels:pixelsize=11:antialias=true:autohint=true" };
static const char dmenufont[]            = { "3270 Nerd Font Mono:pixelsize=20:antialias=true:autohint=true:size=16" };
static char normbgcolor[]                = "#222222"; // default #000000
static char normbordercolor[]            = "#000000"; // default #606060
static char normfgcolor[]                = "#bbbbbb"; // default #bbbbbb
static char selfgcolor[]                 = "#EEEEEE"; // default #EEEEEE
static char selbordercolor[]             = "#005577"; // default 
static char selbgcolor[]                 = "#005577"; // default #000000

static const char statussep              = ';';      /* separator between statuses */
static char *colors[][3]                 = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

/* tagging */
/* static const char *tags[] = { "一", "二", "三", "四", "五"};                     /* Use Kanji Font*/
/* static const char *tags[] = { "ایک", "دو", "تین", "چار", "پانچ", "چھ", "سات"};   /* in urdu cardinal must must apply bidi patch */
static const char *tags[] = { "1", "2", "3", "4", "5", "6"};                        /* the most simple one*/

/* launcher commands (They must be NULL terminated) */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont};
static const char *lock[]     = { "slock", NULL};
static const char *termcmd[]  = { "st", NULL };
static const char *surf[]     = { "surf", "duckduckgo.com", NULL };
static const char *min[]      = { "min", NULL };

static const Launcher launchers[] = {
    /* command       name to display */
	{  surf,         "surf" },
	{  termcmd,      ">_" },
	{  min,          "min" },
	{  lock,         "lock" },
};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class                instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "TelegramDesktop",    NULL,     NULL,           1 << 6,         0,          0,           0,        -1 },
	{ "discord",            NULL,     NULL,           1 << 5,         0,          0,           0,        -1 },
	{ "zoom",               NULL,     NULL,           1 << 5,         0,          0,           0,        -1 },
	{ "obs",                NULL,     NULL,           1 << 4,         0,          0,           0,        -1 },
	{ "firefox",            NULL,     NULL,           1 << 2,         0,          0,          -1,        -1 },
	{ "chromium",           NULL,     NULL,           1 << 8,         0,          0,          -1,        -1 },
	{ "postman",            NULL,     NULL,           1 << 1,         0,          0,          -1,        -1 },
	{ "Min",                NULL,     NULL,           1 << 2,         0,          0,          -1,        -1 },
	{ "Code",               NULL,     NULL,           1 << 1,         0,          0,          -1,        -1 },
	{ "St",                 NULL,     NULL,           0,              0,          1,           0,        -1 },
	{ NULL,                 NULL,     "Event Tester", 0,              0,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },                    /* first entry is default */
 	{ "[\\]",     dwindle },
	{ "|M|",      centeredmaster },          
	{ ">M>",      centeredfloatingmaster }, 
	{ "><>",      NULL },                    /* no layout function means floating behavior */
	{ "[M]",      monocle },
 	{ "[@]",      spiral },
};

/* key definitions */
#define MODKEY Mod4Mask
#define ALTMOD Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} }, 
 /* { ALTMOD,                       KEY,      focusnthmon,    {.i  = TAG } }, \ */
 /* { ALTMOD|ShiftMask,             KEY,      tagnthmon,      {.i  = TAG } }, */


/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

#include "shiftview.c"
static Key keys[] = {
	/* modifier                     key                           function              argument */
	{ MODKEY,                       XK_l,                         setmfact,             {.f = +0.05} },
	{ MODKEY,                       XK_k,                         focusstack,           {.i = -1 } },
	{ MODKEY,                       XK_j,                         focusstack,           {.i = +1 } },
	{ MODKEY,                       XK_h,                         setmfact,             {.f = -0.05} },
	{ MODKEY,                       XK_g,                         togglebar,            {0} },
	{ MODKEY|ShiftMask,             XK_g,                         toggleextrabar,       {0} },
	{ MODKEY|ShiftMask,             XK_f,                         zoom,                 {0} },
	{ MODKEY|ShiftMask,             XK_l,                         spawn,                {.v = lock} },
	{ MODKEY,                       XK_d,                         incnmaster,           {.i = -1 } },
	{ MODKEY,                       XK_s,                         incnmaster,           {.i = +1 } },
	{ MODKEY,                       XK_q,                         killclient,           {0} },
	{ MODKEY,                       XK_w,                         setlayout,            {.v = &layouts[0]} },
	{ MODKEY,                       XK_e,                         setlayout,            {.v = &layouts[1]} },
	{ MODKEY,                       XK_r,                         setlayout,            {.v = &layouts[2]} },
	{ MODKEY,                       XK_t,                         setlayout,            {.v = &layouts[5]}  },
	{ MODKEY,                       XK_y,                         setlayout,            {.v = &layouts[3]} },
	{ MODKEY,                       XK_u,                         setlayout,            {.v = &layouts[4]} },
	{ MODKEY|ShiftMask,             XK_r,                         togglefloating,       {0} },
	{ MODKEY|ShiftMask,             XK_r,                         togglealwaysontop,    {0} },
	{ MODKEY,                       XK_f,                         togglefullscr,        {0} },
	{ MODKEY,                       XK_n,                         shiftview,            {.i = +1} },
	{ MODKEY,                       XK_b,                         shiftview,            {.i = -1} },
	{ 0,                            XK_Print,                     spawn,                {.v = ss}},
	{ MODKEY,                       XK_space,                     spawn,                {.v = dmenucmd } },
	{ MODKEY,                       XK_Return,                    spawn,                {.v = termcmd } },
	{ MODKEY,                       XK_Tab,                       view,                 {0} },
	{ MODKEY,                       XK_0,                         view,                 {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,                         tag,                  {.ui = ~0 } },
	{ MODKEY,                       XK_comma,                     focusmon,             {.i = -1 } },
	{ MODKEY,                       XK_period,                    focusmon,             {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,                     tagmon,               {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,                    tagmon,               {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_minus,                     incrgaps,             {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_equal,                     incrgaps,             {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_i,                         incrigaps,            {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_i,                         incrigaps,            {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_o,                         incrogaps,            {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_o,                         incrogaps,            {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_6,                         incrihgaps,           {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_6,                         incrihgaps,           {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_7,                         incrivgaps,           {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_7,                         incrivgaps,           {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_8,                         incrohgaps,           {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_8,                         incrohgaps,           {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_9,                         incrovgaps,           {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_9,                         incrovgaps,           {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_0,                         togglegaps,           {0} },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_0,                         defaultgaps,          {0} },
	{ 0,                            XF86XK_AudioMute,             spawn,                {.v = mutevol } },
	{ 0,                            XF86XK_AudioLowerVolume,      spawn,                {.v = downvol } },
	{ 0,                            XF86XK_AudioRaiseVolume,      spawn,                {.v = upvol   } },
	{ 0,                            XF86XK_MonBrightnessDown,     spawn,                {.v = downbright } },
	{ 0,                            XF86XK_MonBrightnessUp,       spawn,                {.v = upbright } },
	TAGKEYS(                        XK_1,                                         0)
	TAGKEYS(                        XK_2,                                         1)
	TAGKEYS(                        XK_3,                                         2)
	TAGKEYS(                        XK_4,                                         3)
	TAGKEYS(                        XK_5,                                         4)
	TAGKEYS(                        XK_6,                                         5)
	TAGKEYS(                        XK_7,                                         6)
	TAGKEYS(                        XK_8,                                         7)
	TAGKEYS(                        XK_9,                                         8)
	{ MODKEY|ShiftMask,             XK_q,                         quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkRootWin,           0,              Button3,        spawn,          {.v = termcmd } },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkWinTitle,          0,              Button1,        togglebar,      {0} },
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
	{ ClkExBarLeftStatus,   0,              Button1,        toggleextrabar, {0} },
	{ ClkExBarMiddle,       0,              Button1,        toggleextrabar, {0} },
	{ ClkExBarRightStatus,  0,              Button2,        spawn,          {.v = termcmd } },
};

