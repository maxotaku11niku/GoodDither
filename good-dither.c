#include "config.h"
#include <glib/gi18n-lib.h>

#ifdef GEGL_PROPERTIES

enum_start(ditherMethods)
enum_value(BAYER2X2, "bayer2", "Bayer 2x2")
enum_value(BAYER4X4, "bayer4", "Bayer 4x4")
enum_value(BAYER8X8, "bayer8", "Bayer 8x8")
enum_value(BAYER16X16, "bayer16", "Bayer 16x16")
enum_value(VOID16X16, "void16", "Void and cluster 16x16")
enum_value(FLOYD_STEINBERG, "floyd", "Floyd-Steinberg")
enum_value(FLOYD_FALSE, "floydfalse", "False Floyd-Steinberg")
enum_value(JJN, "jjn", "Jarvis-Judice-Ninke")
enum_value(STUCKI, "stucki", "Stucki")
enum_value(BURKES, "burkes", "Burkes")
enum_value(SIERRA, "sierra", "Sierra")
enum_value(SIERRA2ROW, "sierra2row", "Sierra 2-Row")
enum_value(FILTERLITE, "filterlite", "Filter Lite")
enum_value(ATKINSON, "atkinson", "Atkinson")
enum_end(ditherMethods)

enum_start(palettes)
enum_value(I1, "i1", "Black and white (2 colours)")
enum_value(R1G1B1, "r1g1b1", "R1G1B1 (8 colours)")
enum_value(R1G1B1I1, "r1g1b1i1", "R1G1B1I1 (16 colours)")
enum_value(R2G2B2, "r2g2b2", "R2G2B2 (64 colours)")
enum_value(R3G3B3, "r3g3b3", "R3G3B3 (512 colours)")
enum_value(MY16, "my16", "My 16 colours")
enum_value(MSWINDOWS, "windows", "Windows 3/9x/2000 default (16 colours)")
enum_value(MAC2, "mac2", "Mac II default (16 colours)")
enum_value(RISCOS, "riscos", "RISC OS 2/3 default (16 colours)")
enum_value(APPLE2_6, "apple2_6", "Apple II default (6 colours)")
enum_value(APPLE2_15, "apple2_15", "Apple II default (15 colours)")
enum_value(C64, "c64", "Commodore 64 default (16 colours)")
enum_value(MSX, "msx", "MSX default (15 colours)")
enum_value(INTELLIVISION, "intellivision", "Intellivision default (16 colours)")
enum_value(GB, "gameboy", "Game Boy default approximation (4 colours)")
enum_value(ADAPTIVE, "adaptive", "Adaptive (find best colours for this image)")
enum_value(FROMFILE, "file", "From file (load .gpl file)")
enum_end(palettes)

property_enum (ditherMethod, _("Dither Method"), ditherMethods, ditherMethods, BAYER4X4)
    description (_("Choose from a variety of dithering methods, both ordered and error-diffusing."))

property_enum (curpal, _("Palette"), palettes, palettes, MY16)
    description (_("Choose the palette you want to use."))

property_int (numcol, _("Number of Colours"), 16)
    description (_("Number of colours in the generated palette."))
    value_range (2, 512)
    ui_range    (2, 256)

property_double (adptBright, _("Adaptive Pre-brightness"),  0.0)
    description (_("Brightness adjustment applied before finding best palette."))
    value_range (-1.0, 1.0)
    ui_range    (-1.0, 1.0)

property_double (adptContrast, _("Adaptive Pre-contrast"),  0.0)
    description (_("Contrast adjustment applied before finding best palette."))
    value_range (-1.0, 1.0)
    ui_range    (-1.0, 1.0)

property_double (adptchromabias, _("Adaptive Chroma Bias"),  1.0)
    description (_("Adjust bias towards generating 'colourful' colours for an adaptive palette."))
    value_range (0.2, 8.0)
    ui_range    (0.5, 4.0)

property_double (ditherAmountL, _("Luminosity Dither"),  0.5)
    description (_("Magnitude of dither effect on the luminosity."))
    value_range (0.0, 2.0)
    ui_range    (0.0, 1.0)

property_double (ditherAmountS, _("Saturation Dither"),  0.2)
    description (_("Magnitude of dither effect on the saturation."))
    value_range (0.0, 2.0)
    ui_range    (0.0, 1.0)

property_double (ditherAmountH, _("Hue Dither"),  1.0)
    description (_("Magnitude of dither effect on the hue."))
    value_range (0.0, 10.0)
    ui_range    (0.0, 6.0)

property_double (ditherAmountEL, _("Luminosity Error Diffusion"),  1.0)
    description (_("Magnitude of error diffusion in the luminosity channel."))
    value_range (0.0, 1.0)
    ui_range    (0.0, 1.0)

property_double (ditherAmountEC, _("Chroma Error Diffusion"),  1.0)
    description (_("Magnitude of error diffusion in the chroma channels."))
    value_range (0.0, 1.0)
    ui_range    (0.0, 1.0)

property_double (randomAmountL, _("Luminosity Diffusion Randomisation"),  0.0)
    description (_("Magnitude of error diffusion randomisation in the luminosity channel."))
    value_range (0.0, 0.5)
    ui_range    (0.0, 0.2)

property_double (randomAmountC, _("Chroma Diffusion Randomisation"),  0.0)
    description (_("Magnitude of error diffusion randomisation in the chroma channels."))
    value_range (0.0, 0.5)
    ui_range    (0.0, 0.2)

property_double (chromabias, _("Chroma Bias"),  1.0)
    description (_("Adjust bias towards using 'colourful' colours."))
    value_range (0.1, 3.0)
    ui_range    (0.5, 2.0)

property_double (preBright, _("Pre-brightness"),  0.0)
    description (_("Brightness adjustment applied before dithering."))
    value_range (-1.0, 1.0)
    ui_range    (-1.0, 1.0)

property_double (preContrast, _("Pre-contrast"),  0.0)
    description (_("Contrast adjustment applied before dithering."))
    value_range (-1.0, 1.0)
    ui_range    (-1.0, 1.0)

property_double (postBright, _("Post-brightness"),  0.0)
    description (_("Brightness adjustment applied just before finding the best colour."))
    value_range (-1.0, 1.0)
    ui_range    (-1.0, 1.0)

property_double (postContrast, _("Post-contrast"),  0.0)
    description (_("Contrast adjustment applied just before finding the best colour."))
    value_range (-1.0, 1.0)
    ui_range    (-1.0, 1.0)

property_boolean (boustrophedon, _("Boustrophedon Scanning"), FALSE)
    description (_("Use back-and-forth scanning in error diffusion dithering."))

#else

#define GEGL_OP_FILTER
#define GEGL_OP_NAME     good_dither
#define GEGL_OP_C_SOURCE good-dither.c

#include <gegl-op.h>
#include <math.h>

//Type definitions
typedef struct
{
    unsigned char R;
    unsigned char G;
    unsigned char B;
    unsigned char A;
} ColourRGBA8;

typedef struct
{
    float R;
    float G;
    float B;
    float A;
} ColourRGBA;

typedef struct
{
    float L;
    float a;
    float b;
    float A;
} ColourOkLabA;

static inline ColourOkLabA ColourOkLabAAdd(ColourOkLabA l, ColourOkLabA r)
{
    ColourOkLabA c;
    /*/
    c.L = l.L + r.L;
    c.a = l.a + r.a;
    c.b = l.b + r.b;
    c.A = l.A + r.A;
    //*/
    /**/
    __asm (
        "movups %1, %0\n\t"
        "addps %2, %0"
    : "=x" (c) : "xm" (l), "xm" (r)); //Should be compatible with all x86-64 processors
    //*/
    return c;
}

static inline ColourOkLabA ColourOkLabAAddAccumulate(ColourOkLabA l, ColourOkLabA r)
{
    /*/
    l.L += r.L;
    l.a += r.a;
    l.b += r.b;
    l.A += r.A;
    //*/
    /**/
    __asm (
        "addps %1, %0"
    : "+x" (l) : "xm" (r)); //Should be compatible with all x86-64 processors
    //*/
    return l;
}

static inline ColourOkLabA ColourOkLabAMultiply(ColourOkLabA l, ColourOkLabA r)
{

    ColourOkLabA c;
    /*/
    c.L = l.L * r.L;
    c.a = l.a * r.a;
    c.b = l.b * r.b;
    c.A = l.A * r.A;
    //*/
    /**/
    __asm (
        "movups %1, %0\n\t"
        "mulps %2, %0"
    : "=x" (c) : "xm" (l), "xm" (r)); //Should be compatible with all x86-64 processors
    //*/
    return c;
}

static inline ColourOkLabA ColourOkLabAMultiplyAccumulate(ColourOkLabA l, ColourOkLabA r)
{
    /*/
    l.L *= r.L;
    l.a *= r.a;
    l.b *= r.b;
    l.A *= r.A;
    //*/
    /**/
    __asm (
        "mulps %1, %0"
    : "+x" (l) : "xm" (r)); //Should be compatible with all x86-64 processors
    //*/
    return l;
}

static inline ColourOkLabA ColourOkLabAFMA(ColourOkLabA a, ColourOkLabA ml, ColourOkLabA mr)
{
    ColourOkLabA c;
    /*/
    c.L = a.L + (ml.L * mr.L);
    c.a = a.a + (ml.a * mr.a);
    c.b = a.b + (ml.b * mr.b);
    c.A = a.A + (ml.A * mr.A);
    //*/
    /**/
    __asm (
        "movups %2, %%xmm7\n\t"
        "mulps %3, %%xmm7\n\t"
        "movups %1, %0\n\t"
        "addps %%xmm7, %0"
    : "=x" (c) : "xm" (a), "xm" (ml), "xm" (mr) : "%xmm7"); //Should be compatible with all x86-64 processors
    //*/
    return c;
}

static inline ColourOkLabA ColourOkLabAFMAAccumulate(ColourOkLabA a, ColourOkLabA ml, ColourOkLabA mr)
{
    /*/
    a.L += ml.L * mr.L;
    a.a += ml.a * mr.a;
    a.b += ml.b * mr.b;
    a.A += ml.A * mr.A;
    //*/
    /**/
    __asm (
        "movups %1, %%xmm7\n\t"
        "mulps %2, %%xmm7\n\t"
        "addps %%xmm7, %0"
    : "+x" (a) : "xm" (ml), "xm" (mr) : "%xmm7"); //Should be compatible with all x86-64 processors
    //*/
    return a;
}

enum_start(ditherMethods)
enum_value(BAYER2X2, "bayer2", "Bayer 2x2")
enum_value(BAYER4X4, "bayer4", "Bayer 4x4")
enum_value(BAYER8X8, "bayer8", "Bayer 8x8")
enum_value(BAYER16X16, "bayer16", "Bayer 16x16")
enum_value(VOID16X16, "void16", "Void and cluster 16x16")
enum_value(FLOYD_STEINBERG, "floyd", "Floyd-Steinberg")
enum_value(FLOYD_FALSE, "floydfalse", "False Floyd-Steinberg")
enum_value(JJN, "jjn", "Jarvis-Judice-Ninke")
enum_value(STUCKI, "stucki", "Stucki")
enum_value(BURKES, "burkes", "Burkes")
enum_value(SIERRA, "sierra", "Sierra")
enum_value(SIERRA2ROW, "sierra2row", "Sierra 2-Row")
enum_value(FILTERLITE, "filterlite", "Filter Lite")
enum_value(ATKINSON, "atkinson", "Atkinson")
enum_end(ditherMethods)

enum_start(palettes)
enum_value(I1, "i1", "Black and white (2 colours)")
enum_value(R1G1B1, "r1g1b1", "R1G1B1 (8 colours)")
enum_value(R1G1B1I1, "r1g1b1i1", "R1G1B1I1 (16 colours)")
enum_value(R2G2B2, "r2g2b2", "R2G2B2 (64 colours)")
enum_value(R3G3B3, "r3g3b3", "R3G3B3 (512 colours)")
enum_value(MY16, "my16", "My 16 colours")
enum_value(MSWINDOWS, "windows", "Windows 3/9x/2000 default (16 colours)")
enum_value(MAC2, "mac2", "Mac II default (16 colours)")
enum_value(RISCOS, "riscos", "RISC OS 2/3 default (16 colours)")
enum_value(APPLE2_6, "apple2_6", "Apple II default (6 colours)")
enum_value(APPLE2_15, "apple2_15", "Apple II default (15 colours)")
enum_value(C64, "c64", "Commodore 64 default (16 colours)")
enum_value(MSX, "msx", "MSX default (15 colours)")
enum_value(INTELLIVISION, "intellivision", "Intellivision default (16 colours)")
enum_value(GB, "gameboy", "Game Boy default approximation (4 colours)")
enum_value(ADAPTIVE, "adaptive", "Adaptive (find best colours for this image)")
enum_value(FROMFILE, "file", "From file (load .gpl file)")
enum_end(palettes)

//Controls the amount to expand any ROI in each direction in order to give some "burn in" to error diffusion
//This allows parallel processing and prevents artifacts appearing at the top of images
#define EDD_EXPAND_X        19
#define EDD_EXPAND_Y_TOP    19
#define EDD_EXPAND_Y_BOTTOM 3

/** OkLab constants **/
const float OkLabK1 = 0.206f;
const float OkLabK2 = 0.03f;
const float OkLabK3 = 1.17087378640776f;

const float SRGBtoLMS[9] = { 0.4122214708f, 0.5363325363f, 0.0514459929f,
                             0.2119034982f, 0.6806995451f, 0.1073969566f,
                             0.0883024619f, 0.2817188376f, 0.6299787005f };

const float CRLMStoOKLab[9] = { 0.2104542553f,  0.7936177850f, -0.0040720468f,
                                1.9779984951f, -2.4285922050f,  0.4505937099f,
                                0.0259040371f,  0.7827717662f, -0.8086757660f };

const float OKLabtoCRLMS[9] = { 1.0f,  0.3963377774f,  0.2158037573f,
                                1.0f, -0.1055613458f, -0.0638541728f,
                                1.0f, -0.0894841775f, -1.2914855480f };

const float LMStoSRGB[9] = { 4.0767416621f, -3.3077115913f,  0.2309699292f,
                            -1.2684380046f,  2.6097574011f, -0.3413193965f,
                            -0.0041960863f, -0.7034186147f,  1.7076147010f };

/** Ordered dither matrices **/
const float bayer2x2[4] = { -0.5f,   0.0f,
                             0.25f, -0.25f };

const float bayer4x4[16] = { -0.5f,     0.0f,    -0.375f,   0.125f,
                              0.25f,   -0.25f,    0.375f,  -0.125f,
                             -0.3125f,  0.1875f, -0.4375f,  0.0625f,
                              0.4375f, -0.0625f,  0.3125f, -0.1875f };

const float bayer8x8[64] = { -0.5f,       0.0f,      -0.375f,     0.125f,    -0.46875f,   0.03125f,  -0.34375f,   0.15625f,
                              0.25f,     -0.25f,      0.375f,    -0.125f,     0.28125f,  -0.21875f,   0.40625f,  -0.09375f,
                             -0.3125f,    0.1875f,   -0.4375f,    0.0625f,   -0.28125f,   0.21875f,  -0.40625f,   0.09375f,
                              0.4375f,   -0.0625f,    0.3125f,   -0.1875f,    0.46875f,  -0.03125f,   0.34375f,  -0.15625f,
                             -0.453125f,  0.046875f, -0.328125f,  0.171875f, -0.484375f,  0.015625f, -0.359375f,  0.140625f,
                              0.296875f, -0.203125f,  0.421875f, -0.078125f,  0.265625f, -0.234375f,  0.390625f, -0.109375f,
                             -0.265625f,  0.234375f, -0.390625f,  0.109375f, -0.296875f,  0.203125f, -0.421875f,  0.078125f,
                              0.484375f, -0.015625f,  0.359375f, -0.140625f,  0.453125f, -0.046875f,  0.328125f, -0.171875f };

const float bayer16x16[256] = { -0.5f,         0.0f,        -0.375f,       0.125f,      -0.46875f,     0.03125f,    -0.34375f,     0.15625f,    -0.4921875f,   0.0078125f,  -0.3671875f,   0.1328125f,  -0.4609375f,   0.0390625f,  -0.3359375f,   0.1640625f,
                                 0.25f,       -0.25f,        0.375f,      -0.125f,       0.28125f,    -0.21875f,     0.40625f,    -0.09375f,     0.2578125f,  -0.2421875f,   0.3828125f,  -0.1171875f,   0.2890625f,  -0.2109375f,   0.4140625f,  -0.0859375f,
                                -0.3125f,      0.1875f,     -0.4375f,      0.0625f,     -0.28125f,     0.21875f,    -0.40625f,     0.09375f,    -0.3046875f,   0.1953125f,  -0.4296875f,   0.0703125f,  -0.2734375f,   0.2265625f,  -0.3984375f,   0.1015625f,
                                 0.4375f,     -0.0625f,      0.3125f,     -0.1875f,      0.46875f,    -0.03125f,     0.34375f,    -0.15625f,     0.4453125f,  -0.0546875f,   0.3203125f,  -0.1796875f,   0.4765625f,  -0.0234375f,   0.3515625f,  -0.1484375f,
                                -0.453125f,    0.046875f,   -0.328125f,    0.171875f,   -0.484375f,    0.015625f,   -0.359375f,    0.140625f,   -0.4453125f,   0.0546875f,  -0.3203125f,   0.1796875f,  -0.4765625f,   0.0234375f,  -0.3515625f,   0.1484375f,
                                 0.296875f,   -0.203125f,    0.421875f,   -0.078125f,    0.265625f,   -0.234375f,    0.390625f,   -0.109375f,    0.3046875f,  -0.1953125f,   0.4296875f,  -0.0703125f,   0.2734375f,  -0.2265625f,   0.3984375f,  -0.1015625f,
                                -0.265625f,    0.234375f,   -0.390625f,    0.109375f,   -0.296875f,    0.203125f,   -0.421875f,    0.078125f,   -0.2578125f,   0.2421875f,  -0.3828125f,   0.1171875f,  -0.2890625f,   0.2109375f,  -0.4140625f,   0.0859375f,
                                 0.484375f,   -0.015625f,    0.359375f,   -0.140625f,    0.453125f,   -0.046875f,    0.328125f,   -0.171875f,    0.4921875f,  -0.0078125f,   0.3671875f,  -0.1328125f,   0.4609375f,  -0.0390625f,   0.3359375f,  -0.1640625f,
                                -0.48828125f,  0.01171875f, -0.36328125f,  0.13671875f, -0.45703125f,  0.04296875f, -0.33203125f,  0.16796875f, -0.49609375f,  0.00390625f, -0.37109375f,  0.12890625f, -0.46484375f,  0.03515625f, -0.33984375f,  0.16015625f,
                                 0.26171875f, -0.23828125f,  0.38671875f, -0.11328125f,  0.29296875f, -0.20703125f,  0.41796875f, -0.08203125f,  0.25390625f, -0.24609375f,  0.37890625f, -0.12109375f,  0.28515625f, -0.21484375f,  0.41015625f, -0.08984375f,
                                -0.30078125f,  0.19921875f, -0.42578125f,  0.07421875f, -0.26953125f,  0.23046875f, -0.39453125f,  0.10546875f, -0.30859375f,  0.19140625f, -0.43359375f,  0.06640625f, -0.27734375f,  0.22265625f, -0.40234375f,  0.09765625f,
                                 0.44921875f, -0.05078125f,  0.32421875f, -0.17578125f,  0.48046875f, -0.01953125f,  0.35546875f, -0.14453125f,  0.44140625f, -0.05859375f,  0.31640625f, -0.18359375f,  0.47265625f, -0.02734375f,  0.34765625f, -0.15234375f,
                                -0.44140625f,  0.05859375f, -0.31640625f,  0.18359375f, -0.47265625f,  0.02734375f, -0.34765625f,  0.15234375f, -0.44921875f,  0.05078125f, -0.32421875f,  0.17578125f, -0.48046875f,  0.01953125f, -0.35546875f,  0.14453125f,
                                 0.30859375f, -0.19140625f,  0.43359375f, -0.06640625f,  0.27734375f, -0.22265625f,  0.40234375f, -0.09765625f,  0.30078125f, -0.19921875f,  0.42578125f, -0.07421875f,  0.26953125f, -0.23046875f,  0.39453125f, -0.10546875f,
                                -0.25390625f,  0.24609375f, -0.37890625f,  0.12109375f, -0.28515625f,  0.21484375f, -0.41015625f,  0.08984375f, -0.26171875f,  0.23828125f, -0.38671875f,  0.11328125f, -0.29296875f,  0.20703125f, -0.41796875f,  0.08203125f,
                                 0.49609375f, -0.00390625f,  0.37109375f, -0.12890625f,  0.46484375f, -0.03515625f,  0.33984375f, -0.16015625f,  0.48828125f, -0.01171875f,  0.36328125f, -0.13671875f,  0.45703125f, -0.04296875f,  0.33203125f, -0.16796875f };

const float void16x16_1[256] = { -0.35546875f, -0.05859375f,  0.4765625f,   0.1796875f,  -0.1875f,     -0.046875f,   -0.421875f,    0.1171875f,  -0.16015625f,  0.46484375f, -0.09765625f, -0.40234375f,  0.12890625f,  0.28515625f, -0.27734375f, -0.4375f,
                                  0.0546875f,  -0.20703125f, -0.3046875f,   0.296875f,    0.08203125f, -0.2734375f,   0.390625f,    0.30859375f, -0.23046875f,  0.03515625f,  0.18359375f,  0.3515625f,  -0.00390625f, -0.484375f,   -0.08984375f,  0.37109375f,
                                  0.26171875f,  0.41796875f,  0.00390625f, -0.40625f,     0.2421875f,  -0.34765625f, -0.1328125f,   0.171875f,   -0.44140625f,  0.26953125f, -0.3671875f,  -0.1796875f,   0.07421875f,  0.484375f,   -0.15625f,     0.2109375f,
                                 -0.2421875f,  -0.125f,      -0.46484375f,  0.14453125f,  0.43359375f, -0.0859375f,   0.06640625f,  0.4921875f,  -0.3125f,     -0.0390625f,   0.4296875f,  -0.2578125f,   0.25f,       -0.3203125f,  -0.4140625f,   0.11328125f,
                                 -0.37890625f,  0.32421875f, -0.03515625f, -0.171875f,    0.34375f,    -0.24609375f, -0.4921875f,  -0.0078125f,   0.328125f,    0.09765625f, -0.109375f,   -0.46875f,     0.1640625f,   0.33203125f, -0.07421875f,  0.0234375f,
                                 -0.29296875f,  0.19140625f,  0.48046875f, -0.36328125f,  0.03125f,     0.203125f,    0.2578125f,  -0.21484375f, -0.38671875f, -0.1640625f,   0.2265625f,   0.39453125f, -0.0234375f,  -0.203125f,    0.4375f,      0.2734375f,
                                  0.3828125f,   0.05859375f, -0.2265625f,   0.109375f,   -0.30078125f, -0.42578125f,  0.40625f,    -0.0703125f,   0.125f,       0.45703125f, -0.28515625f, -0.4296875f,   0.046875f,   -0.34375f,     0.13671875f, -0.49609375f,
                                 -0.15234375f, -0.41796875f, -0.0546875f,   0.29296875f,  0.44140625f, -0.1484375f,   0.16015625f,  0.35546875f, -0.33984375f,  0.2890625f,   0.01171875f,  0.1875f,     -0.13671875f,  0.359375f,   -0.25390625f, -0.09375f,
                                  0.4609375f,   0.15234375f,  0.23046875f, -0.47265625f, -0.10546875f, -0.015625f,   -0.26953125f,  0.05078125f, -0.4609375f,  -0.1015625f,  -0.22265625f, -0.39453125f,  0.47265625f,  0.23828125f,  0.09375f,     0.0f,
                                 -0.375f,      -0.19921875f,  0.34765625f, -0.328125f,    0.0859375f,   0.3125f,     -0.3984375f,  -0.18359375f,  0.38671875f,  0.21484375f,  0.078125f,    0.31640625f, -0.0625f,     -0.44921875f, -0.32421875f,  0.30078125f,
                                  0.20703125f, -0.28125f,     0.02734375f,  0.40234375f, -0.234375f,    0.24609375f,  0.48828125f,  0.17578125f, -0.04296875f, -0.30859375f,  0.42578125f,  0.1328125f,  -0.265625f,   -0.17578125f,  0.4140625f,  -0.03125f,
                                  0.375f,      -0.12890625f,  0.12109375f, -0.4453125f,  -0.06640625f, -0.359375f,    0.01953125f, -0.5f,         0.27734375f, -0.14453125f, -0.43359375f, -0.3515625f,   0.0390625f,   0.265625f,    0.15625f,    -0.48046875f,
                                  0.0703125f,  -0.41015625f,  0.46875f,    -0.16796875f,  0.19921875f,  0.421875f,   -0.12109375f,  0.1015625f,  -0.26171875f,  0.453125f,   -0.01171875f,  0.36328125f, -0.1171875f,   0.49609375f, -0.23828125f, -0.078125f,
                                 -0.31640625f,  0.28125f,    -0.01953125f,  0.3203125f,   0.140625f,   -0.296875f,   -0.2109375f,   0.3359375f,  -0.3828125f,   0.1484375f,  -0.1953125f,   0.1953125f,  -0.45703125f,  0.08984375f, -0.390625f,    0.33984375f,
                                 -0.19140625f,  0.22265625f, -0.25f,       -0.37109375f,  0.04296875f, -0.453125f,    0.25390625f, -0.08203125f,  0.37890625f,  0.0625f,     -0.05078125f,  0.3046875f,  -0.3359375f,   0.234375f,   -0.140625f,    0.015625f,
                                  0.3984375f,   0.10546875f, -0.48828125f, -0.11328125f,  0.3671875f,   0.44921875f,  0.0078125f,  -0.33203125f,  0.21875f,    -0.4765625f,  -0.2890625f,   0.41015625f, -0.21875f,    -0.02734375f,  0.4453125f,   0.16796875f };

const float void16x16_2[256] = { -0.0546875f,  -0.17578125f,  0.1328125f,   0.25f,       -0.453125f,    0.41015625f,  0.21484375f, -0.42578125f,  0.28515625f, -0.22265625f, -0.44140625f,  0.01953125f, -0.1875f,      0.38671875f, -0.35546875f,  0.08984375f,
                                 -0.41015625f, -0.25390625f,  0.375f,      -0.3359375f,  -0.109375f,    0.11328125f, -0.0625f,     -0.31640625f,  0.04296875f, -0.1171875f,   0.3671875f,   0.125f,      -0.25f,        0.203125f,   -0.00390625f,  0.46484375f,
                                  0.29296875f,  0.03515625f, -0.48046875f, -0.01171875f,  0.4609375f,  -0.2421875f,   0.33984375f,  0.1484375f,   0.453125f,   -0.37109375f,  0.2265625f,   0.4921875f,  -0.328125f,   -0.12890625f, -0.44921875f,  0.15234375f,
                                 -0.10546875f,  0.40234375f,  0.234375f,   -0.14453125f,  0.30078125f, -0.39453125f, -0.19140625f, -0.48828125f, -0.0234375f,  -0.1640625f,   0.08203125f, -0.47265625f, -0.03515625f,  0.265625f,    0.34375f,    -0.2890625f,
                                  0.09375f,    -0.21484375f,  0.1640625f,  -0.30859375f,  0.0703125f,   0.1875f,      0.015625f,    0.390625f,    0.26953125f, -0.28125f,     0.3203125f,  -0.078125f,    0.41796875f,  0.06640625f, -0.171875f,   -0.390625f,
                                 -0.04296875f, -0.36328125f,  0.48828125f, -0.43359375f, -0.0703125f,   0.43359375f, -0.34765625f, -0.09765625f,  0.20703125f, -0.23046875f, -0.421875f,    0.17578125f, -0.3515625f,  -0.26171875f,  0.22265625f,  0.4453125f,
                                  0.12890625f,  0.0078125f,   0.28125f,    -0.15625f,     0.359375f,   -0.2734375f,   0.13671875f, -0.45703125f,  0.05078125f,  0.46875f,     0.109375f,    0.37890625f, -0.203125f,    0.02734375f,  0.35546875f, -0.46484375f,
                                 -0.33203125f,  0.328125f,   -0.234375f,   -0.49609375f,  0.24609375f, -0.02734375f, -0.20703125f,  0.33203125f, -0.140625f,   -0.3203125f,  -0.0078125f,  -0.12109375f,  0.25390625f, -0.41796875f,  0.15625f,    -0.08203125f,
                                  0.421875f,   -0.125f,       0.19921875f,  0.09765625f,  0.03125f,     0.47265625f, -0.40234375f,  0.23828125f,  0.4140625f,  -0.3828125f,   0.3046875f,  -0.4921875f,  -0.046875f,    0.484375f,   -0.15234375f, -0.27734375f,
                                  0.0546875f,  -0.40625f,     0.37109375f, -0.30078125f, -0.3671875f,  -0.11328125f,  0.16796875f,  0.078125f,   -0.05859375f, -0.1796875f,   0.140625f,    0.44140625f, -0.3046875f,   0.0859375f,   0.3125f,      0.18359375f,
                                  0.2734375f,  -0.01953125f, -0.1953125f,  -0.05078125f,  0.4375f,      0.296875f,   -0.24609375f, -0.4453125f,  -0.29296875f,  0.27734375f,  0.19140625f, -0.23828125f,  0.01171875f, -0.375f,      -0.2109375f,  -0.4765625f,
                                 -0.33984375f,  0.45703125f,  0.14453125f,  0.21875f,    -0.46875f,    -0.16015625f,  0.34765625f,  0.0f,         0.3984375f,   0.0390625f,  -0.4375f,     -0.1015625f,   0.3359375f,   0.2109375f,   0.40625f,    -0.07421875f,
                                  0.10546875f, -0.2578125f,  -0.4296875f,   0.39453125f,  0.05859375f, -0.32421875f,  0.12109375f, -0.0859375f,   0.4765625f,  -0.19921875f, -0.34375f,     0.3828125f,   0.1171875f,  -0.4140625f,  -0.16796875f,  0.00390625f,
                                  0.3515625f,  -0.13671875f,  0.2890625f,  -0.09375f,    -0.2265625f,   0.1796875f,   0.2578125f,  -0.359375f,   -0.484375f,    0.1015625f,   0.23046875f, -0.1484375f,  -0.0390625f,  -0.26953125f,  0.48046875f,  0.2421875f,
                                 -0.4609375f,   0.046875f,   -0.37890625f, -0.03125f,     0.49609375f, -0.3984375f,   0.36328125f, -0.1328125f,  -0.015625f,    0.31640625f, -0.296875f,    0.44921875f,  0.0625f,     -0.5f,         0.16015625f, -0.3125f,
                                  0.42578125f,  0.1953125f,   0.32421875f, -0.28515625f,  0.0234375f,  -0.18359375f,  0.07421875f, -0.265625f,    0.4296875f,   0.171875f,   -0.06640625f, -0.38671875f,  0.26171875f,  0.30859375f, -0.08984375f, -0.21875f };

const float void16x16_3[256] = {  0.48828125f,  0.37890625f,  0.015625f,   -0.3125f,      0.35546875f, -0.48828125f,  0.078125f,   -0.23046875f, -0.30859375f,  0.41015625f, -0.4375f,      0.0f,        -0.1328125f,   0.43359375f,  0.33984375f, -0.41015625f,
                                 -0.2734375f,  -0.15234375f, -0.0703125f,  -0.21484375f,  0.2109375f,  -0.3515625f,   0.30859375f,  0.14453125f, -0.39453125f, -0.1015625f,   0.1640625f,   0.36328125f, -0.29296875f,  0.2734375f,  -0.19140625f,  0.0859375f,
                                  0.2265625f,  -0.37109375f,  0.2890625f,  -0.43359375f,  0.4140625f,  -0.0078125f,  -0.16796875f,  0.44140625f,  0.03125f,     0.2578125f,   0.0703125f,  -0.375f,      -0.0625f,      0.12109375f, -0.328125f,   -0.015625f,
                                  0.33203125f,  0.05859375f,  0.45703125f,  0.16015625f,  0.09375f,    -0.11328125f, -0.27734375f, -0.45703125f,  0.3828125f,  -0.203125f,   -0.26171875f,  0.4765625f,  -0.48046875f,  0.20703125f,  0.39453125f, -0.44921875f,
                                  0.1328125f,  -0.12890625f, -0.25390625f, -0.046875f,   -0.38671875f,  0.23828125f,  0.3359375f,  -0.07421875f,  0.1953125f,  -0.33984375f, -0.0234375f,   0.3203125f,  -0.16015625f,  0.02734375f, -0.2265625f,  -0.08984375f,
                                 -0.3046875f,  -0.5f,         0.37109375f, -0.1875f,     -0.32421875f,  0.4921875f,   0.125f,       0.01171875f, -0.41796875f,  0.29296875f, -0.1171875f,   0.10546875f,  0.41796875f, -0.421875f,    0.27734375f,  0.46484375f,
                                  0.0078125f,   0.25390625f,  0.19140625f,  0.0390625f,   0.30078125f, -0.46875f,    -0.2109375f,  -0.30078125f,  0.4609375f,   0.15234375f, -0.4609375f,   0.234375f,   -0.2890625f,  -0.05078125f,  0.171875f,   -0.35546875f,
                                 -0.20703125f,  0.40625f,    -0.4140625f,  -0.09375f,     0.421875f,   -0.03125f,     0.08203125f, -0.14453125f,  0.3984375f,   0.046875f,   -0.2421875f,   0.3671875f,  -0.3671875f,  -0.18359375f,  0.07421875f,  0.34375f,
                                 -0.02734375f,  0.1015625f,  -0.15625f,    -0.28125f,     0.13671875f,  0.21875f,    -0.40625f,     0.26953125f, -0.359375f,   -0.17578125f, -0.08203125f, -0.00390625f,  0.203125f,    0.49609375f, -0.125f,      -0.3984375f,
                                  0.4453125f,   0.16796875f, -0.4765625f,   0.32421875f, -0.34765625f, -0.23828125f,  0.359375f,   -0.05859375f,  0.18359375f,  0.328125f,   -0.44140625f,  0.4296875f,   0.11328125f, -0.484375f,    0.3046875f,  -0.265625f,
                                 -0.33203125f,  0.265625f,   -0.0546875f,   0.48046875f,  0.01953125f, -0.12109375f,  0.4375f,     -0.49609375f, -0.26953125f,  0.08984375f,  0.25f,       -0.3203125f,  -0.234375f,    0.04296875f,  0.22265625f, -0.0859375f,
                                  0.375f,      -0.21875f,     0.0546875f,  -0.3828125f,   0.23046875f, -0.1796875f,   0.0625f,      0.15625f,    -0.01171875f,  0.47265625f, -0.390625f,   -0.13671875f, -0.03515625f,  0.390625f,   -0.4296875f,   0.12890625f,
                                 -0.1484375f,  -0.453125f,    0.19921875f, -0.28515625f,  0.40234375f, -0.4453125f,   0.28515625f, -0.31640625f, -0.19921875f, -0.09765625f,  0.28125f,     0.17578125f,  0.3515625f,  -0.171875f,   -0.296875f,    0.00390625f,
                                  0.42578125f,  0.09765625f,  0.31640625f, -0.10546875f, -0.01953125f,  0.1171875f,   0.34765625f, -0.36328125f,  0.38671875f,  0.0234375f,  -0.2578125f,  -0.42578125f,  0.06640625f,  0.46875f,    -0.37890625f,  0.296875f,
                                 -0.04296875f, -0.34375f,    -0.1953125f,   0.453125f,   -0.40234375f, -0.25f,       -0.078125f,    0.1875f,     -0.46484375f,  0.109375f,    0.44921875f, -0.3359375f,  -0.06640625f,  0.1484375f,   0.2421875f,  -0.24609375f,
                                  0.1796875f,  -0.47265625f,  0.140625f,    0.26171875f,  0.05078125f, -0.140625f,    0.484375f,    0.24609375f, -0.0390625f,  -0.1640625f,   0.3125f,      0.21484375f, -0.22265625f, -0.4921875f,   0.03515625f, -0.109375f };

/** Built-in palettes (hardware palettes are converted to sRGB)**/
// This section only contains master palettes that can be fully used, in order to prevent misleading use (such as dithering for the NES's master palette, which cannot fully be used for a single frame without silly scanline tricks)
// If you want to use a different palette that's not listed here, put it in a .gpl file (coming soon)

const ColourRGBA8 i1Palette[2] = { { 0x00, 0x00, 0x00, 0xFF },
                                   { 0xFF, 0xFF, 0xFF, 0xFF } };

const ColourRGBA8 r1g1b1Palette[8] = { { 0x00, 0x00, 0x00, 0xFF },
                                       { 0xFF, 0x00, 0x00, 0xFF },
                                       { 0x00, 0xFF, 0x00, 0xFF },
                                       { 0xFF, 0xFF, 0x00, 0xFF },
                                       { 0x00, 0x00, 0xFF, 0xFF },
                                       { 0xFF, 0x00, 0xFF, 0xFF },
                                       { 0x00, 0xFF, 0xFF, 0xFF },
                                       { 0xFF, 0xFF, 0xFF, 0xFF } };

const ColourRGBA8 r1g1b1i1Palette[16] = { { 0x00, 0x00, 0x00, 0xFF },
                                          { 0x80, 0x00, 0x00, 0xFF },
                                          { 0x00, 0x80, 0x00, 0xFF },
                                          { 0x80, 0x80, 0x00, 0xFF },
                                          { 0x00, 0x00, 0x80, 0xFF },
                                          { 0x80, 0x00, 0x80, 0xFF },
                                          { 0x00, 0x80, 0x80, 0xFF },
                                          { 0x55, 0x55, 0x55, 0xFF },
                                          { 0xAA, 0xAA, 0xAA, 0xFF },
                                          { 0xFF, 0x00, 0x00, 0xFF },
                                          { 0x00, 0xFF, 0x00, 0xFF },
                                          { 0xFF, 0xFF, 0x00, 0xFF },
                                          { 0x00, 0x00, 0xFF, 0xFF },
                                          { 0xFF, 0x00, 0xFF, 0xFF },
                                          { 0x00, 0xFF, 0xFF, 0xFF },
                                          { 0xFF, 0xFF, 0xFF, 0xFF } };

//RGB palettes beyond this are generated algorithmically

//A 16-colour palette that I use a lot
const ColourRGBA8 my16Palette[16] = { { 0x11, 0x11, 0x11, 0xFF },
                                      { 0x77, 0x77, 0x77, 0xFF },
                                      { 0xBB, 0x33, 0xBB, 0xFF },
                                      { 0xFF, 0x77, 0xFF, 0xFF },
                                      { 0x77, 0x11, 0x11, 0xFF },
                                      { 0xDD, 0x44, 0x44, 0xFF },
                                      { 0xFF, 0xBB, 0x77, 0xFF },
                                      { 0xCC, 0xBB, 0x33, 0xFF },
                                      { 0x22, 0x77, 0x33, 0xFF },
                                      { 0x55, 0xDD, 0x55, 0xFF },
                                      { 0x88, 0xFF, 0x55, 0xFF },
                                      { 0xFF, 0xFF, 0x66, 0xFF },
                                      { 0x33, 0x33, 0xBB, 0xFF },
                                      { 0x33, 0xAA, 0xFF, 0xFF },
                                      { 0x99, 0xFF, 0xFF, 0xFF },
                                      { 0xFF, 0xFF, 0xFF, 0xFF } };

//Palettes for OSes

const ColourRGBA8 windowsPalette[16] = { { 0x00, 0x00, 0x00, 0xFF },
                                         { 0x80, 0x00, 0x00, 0xFF },
                                         { 0x00, 0x80, 0x00, 0xFF },
                                         { 0x80, 0x80, 0x00, 0xFF },
                                         { 0x00, 0x00, 0x80, 0xFF },
                                         { 0x80, 0x00, 0x80, 0xFF },
                                         { 0x00, 0x80, 0x80, 0xFF },
                                         { 0xC0, 0xC0, 0xC0, 0xFF },
                                         { 0x80, 0x80, 0x80, 0xFF },
                                         { 0xFF, 0x00, 0x00, 0xFF },
                                         { 0x00, 0xFF, 0x00, 0xFF },
                                         { 0xFF, 0xFF, 0x00, 0xFF },
                                         { 0x00, 0x00, 0xFF, 0xFF },
                                         { 0xFF, 0x00, 0xFF, 0xFF },
                                         { 0x00, 0xFF, 0xFF, 0xFF },
                                         { 0xFF, 0xFF, 0xFF, 0xFF } };

const ColourRGBA8 mac2Palette[16] = { { 0xFF, 0xFF, 0xFF, 0xFF },
                                      { 0xFC, 0xF4, 0x00, 0xFF },
                                      { 0xFF, 0x64, 0x00, 0xFF },
                                      { 0xDD, 0x02, 0x02, 0xFF },
                                      { 0xF1, 0x02, 0x85, 0xFF },
                                      { 0x46, 0x00, 0xA6, 0xFF },
                                      { 0x00, 0x00, 0xD5, 0xFF },
                                      { 0x00, 0xAE, 0xE9, 0xFF },
                                      { 0x1A, 0xB9, 0x0C, 0xFF },
                                      { 0x00, 0x64, 0x08, 0xFF },
                                      { 0x58, 0x28, 0x00, 0xFF },
                                      { 0x91, 0x71, 0x35, 0xFF },
                                      { 0xC1, 0xC1, 0xC1, 0xFF },
                                      { 0x81, 0x81, 0x81, 0xFF },
                                      { 0x3E, 0x3E, 0x3E, 0xFF },
                                      { 0x00, 0x00, 0x00, 0xFF } };

const ColourRGBA8 riscosPalette[16] = { { 0xFF, 0xFF, 0xFF, 0xFF },
                                        { 0xDD, 0xDD, 0xDD, 0xFF },
                                        { 0xBD, 0xBD, 0xBD, 0xFF },
                                        { 0x99, 0x99, 0x99, 0xFF },
                                        { 0x79, 0x79, 0x79, 0xFF },
                                        { 0x53, 0x53, 0x53, 0xFF },
                                        { 0x31, 0x31, 0x31, 0xFF },
                                        { 0x00, 0x00, 0x00, 0xFF },
                                        { 0x00, 0x42, 0x99, 0xFF },
                                        { 0xF0, 0xF0, 0x00, 0xFF },
                                        { 0x00, 0xCD, 0x00, 0xFF },
                                        { 0xDD, 0x00, 0x00, 0xFF },
                                        { 0xF0, 0xF0, 0xBD, 0xFF },
                                        { 0x53, 0x89, 0x00, 0xFF },
                                        { 0xFF, 0xBD, 0x00, 0xFF },
                                        { 0x00, 0xBD, 0xFF, 0xFF } };

//Palettes for PCs

const ColourRGBA8 apple2_6Palette[6] = { { 0x01, 0x01, 0x01, 0xFF },
                                         { 0xFF, 0x6B, 0xFD, 0xFF },
                                         { 0x15, 0xF5, 0x3D, 0xFF },
                                         { 0x15, 0xCF, 0xFD, 0xFF },
                                         { 0xFF, 0x6B, 0x3D, 0xFF },
                                         { 0xFF, 0xFF, 0xFF, 0xFF } };

const ColourRGBA8 apple2_15Palette[15] = { { 0x00, 0x00, 0x00, 0xFF },
                                           { 0x85, 0x3B, 0x51, 0xFF },
                                           { 0x50, 0x47, 0x89, 0xFF },
                                           { 0xEA, 0x5D, 0xF0, 0xFF },
                                           { 0x00, 0x68, 0x52, 0xFF },
                                           { 0x92, 0x92, 0x92, 0xFF },
                                           { 0x00, 0xA8, 0xF1, 0xFF },
                                           { 0xCA, 0xC3, 0xF8, 0xFF },
                                           { 0x51, 0x5C, 0x0F, 0xFF },
                                           { 0xEB, 0x7F, 0x23, 0xFF },
                                           { 0xF6, 0xB9, 0xCA, 0xFF },
                                           { 0x00, 0xCA, 0x29, 0xFF },
                                           { 0xCB, 0xD3, 0x9B, 0xFF },
                                           { 0x9A, 0xDC, 0xCB, 0xFF },
                                           { 0xFF, 0xFF, 0xFF, 0xFF } };

const ColourRGBA8 c64Palette[16] = { { 0x00, 0x00, 0x00, 0xFF },
                                     { 0xFF, 0xFF, 0xFF, 0xFF },
                                     { 0xA1, 0x4D, 0x43, 0xFF },
                                     { 0x6A, 0xC1, 0xC8, 0xFF },
                                     { 0xA2, 0x57, 0xA5, 0xFF },
                                     { 0x5C, 0xAD, 0x5F, 0xFF },
                                     { 0x50, 0x44, 0x9C, 0xFF },
                                     { 0xCD, 0xD6, 0x89, 0xFF },
                                     { 0xA3, 0x68, 0x3A, 0xFF },
                                     { 0x6E, 0x53, 0x0B, 0xFF },
                                     { 0xCC, 0x7F, 0x76, 0xFF },
                                     { 0x63, 0x63, 0x63, 0xFF },
                                     { 0x8B, 0x8B, 0x8B, 0xFF },
                                     { 0x9B, 0xE3, 0x9D, 0xFF },
                                     { 0x8A, 0x7F, 0xCD, 0xFF },
                                     { 0xAF, 0xAF, 0xAF, 0xFF } };

const ColourRGBA8 msxPalette[15] = { { 0x00, 0x00, 0x00, 0xFF },
                                     { 0x3E, 0xB8, 0x49, 0xFF },
                                     { 0x74, 0xD0, 0x7D, 0xFF },
                                     { 0x59, 0x55, 0xE0, 0xFF },
                                     { 0x80, 0x76, 0xF1, 0xFF },
                                     { 0xB9, 0x5E, 0x51, 0xFF },
                                     { 0x65, 0xDB, 0xEF, 0xFF },
                                     { 0xDB, 0x65, 0x59, 0xFF },
                                     { 0xFF, 0x89, 0x7D, 0xFF },
                                     { 0xCC, 0xC3, 0x5E, 0xFF },
                                     { 0xDE, 0xD0, 0x87, 0xFF },
                                     { 0x3A, 0xA2, 0x41, 0xFF },
                                     { 0xB7, 0x66, 0xB5, 0xFF },
                                     { 0xCC, 0xCC, 0xCC, 0xFF },
                                     { 0xFF, 0xFF, 0xFF, 0xFF } };

//Palettes for consoles

const ColourRGBA8 intellivisionPalette[16] = { { 0x00, 0x00, 0x00, 0xFF },
                                               { 0x00, 0x2D, 0xFF, 0xFF },
                                               { 0xFF, 0x3E, 0x00, 0xFF },
                                               { 0xC9, 0xD4, 0x64, 0xFF },
                                               { 0x00, 0x78, 0x0F, 0xFF },
                                               { 0x00, 0xA7, 0x20, 0xFF },
                                               { 0xFA, 0xEA, 0x27, 0xFF },
                                               { 0xFF, 0xFC, 0xFF, 0xFF },
                                               { 0xA7, 0xA8, 0xA8, 0xFF },
                                               { 0x5A, 0xCB, 0xFF, 0xFF },
                                               { 0xFF, 0xA6, 0x00, 0xFF },
                                               { 0x3C, 0x58, 0x00, 0xFF },
                                               { 0xFF, 0x32, 0x76, 0xFF },
                                               { 0xBD, 0x95, 0xFF, 0xFF },
                                               { 0x6C, 0xCD, 0x30, 0xFF },
                                               { 0xC8, 0x1A, 0x7D, 0xFF } };

//Approximation to the Game Boy's crude LCD under normal conditions
const ColourRGBA8 gameboyPalette[4] = { { 0x29, 0x41, 0x39, 0xFF },
                                        { 0x39, 0x59, 0x4A, 0xFF },
                                        { 0x5A, 0x79, 0x42, 0xFF },
                                        { 0x7B, 0x82, 0x10, 0xFF } };

volatile int hasStartedToFindBestColours;
volatile int hasFoundBestColours;
int palSize;
ColourRGBA8* selpalette;
ColourRGBA* srcpalette;
ColourOkLabA* palette;
Babl* space;
unsigned int rngNum[4];

typedef ColourRGBA OrderedDitherFunction(ColourOkLabA, int, int, float, float, float, float, float, float);
typedef ColourOkLabA ErrorDiffusionDitherFunction(ColourOkLabA, int, int, int, float, float, float, float, float, ColourOkLabA*, int, float, float);

static inline ColourRGBA SRGBToLinear(ColourRGBA c)
{
    if (c.R <= 0.04045f) c.R /= 12.92f;
    else c.R = powf((c.R + 0.055f)/1.055f, 2.4f);
    if (c.G <= 0.04045f) c.G /= 12.92f;
    else c.G = powf((c.G + 0.055f)/1.055f, 2.4f);
    if (c.B <= 0.04045f) c.B /= 12.92f;
    else c.B = powf((c.B + 0.055f)/1.055f, 2.4f);
    return c;
}

static inline ColourRGBA LinearToSRGB(ColourRGBA c)
{
    if (c.R <= 0.0031308f) c.R *= 12.92f;
    else c.R = 1.055f * powf(c.R, 1.0f/2.4f) - 0.055f;
    if (c.G <= 0.0031308f) c.G *= 12.92f;
    else c.G = 1.055f * powf(c.G, 1.0f/2.4f) - 0.055f;
    if (c.B <= 0.0031308f) c.B *= 12.92f;
    else c.B = 1.055f * powf(c.B, 1.0f/2.4f) - 0.055f;
    return c;
}

static inline ColourRGBA SRGB8ToLinearFloat(ColourRGBA8 c)
{
    ColourRGBA fltcol = { ((float)c.R)/255.0f, ((float)c.G)/255.0f, ((float)c.B)/255.0f, ((float)c.A)/255.0f };
    return SRGBToLinear(fltcol);
}

static inline ColourRGBA8 LinearFloatToSRGB8(ColourRGBA c)
{
    ColourRGBA fltcol = LinearToSRGB(c);
    int oR = (int)((fltcol.R * 255.0f) + 0.5f);
    int oG = (int)((fltcol.G * 255.0f) + 0.5f);
    int oB = (int)((fltcol.B * 255.0f) + 0.5f);
    int oA = (int)((fltcol.A * 255.0f) + 0.5f);
    if (oR > 0xFF) oR = 0xFF; else if (oR < 0) oR = 0;
    if (oG > 0xFF) oG = 0xFF; else if (oG < 0) oG = 0;
    if (oB > 0xFF) oB = 0xFF; else if (oB < 0) oB = 0;
    if (oA > 0xFF) oA = 0xFF; else if (oA < 0) oA = 0;
    ColourRGBA8 outcol = { (unsigned char)oR, (unsigned char)oG, (unsigned char)oB, (unsigned char)oA };
    return outcol;
}

static ColourOkLabA SRGBToOkLab(ColourRGBA c)
{
    float l = SRGBtoLMS[0] * c.R + SRGBtoLMS[1] * c.G + SRGBtoLMS[2] * c.B;
    float m = SRGBtoLMS[3] * c.R + SRGBtoLMS[4] * c.G + SRGBtoLMS[5] * c.B;
    float s = SRGBtoLMS[6] * c.R + SRGBtoLMS[7] * c.G + SRGBtoLMS[8] * c.B;
    l = cbrtf(l); m = cbrtf(m); s = cbrtf(s);
    float L = CRLMStoOKLab[0] * l + CRLMStoOKLab[1] * m + CRLMStoOKLab[2] * s;
    float a = CRLMStoOKLab[3] * l + CRLMStoOKLab[4] * m + CRLMStoOKLab[5] * s;
    float b = CRLMStoOKLab[6] * l + CRLMStoOKLab[7] * m + CRLMStoOKLab[8] * s;
    L = (OkLabK3 * L - OkLabK1 + sqrtf((OkLabK3 * L - OkLabK1) * (OkLabK3 * L - OkLabK1) + 4.0f * OkLabK2 * OkLabK3 * L)) * 0.5f;
    ColourOkLabA outcol = { L, a, b, c.A };
    return outcol;
}

static ColourRGBA OkLabToSRGB(ColourOkLabA c)
{
    c.L = (c.L * (c.L + OkLabK1))/(OkLabK3 * (c.L + OkLabK2));
    float l = OKLabtoCRLMS[0] * c.L + OKLabtoCRLMS[1] * c.a + OKLabtoCRLMS[2] * c.b;
    float m = OKLabtoCRLMS[3] * c.L + OKLabtoCRLMS[4] * c.a + OKLabtoCRLMS[5] * c.b;
    float s = OKLabtoCRLMS[6] * c.L + OKLabtoCRLMS[7] * c.a + OKLabtoCRLMS[8] * c.b;
    l = l*l*l; m = m*m*m; s = s*s*s;
    float R = LMStoSRGB[0] * l + LMStoSRGB[1] * m + LMStoSRGB[2] * s;
    float G = LMStoSRGB[3] * l + LMStoSRGB[4] * m + LMStoSRGB[5] * s;
    float B = LMStoSRGB[6] * l + LMStoSRGB[7] * m + LMStoSRGB[8] * s;
    ColourRGBA outcol = { R, G, B, c.A };
    return outcol;
}

static inline ColourOkLabA ColourAdjust(ColourOkLabA c, float bright, float contrast)
{
    c.L += bright;

    float contrastfac = (1.05f * (contrast + 1.0f)) / (1.05f - contrast);
    c.L -= 0.5f;
    c.L *= contrastfac; c.a *= contrastfac; c.b *= contrastfac;
    c.L += 0.5f;

    return c;
}

//xoshiro128+
static inline unsigned int RNGUpdate()
{
    unsigned int* s = rngNum;
    unsigned int r = s[0] + s[3];
    unsigned int t = s[1] << 17;
    s[2] ^= s[0];
    s[3] ^= s[1];
    s[1] ^= s[2];
    s[0] ^= s[3];
    s[2] ^= t;
    s[3] = (s[3] << 13) | (s[3] >> 19);
    return r;
}

static inline float RNGUpdateFloat()
{
    unsigned int r = RNGUpdate();
    unsigned int o = 0x3F800000; //1.0
    o |= r >> 9;
    float f = *((float*)(&o)); //Should be between 1 and ~2
    return 2.0f * (f - 1.5f); //Should be between -1 and ~1
}

static ColourRGBA GetClosestColourOkLab(ColourOkLabA col, float bright, float contrast, float uvbias)
{
    float lowestDistance = 999999999999999999999999.9;
    int chosenColour = 0;
    col = ColourAdjust(col, bright, contrast);
    for (int i = 0; i < palSize; i++)
    {
        const ColourOkLabA incol = palette[i];
        const float dL = (col.L - incol.L) * uvbias;
        const float da = col.a - incol.a;
        const float db = col.b - incol.b;
        const float dist = (dL * dL) + (da * da) + (db * db);
        if (dist < lowestDistance)
        {
            lowestDistance = dist;
            chosenColour = i;
        }
    }
    return srcpalette[chosenColour];
}

static ColourOkLabA GetClosestColourOkLabWithError(ColourOkLabA col, ColourOkLabA* error, float bright, float contrast, float uvbias, float rngAmtL, float rngAmtC)
{
    float lowestDistance = 999999999999999999999999.9;
    int chosenColour = 0;
    ColourOkLabA postcol = ColourAdjust(col, bright, contrast);
    for (int i = 0; i < palSize; i++)
    {
        const ColourOkLabA incol = palette[i];
        const float dL = (postcol.L - incol.L) * uvbias;
        const float da = postcol.a - incol.a;
        const float db = postcol.b - incol.b;
        const float dist = (dL * dL) + (da * da) + (db * db);
        if (dist < lowestDistance)
        {
            lowestDistance = dist;
            chosenColour = i;
        }
    }
    ColourOkLabA outcol = palette[chosenColour];
    error->L = col.L - outcol.L + RNGUpdateFloat()*rngAmtL;
    error->a = col.a - outcol.a + RNGUpdateFloat()*rngAmtC;
    error->b = col.b - outcol.b + RNGUpdateFloat()*rngAmtC;
    error->A = 0.0f;
    return outcol;
}

static ColourRGBA OrderedDitherBayer2x2(ColourOkLabA col, int x, int y, float amtL, float amtS, float amtH, float bright, float contrast, float uvbias)
{
    col.L += bayer2x2[(y % 2) * 2 + (x % 2)] * amtL;
    float sat = sqrtf(col.a * col.a + col.b * col.b);
    float hue = atan2f(col.b, col.a);
    const float midsat = -amtS * bayer2x2[(y % 2) * 2 + ((x + 1) % 2)];
    sat *= 1.0f + midsat;
    sat += midsat * 0.5f;
    hue += amtH * bayer4x4[((y + 1) % 2) * 2 + (x % 2)];
    col.a = sat * cosf(hue);
    col.b = sat * sinf(hue);
    return GetClosestColourOkLab(col, bright, contrast, uvbias);
}

static ColourRGBA OrderedDitherBayer4x4(ColourOkLabA col, int x, int y, float amtL, float amtS, float amtH, float bright, float contrast, float uvbias)
{
    col.L += bayer4x4[(y % 4) * 4 + (x % 4)] * amtL;
    float sat = sqrtf(col.a * col.a + col.b * col.b);
    float hue = atan2f(col.b, col.a);
    const float midsat = -amtS * bayer4x4[((y + 3) % 4) * 4 + ((x + 1) % 4)];
    sat *= 1.0f + midsat;
    sat += midsat * 0.5f;
    hue += amtH * bayer4x4[((y + 1) % 4) * 4 + ((x + 2) % 4)];
    col.a = sat * cosf(hue);
    col.b = sat * sinf(hue);
    return GetClosestColourOkLab(col, bright, contrast, uvbias);
}

static ColourRGBA OrderedDitherBayer8x8(ColourOkLabA col, int x, int y, float amtL, float amtS, float amtH, float bright, float contrast, float uvbias)
{
    col.L += bayer8x8[(y % 8) * 8 + (x % 8)] * amtL;
    float sat = sqrtf(col.a * col.a + col.b * col.b);
    float hue = atan2f(col.b, col.a);
    const float midsat = -amtS * bayer8x8[((y + 6) % 8) * 8 + ((x + 1) % 8)];
    sat *= 1.0f + midsat;
    sat += midsat * 0.5f;
    hue += amtH * bayer8x8[((y + 3) % 8) * 8 + ((x + 4) % 8)];
    col.a = sat * cosf(hue);
    col.b = sat * sinf(hue);
    return GetClosestColourOkLab(col, bright, contrast, uvbias);
}

static ColourRGBA OrderedDitherBayer16x16(ColourOkLabA col, int x, int y, float amtL, float amtS, float amtH, float bright, float contrast, float uvbias)
{
    col.L += bayer16x16[(y % 16) * 16 + (x % 16)] * amtL;
    float sat = sqrtf(col.a * col.a + col.b * col.b);
    float hue = atan2f(col.b, col.a);
    const float midsat = -amtS * bayer16x16[((y + 7) % 16) * 16 + ((x + 4) % 16)];
    sat *= 1.0f + midsat;
    sat += midsat * 0.5f;
    hue += amtH * bayer16x16[((y + 10) % 16) * 16 + ((x + 1) % 16)];
    col.a = sat * cosf(hue);
    col.b = sat * sinf(hue);
    return GetClosestColourOkLab(col, bright, contrast, uvbias);
}

static ColourRGBA OrderedDitherVoid16x16(ColourOkLabA col, int x, int y, float amtL, float amtS, float amtH, float bright, float contrast, float uvbias)
{
    int matind = (y % 16) * 16 + (x % 16);
    col.L += void16x16_1[matind] * amtL;
    float sat = sqrtf(col.a * col.a + col.b * col.b);
    float hue = atan2f(col.b, col.a);
    const float midsat = -amtS * void16x16_2[matind];
    sat *= 1.0f + midsat;
    sat += midsat * 0.5f;
    hue += amtH * void16x16_3[matind];
    col.a = sat * cosf(hue);
    col.b = sat * sinf(hue);
    return GetClosestColourOkLab(col, bright, contrast, uvbias);
}

static ColourOkLabA DitherFloydSteinberg(ColourOkLabA col, int x, int y, int w, float amtL, float amtC, float bright, float contrast, float uvbias, ColourOkLabA* diffErr, int boustro, float rngAmtL, float rngAmtC)
{
    ColourOkLabA outerr;
    ColourOkLabA* diffCol = &diffErr[x +  y * w];
    float inalpha = col.A;
    col = ColourOkLabAAddAccumulate(col, *diffCol);
    ColourOkLabA outcol = GetClosestColourOkLabWithError(col, &outerr, bright, contrast, uvbias, rngAmtL, rngAmtC);

    diffCol = &diffErr[(x + boustro) +  y * w];
    const ColourOkLabA coeff1 = { 0.4375f * amtL,  0.4375f * amtC, 0.4375f * amtC, 1.0f };
    *diffCol = ColourOkLabAFMAAccumulate(*diffCol, outerr, coeff1);
    diffCol = &diffErr[(x - boustro) + (y + 1) * w];
    const ColourOkLabA coeff2 = { 0.1875f * amtL,  0.1875f * amtC, 0.1875f * amtC, 1.0f };
    *diffCol = ColourOkLabAFMAAccumulate(*diffCol, outerr, coeff2);
    diffCol = &diffErr[ x            + (y + 1) * w];
    const ColourOkLabA coeff3 = { 0.3125f * amtL,  0.3125f * amtC, 0.3125f * amtC, 1.0f };
    *diffCol = ColourOkLabAFMAAccumulate(*diffCol, outerr, coeff3);
    diffCol = &diffErr[(x + boustro) + (y + 1) * w];
    const ColourOkLabA coeff4 = { 0.0625f * amtL,  0.0625f * amtC, 0.0625f * amtC, 1.0f };
    *diffCol = ColourOkLabAFMAAccumulate(*diffCol, outerr, coeff4);

    outcol.A = inalpha;
    return outcol;
}

static ColourOkLabA DitherFloydFalse(ColourOkLabA col, int x, int y, int w, float amtL, float amtC, float bright, float contrast, float uvbias, ColourOkLabA* diffErr, int boustro, float rngAmtL, float rngAmtC)
{
    ColourOkLabA outerr;
    ColourOkLabA* diffCol = &diffErr[x +  y * w];
    float inalpha = col.A;
    col = ColourOkLabAAddAccumulate(col, *diffCol);
    ColourOkLabA outcol = GetClosestColourOkLabWithError(col, &outerr, bright, contrast, uvbias, rngAmtL, rngAmtC);

    const ColourOkLabA coeff1 = { 0.375f * amtL, 0.375f * amtC, 0.375f * amtC, 1.0f };
    const ColourOkLabA errc = ColourOkLabAMultiply(outerr, coeff1);
    diffCol = &diffErr[(x + boustro) +  y * w];
    *diffCol = ColourOkLabAAddAccumulate(*diffCol, errc);
    diffCol = &diffErr[ x            + (y + 1) * w];
    *diffCol = ColourOkLabAAddAccumulate(*diffCol, errc);
    const ColourOkLabA coeff2 = { 0.25f * amtL, 0.25f * amtC, 0.25f * amtC, 1.0f };
    diffCol = &diffErr[(x + boustro) + (y + 1) * w];
    *diffCol = ColourOkLabAFMAAccumulate(*diffCol, outerr, coeff2);

    outcol.A = inalpha;
    return outcol;
}

static ColourOkLabA DitherJJN(ColourOkLabA col, int x, int y, int w, float amtL, float amtC, float bright, float contrast, float uvbias, ColourOkLabA* diffErr, int boustro, float rngAmtL, float rngAmtC)
{
    ColourOkLabA outerr;
    ColourOkLabA* diffCol = &diffErr[x +  y * w];
    float inalpha = col.A;
    col = ColourOkLabAAddAccumulate(col, *diffCol);
    ColourOkLabA outcol = GetClosestColourOkLabWithError(col, &outerr, bright, contrast, uvbias, rngAmtL, rngAmtC);

    const ColourOkLabA coeff1 = { (7.0f/48.0f) * amtL, (7.0f/48.0f) * amtC, (7.0f/48.0f) * amtC, 1.0f };
    ColourOkLabA errc = ColourOkLabAMultiply(outerr, coeff1);
    diffCol = &diffErr[(x + boustro) +  y * w];
    *diffCol = ColourOkLabAAddAccumulate(*diffCol, errc);
    diffCol = &diffErr[ x            + (y + 1) * w];
    *diffCol = ColourOkLabAAddAccumulate(*diffCol, errc);

    const ColourOkLabA coeff2 = { (5.0f/48.0f) * amtL, (5.0f/48.0f) * amtC, (5.0f/48.0f) * amtC, 1.0f };
    errc = ColourOkLabAMultiply(outerr, coeff2);
    diffCol = &diffErr[(x + 2 * boustro) +  y * w];
    *diffCol = ColourOkLabAAddAccumulate(*diffCol, errc);
    diffCol = &diffErr[(x + boustro)     + (y + 1) * w];
    *diffCol = ColourOkLabAAddAccumulate(*diffCol, errc);
    diffCol = &diffErr[ x                + (y + 2) * w];
    *diffCol = ColourOkLabAAddAccumulate(*diffCol, errc);
    diffCol = &diffErr[(x - boustro)     + (y + 1) * w];
    *diffCol = ColourOkLabAAddAccumulate(*diffCol, errc);

    const ColourOkLabA coeff3 = { (3.0f/48.0f) * amtL, (3.0f/48.0f) * amtC, (3.0f/48.0f) * amtC, 1.0f };
    errc = ColourOkLabAMultiply(outerr, coeff3);
    diffCol = &diffErr[(x + 2 * boustro) + (y + 1) * w];
    *diffCol = ColourOkLabAAddAccumulate(*diffCol, errc);
    diffCol = &diffErr[(x + boustro)     + (y + 2) * w];
    *diffCol = ColourOkLabAAddAccumulate(*diffCol, errc);
    diffCol = &diffErr[(x - boustro)     + (y + 2) * w];
    *diffCol = ColourOkLabAAddAccumulate(*diffCol, errc);
    diffCol = &diffErr[(x - 2 * boustro) + (y + 1) * w];
    *diffCol = ColourOkLabAAddAccumulate(*diffCol, errc);

    const ColourOkLabA coeff4 = { (1.0f/48.0f) * amtL, (1.0f/48.0f) * amtC, (1.0f/48.0f) * amtC, 1.0f };
    errc = ColourOkLabAMultiply(outerr, coeff4);
    diffCol = &diffErr[(x + 2 * boustro) + (y + 2) * w];
    *diffCol = ColourOkLabAAddAccumulate(*diffCol, errc);
    diffCol = &diffErr[(x - 2 * boustro) + (y + 2) * w];
    *diffCol = ColourOkLabAAddAccumulate(*diffCol, errc);

    outcol.A = inalpha;
    return outcol;
}

static ColourOkLabA DitherStucki(ColourOkLabA col, int x, int y, int w, float amtL, float amtC, float bright, float contrast, float uvbias, ColourOkLabA* diffErr, int boustro, float rngAmtL, float rngAmtC)
{
    ColourOkLabA outerr;
    ColourOkLabA* diffCol = &diffErr[x +  y * w];
    float inalpha = col.A;
    col = ColourOkLabAAddAccumulate(col, *diffCol);
    ColourOkLabA outcol = GetClosestColourOkLabWithError(col, &outerr, bright, contrast, uvbias, rngAmtL, rngAmtC);

    const ColourOkLabA coeff1 = { (8.0f/42.0f) * amtL, (8.0f/42.0f) * amtC, (8.0f/42.0f) * amtC, 1.0f };
    ColourOkLabA errc = ColourOkLabAMultiply(outerr, coeff1);
    diffCol = &diffErr[(x + boustro) +  y * w];
    *diffCol = ColourOkLabAAddAccumulate(*diffCol, errc);
    diffCol = &diffErr[ x            + (y + 1) * w];
    *diffCol = ColourOkLabAAddAccumulate(*diffCol, errc);

    const ColourOkLabA coeff2 = { (4.0f/42.0f) * amtL, (4.0f/42.0f) * amtC, (4.0f/42.0f) * amtC, 1.0f };
    errc = ColourOkLabAMultiply(outerr, coeff2);
    diffCol = &diffErr[(x + 2 * boustro) +  y * w];
    *diffCol = ColourOkLabAAddAccumulate(*diffCol, errc);
    diffCol = &diffErr[(x + boustro)     + (y + 1) * w];
    *diffCol = ColourOkLabAAddAccumulate(*diffCol, errc);
    diffCol = &diffErr[ x                + (y + 2) * w];
    *diffCol = ColourOkLabAAddAccumulate(*diffCol, errc);
    diffCol = &diffErr[(x - boustro)     + (y + 1) * w];
    *diffCol = ColourOkLabAAddAccumulate(*diffCol, errc);

    const ColourOkLabA coeff3 = { (2.0f/42.0f) * amtL, (2.0f/42.0f) * amtC, (2.0f/42.0f) * amtC, 1.0f };
    errc = ColourOkLabAMultiply(outerr, coeff3);
    diffCol = &diffErr[(x + 2 * boustro) + (y + 1) * w];
    *diffCol = ColourOkLabAAddAccumulate(*diffCol, errc);
    diffCol = &diffErr[(x + boustro)     + (y + 2) * w];
    *diffCol = ColourOkLabAAddAccumulate(*diffCol, errc);
    diffCol = &diffErr[(x - boustro)     + (y + 2) * w];
    *diffCol = ColourOkLabAAddAccumulate(*diffCol, errc);
    diffCol = &diffErr[(x - 2 * boustro) + (y + 1) * w];
    *diffCol = ColourOkLabAAddAccumulate(*diffCol, errc);

    const ColourOkLabA coeff4 = { (1.0f/42.0f) * amtL, (1.0f/42.0f) * amtC, (1.0f/42.0f) * amtC, 1.0f };
    errc = ColourOkLabAMultiply(outerr, coeff4);
    diffCol = &diffErr[(x + 2 * boustro) + (y + 2) * w];
    *diffCol = ColourOkLabAAddAccumulate(*diffCol, errc);
    diffCol = &diffErr[(x - 2 * boustro) + (y + 2) * w];
    *diffCol = ColourOkLabAAddAccumulate(*diffCol, errc);

    outcol.A = inalpha;
    return outcol;
}

static ColourOkLabA DitherBurkes(ColourOkLabA col, int x, int y, int w, float amtL, float amtC, float bright, float contrast, float uvbias, ColourOkLabA* diffErr, int boustro, float rngAmtL, float rngAmtC)
{
    ColourOkLabA outerr;
    ColourOkLabA* diffCol = &diffErr[x +  y * w];
    float inalpha = col.A;
    col = ColourOkLabAAddAccumulate(col, *diffCol);
    ColourOkLabA outcol = GetClosestColourOkLabWithError(col, &outerr, bright, contrast, uvbias, rngAmtL, rngAmtC);

    const ColourOkLabA coeff1 = { (8.0f/32.0f) * amtL, (8.0f/32.0f) * amtC, (8.0f/32.0f) * amtC, 1.0f };
    ColourOkLabA errc = ColourOkLabAMultiply(outerr, coeff1);
    diffCol = &diffErr[(x + boustro) +  y * w];
    *diffCol = ColourOkLabAAddAccumulate(*diffCol, errc);
    diffCol = &diffErr[ x            + (y + 1) * w];
    *diffCol = ColourOkLabAAddAccumulate(*diffCol, errc);

    const ColourOkLabA coeff2 = { (4.0f/32.0f) * amtL, (4.0f/32.0f) * amtC, (4.0f/32.0f) * amtC, 1.0f };
    errc = ColourOkLabAMultiply(outerr, coeff2);
    diffCol = &diffErr[(x + 2 * boustro) +  y * w];
    *diffCol = ColourOkLabAAddAccumulate(*diffCol, errc);
    diffCol = &diffErr[(x + boustro)     + (y + 1) * w];
    *diffCol = ColourOkLabAAddAccumulate(*diffCol, errc);
    diffCol = &diffErr[(x - boustro)     + (y + 1) * w];
    *diffCol = ColourOkLabAAddAccumulate(*diffCol, errc);

    const ColourOkLabA coeff3 = { (2.0f/32.0f) * amtL, (2.0f/32.0f) * amtC, (2.0f/32.0f) * amtC, 1.0f };
    errc = ColourOkLabAMultiply(outerr, coeff3);
    diffCol = &diffErr[(x + 2 * boustro) + (y + 1) * w];
    *diffCol = ColourOkLabAAddAccumulate(*diffCol, errc);
    diffCol = &diffErr[(x - 2 * boustro) + (y + 1) * w];
    *diffCol = ColourOkLabAAddAccumulate(*diffCol, errc);

    outcol.A = inalpha;
    return outcol;
}

static ColourOkLabA DitherSierra(ColourOkLabA col, int x, int y, int w, float amtL, float amtC, float bright, float contrast, float uvbias, ColourOkLabA* diffErr, int boustro, float rngAmtL, float rngAmtC)
{
    ColourOkLabA outerr;
    ColourOkLabA* diffCol = &diffErr[x +  y * w];
    float inalpha = col.A;
    col = ColourOkLabAAddAccumulate(col, *diffCol);
    ColourOkLabA outcol = GetClosestColourOkLabWithError(col, &outerr, bright, contrast, uvbias, rngAmtL, rngAmtC);

    const ColourOkLabA coeff1 = { (5.0f/32.0f) * amtL, (5.0f/32.0f) * amtC, (5.0f/32.0f) * amtC, 1.0f };
    ColourOkLabA errc = ColourOkLabAMultiply(outerr, coeff1);
    diffCol = &diffErr[(x + boustro) +  y * w];
    *diffCol = ColourOkLabAAddAccumulate(*diffCol, errc);
    diffCol = &diffErr[ x            + (y + 1) * w];
    *diffCol = ColourOkLabAAddAccumulate(*diffCol, errc);

    const ColourOkLabA coeff2 = { (4.0f/32.0f) * amtL, (4.0f/32.0f) * amtC, (4.0f/32.0f) * amtC, 1.0f };
    errc = ColourOkLabAMultiply(outerr, coeff2);
    diffCol = &diffErr[(x + boustro)     + (y + 1) * w];
    *diffCol = ColourOkLabAAddAccumulate(*diffCol, errc);
    diffCol = &diffErr[(x - boustro)     + (y + 1) * w];
    *diffCol = ColourOkLabAAddAccumulate(*diffCol, errc);

    const ColourOkLabA coeff3 = { (3.0f/32.0f) * amtL, (3.0f/32.0f) * amtC, (3.0f/32.0f) * amtC, 1.0f };
    errc = ColourOkLabAMultiply(outerr, coeff3);
    diffCol = &diffErr[(x + 2 * boustro) +  y * w];
    *diffCol = ColourOkLabAAddAccumulate(*diffCol, errc);
    diffCol = &diffErr[ x                + (y + 2) * w];
    *diffCol = ColourOkLabAAddAccumulate(*diffCol, errc);

    const ColourOkLabA coeff4 = { (2.0f/32.0f) * amtL, (2.0f/32.0f) * amtC, (2.0f/32.0f) * amtC, 1.0f };
    errc = ColourOkLabAMultiply(outerr, coeff4);
    diffCol = &diffErr[(x + 2 * boustro) + (y + 1) * w];
    *diffCol = ColourOkLabAAddAccumulate(*diffCol, errc);
    diffCol = &diffErr[(x + boustro)     + (y + 2) * w];
    *diffCol = ColourOkLabAAddAccumulate(*diffCol, errc);
    diffCol = &diffErr[(x - boustro)     + (y + 2) * w];
    *diffCol = ColourOkLabAAddAccumulate(*diffCol, errc);
    diffCol = &diffErr[(x - 2 * boustro) + (y + 1) * w];
    *diffCol = ColourOkLabAAddAccumulate(*diffCol, errc);

    outcol.A = inalpha;
    return outcol;
}

static ColourOkLabA DitherSierra2Row(ColourOkLabA col, int x, int y, int w, float amtL, float amtC, float bright, float contrast, float uvbias, ColourOkLabA* diffErr, int boustro, float rngAmtL, float rngAmtC)
{
    ColourOkLabA outerr;
    ColourOkLabA* diffCol = &diffErr[x +  y * w];
    float inalpha = col.A;
    col = ColourOkLabAAddAccumulate(col, *diffCol);
    ColourOkLabA outcol = GetClosestColourOkLabWithError(col, &outerr, bright, contrast, uvbias, rngAmtL, rngAmtC);

    const ColourOkLabA coeff1 = { (4.0f/16.0f) * amtL, (4.0f/16.0f) * amtC, (4.0f/16.0f) * amtC, 1.0f };
    diffCol = &diffErr[(x + boustro) +  y * w];
    *diffCol = ColourOkLabAFMAAccumulate(*diffCol, outerr, coeff1);

    const ColourOkLabA coeff2 = { (3.0f/16.0f) * amtL, (3.0f/16.0f) * amtC, (3.0f/16.0f) * amtC, 1.0f };
    ColourOkLabA errc = ColourOkLabAMultiply(outerr, coeff2);
    diffCol = &diffErr[(x + 2 * boustro) +  y * w];
    *diffCol = ColourOkLabAAddAccumulate(*diffCol, errc);
    diffCol = &diffErr[ x                + (y + 1) * w];
    *diffCol = ColourOkLabAAddAccumulate(*diffCol, errc);

    const ColourOkLabA coeff3 = { (2.0f/16.0f) * amtL, (2.0f/16.0f) * amtC, (2.0f/16.0f) * amtC, 1.0f };
    errc = ColourOkLabAMultiply(outerr, coeff3);
    diffCol = &diffErr[(x + boustro)     + (y + 1) * w];
    *diffCol = ColourOkLabAAddAccumulate(*diffCol, errc);
    diffCol = &diffErr[(x - boustro)     + (y + 1) * w];
    *diffCol = ColourOkLabAAddAccumulate(*diffCol, errc);

    const ColourOkLabA coeff4 = { (1.0f/16.0f) * amtL, (1.0f/16.0f) * amtC, (1.0f/16.0f) * amtC, 1.0f };
    errc = ColourOkLabAMultiply(outerr, coeff4);
    diffCol = &diffErr[(x + 2 * boustro) + (y + 1) * w];
    *diffCol = ColourOkLabAAddAccumulate(*diffCol, errc);
    diffCol = &diffErr[(x - 2 * boustro) + (y + 1) * w];
    *diffCol = ColourOkLabAAddAccumulate(*diffCol, errc);

    outcol.A = inalpha;
    return outcol;
}

static ColourOkLabA DitherFilterLite(ColourOkLabA col, int x, int y, int w, float amtL, float amtC, float bright, float contrast, float uvbias, ColourOkLabA* diffErr, int boustro, float rngAmtL, float rngAmtC)
{
    ColourOkLabA outerr;
    ColourOkLabA* diffCol = &diffErr[x +  y * w];
    float inalpha = col.A;
    col = ColourOkLabAAddAccumulate(col, *diffCol);
    ColourOkLabA outcol = GetClosestColourOkLabWithError(col, &outerr, bright, contrast, uvbias, rngAmtL, rngAmtC);

    const ColourOkLabA coeff1 = { 0.5f * amtL, 0.5f * amtC, 0.5f * amtC, 1.0f };
    diffCol = &diffErr[(x + boustro) +  y * w];
    *diffCol = ColourOkLabAFMAAccumulate(*diffCol, outerr, coeff1);
    const ColourOkLabA coeff2 = { 0.25f * amtL, 0.25f * amtC, 0.25f * amtC, 1.0f };
    const ColourOkLabA errc = ColourOkLabAMultiply(outerr, coeff2);
    diffCol = &diffErr[ x            + (y + 1) * w];
    *diffCol = ColourOkLabAAddAccumulate(*diffCol, errc);
    diffCol = &diffErr[(x - boustro) + (y + 1) * w];
    *diffCol = ColourOkLabAAddAccumulate(*diffCol, errc);

    outcol.A = inalpha;
    return outcol;
}

static ColourOkLabA DitherAtkinson(ColourOkLabA col, int x, int y, int w, float amtL, float amtC, float bright, float contrast, float uvbias, ColourOkLabA* diffErr, int boustro, float rngAmtL, float rngAmtC)
{
    ColourOkLabA outerr;
    ColourOkLabA* diffCol = &diffErr[x +  y * w];
    float inalpha = col.A;
    col = ColourOkLabAAddAccumulate(col, *diffCol);
    ColourOkLabA outcol = GetClosestColourOkLabWithError(col, &outerr, bright, contrast, uvbias, rngAmtL, rngAmtC);

    const ColourOkLabA coeff = { amtL/6.0f, amtC/6.0f, amtC/6.0f, 1.0f }; //Note: the canonical Atkinson dither only diffuses 3/4 of the error, but we'll normalise this one anyway
    const ColourOkLabA errc = ColourOkLabAMultiply(outerr, coeff);
    diffCol = &diffErr[(x + boustro)     +  y * w];
    *diffCol = ColourOkLabAAddAccumulate(*diffCol, errc);
    diffCol = &diffErr[(x + 2 * boustro) +  y * w];
    *diffCol = ColourOkLabAAddAccumulate(*diffCol, errc);
    diffCol = &diffErr[(x - boustro)     + (y + 1) * w];
    *diffCol = ColourOkLabAAddAccumulate(*diffCol, errc);
    diffCol = &diffErr[ x                + (y + 1) * w];
    *diffCol = ColourOkLabAAddAccumulate(*diffCol, errc);
    diffCol = &diffErr[(x + boustro)     + (y + 1) * w];
    *diffCol = ColourOkLabAAddAccumulate(*diffCol, errc);
    diffCol = &diffErr[ x                + (y + 2) * w];
    *diffCol = ColourOkLabAAddAccumulate(*diffCol, errc);

    outcol.A = inalpha;
    return outcol;
}

typedef struct
{
    ColourOkLabA mean;
    ColourOkLabA lastmean;
    long long numInCluster;
    double sumL;
    double suma;
    double sumb;
} KMean;

ColourOkLabA* adptColours;
KMean* adptMeans;
long long adptNumPixels;
int adptNumColours;
float adptuvbias;
volatile long long adptCurrentStartPixel;
volatile int canStartNewParallelLoops;
volatile int numThreadsSpawned;
#define MAX_ADAPTIVE_THREADS 2048
#define ADAPTIVE_CHUNKSIZE 8191
volatile unsigned char adptThreadActive[MAX_ADAPTIVE_THREADS];

//Main embarrasingly parallel loop in the palette-finding function
static int GetBestPaletteParallelLoop()
{
    if (!canStartNewParallelLoops) return 1;
    long long s = adptCurrentStartPixel;
    adptCurrentStartPixel += ADAPTIVE_CHUNKSIZE;
    long long e;
    if (!canStartNewParallelLoops) return 1;
    if (adptCurrentStartPixel > adptNumPixels)
    {
        e = adptNumPixels;
        if (!canStartNewParallelLoops) return 1;
        canStartNewParallelLoops = 0;
    }
    else e = s + ADAPTIVE_CHUNKSIZE;
    ColourOkLabA* colours = adptColours;
    KMean* means = adptMeans;
    int numColours = adptNumColours;
    float uvbias = adptuvbias;
    for (long long i = s; i < e; i++)
    {
        ColourOkLabA col = colours[i];
        float lowestDistance = 999999999999999999999999.9;
        int chosenColour = 0;
        for (int j = 0; j < numColours; j++)
        {
            const ColourOkLabA incol = means[j].mean;
            const float dL = (col.L - incol.L) * uvbias;
            const float da = col.a - incol.a;
            const float db = col.b - incol.b;
            const float dist = (dL * dL) + (da * da) + (db * db);
            if (dist < lowestDistance)
            {
                lowestDistance = dist;
                chosenColour = j;
            }
        }
        KMean* m = &means[chosenColour];
        m->sumL += col.L;
        m->suma += col.a;
        m->sumb += col.b;
        m->numInCluster++;
    }
    if (!canStartNewParallelLoops) return 1;
    else return 0;
}

//Currently uses the k-means algorithm
static void GetBestPalette(ColourRGBA8* pal, int numColours, ColourRGBA* pixels, int w, int h, float uvbias, float bright, float contrast)
{
    long long fullNumPixels = w * h;
    ColourOkLabA* fullColours = malloc(fullNumPixels * sizeof(ColourOkLabA));
    KMean* means = malloc(numColours * sizeof(KMean));
    //Initialise means
    for (int i = 0; i < numColours; i++)
    {
        KMean m;
        m.numInCluster = 0;
        m.sumL = 0.0; m.suma = 0.0; m.sumb = 0.0;
        means[i] = m;
    }
    //Initialise colour array
    for (long long i = 0; i < fullNumPixels; i++)
    {
        fullColours[i] = ColourAdjust(SRGBToOkLab(pixels[i]), bright, contrast);
    }
    //Subsample image (we don't need to sample EVERY SINGLE PIXEL in most images)
    int xSubsampleFactor = (w / 768) + 1;
    int ySubsampleFactor = (h / 768) + 1;
    int newWidth = w / xSubsampleFactor;
    int newHeight = h / ySubsampleFactor;
    float mF = (float)(1.0 / (double)(xSubsampleFactor * ySubsampleFactor));
    ColourOkLabA multFac = { mF, mF, mF, mF };
    long long numPixels = newWidth * newHeight;
    ColourOkLabA* colours = malloc(numPixels * sizeof(ColourOkLabA));
    for (int i = 0; i < newHeight; i++)
    {
        for (int j = 0; j < newWidth; j++)
        {
            long long inIndex = (j * xSubsampleFactor) + (i * w * ySubsampleFactor);
            ColourOkLabA* sampRect = fullColours + inIndex;
            ColourOkLabA sumC = { 0.0f, 0.0f, 0.0f, 0.0f };
            for (int v = 0; v < ySubsampleFactor; v++)
            {
                for (int u = 0; u < xSubsampleFactor; u++)
                {
                    ColourOkLabA sampCol = sampRect[u + v * w];
                    sumC = ColourOkLabAAddAccumulate(sumC, sampCol);
                }
            }
            colours[j + i * newWidth] = ColourOkLabAMultiply(sumC, multFac);
        }
    }
    free(fullColours);
    //Pick some means (k-means||)
    ColourOkLabA* csamples = (ColourOkLabA*)malloc(17 * numColours * sizeof(ColourOkLabA));
    double* probs = (double*)malloc(numPixels * sizeof(double));
    unsigned long long rnum = RNGUpdate() % numPixels;
    csamples[0] = colours[rnum];
    int totalSamples = 1;
    int sampPerIter = 2 * numColours;
    //Pick some initial points
    for (int i = 0; i < 8; i++)
    {
        //Cost calculation
        double cost = 0.0;
        for (long long j = 0; j < numPixels; j++)
        {
            ColourOkLabA col = colours[j];
            float lowestDistance = 999999999999999999999999.9;
            for (int k = 0; k < totalSamples; k++)
            {
                const ColourOkLabA incol = csamples[k];
                const float dL = (col.L - incol.L) * uvbias;
                const float da = col.a - incol.a;
                const float db = col.b - incol.b;
                const float dist = (dL * dL) + (da * da) + (db * db);
                if (dist < lowestDistance)
                {
                    lowestDistance = dist;
                }
            }
            cost += (double)lowestDistance;
            probs[j] = (double)lowestDistance;
        }
        double probmod = ((double)sampPerIter)/cost;
        double cumProb = 0.0; //hee hee
        for (long long j = 0; j < numPixels; j++)
        {
            cumProb += probmod * probs[j];
            probs[j] = cumProb;
        }
        //Pick samples
        for (int j = 0; j < sampPerIter; j++)
        {
            double p = ((double)((RNGUpdateFloat() * 0.5f) + 0.5f)) * cumProb;
            long long ind = numPixels/2;
            long long lBound = 0;
            long long uBound = numPixels - 1;
            while (ind != lBound || ind != uBound)
            {
                if (p < probs[ind])
                {
                    uBound = ind;
                }
                else
                {
                    lBound = ind + 1;
                }
                ind = lBound + ((uBound - lBound)/2);
            }
            csamples[totalSamples] = colours[ind];
            totalSamples++;
        }
    }
    //Weight the points
    long long* weights = (long long*)calloc(totalSamples, sizeof(long long));
    for (long long i = 0; i < numPixels; i++)
    {
        ColourOkLabA col = colours[i];
        float lowestDistance = 999999999999999999999999.9;
        int chosenColour = 0;
        for (int j = 0; j < totalSamples; j++)
        {
            const ColourOkLabA incol = csamples[j];
            const float dL = (col.L - incol.L) * uvbias;
            const float da = col.a - incol.a;
            const float db = col.b - incol.b;
            const float dist = (dL * dL) + (da * da) + (db * db);
            if (dist < lowestDistance)
            {
                lowestDistance = dist;
                chosenColour = j;
            }
        }
        weights[chosenColour]++;
    }
    //Recluster according to k-means++
    KMean* initM = &means[0];
    rnum = RNGUpdate() % totalSamples;
    initM->mean = csamples[rnum];
    for (int i = 1; i < numColours; i++)
    {
        //Cost calculation
        double cost = 0.0;
        for (int j = 0; j < totalSamples; j++)
        {
            ColourOkLabA col = csamples[j];
            float lowestDistance = 999999999999999999999999.9;
            for (int k = 0; k < i; k++)
            {
                const ColourOkLabA incol = means[k].mean;
                const float dL = (col.L - incol.L) * uvbias;
                const float da = col.a - incol.a;
                const float db = col.b - incol.b;
                const float dist = (dL * dL) + (da * da) + (db * db);
                if (dist < lowestDistance)
                {
                    lowestDistance = dist;
                }
            }
            cost += (double)lowestDistance;
            probs[j] = (double)lowestDistance;
        }
        double probmod = ((double)sampPerIter)/cost;
        double cumProb = 0.0; //hee hee
        for (long long j = 0; j < totalSamples; j++)
        {
            cumProb += probmod * probs[j] * ((double)weights[j]);
            probs[j] = cumProb;
        }
        double p = ((double)((RNGUpdateFloat() * 0.5f) + 0.5f)) * cumProb;
        int ind = totalSamples/2;
        int lBound = 0;
        int uBound = totalSamples - 1;
        while (ind != lBound || ind != uBound)
        {
            if (p < probs[ind])
            {
                uBound = ind;
            }
            else
            {
                lBound = ind + 1;
            }
            ind = lBound + ((uBound - lBound)/2);
        }
        means[i].mean = csamples[ind];
    }

    free(probs);
    free(weights);
    free(csamples);

    adptColours = colours;
    adptMeans = means;
    adptNumColours = numColours;
    adptNumPixels = numPixels;
    adptuvbias = uvbias;

    //Iterate the means
    /*/
    int iterationsLeft = 696969;
    double lastMeandiff = 999999999999999999999999.9;
    while (iterationsLeft > 0)
    {
        //Zero out sums and counts
        for (int i = 0; i < numColours; i++)
        {
            KMean m = means[i];
            m.lastmean = m.mean;
            m.numInCluster = 0;
            m.sumL = 0.0; m.suma = 0.0; m.sumb = 0.0;
            means[i] = m;
        }
        //Associate each colour with the closest mean
        for (long long i = 0; i < ADAPTIVE_CHUNKSIZE; i++)
        {
            ColourOkLabA col = colours[i];
            float lowestDistance = 999999999999999999999999.9;
            int chosenColour = 0;
            for (int j = 0; j < numColours; j++)
            {
                const ColourOkLabA incol = means[j].mean;
                const float dL = (col.L - incol.L) * uvbias;
                const float da = col.a - incol.a;
                const float db = col.b - incol.b;
                const float dist = (dL * dL) + (da * da) + (db * db);
                if (dist < lowestDistance)
                {
                    lowestDistance = dist;
                    chosenColour = j;
                }
            }
            KMean m = means[chosenColour];
            m.sumL += (double)col.L;
            m.suma += (double)col.a;
            m.sumb += (double)col.b;
            m.numInCluster++;
            means[chosenColour] = m;
        }
        adptCurrentStartPixel = ADAPTIVE_CHUNKSIZE;
        canStartNewParallelLoops = 1;
        adptThreadActive[0] = 1;
        while (1)
        {
            if (GetBestPaletteParallelLoop())
            {
                adptThreadActive[0] = 0;
                int allThreadsDone = 1;
                for (int i = 0; i < numThreadsSpawned; i++)
                {
                    if (adptThreadActive[i])
                    {
                        allThreadsDone = 0;
                        break;
                    }
                }
                if (allThreadsDone) break;
            }
        }

        //Calculate means
        double meandiff = 0.0;
        for (int i = 0; i < numColours; i++)
        {
            KMean m = means[i];
            ColourOkLabA meancol;
            if (m.numInCluster <= 0) //Fallback because of suspected division by zero errors;
            {
                meancol.L = (RNGUpdateFloat() * 0.5f) + 0.5f;
                meancol.a = RNGUpdateFloat() * 0.5f;
                meancol.b = RNGUpdateFloat() * 0.5f;
            }
            else
            {
                meancol.L = m.sumL/((double)m.numInCluster);
                meancol.a = m.suma/((double)m.numInCluster);
                meancol.b = m.sumb/((double)m.numInCluster);
            }
            meancol.A = 1.0f;
            m.mean = meancol;
            const float dL = (m.mean.L - m.lastmean.L) * uvbias;
            const float da = m.mean.a - m.lastmean.a;
            const float db = m.mean.b - m.lastmean.b;
            const float dist = (dL * dL) + (da * da) + (db * db);
            meandiff += sqrt((double)dist);
            means[i] = m;
        }
        if (meandiff < 0.00001 && lastMeandiff <= meandiff) //Break out if convergence has been reached
        {
            iterationsLeft = 0;
            for (int i = 0; i < numColours; i++)
            {
                means[i].mean = means[i].lastmean;
            }
        }
        iterationsLeft--;
        lastMeandiff = meandiff;
    }
    //*/

    /**/
    int iterationsLeft = 696969;
    double lastMeandiff = 999999999999999999999999.9;
    while (iterationsLeft > 0)
    {
        //Zero out sums and counts
        for (int i = 0; i < numColours; i++)
        {
            KMean m = means[i];
            m.lastmean = m.mean;
            m.numInCluster = 0;
            m.sumL = 0.0; m.suma = 0.0; m.sumb = 0.0;
            means[i] = m;
        }

        //Associate each colour with the closest mean
        for (long long i = 0; i < numPixels; i++)
        {
            ColourOkLabA col = colours[i];
            float lowestDistance = 999999999999999999999999.9;
            int chosenColour = 0;
            for (int j = 0; j < numColours; j++)
            {
                const ColourOkLabA incol = means[j].mean;
                const float dL = (col.L - incol.L) * uvbias;
                const float da = col.a - incol.a;
                const float db = col.b - incol.b;
                const float dist = (dL * dL) + (da * da) + (db * db);
                if (dist < lowestDistance)
                {
                    lowestDistance = dist;
                    chosenColour = j;
                }
            }
            KMean* m = &means[chosenColour];
            m->sumL += (double)col.L;
            m->suma += (double)col.a;
            m->sumb += (double)col.b;
            m->numInCluster++;
        }

        //Calculate means
        double meandiff = 0.0;
        for (int i = 0; i < numColours; i++)
        {
            KMean m = means[i];
            ColourOkLabA meancol;
            if (m.numInCluster <= 0) //Fallback because of suspected division by zero errors;
            {
                meancol.L = (RNGUpdateFloat() * 0.5f) + 0.5f;
                meancol.a = RNGUpdateFloat() * 0.5f;
                meancol.b = RNGUpdateFloat() * 0.5f;
            }
            else
            {
                meancol.L = m.sumL/((double)m.numInCluster);
                meancol.a = m.suma/((double)m.numInCluster);
                meancol.b = m.sumb/((double)m.numInCluster);
            }
            meancol.A = 1.0f;
            m.mean = meancol;
            const double dL = (((double)m.mean.L) - ((double)m.lastmean.L)) * ((double)uvbias);
            const double da = ((double)m.mean.a) - ((double)m.lastmean.a);
            const double db = ((double)m.mean.b) - ((double)m.lastmean.b);
            const double dist = (dL * dL) + (da * da) + (db * db);
            meandiff += sqrt(dist);
            means[i] = m;
        }
        if (meandiff < 0.00001 && lastMeandiff <= meandiff) //Break out if convergence has been reached
        {
            iterationsLeft = 0;
            for (int i = 0; i < numColours; i++)
            {
                means[i].mean = means[i].lastmean;
            }
        }
        iterationsLeft--;
        lastMeandiff = meandiff;
    }
    //*/


    //Confirm colours
    for (int i = 0; i < numColours; i++)
    {
        ColourOkLabA incol = means[i].mean;
        ColourRGBA midcol = OkLabToSRGB(incol);
        pal[i] = LinearFloatToSRGB8(midcol);
    }

    free(means);
    free(colours);
}

static void prepare(GeglOperation* operation)
{
    space = gegl_operation_get_source_space(operation, "input");
    gegl_operation_set_format(operation, "input", babl_format_with_space("RGBA float", space));
    gegl_operation_set_format(operation, "output", babl_format_with_space("RGBA float", space));
    numThreadsSpawned = 0;
    for (int i = 0; i < MAX_ADAPTIVE_THREADS; i++)
    {
        adptThreadActive[i] = 0;
    }

    //Get palette
    GeglProperties* props = GEGL_PROPERTIES(operation);
    rngNum[0] = 0x61CB3AF9 * ((unsigned int)operation);
    rngNum[1] = 0xF62D039A * ((unsigned int)props);
    rngNum[2] = 0x78AFC253 * ((unsigned int)operation);
    rngNum[3] = 0x23B90FC7 * ((unsigned int)props); //Yes, I'm seeding the RNG with a memory address
    palettes pal = props->curpal;
    hasFoundBestColours = 1;
    switch (pal)
    {
        case I1:
            palSize = 2;
            selpalette = (ColourRGBA8*)i1Palette;
            break;
        case R1G1B1:
            palSize = 8;
            selpalette = (ColourRGBA8*)r1g1b1Palette;
            break;
        case R1G1B1I1:
            palSize = 16;
            selpalette = (ColourRGBA8*)r1g1b1i1Palette;
            break;
        case R2G2B2:
            palSize = 64;
            selpalette = malloc(palSize * sizeof(ColourRGBA8));
            for (int i = 0; i < palSize; i++)
            {
                ColourRGBA8 curCol = { 0x55 * (i & 0x03), 0x55 * ((i & 0x0C) >> 2), 0x55 * ((i & 0x30) >> 4), 0xFF};
                selpalette[i] = curCol;
            }
            break;
        case R3G3B3:
            palSize = 512;
            selpalette = malloc(palSize * sizeof(ColourRGBA8));
            for (int i = 0; i < palSize; i++)
            {
                ColourRGBA8 curCol = { ((((0xFF * (i & 0x0007)) << 20) / 7) + 0x80000) >> 20,
                                       ((((0xFF * (i & 0x0038)) << 17) / 7) + 0x80000) >> 20,
                                       ((((0xFF * (i & 0x01C0)) << 14) / 7) + 0x80000) >> 20,
                                       0xFF }; //component * 255/7 for RGB, but done in fixed point
                selpalette[i] = curCol;
            }
            break;
        case MY16:
            palSize = 16;
            selpalette = (ColourRGBA8*)my16Palette;
            break;
        case MSWINDOWS:
            palSize = 16;
            selpalette = (ColourRGBA8*)windowsPalette;
            break;
        case MAC2:
            palSize = 16;
            selpalette = (ColourRGBA8*)mac2Palette;
            break;
        case RISCOS:
            palSize = 16;
            selpalette = (ColourRGBA8*)riscosPalette;
            break;
        case APPLE2_6:
            palSize = 6;
            selpalette = (ColourRGBA8*)apple2_6Palette;
            break;
        case APPLE2_15:
            palSize = 15;
            selpalette = (ColourRGBA8*)apple2_15Palette;
            break;
        case C64:
            palSize = 16;
            selpalette = (ColourRGBA8*)c64Palette;
            break;
        case MSX:
            palSize = 15;
            selpalette = (ColourRGBA8*)msxPalette;
            break;
        case INTELLIVISION:
            palSize = 16;
            selpalette = (ColourRGBA8*)intellivisionPalette;
            break;
        case GB:
            palSize = 4;
            selpalette = (ColourRGBA8*)gameboyPalette;
            break;
        case ADAPTIVE:
            palSize = props->numcol;
            selpalette = malloc(palSize * sizeof(ColourRGBA8));
            hasFoundBestColours = 0;
            hasStartedToFindBestColours = 0;
            canStartNewParallelLoops = 0;
            break;
        case FROMFILE: //Fallback on my 16-colour palette for now
            palSize = 16;
            selpalette = (ColourRGBA8*)my16Palette;
            break;
    }
    srcpalette = malloc(palSize * sizeof(ColourRGBA));
    palette = malloc(palSize * sizeof(ColourOkLabA));
    for (int i = 0; i < palSize; i++)
    {
        srcpalette[i] = SRGB8ToLinearFloat(selpalette[i]);
        palette[i] = SRGBToOkLab(srcpalette[i]);
    }
}

static gboolean process(GeglOperation* op, GeglBuffer* inBuf, GeglBuffer* outBuf, const GeglRectangle* roi, gint level)
{
    int threadNum = numThreadsSpawned;
    numThreadsSpawned++;
    //Get properties
    GeglProperties* props = GEGL_PROPERTIES(op);
    if (!hasFoundBestColours) //hacky
    {
        if (!hasStartedToFindBestColours) //First thread spanwed by GEGL gets to coordinate the others
        {
            hasStartedToFindBestColours = 1; //for god's sake please get here really really fast before some other stupid chunk starts processing
            GeglRectangle totalRect = gegl_operation_get_bounding_box(op);
            long long numpix = totalRect.width * totalRect.height;
            const Babl* fmt = babl_format_with_space("RGBA float", space);
            ColourRGBA* totalImg = malloc(numpix * sizeof(ColourRGBA));
            gegl_buffer_get(inBuf, &totalRect, 1.0, fmt, totalImg, GEGL_AUTO_ROWSTRIDE, GEGL_ABYSS_CLAMP);
            GetBestPalette(selpalette, palSize, totalImg, totalRect.width, totalRect.height, 1.0f/props->adptchromabias, props->adptBright, props->adptContrast);
            free(totalImg);
            for (int i = 0; i < palSize; i++)
            {
                srcpalette[i] = SRGB8ToLinearFloat(selpalette[i]);
                palette[i] = SRGBToOkLab(srcpalette[i]);
            }
            hasFoundBestColours = 1;
        }
        else //Other threads only join in the main embarrasingly parallel loop
        {
            while (1)
            {
                while (1)
                {
                    if (canStartNewParallelLoops) break;
                    if (hasFoundBestColours) break;
                }
                if (hasFoundBestColours) break;
                adptThreadActive[threadNum] = 1;
                while (1)
                {
                    if (GetBestPaletteParallelLoop())
                    {
                        adptThreadActive[threadNum] = 0;
                        break;
                    }
                }
            }
        }
    }
    //Palette is fully known by this point, now let's dither
    const Babl* fmt = babl_format_with_space("RGBA float", space);
    glong x = roi->x;
    glong y = roi->y;
    glong w = roi->width;
    glong h = roi->height;
    ditherMethods dmet = props->ditherMethod;
    gfloat ditAmtL = props->ditherAmountL;
    gfloat ditAmtS = props->ditherAmountS;
    gfloat ditAmtH = props->ditherAmountH;
    gfloat ditAmtEL = props->ditherAmountEL;
    gfloat ditAmtEC = props->ditherAmountEC;
    gfloat rngAmtL = props->randomAmountL;
    gfloat rngAmtC = props->randomAmountC;
    gfloat cbias = props->chromabias;
    gfloat preB = props->preBright;
    gfloat preC = props->preContrast;
    gfloat postB = props->postBright;
    gfloat postC = props->postContrast;
    gboolean globBoustro = props->boustrophedon;

    //Allocate buffers
    ColourRGBA* pixel = malloc(w * h * sizeof(ColourRGBA));
    ColourRGBA* expandedInput;
    ColourOkLabA* diffusedError;
    OrderedDitherFunction* odfunc;
    ErrorDiffusionDitherFunction* eddfunc;
    int eddMarginX, eddMarginY;
    GeglRectangle newRoi;
    int isErrorDiffusion;

    //Select function and set parameters
    switch (dmet)
    {
        case BAYER2X2:
            odfunc = &OrderedDitherBayer2x2; break;
        case BAYER4X4:
            odfunc = &OrderedDitherBayer4x4; break;
        case BAYER8X8:
            odfunc = &OrderedDitherBayer8x8; break;
        case BAYER16X16:
            odfunc = &OrderedDitherBayer16x16; break;
        case VOID16X16:
            odfunc = &OrderedDitherVoid16x16; break;
        case FLOYD_STEINBERG:
            eddfunc = &DitherFloydSteinberg;
            eddMarginX = 1; eddMarginY = 1;
            break;
        case FLOYD_FALSE:
            eddfunc = &DitherFloydFalse;
            eddMarginX = 1; eddMarginY = 1;
            break;
        case JJN:
            eddfunc = &DitherJJN;
            eddMarginX = 2; eddMarginY = 2;
            break;
        case STUCKI:
            eddfunc = &DitherStucki;
            eddMarginX = 2; eddMarginY = 2;
            break;
        case BURKES:
            eddfunc = &DitherBurkes;
            eddMarginX = 2; eddMarginY = 1;
            break;
        case SIERRA:
            eddfunc = &DitherSierra;
            eddMarginX = 2; eddMarginY = 2;
            break;
        case SIERRA2ROW:
            eddfunc = &DitherSierra2Row;
            eddMarginX = 2; eddMarginY = 1;
            break;
        case FILTERLITE:
            eddfunc = &DitherFilterLite;
            eddMarginX = 1; eddMarginY = 1;
            break;
        case ATKINSON:
            eddfunc = &DitherAtkinson;
            eddMarginX = 2; eddMarginY = 2;
            break;
    }

    //Carry out operation
    if (dmet < FLOYD_STEINBERG) //Ordered dithering
    {
        gegl_buffer_get(inBuf, roi, 1.0, fmt, pixel, GEGL_AUTO_ROWSTRIDE, GEGL_ABYSS_CLAMP);
        isErrorDiffusion = 0;
        for (glong i = 0; i < h; i++)
        {
            for (glong j = 0; j < w; j++)
            {
                const glong index = i * w + j;
                ColourOkLabA incol = SRGBToOkLab(pixel[index]);
                incol = ColourAdjust(incol, preB, preC);
                pixel[index] = odfunc(incol, j + x, i + y, ditAmtL, ditAmtS, ditAmtH, postB, postC, cbias);
            }
        }
    }
    else //Error diffusion
    {
        x -= EDD_EXPAND_X;   y -= EDD_EXPAND_Y_TOP;
        w += 2*EDD_EXPAND_X; h += EDD_EXPAND_Y_TOP + EDD_EXPAND_Y_BOTTOM; //Expand ROI to ease in error diffusion
        expandedInput = malloc(w * h * sizeof(ColourRGBA));
        gegl_rectangle_set(&newRoi, x, y, w, h);
        gegl_buffer_get(inBuf, &newRoi, 1.0, fmt, expandedInput, GEGL_AUTO_ROWSTRIDE, GEGL_ABYSS_CLAMP);
        diffusedError = calloc(w * h, sizeof(ColourOkLabA));
        isErrorDiffusion = 1;
        for (glong i = 0; i < h-eddMarginY; i++)
        {
            const int boustro = i % 2;
            if (globBoustro & boustro)
            {
                for (glong j = w-1-eddMarginX; j >= eddMarginX; j--)
                {
                    const glong index = i * w + j;
                    ColourOkLabA incol = SRGBToOkLab(expandedInput[index]);
                    incol = ColourAdjust(incol, preB, preC);
                    expandedInput[index] = OkLabToSRGB(eddfunc(incol, j, i, w, ditAmtEL, ditAmtEC, postB, postC, cbias, diffusedError, -1, rngAmtL, rngAmtC));
                }
            }
            else
            {
                for (glong j = eddMarginX; j < w-eddMarginX; j++)
                {
                    const glong index = i * w + j;
                    ColourOkLabA incol = SRGBToOkLab(expandedInput[index]);
                    incol = ColourAdjust(incol, preB, preC);
                    expandedInput[index] = OkLabToSRGB(eddfunc(incol, j, i, w, ditAmtEL, ditAmtEC, postB, postC, cbias, diffusedError, 1, rngAmtL, rngAmtC));
                }
            }
        }
    }

    //Copy back
    if (isErrorDiffusion) //Only copy over the parts that need to be written
    {
        w -= 2*EDD_EXPAND_X; h -= EDD_EXPAND_Y_TOP + EDD_EXPAND_Y_BOTTOM;
        for (int i = 0; i < h; i++)
        {
            memcpy(&pixel[i * w], &expandedInput[(i + EDD_EXPAND_Y_TOP) * (w + 2*EDD_EXPAND_X) + EDD_EXPAND_X], w * sizeof(ColourRGBA));
        }
        free(diffusedError);
        free(expandedInput);
    }
    gegl_buffer_set(outBuf, roi, 0, fmt, pixel, GEGL_AUTO_ROWSTRIDE);
    free(pixel);
    return TRUE;
}

static void gegl_op_class_init (GeglOpClass* klass)
{
    GeglOperationClass* operationClass;
    GeglOperationFilterClass* filterClass;
    gchar* composition =
        "<?xml version='1.0' encoding='UTF-8'?>"
        "<gegl>"
        "  <node operation='gegl:crop' width='200' height='200'/>"
        "  <node operation='maxh:good-dither'>"
        "    <params>"
        "      <param name='ditherAmountL'>0.4</param>"
        "    </params>"
        "  </node>"
        "</gegl>";

    operationClass    = GEGL_OPERATION_CLASS(klass);
    filterClass = GEGL_OPERATION_FILTER_CLASS(klass);

    /* override the prepare methods of the GeglOperation class */
    operationClass->prepare = prepare;
    /* override the process method of the point filter class (the process methods
    * of our superclasses deal with the handling on their level of abstraction)
    */
    filterClass->process = process;

    gegl_operation_class_set_keys(operationClass,
        "name",       "maxh:good-dither",
        "title",      _("A Good Dither"),
        "categories", "dither",
        "reference-hash", "ef9f675766fc6eacfbbefda962045052",

        /* xgettext:no-c-format */
        "description", _("Multifunctional ditherer."),
        "reference-composition", composition,
        NULL);
}
#endif
