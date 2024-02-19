#include "config.h"
#include <glib/gi18n-lib.h>

#ifdef GEGL_PROPERTIES

enum_start(ditherMethods)
enum_value(BAYER2X2, "bayer2", "Bayer 2x2")
enum_value(BAYER4X4, "bayer4", "Bayer 4x4")
enum_value(FLOYD_STEINBERG, "floyd", "Floyd-Steinberg")
enum_value(JJN, "jjn", "Jarvis-Judice-Ninke")
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

property_enum (ditherMethod, _("Dither Method"), ditherMethods, ditherMethods, 1)
    description (_("Choose from a variety of dithering methods, both ordered and error-diffusing."))

property_enum (curpal, _("Palette"), palettes, palettes, 5)
    description (_("Choose the palette you want to use."))

property_double (ditherAmountL, _("Luminosity Dither"),  0.5)
    description (_("Magnitude of dither effect on the luminosity."))
    value_range (0.0, 2.0)
    ui_range    (0.0, 1.0)

property_double (ditherAmountS, _("Saturation Dither"),  0.5)
    description (_("Magnitude of dither effect on the saturation."))
    value_range (0.0, 2.0)
    ui_range    (0.0, 1.0)

property_double (ditherAmountH, _("Hue Dither"),  1.0)
    description (_("Magnitude of dither effect on the hue."))
    value_range (0.0, 10.0)
    ui_range    (0.0, 6.0)

property_double (ditherAmountE, _("Error Diffusion"),  1.0)
    description (_("Magnitude of error diffusion."))
    value_range (0.0, 1.0)
    ui_range    (0.0, 1.0)

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

enum_start(ditherMethods)
enum_value(BAYER2X2, "bayer2", "Bayer 2x2")
enum_value(BAYER4X4, "bayer4", "Bayer 4x4")
enum_value(FLOYD_STEINBERG, "floyd", "Floyd-Steinberg")
enum_value(JJN, "jjn", "Jarvis-Judice-Ninke")
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
#define EDD_EXPAND_X        10
#define EDD_EXPAND_Y_TOP    10
#define EDD_EXPAND_Y_BOTTOM 4

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
const float bayer2x2[4] = { -0.5f,  0.25f,
                             0.0f, -0.25f };

const float bayer4x4[16] = { -0.5f,   0.25f, -0.3125f, 0.4375f,
                              0.0f,  -0.25f,  0.1875f,-0.0625f,
                             -0.375f, 0.375f,-0.4375f, 0.3125f,
                              0.125f,-0.125f, 0.0625f,-0.1875f };

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
                                        { 0x4C, 0x77, 0x63, 0xFF },
                                        { 0x96, 0xCA, 0x6E, 0xFF },
                                        { 0xF6, 0xFF, 0x20, 0xFF } };

int palSize;
ColourRGBA8* selpalette;
ColourRGBA* srcpalette;
ColourOkLabA* palette;
Babl* space;

typedef ColourRGBA OrderedDitherFunction(ColourOkLabA, int, int, float, float, float);
typedef ColourOkLabA ErrorDiffusionDitherFunction(ColourOkLabA, int, int, int, float, ColourOkLabA*, int);

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
    ColourRGBA outcol = { R, G, B, c.A};
    return outcol;
}

static ColourRGBA GetClosestColourOkLab(ColourOkLabA col)
{
    float lowestDistance = 999999999999999999999999.9;
    int chosenColour = 0;
    for (int i = 0; i < palSize; i++)
    {
        const ColourOkLabA incol = palette[i];
        const float dL = col.L - incol.L;
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

static ColourOkLabA GetClosestColourOkLabWithError(ColourOkLabA col, ColourOkLabA* error)
{
    float lowestDistance = 999999999999999999999999.9;
    int chosenColour = 0;
    for (int i = 0; i < palSize; i++)
    {
        const ColourOkLabA incol = palette[i];
        const float dL = col.L - incol.L;
        const float da = col.a - incol.a;
        const float db = col.b - incol.b;
        const float dist = (dL * dL) + (da * da) + (db * db);
        if (dist < lowestDistance)
        {
            lowestDistance = dist;
            chosenColour = i;
        }
    }
    ColourOkLabA outcol = palette[chosenColour];
    error->L = col.L - outcol.L;
    error->a = col.a - outcol.a;
    error->b = col.b - outcol.b;
    error->A = 0.0f;
    return outcol;
}

static ColourRGBA OrderedDitherBayer2x2(ColourOkLabA col, int x, int y, float amtL, float amtS, float amtH)
{
    col.L += bayer2x2[(y % 2) * 2 + (x % 2)] * amtL;
    float sat = sqrtf(col.a * col.a + col.b * col.b);
    float hue = atan2f(col.b, col.a);
    const float midsat = -amtS * bayer2x2[(y % 4) * 4 + ((x + 1) % 4)];
    sat *= 1.0f + midsat;
    sat += midsat * 0.5f;
    hue += amtH * bayer4x4[((y + 1) % 4) * 4 + (x % 4)];
    col.a = sat * cosf(hue);
    col.b = sat * sinf(hue);
    return GetClosestColourOkLab(col);
}

static ColourRGBA OrderedDitherBayer4x4(ColourOkLabA col, int x, int y, float amtL, float amtS, float amtH)
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
    return GetClosestColourOkLab(col);
}

static ColourOkLabA DitherFloydSteinberg(ColourOkLabA col, int x, int y, int w, float amt, ColourOkLabA* diffErr, int boustro)
{
    ColourOkLabA outerr;
    ColourOkLabA* diffCol = &diffErr[x +  y * w];
    col.L += diffCol->L; col.a += diffCol->a; col.b += diffCol->b;
    ColourOkLabA outcol = GetClosestColourOkLabWithError(col, &outerr);

    diffCol = &diffErr[(x + boustro) +  y * w];
    float coeff = 0.4375f * amt;
    diffCol->L += outerr.L * coeff; diffCol->a += outerr.a * coeff; diffCol->b += outerr.b * coeff;
    diffCol = &diffErr[(x - boustro) + (y + 1) * w];
    coeff = 0.3125f * amt;
    diffCol->L += outerr.L * coeff; diffCol->a += outerr.a * coeff; diffCol->b += outerr.b * coeff;
    diffCol = &diffErr[ x            + (y + 1) * w];
    coeff = 0.1875f * amt;
    diffCol->L += outerr.L * coeff; diffCol->a += outerr.a * coeff; diffCol->b += outerr.b * coeff;
    diffCol = &diffErr[(x + boustro) + (y + 1) * w];
    coeff = 0.0625f * amt;
    diffCol->L += outerr.L * coeff; diffCol->a += outerr.a * coeff; diffCol->b += outerr.b * coeff;
    return outcol;
}

static ColourOkLabA DitherJJN(ColourOkLabA col, int x, int y, int w, float amt, ColourOkLabA* diffErr, int boustro)
{
    ColourOkLabA outerr;
    ColourOkLabA* diffCol = &diffErr[x +  y * w];
    col.L += diffCol->L; col.a += diffCol->a; col.b += diffCol->b;
    ColourOkLabA outcol = GetClosestColourOkLabWithError(col, &outerr);

    float coeff = (7.0f/48.0f) * amt;
    diffCol = &diffErr[(x + boustro) +  y * w];
    diffCol->L += outerr.L * coeff; diffCol->a += outerr.a * coeff; diffCol->b += outerr.b * coeff;
    diffCol = &diffErr[ x            + (y + 1) * w];
    diffCol->L += outerr.L * coeff; diffCol->a += outerr.a * coeff; diffCol->b += outerr.b * coeff;


    coeff = (5.0f/48.0f) * amt;
    diffCol = &diffErr[(x + 2 * boustro) +  y * w];
    diffCol->L += outerr.L * coeff; diffCol->a += outerr.a * coeff; diffCol->b += outerr.b * coeff;
    diffCol = &diffErr[(x + boustro)     + (y + 1) * w];
    diffCol->L += outerr.L * coeff; diffCol->a += outerr.a * coeff; diffCol->b += outerr.b * coeff;
    diffCol = &diffErr[ x                + (y + 2) * w];
    diffCol->L += outerr.L * coeff; diffCol->a += outerr.a * coeff; diffCol->b += outerr.b * coeff;
    diffCol = &diffErr[(x - boustro)     + (y + 1) * w];
    diffCol->L += outerr.L * coeff; diffCol->a += outerr.a * coeff; diffCol->b += outerr.b * coeff;

    coeff = (3.0f/48.0f) * amt;
    diffCol = &diffErr[(x + 2 * boustro) + (y + 1) * w];
    diffCol->L += outerr.L * coeff; diffCol->a += outerr.a * coeff; diffCol->b += outerr.b * coeff;
    diffCol = &diffErr[(x + boustro)     + (y + 2) * w];
    diffCol->L += outerr.L * coeff; diffCol->a += outerr.a * coeff; diffCol->b += outerr.b * coeff;
    diffCol = &diffErr[(x - boustro)     + (y + 2) * w];
    diffCol->L += outerr.L * coeff; diffCol->a += outerr.a * coeff; diffCol->b += outerr.b * coeff;
    diffCol = &diffErr[(x - 2 * boustro) + (y + 1) * w];
    diffCol->L += outerr.L * coeff; diffCol->a += outerr.a * coeff; diffCol->b += outerr.b * coeff;

    coeff = (1.0f/48.0f) * amt;
    diffCol = &diffErr[(x + 2 * boustro) + (y + 2) * w];
    diffCol->L += outerr.L * coeff; diffCol->a += outerr.a * coeff; diffCol->b += outerr.b * coeff;
    diffCol = &diffErr[(x - 2 * boustro) + (y + 2) * w];
    diffCol->L += outerr.L * coeff; diffCol->a += outerr.a * coeff; diffCol->b += outerr.b * coeff;

    return outcol;
}

static ColourOkLabA DitherAtkinson(ColourOkLabA col, int x, int y, int w, float amt, ColourOkLabA* diffErr, int boustro)
{
    ColourOkLabA outerr;
    ColourOkLabA* diffCol = &diffErr[x +  y * w];
    col.L += diffCol->L; col.a += diffCol->a; col.b += diffCol->b;
    ColourOkLabA outcol = GetClosestColourOkLabWithError(col, &outerr);

    const float coeff = amt / 6.0f; //Note: the canonical Atkinson dither only diffuses 3/4 of the error, but we'll normalise this one anyway
    diffCol = &diffErr[(x + boustro)     +  y * w];
    diffCol->L += outerr.L * coeff; diffCol->a += outerr.a * coeff; diffCol->b += outerr.b * coeff;
    diffCol = &diffErr[(x + 2 * boustro) +  y * w];
    diffCol->L += outerr.L * coeff; diffCol->a += outerr.a * coeff; diffCol->b += outerr.b * coeff;
    diffCol = &diffErr[(x - boustro)     + (y + 1) * w];
    diffCol->L += outerr.L * coeff; diffCol->a += outerr.a * coeff; diffCol->b += outerr.b * coeff;
    diffCol = &diffErr[ x                + (y + 1) * w];
    diffCol->L += outerr.L * coeff; diffCol->a += outerr.a * coeff; diffCol->b += outerr.b * coeff;
    diffCol = &diffErr[(x + boustro)     + (y + 1) * w];
    diffCol->L += outerr.L * coeff; diffCol->a += outerr.a * coeff; diffCol->b += outerr.b * coeff;
    diffCol = &diffErr[ x                + (y + 2) * w];
    diffCol->L += outerr.L * coeff; diffCol->a += outerr.a * coeff; diffCol->b += outerr.b * coeff;

    return outcol;
}

static void prepare(GeglOperation* operation)
{
    space = gegl_operation_get_source_space(operation, "input");
    gegl_operation_set_format(operation, "input", babl_format_with_space("RGBA float", space));
    gegl_operation_set_format(operation, "output", babl_format_with_space("RGBA float", space));

    //Get palette
    GeglProperties* props = GEGL_PROPERTIES(operation);
    palettes pal = props->curpal;
    switch (pal)
    {
        case I1:
            palSize = 2;
            selpalette = i1Palette;
            break;
        case R1G1B1:
            palSize = 8;
            selpalette = r1g1b1Palette;
            break;
        case R1G1B1I1:
            palSize = 16;
            selpalette = r1g1b1i1Palette;
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
                ColourRGBA8 curCol = { 0x24 * (i & 0x0007), 0x24 * ((i & 0x0038) >> 3), 0x24 * ((i & 0x01C0) >> 6), 0xFF};
                selpalette[i] = curCol;
            }
            break;
        case MY16:
            palSize = 16;
            selpalette = my16Palette;
            break;
        case MSWINDOWS:
            palSize = 16;
            selpalette = windowsPalette;
            break;
        case MAC2:
            palSize = 16;
            selpalette = mac2Palette;
            break;
        case RISCOS:
            palSize = 16;
            selpalette = riscosPalette;
            break;
        case APPLE2_6:
            palSize = 6;
            selpalette = apple2_6Palette;
            break;
        case APPLE2_15:
            palSize = 15;
            selpalette = apple2_15Palette;
            break;
        case C64:
            palSize = 16;
            selpalette = c64Palette;
            break;
        case MSX:
            palSize = 15;
            selpalette = msxPalette;
            break;
        case INTELLIVISION:
            palSize = 16;
            selpalette = intellivisionPalette;
            break;
        case GB:
            palSize = 4;
            selpalette = gameboyPalette;
            break;
        case ADAPTIVE: //Fallback on my 16-colour palette for now
            palSize = 16;
            selpalette = my16Palette;
            break;
        case FROMFILE: //Fallback on my 16-colour palette for now
            palSize = 16;
            selpalette = my16Palette;
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
    //Get properties
    GeglProperties* props = GEGL_PROPERTIES(op);
    const Babl* fmt = babl_format_with_space("RGBA float", space);
    glong x = roi->x;
    glong y = roi->y;
    glong w = roi->width;
    glong h = roi->height;
    ditherMethods dmet = props->ditherMethod;
    gfloat ditAmtL = props->ditherAmountL;
    gfloat ditAmtS = props->ditherAmountS;
    gfloat ditAmtH = props->ditherAmountH;
    gfloat ditAmtE = props->ditherAmountE;
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
        case FLOYD_STEINBERG:
            eddfunc = &DitherFloydSteinberg;
            eddMarginX = 1; eddMarginY = 1;
            break;
        case JJN:
            eddfunc = &DitherJJN;
            eddMarginX = 2; eddMarginY = 2;
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
                pixel[index] = odfunc(incol, j + x, i + y, ditAmtL, ditAmtS, ditAmtH);
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
                    expandedInput[index] = OkLabToSRGB(eddfunc(incol, j, i, w, ditAmtE, diffusedError, -1));
                }
            }
            else
            {
                for (glong j = eddMarginX; j < w-eddMarginX; j++)
                {
                    const glong index = i * w + j;
                    ColourOkLabA incol = SRGBToOkLab(expandedInput[index]);
                    expandedInput[index] = OkLabToSRGB(eddfunc(incol, j, i, w, ditAmtE, diffusedError, 1));
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
