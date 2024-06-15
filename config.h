/* See LICENSE file for copyright and license details. */

/* constants */
#define TERMINAL "alacritty"
#define BROWSER "firefox"
#define FM "nnn"

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "terminus:size=12" };
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "^steam$",  NULL,       NULL,       0,            1,           -1 },
	{ "^Steam$",  NULL,       NULL,       0,            1,           -1 },
	{ "^steam$",  NULL,       "^Steam$",  0,            0,           -1 },
	{ "firefox",  NULL,       NULL,       1 << 1,       0,           -1 },
	{ "vesktop",  NULL,       NULL,       1 << 2,       0,           -1 },
	{ "steam",    NULL,       NULL,       1 << 3,       0,           -1 },
	{ "lutris",   NULL,       NULL,       1 << 3,       0,           -1 },
	{ "obs",      NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask

/* workaround for cz-qwertz layout */
#define XK_1 0x2b
#define XK_2 0x1ec
#define XK_3 0x1b9
#define XK_4 0x1e8
#define XK_5 0x1f8
#define XK_6 0x1be
#define XK_7 0xfd
#define XK_8 0xe1
#define XK_9 0xed
#define XK_0 0xe9

#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* spawn helpers */
#define CMD(CMD) { .v = (const char*[]){ CMD, NULL } }
#define TERMCMD(CMD) { .v = (const char*[]){ TERMINAL, "-e", CMD, NULL } }
#define SCREENSHOT(TYPE) { .v = (const char*[]){ "screenshot", TYPE, NULL } }

/* keybinds  */
static const Key keys[] = {
    /* modifier                     key        function        argument */

    /* tags */
    TAGKEYS(                        XK_1,                      0)
    TAGKEYS(                        XK_2,                      1)
    TAGKEYS(                        XK_3,                      2)
    TAGKEYS(                        XK_4,                      3)
    TAGKEYS(                        XK_5,                      4)
    TAGKEYS(                        XK_6,                      5)
    TAGKEYS(                        XK_7,                      6)
    TAGKEYS(                        XK_8,                      7)
    TAGKEYS(                        XK_9,                      8)

    /* spawn */
    { MODKEY,                       XK_d,      spawn,          {.v = (const char*[]){ "dmenu_run", "-i", NULL } } },
    { MODKEY,                       XK_Return, spawn,          CMD(TERMINAL) },
    { MODKEY,                       XK_e,      spawn,          TERMCMD(FM) },
    { MODKEY,                       XK_w,      spawn,          CMD(BROWSER) },
    { 0,                            XK_Print,  spawn,          SCREENSHOT("full") }, 
    { ShiftMask,                    XK_Print,  spawn,          SCREENSHOT("crop") }, 
    { MODKEY,                       XK_period, spawn,          CMD("emojimenu") },
    { MODKEY,                       XK_F1,     spawn,          TERMCMD("htop") },
    { MODKEY,                       XK_F2,     spawn,          TERMCMD("pulsemixer") },
    { MODKEY,                       XK_F3,     spawn,          CMD("mounter") },
    { MODKEY,                       XK_F4,     spawn,          CMD("unmounter") },

    /* layouts */
    { MODKEY|Mod1Mask,              XK_1,      setlayout,      {.v = &layouts[0]} },
    { MODKEY|Mod1Mask,              XK_2,      setlayout,      {.v = &layouts[1]} },
    { MODKEY|Mod1Mask,              XK_3,      setlayout,      {.v = &layouts[2]} },

    /* window management */
    { MODKEY,                       XK_q,      killclient,     {0} },
    { MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
    { MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
    { MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
    { MODKEY|ShiftMask,             XK_i,      incnmaster,     {.i = -1 } },
    { MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
    { MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
    { MODKEY,                       XK_space,  zoom,           {0} },
    { MODKEY,                       XK_Tab,    view,           {0} },
    { MODKEY,                       XK_g,      togglefloating, {0} },
    { MODKEY,                       XK_f,      togglefullscr,  {0} },
    { MODKEY,                       XK_0,      view,           {.ui = ~0 } },
    { MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
    /*
    { MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
    { MODKEY,                       XK_period, focusmon,       {.i = +1 } },
    { MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
    { MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
    */

    /* other */
    { MODKEY|ShiftMask,             XK_q,      quit,           {0} },
    { MODKEY,                       XK_b,      togglebar,      {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

