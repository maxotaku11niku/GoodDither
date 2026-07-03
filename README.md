# GoodDither

## It's a pretty good dithering plugin, methinks

This is a GEGL plugin that implements ordered dithering and error-diffusion dithering, along with colour quantisation. The error-diffusion uses several classic kernels (Floyd-Steinberg, Sierra etc.) and diffuses errors in linear sRGB, after determining the closest colour in OkLab space. Not too special, really. But, the ordered dithering uses a radically different technique I call **Geometric Mixing Calculation**, which leads to results that are much closer in fidelity to error diffusion. It still uses Bayer patterns and a fixed blue-noise pattern, of course. An explanation for it can be found in GMC.md. Colour quantisation uses k-means clustering of the input pixel colours. There are also a number of tweaking options that are mostly useful for colour quantisation and error-diffusion.

It's much better than GIMP's built in dithering options, at least.
