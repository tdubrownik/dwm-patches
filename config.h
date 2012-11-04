/* See LICENSE file for copyright and license details. */

/* appearance */
//static const char font[]            = "-*-terminus-medium-r-*-*-16-*-*-*-*-*-*-*";
//static const char font[]            = "-*-nimbus sans l-medium-r-normal-*-14-*-*-*-*-*-*-*";
//static const char font[]            = "DejaVu 9";
#include "push.c"
static const char font[]            = "Terminus (TTF) 9";
static const char normbordercolor[] = "#444444";
static const char normbgcolor[]     = "#222222";
static const char normfgcolor[]     = "#bbbbbb";
static const char selbordercolor[]  = "#bbbbbb";
static const char selbgcolor[]      = "#333333";
static const char selfgcolor[]      = "#eeeeee";
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = True;     /* False means bottom bar */
static const Bool viewontag         = True;

/* tagging -- see tags.h */

static const Rule rules[] = {
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            True,        -1 },
//	{ "Firefox",  NULL,       NULL,       1 << 8,       False,       -1 },
        { "Amarok",          NULL,       NULL,       1 << 10,      False,       -1 },    
	{ "Pidgin",          NULL,       NULL,       1 << 11,      False,        0 },
	{ "HTOP",            NULL,       NULL,       1 << 8,       False,        0 },
	{ "NCMPCPP",         NULL,       NULL,       1 << 10,      False,        0 },
	{ "MPlayer",         NULL,       NULL,       0,            True,         1 },
	{ "CONSOLE",         NULL,       NULL,       1 << 13,      False,        0 },
	{ "stalonetray",     NULL,       NULL,       1 << 14,      False,        0 },
	{ "Google-chrome",   "google-chrome",       NULL,       0,            False,       -1 },
	{ "Google-chrome",   "gmail.com",           NULL,       1 << 9,       False,        0 },
	{ "Thunderbird",     "Mail",     NULL,       1 << 9,       False,        0 },
	{ "Google-chrome",   "calendar.google.com", NULL,       1 << 6,       False,        0 },
	{ "Google-chrome",   "www.wunderlist.com",  NULL,       1 << 7,       False,        0 },
	{ "Google-chrome",   "web.tweetdeck.com",   NULL,       1 << 12,      False,        0 },
};

/* layout(s) */
static const float mfact      = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster      = 1;    /* number of clients in master area */
static const Bool resizehints = True; /* True means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "###",      gaplessgrid },
};

/* pertag-static */
static TagConfig pertag[LENGTH(tags) + 1] = {
    /*  nlayout       nmaster       showbar          mfact */ 
        DEFAULT_TAG, /* 0 */
        DEFAULT_TAG, /* 1 */
        DEFAULT_TAG, /* 2 */
        DEFAULT_TAG, /* 3 */
        DEFAULT_TAG, /* 4 */
        DEFAULT_TAG, /* 5 */
        DEFAULT_TAG, /* 6 */
        DEFAULT_TAG, /* 7 */
        DEFAULT_TAG, /* 8 */
        DEFAULT_TAG, /* 9 */
        { 0,            1,            1,               0.60 }, /* q */
        DEFAULT_TAG, /* w */
        { 0,            1,            1,               0.8  }, /* e */
        DEFAULT_TAG, /* r */
        { 3,            1,            1,               0.5  }, /* ~ */
};

/* key definitions */
#define MODKEY Mod4Mask
#define ALT Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *dmenucmd[] = { "dmenu_run", "-fn", font, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "evilvte", NULL };
static const char *browsercmd[]  = { "google-chrome", NULL };
static const char *focuscmd[]  = { "/home/tomek/Programs/xtools/dmenu_focus", NULL };
static const char *fastmenucmd[]  = { "/home/tomek/Programs/xtools/m", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_space,  spawn,          {.v = dmenucmd } },
	{ ALT,                          XK_t,      spawn,          {.v = termcmd } },
//	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_space,  spawn,          {.v = focuscmd } },
	{ MODKEY|ControlMask,           XK_space,  spawn,          {.v = fastmenucmd } },
	{ MODKEY,                       XK_n,      spawn,          {.v = browsercmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ ALT,                          XK_Tab,    swapfocus,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
        { MODKEY|ShiftMask,             XK_j,      pushdown,       {0} },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
        { MODKEY|ShiftMask,             XK_k,      pushup,         {0} },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ ALT|ShiftMask,                XK_k,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_g,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY|ShiftMask,             XK_f,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
        { 0,                            0x1008ff12,spawn,          SHCMD("volume mute") },
        { MODKEY,                       0x1008ff12,spawn,          SHCMD("mpc toggle") },
        { 0,                            0x1008ff11,spawn,          SHCMD("volume dec") },
        { MODKEY,                       0x1008ff11,spawn,          SHCMD("mpc prev") },
        { 0,                            0x1008ff13,spawn,          SHCMD("volume inc") },
        { MODKEY,                       0x1008ff13,spawn,          SHCMD("mpc next") },
        { ALT|ControlMask,              XK_l,      spawn,          SHCMD("lock") },        
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	TAGKEYS(                        XK_q,                      9)
	TAGKEYS(                        XK_w,                      10)
	TAGKEYS(                        XK_e,                      11)
	TAGKEYS(                        XK_r,                      12)
	TAGKEYS(                        XK_grave,                  13)

        { MODKEY,                       XK_backslash, toggleview,  {.ui = 1 << 14 } },

	{ ALT|ShiftMask,                XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         ALT,            Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         ALT,            Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

