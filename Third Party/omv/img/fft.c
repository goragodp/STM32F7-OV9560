/*
 * This file is part of the OpenMV project.
 * Copyright (c) 2013-2016 Kwabena W. Agyeman <kwagyeman@openmv.io>
 * This work is licensed under the MIT license, see the file LICENSE for details.
 *
 * FFT LIB - can do 1024 point real FFTs and 512 point complex FFTs
 *
 */
#include <arm_math.h>
#include "fb_alloc.h"
#include "ff_wrapper.h"
#include "common.h"
#include "fft.h"
// http://processors.wiki.ti.com/index.php/Efficient_FFT_Computation_of_Real_Input

const static float fft_cos_table[512] = {
     1.000000f,  0.999981f,  0.999925f,  0.999831f,  0.999699f,  0.999529f,  0.999322f,  0.999078f,
     0.998795f,  0.998476f,  0.998118f,  0.997723f,  0.997290f,  0.996820f,  0.996313f,  0.995767f,
     0.995185f,  0.994565f,  0.993907f,  0.993212f,  0.992480f,  0.991710f,  0.990903f,  0.990058f,
     0.989177f,  0.988258f,  0.987301f,  0.986308f,  0.985278f,  0.984210f,  0.983105f,  0.981964f,
     0.980785f,  0.979570f,  0.978317f,  0.977028f,  0.975702f,  0.974339f,  0.972940f,  0.971504f,
     0.970031f,  0.968522f,  0.966976f,  0.965394f,  0.963776f,  0.962121f,  0.960431f,  0.958703f,
     0.956940f,  0.955141f,  0.953306f,  0.951435f,  0.949528f,  0.947586f,  0.945607f,  0.943593f,
     0.941544f,  0.939459f,  0.937339f,  0.935184f,  0.932993f,  0.930767f,  0.928506f,  0.926210f,
     0.923880f,  0.921514f,  0.919114f,  0.916679f,  0.914210f,  0.911706f,  0.909168f,  0.906596f,
     0.903989f,  0.901349f,  0.898674f,  0.895966f,  0.893224f,  0.890449f,  0.887640f,  0.884797f,
     0.881921f,  0.879012f,  0.876070f,  0.873095f,  0.870087f,  0.867046f,  0.863973f,  0.860867f,
     0.857729f,  0.854558f,  0.851355f,  0.848120f,  0.844854f,  0.841555f,  0.838225f,  0.834863f,
     0.831470f,  0.828045f,  0.824589f,  0.821103f,  0.817585f,  0.814036f,  0.810457f,  0.806848f,
     0.803208f,  0.799537f,  0.795837f,  0.792107f,  0.788346f,  0.784557f,  0.780737f,  0.776888f,
     0.773010f,  0.769103f,  0.765167f,  0.761202f,  0.757209f,  0.753187f,  0.749136f,  0.745058f,
     0.740951f,  0.736817f,  0.732654f,  0.728464f,  0.724247f,  0.720003f,  0.715731f,  0.711432f,
     0.707107f,  0.702755f,  0.698376f,  0.693971f,  0.689541f,  0.685084f,  0.680601f,  0.676093f,
     0.671559f,  0.667000f,  0.662416f,  0.657807f,  0.653173f,  0.648514f,  0.643832f,  0.639124f,
     0.634393f,  0.629638f,  0.624859f,  0.620057f,  0.615232f,  0.610383f,  0.605511f,  0.600616f,
     0.595699f,  0.590760f,  0.585798f,  0.580814f,  0.575808f,  0.570781f,  0.565732f,  0.560662f,
     0.555570f,  0.550458f,  0.545325f,  0.540171f,  0.534998f,  0.529804f,  0.524590f,  0.519356f,
     0.514103f,  0.508830f,  0.503538f,  0.498228f,  0.492898f,  0.487550f,  0.482184f,  0.476799f,
     0.471397f,  0.465976f,  0.460539f,  0.455084f,  0.449611f,  0.444122f,  0.438616f,  0.433094f,
     0.427555f,  0.422000f,  0.416430f,  0.410843f,  0.405241f,  0.399624f,  0.393992f,  0.388345f,
     0.382683f,  0.377007f,  0.371317f,  0.365613f,  0.359895f,  0.354164f,  0.348419f,  0.342661f,
     0.336890f,  0.331106f,  0.325310f,  0.319502f,  0.313682f,  0.307850f,  0.302006f,  0.296151f,
     0.290285f,  0.284408f,  0.278520f,  0.272621f,  0.266713f,  0.260794f,  0.254866f,  0.248928f,
     0.242980f,  0.237024f,  0.231058f,  0.225084f,  0.219101f,  0.213110f,  0.207111f,  0.201105f,
     0.195090f,  0.189069f,  0.183040f,  0.177004f,  0.170962f,  0.164913f,  0.158858f,  0.152797f,
     0.146730f,  0.140658f,  0.134581f,  0.128498f,  0.122411f,  0.116319f,  0.110222f,  0.104122f,
     0.098017f,  0.091909f,  0.085797f,  0.079682f,  0.073565f,  0.067444f,  0.061321f,  0.055195f,
     0.049068f,  0.042938f,  0.036807f,  0.030675f,  0.024541f,  0.018407f,  0.012272f,  0.006136f,
     0.000000f, -0.006136f, -0.012272f, -0.018407f, -0.024541f, -0.030675f, -0.036807f, -0.042938f,
    -0.049068f, -0.055195f, -0.061321f, -0.067444f, -0.073565f, -0.079682f, -0.085797f, -0.091909f,
    -0.098017f, -0.104122f, -0.110222f, -0.116319f, -0.122411f, -0.128498f, -0.134581f, -0.140658f,
    -0.146730f, -0.152797f, -0.158858f, -0.164913f, -0.170962f, -0.177004f, -0.183040f, -0.189069f,
    -0.195090f, -0.201105f, -0.207111f, -0.213110f, -0.219101f, -0.225084f, -0.231058f, -0.237024f,
    -0.242980f, -0.248928f, -0.254866f, -0.260794f, -0.266713f, -0.272621f, -0.278520f, -0.284408f,
    -0.290285f, -0.296151f, -0.302006f, -0.307850f, -0.313682f, -0.319502f, -0.325310f, -0.331106f,
    -0.336890f, -0.342661f, -0.348419f, -0.354164f, -0.359895f, -0.365613f, -0.371317f, -0.377007f,
    -0.382683f, -0.388345f, -0.393992f, -0.399624f, -0.405241f, -0.410843f, -0.416430f, -0.422000f,
    -0.427555f, -0.433094f, -0.438616f, -0.444122f, -0.449611f, -0.455084f, -0.460539f, -0.465976f,
    -0.471397f, -0.476799f, -0.482184f, -0.487550f, -0.492898f, -0.498228f, -0.503538f, -0.508830f,
    -0.514103f, -0.519356f, -0.524590f, -0.529804f, -0.534998f, -0.540171f, -0.545325f, -0.550458f,
    -0.555570f, -0.560662f, -0.565732f, -0.570781f, -0.575808f, -0.580814f, -0.585798f, -0.590760f,
    -0.595699f, -0.600616f, -0.605511f, -0.610383f, -0.615232f, -0.620057f, -0.624859f, -0.629638f,
    -0.634393f, -0.639124f, -0.643832f, -0.648514f, -0.653173f, -0.657807f, -0.662416f, -0.667000f,
    -0.671559f, -0.676093f, -0.680601f, -0.685084f, -0.689541f, -0.693971f, -0.698376f, -0.702755f,
    -0.707107f, -0.711432f, -0.715731f, -0.720003f, -0.724247f, -0.728464f, -0.732654f, -0.736817f,
    -0.740951f, -0.745058f, -0.749136f, -0.753187f, -0.757209f, -0.761202f, -0.765167f, -0.769103f,
    -0.773010f, -0.776888f, -0.780737f, -0.784557f, -0.788346f, -0.792107f, -0.795837f, -0.799537f,
    -0.803208f, -0.806848f, -0.810457f, -0.814036f, -0.817585f, -0.821103f, -0.824589f, -0.828045f,
    -0.831470f, -0.834863f, -0.838225f, -0.841555f, -0.844854f, -0.848120f, -0.851355f, -0.854558f,
    -0.857729f, -0.860867f, -0.863973f, -0.867046f, -0.870087f, -0.873095f, -0.876070f, -0.879012f,
    -0.881921f, -0.884797f, -0.887640f, -0.890449f, -0.893224f, -0.895966f, -0.898674f, -0.901349f,
    -0.903989f, -0.906596f, -0.909168f, -0.911706f, -0.914210f, -0.916679f, -0.919114f, -0.921514f,
    -0.923880f, -0.926210f, -0.928506f, -0.930767f, -0.932993f, -0.935184f, -0.937339f, -0.939459f,
    -0.941544f, -0.943593f, -0.945607f, -0.947586f, -0.949528f, -0.951435f, -0.953306f, -0.955141f,
    -0.956940f, -0.958703f, -0.960431f, -0.962121f, -0.963776f, -0.965394f, -0.966976f, -0.968522f,
    -0.970031f, -0.971504f, -0.972940f, -0.974339f, -0.975702f, -0.977028f, -0.978317f, -0.979570f,
    -0.980785f, -0.981964f, -0.983105f, -0.984210f, -0.985278f, -0.986308f, -0.987301f, -0.988258f,
    -0.989177f, -0.990058f, -0.990903f, -0.991710f, -0.992480f, -0.993212f, -0.993907f, -0.994565f,
    -0.995185f, -0.995767f, -0.996313f, -0.996820f, -0.997290f, -0.997723f, -0.998118f, -0.998476f,
    -0.998795f, -0.999078f, -0.999322f, -0.999529f, -0.999699f, -0.999831f, -0.999925f, -0.999981f
};

ALWAYS_INLINE static float get_cos(int k, int N_pow2) // N=512 -> N=pow2=9
{
    return fft_cos_table[k << (9 - N_pow2)];
}

ALWAYS_INLINE static float get_ai(int k, int N_pow2) // N=512 -> N=pow2=9
{
    return 0.5 * (-get_cos(k, N_pow2));
}

ALWAYS_INLINE static float get_bi(int k, int N_pow2) // N=512 -> N=pow2=9
{
    return 0.5 * (+get_cos(k, N_pow2));
}

ALWAYS_INLINE static float get_a_star_i(int k, int N_pow2) // N=512 -> N=pow2=9
{
    return 0.5 * (+get_cos(k, N_pow2));
}

ALWAYS_INLINE static float get_b_star_i(int k, int N_pow2) // N=512 -> N=pow2=9
{
    return 0.5 * (-get_cos(k, N_pow2));
}

//// For samples 0 to (n/2)-1 --- Note: clog2(n/2) = N_pow2
//ALWAYS_INLINE static float get_hann_l_side(int k, int N_pow2)
//{
//    return 0.5 * (1 - get_cos(k, N_pow2));
//}

//// For samples (n/2) to n-1 --- Note: clog2(n/2) = N_pow2
//ALWAYS_INLINE static float get_hann_r_side(int k, int N_pow2)
//{
//    return 0.5 * (1 - get_cos((2 << N_pow2) - k - 1, N_pow2));
//}

const static float fft_sin_table[512] = {
     0.000000f,  0.006136f,  0.012272f,  0.018407f,  0.024541f,  0.030675f,  0.036807f,  0.042938f,
     0.049068f,  0.055195f,  0.061321f,  0.067444f,  0.073565f,  0.079682f,  0.085797f,  0.091909f,
     0.098017f,  0.104122f,  0.110222f,  0.116319f,  0.122411f,  0.128498f,  0.134581f,  0.140658f,
     0.146730f,  0.152797f,  0.158858f,  0.164913f,  0.170962f,  0.177004f,  0.183040f,  0.189069f,
     0.195090f,  0.201105f,  0.207111f,  0.213110f,  0.219101f,  0.225084f,  0.231058f,  0.237024f,
     0.242980f,  0.248928f,  0.254866f,  0.260794f,  0.266713f,  0.272621f,  0.278520f,  0.284408f,
     0.290285f,  0.296151f,  0.302006f,  0.307850f,  0.313682f,  0.319502f,  0.325310f,  0.331106f,
     0.336890f,  0.342661f,  0.348419f,  0.354164f,  0.359895f,  0.365613f,  0.371317f,  0.377007f,
     0.382683f,  0.388345f,  0.393992f,  0.399624f,  0.405241f,  0.410843f,  0.416430f,  0.422000f,
     0.427555f,  0.433094f,  0.438616f,  0.444122f,  0.449611f,  0.455084f,  0.460539f,  0.465976f,
     0.471397f,  0.476799f,  0.482184f,  0.487550f,  0.492898f,  0.498228f,  0.503538f,  0.508830f,
     0.514103f,  0.519356f,  0.524590f,  0.529804f,  0.534998f,  0.540171f,  0.545325f,  0.550458f,
     0.555570f,  0.560662f,  0.565732f,  0.570781f,  0.575808f,  0.580814f,  0.585798f,  0.590760f,
     0.595699f,  0.600616f,  0.605511f,  0.610383f,  0.615232f,  0.620057f,  0.624859f,  0.629638f,
     0.634393f,  0.639124f,  0.643832f,  0.648514f,  0.653173f,  0.657807f,  0.662416f,  0.667000f,
     0.671559f,  0.676093f,  0.680601f,  0.685084f,  0.689541f,  0.693971f,  0.698376f,  0.702755f,
     0.707107f,  0.711432f,  0.715731f,  0.720003f,  0.724247f,  0.728464f,  0.732654f,  0.736817f,
     0.740951f,  0.745058f,  0.749136f,  0.753187f,  0.757209f,  0.761202f,  0.765167f,  0.769103f,
     0.773010f,  0.776888f,  0.780737f,  0.784557f,  0.788346f,  0.792107f,  0.795837f,  0.799537f,
     0.803208f,  0.806848f,  0.810457f,  0.814036f,  0.817585f,  0.821103f,  0.824589f,  0.828045f,
     0.831470f,  0.834863f,  0.838225f,  0.841555f,  0.844854f,  0.848120f,  0.851355f,  0.854558f,
     0.857729f,  0.860867f,  0.863973f,  0.867046f,  0.870087f,  0.873095f,  0.876070f,  0.879012f,
     0.881921f,  0.884797f,  0.887640f,  0.890449f,  0.893224f,  0.895966f,  0.898674f,  0.901349f,
     0.903989f,  0.906596f,  0.909168f,  0.911706f,  0.914210f,  0.916679f,  0.919114f,  0.921514f,
     0.923880f,  0.926210f,  0.928506f,  0.930767f,  0.932993f,  0.935184f,  0.937339f,  0.939459f,
     0.941544f,  0.943593f,  0.945607f,  0.947586f,  0.949528f,  0.951435f,  0.953306f,  0.955141f,
     0.956940f,  0.958703f,  0.960431f,  0.962121f,  0.963776f,  0.965394f,  0.966976f,  0.968522f,
     0.970031f,  0.971504f,  0.972940f,  0.974339f,  0.975702f,  0.977028f,  0.978317f,  0.979570f,
     0.980785f,  0.981964f,  0.983105f,  0.984210f,  0.985278f,  0.986308f,  0.987301f,  0.988258f,
     0.989177f,  0.990058f,  0.990903f,  0.991710f,  0.992480f,  0.993212f,  0.993907f,  0.994565f,
     0.995185f,  0.995767f,  0.996313f,  0.996820f,  0.997290f,  0.997723f,  0.998118f,  0.998476f,
     0.998795f,  0.999078f,  0.999322f,  0.999529f,  0.999699f,  0.999831f,  0.999925f,  0.999981f,
     1.000000f,  0.999981f,  0.999925f,  0.999831f,  0.999699f,  0.999529f,  0.999322f,  0.999078f,
     0.998795f,  0.998476f,  0.998118f,  0.997723f,  0.997290f,  0.996820f,  0.996313f,  0.995767f,
     0.995185f,  0.994565f,  0.993907f,  0.993212f,  0.992480f,  0.991710f,  0.990903f,  0.990058f,
     0.989177f,  0.988258f,  0.987301f,  0.986308f,  0.985278f,  0.984210f,  0.983105f,  0.981964f,
     0.980785f,  0.979570f,  0.978317f,  0.977028f,  0.975702f,  0.974339f,  0.972940f,  0.971504f,
     0.970031f,  0.968522f,  0.966976f,  0.965394f,  0.963776f,  0.962121f,  0.960431f,  0.958703f,
     0.956940f,  0.955141f,  0.953306f,  0.951435f,  0.949528f,  0.947586f,  0.945607f,  0.943593f,
     0.941544f,  0.939459f,  0.937339f,  0.935184f,  0.932993f,  0.930767f,  0.928506f,  0.926210f,
     0.923880f,  0.921514f,  0.919114f,  0.916679f,  0.914210f,  0.911706f,  0.909168f,  0.906596f,
     0.903989f,  0.901349f,  0.898674f,  0.895966f,  0.893224f,  0.890449f,  0.887640f,  0.884797f,
     0.881921f,  0.879012f,  0.876070f,  0.873095f,  0.870087f,  0.867046f,  0.863973f,  0.860867f,
     0.857729f,  0.854558f,  0.851355f,  0.848120f,  0.844854f,  0.841555f,  0.838225f,  0.834863f,
     0.831470f,  0.828045f,  0.824589f,  0.821103f,  0.817585f,  0.814036f,  0.810457f,  0.806848f,
     0.803208f,  0.799537f,  0.795837f,  0.792107f,  0.788346f,  0.784557f,  0.780737f,  0.776888f,
     0.773010f,  0.769103f,  0.765167f,  0.761202f,  0.757209f,  0.753187f,  0.749136f,  0.745058f,
     0.740951f,  0.736817f,  0.732654f,  0.728464f,  0.724247f,  0.720003f,  0.715731f,  0.711432f,
     0.707107f,  0.702755f,  0.698376f,  0.693971f,  0.689541f,  0.685084f,  0.680601f,  0.676093f,
     0.671559f,  0.667000f,  0.662416f,  0.657807f,  0.653173f,  0.648514f,  0.643832f,  0.639124f,
     0.634393f,  0.629638f,  0.624859f,  0.620057f,  0.615232f,  0.610383f,  0.605511f,  0.600616f,
     0.595699f,  0.590760f,  0.585798f,  0.580814f,  0.575808f,  0.570781f,  0.565732f,  0.560662f,
     0.555570f,  0.550458f,  0.545325f,  0.540171f,  0.534998f,  0.529804f,  0.524590f,  0.519356f,
     0.514103f,  0.508830f,  0.503538f,  0.498228f,  0.492898f,  0.487550f,  0.482184f,  0.476799f,
     0.471397f,  0.465976f,  0.460539f,  0.455084f,  0.449611f,  0.444122f,  0.438616f,  0.433094f,
     0.427555f,  0.422000f,  0.416430f,  0.410843f,  0.405241f,  0.399624f,  0.393992f,  0.388345f,
     0.382683f,  0.377007f,  0.371317f,  0.365613f,  0.359895f,  0.354164f,  0.348419f,  0.342661f,
     0.336890f,  0.331106f,  0.325310f,  0.319502f,  0.313682f,  0.307850f,  0.302006f,  0.296151f,
     0.290285f,  0.284408f,  0.278520f,  0.272621f,  0.266713f,  0.260794f,  0.254866f,  0.248928f,
     0.242980f,  0.237024f,  0.231058f,  0.225084f,  0.219101f,  0.213110f,  0.207111f,  0.201105f,
     0.195090f,  0.189069f,  0.183040f,  0.177004f,  0.170962f,  0.164913f,  0.158858f,  0.152797f,
     0.146730f,  0.140658f,  0.134581f,  0.128498f,  0.122411f,  0.116319f,  0.110222f,  0.104122f,
     0.098017f,  0.091909f,  0.085797f,  0.079682f,  0.073565f,  0.067444f,  0.061321f,  0.055195f,
     0.049068f,  0.042938f,  0.036807f,  0.030675f,  0.024541f,  0.018407f,  0.012272f,  0.006136f
};

ALWAYS_INLINE static float get_sin(int k, int N_pow2) // N=512 -> N=pow2=9
{
    return fft_sin_table[k << (9 - N_pow2)];
}

ALWAYS_INLINE static float get_ar(int k, int N_pow2) // N=512 -> N=pow2=9
{
    return 0.5 * (1 - get_sin(k, N_pow2));
}

ALWAYS_INLINE static float get_br(int k, int N_pow2) // N=512 -> N=pow2=9
{
    return 0.5 * (1 + get_sin(k, N_pow2));
}

ALWAYS_INLINE static float get_a_star_r(int k, int N_pow2) // N=512 -> N=pow2=9
{
    return 0.5 * (1 - get_sin(k, N_pow2));
}

ALWAYS_INLINE static float get_b_star_r(int k, int N_pow2) // N=512 -> N=pow2=9
{
    return 0.5 * (1 + get_sin(k, N_pow2));
}

///////////////////////////////////////////////////////////////////////////////

// You give the FFT N real and imaginary pairs where each pair is an even/odd
// real value from 2N data. The FFT will then output N real and imaginary pairs
// and you can use the below function to unpack that into 2N real and imaginary
// pairs the FFT would normally output with 2N data.

// Unpack 2N data from N point fft
// in = N real and complex floats
// out = 2N real and complex floats
static void unpack_fft(float *in, float *out, int N_pow2)
{
    for (int k = 0, l = 2 << N_pow2, m = l << 1; k < l; k += 2) {
        int k_r = k+0;
        int k_i = k+1;
        int N_k_r = ((!k)?0:(l-k))+0;
        int N_k_i = ((!k)?0:(l-k))+1;
        int N2_K_r = ((!k)?0:(m-k))+0;
        int N2_K_i = ((!k)?0:(m-k))+1;
        int k_2 = k >> 1;
        // real
        out[k_r] = (in[k_r] * get_ar(k_2, N_pow2)) -
                   (in[k_i] * get_ai(k_2, N_pow2)) +
                   (in[N_k_r] * get_br(k_2, N_pow2)) +
                   (in[N_k_i] * get_bi(k_2, N_pow2));
        // imaginary
        out[k_i] = (in[k_i] * get_ar(k_2, N_pow2)) +
                   (in[k_r] * get_ai(k_2, N_pow2)) +
                   (in[N_k_r] * get_bi(k_2, N_pow2)) -
                   (in[N_k_i] * get_br(k_2, N_pow2));
        if (k > 0) {
            // real conj
            out[N2_K_r] = out[k_r];
            // imaginary conj
            out[N2_K_i] = -out[k_i];
        }
    }
    out[(2 << N_pow2)+0] = in[0+0] - in[0+1];
    out[(2 << N_pow2)+1] = 0;
}

// The IFFT takes N real and imaginary pairs to generate N real and imaginary
// outputs with the imaginary part set to zero. To be more efficent this function
// packs 2N data into an N IFFT so that the N real and imaginary outputs have
// even/odd real values.

// Pack 2N data to N point fft
// in = 2N real and complex floats
// out = N real and complex floats
static void pack_fft(float *in, float *out, int N_pow2)
{
    for (int k = 0, l = 2 << N_pow2; k < l; k += 2) {
        int k_r = k+0;
        int k_i = k+1;
        int N_k_r = (l-k)+0;
        int N_k_i = (l-k)+1;
        int k_2 = k >> 1;
        // real
        out[k_r] = (in[k_r] * get_a_star_r(k_2, N_pow2)) -
                   (in[k_i] * get_a_star_i(k_2, N_pow2)) +
                   (in[N_k_r] * get_b_star_r(k_2, N_pow2)) +
                   (in[N_k_i] * get_b_star_i(k_2, N_pow2));
        // imaginary
        out[k_i] = (in[k_i] * get_a_star_r(k_2, N_pow2)) +
                   (in[k_r] * get_a_star_i(k_2, N_pow2)) +
                   (in[N_k_r] * get_b_star_i(k_2, N_pow2)) -
                   (in[N_k_i] * get_b_star_r(k_2, N_pow2));
    }
}

///////////////////////////////////////////////////////////////////////////////

ALWAYS_INLINE static int int_flog2(int x) // floor log 2
{
    return 31 - __CLZ(x);
}

ALWAYS_INLINE static int int_clog2(int x) // ceiling log 2
{
    int y = int_flog2(x);
    return (x - (1 << y)) ? (y + 1) : y;
}

///////////////////////////////////////////////////////////////////////////////

// Input even numbered index
// Output even numbered index
ALWAYS_INLINE static int bit_reverse(int index, int N_pow2)
{
    return __RBIT(index) >> (30 - N_pow2);
}

ALWAYS_INLINE static void swap(float *a, float *b)
{
    float tmp = *b;
    *b = *a;
    *a = tmp;
}

//ALWAYS_INLINE static float get_hann(int k, int N_pow2)
//{
//    if (k < (1 << N_pow2)) {
//        return get_hann_l_side(k, N_pow2);
//    } else {
//        return get_hann_r_side(k, N_pow2);
//    }
//}

// Copies 2N real pairs (or pad with zero) from in to out while bit reversing
// their indexes.

static void prepare_real_input(uint8_t *in, int in_len, float *out, int N_pow2)
{
    for (int k = 0, l = 2 << N_pow2; k < l; k += 2) {
        int m = bit_reverse(k, N_pow2);
        out[m+0] = ((k+0) < in_len) ? in[k+0] : 0;
        out[m+1] = ((k+1) < in_len) ? in[k+1] : 0;
//        // Apply Hann Window (this is working on real numbers)
//        out[m+0] *= get_hann(k+0, N_pow2);
//        out[m+1] *= get_hann(k+1, N_pow2);
    }
}

//// This works on complex numbers...
//static void apply_hann_window(float *inout, int N_pow2, int stride)
//{
//    for (int k = 0, l = 2 << N_pow2; k < l; k += 2) {
//        inout[(k*stride)+0] *= get_hann(k>>1, N_pow2-1);
//        inout[(k*stride)+1] *= get_hann(k>>1, N_pow2-1);
//    }
//}

// Copies N complex pairs from in to out while bit reversing their indexes. The
// in and out arrays may be the same.

static void prepare_complex_input(float *in, float *out, int N_pow2, int stride)
{
    if(in == out) {
        for (int k = 0, l = 2 << N_pow2; k < l; k += 2) {
            int m = bit_reverse(k, N_pow2);
            if (k < m) {
                swap(out+(m*stride)+0, in+(k*stride)+0);
                swap(out+(m*stride)+1, in+(k*stride)+1);
            }
        }
    } else {
        for (int k = 0, l = 2 << N_pow2; k < l; k += 2) {
            int m = bit_reverse(k, N_pow2);
            out[(m*stride)+0] = in[(k*stride)+0];
            out[(m*stride)+1] = in[(k*stride)+1];
        }
    }
}

///////////////////////////////////////////////////////////////////////////////

// Performs the fft in place.
static void do_fft(float *inout, int N_pow2, int stride)
{
    int N = 2 << N_pow2;
    for (int N_pow2_i = 1; N_pow2_i <= N_pow2; N_pow2_i++) {
        int N_mul2 = 2 << N_pow2_i;
        int N_div2 = 1 << N_pow2_i;
        for (int i = 0; i < N; i += N_mul2) {
            for (int j = i, k = 0, l = i + N_div2, m = N >> N_pow2_i; j < l; j += 2, k += m) {
                int x0_r = (j*stride)+0;
                int x0_i = (j*stride)+1;
                int x1_r = ((j+N_div2)*stride)+0;
                int x1_i = ((j+N_div2)*stride)+1;
                float tmp_r = (inout[x1_r] * get_cos(k, N_pow2)) +
                              (inout[x1_i] * get_sin(k, N_pow2));
                float tmp_i = (inout[x1_i] * get_cos(k, N_pow2)) -
                              (inout[x1_r] * get_sin(k, N_pow2));
                inout[x1_r] = inout[x0_r] - tmp_r;
                inout[x1_i] = inout[x0_i] - tmp_i;
                inout[x0_r] += tmp_r;
                inout[x0_i] += tmp_i;
            }
        }
    }
}

// Performs the ifft in place.
static void do_ifft(float *inout, int N_pow2, int stride)
{
    int N = 2 << N_pow2;
    for (int N_pow2_i = 1; N_pow2_i <= N_pow2; N_pow2_i++) {
        int N_mul2 = 2 << N_pow2_i;
        int N_div2 = 1 << N_pow2_i;
        for (int i = 0; i < N; i += N_mul2) {
            for (int j = i, k = 0, l = i + N_div2, m = N >> N_pow2_i; j < l; j += 2, k += m) {
                int x0_r = (j*stride)+0;
                int x0_i = (j*stride)+1;
                int x1_r = ((j+N_div2)*stride)+0;
                int x1_i = ((j+N_div2)*stride)+1;
                float tmp_r = (inout[x1_r] * get_cos(k, N_pow2)) -
                              (inout[x1_i] * get_sin(k, N_pow2));
                float tmp_i = (inout[x1_i] * get_cos(k, N_pow2)) +
                              (inout[x1_r] * get_sin(k, N_pow2));
                inout[x1_r] = inout[x0_r] - tmp_r;
                inout[x1_i] = inout[x0_i] - tmp_i;
                inout[x0_r] += tmp_r;
                inout[x0_i] += tmp_i;
            }
        }
    }

    float div = 1.0 / (N >> 1);
    for (int i = 0; i < N; i += 2) {
        inout[(i*stride)+0] *= div;
        inout[(i*stride)+1] *= div;
    }
}

///////////////////////////////////////////////////////////////////////////////

void fft1d_alloc(fft1d_controller_t *controller, uint8_t *buf, int len)
{
    controller->d_pointer = buf;
    controller->d_len = len;
    controller->pow2 = int_clog2(len);
    controller->data = fb_alloc((2 << controller->pow2) * sizeof(float));
}

void fft1d_dealloc()
{
    fb_free();
}

void fft1d_run(fft1d_controller_t *controller)
{
    // We can speed up the FFT by packing data into both the real and imaginary
    // values. This results in having to do an FFT of half the size normally.

    float *h_buffer = fb_alloc((1 << controller->pow2) * sizeof(float));
    prepare_real_input(controller->d_pointer, controller->d_len,
                       h_buffer, controller->pow2 - 1);
    do_fft(h_buffer, controller->pow2 - 1, 1);
    unpack_fft(h_buffer, controller->data, controller->pow2 - 1);
    fb_free();
}

void ifft1d_run(fft1d_controller_t *controller)
{
    // We can speed up the FFT by packing data into both the real and imaginary
    // values. This results in having to do an FFT of half the size normally.

    float *h_buffer = fb_alloc((1 << controller->pow2) * sizeof(float));
    pack_fft(controller->data, h_buffer, controller->pow2 - 1);
    prepare_complex_input(h_buffer, h_buffer,
                          controller->pow2 - 1, 1);
    do_ifft(h_buffer, controller->pow2 - 1, 1);
    memset(controller->data, 0, (2 << controller->pow2) * sizeof(float));
    memcpy(controller->data, h_buffer, (1 << controller->pow2) * sizeof(float));
    fb_free();
}

///////////////////////////////////////////////////////////////////////////////

void fft2d_alloc(fft2d_controller_t *controller, image_t *img, rectangle_t *r)
{
    controller->img = img;
    if (!rectangle_subimg(controller->img, r, &controller->r)) ff_no_intersection(NULL);

    controller->w_pow2 = int_clog2(controller->r.w);
    controller->h_pow2 = int_clog2(controller->r.h);

    controller->data =
    fb_alloc0(2 * (1 << controller->w_pow2) * (1 << controller->h_pow2) * sizeof(float));
}

void fft2d_dealloc()
{
    fb_free();
}

// RGB565 to YUV conversion
extern const int8_t yuv_table[196608];

void fft2d_run(fft2d_controller_t *controller)
{
    // This section copies image data into the fft buffer. It takes care of
    // extracting the grey channel from RGB images if necessary. The code
    // also handles dealing with a rect less than the image size.
    for (int i = 0; i < controller->r.h; i++) {
        // Get image data into buffer.
        uint8_t *tmp = fb_alloc(controller->r.w * sizeof(uint8_t));
        for (int j = 0; j < controller->r.w; j++) {
            if (IM_IS_GS(controller->img)) {
                tmp[j] = IM_GET_GS_PIXEL(controller->img,
                    controller->r.x + j, controller->r.y + i);
            } else {
                tmp[j] = yuv_table[IM_GET_RGB565_PIXEL(controller->img,
                    controller->r.x + j, controller->r.y + i)*3];
            }
        }
        // Do FFT on image data and copy to main buffer.
        fft1d_controller_t fft1d_controller_i;
        fft1d_alloc(&fft1d_controller_i, tmp, controller->r.w);
        fft1d_run(&fft1d_controller_i);
        memcpy(controller->data + (i * (2 << controller->w_pow2)),
               fft1d_controller_i.data, (2 << fft1d_controller_i.pow2) * sizeof(float));
        fft1d_dealloc();
        // Free image data buffer.
        fb_free();
    }

    // The above operates on the rows and this fft operates on the columns. To
    // avoid having to transpose the array the fft takes a stride input.
    for (int i = 0, ii = (2 << controller->w_pow2); i < ii; i += 2) {
        float *p = controller->data + i;
        // Vertical FFTs are full FFTs...
//        apply_hann_window(p, controller->h_pow2, (1 << controller->w_pow2));
        prepare_complex_input(p, p, controller->h_pow2, (1 << controller->w_pow2));
        do_fft(p, controller->h_pow2, (1 << controller->w_pow2));
    }
}

void ifft2d_run(fft2d_controller_t *controller)
{
    // Do columns...
    for (int i = 0, ii = (2 << controller->w_pow2); i < ii; i += 2) {
        float *p = controller->data + i;
        // Vertical FFTs are full FFTs...
        prepare_complex_input(p, p, controller->h_pow2, (1 << controller->w_pow2));
        do_ifft(p, controller->h_pow2, (1 << controller->w_pow2));
    }

    // Do rows...
    for (int i = 0; i < controller->r.h; i++) {
        fft1d_controller_t fft1d_controller_i;
        fft1d_controller_i.pow2 = controller->w_pow2;
        fft1d_controller_i.data = controller->data + (i * (2 << controller->w_pow2));
        ifft1d_run(&fft1d_controller_i);
    }
}
