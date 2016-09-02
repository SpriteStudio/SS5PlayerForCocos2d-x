"                                                                     \n\
#ifdef GL_ES                                                          \n\
precision lowp float;                                                 \n\
#endif                                                                \n\
                                                                      \n\
varying vec4 v_fragmentColor;                                         \n\
varying vec2 v_texCoord;                                              \n\
uniform sampler2D u_texture;                                          \n\
uniform int u_selector;                                               \n\
uniform int u_partblend;                                              \n\
uniform float u_alpha;                                                \n\
uniform int u_hasPremultipliedAlpha;                                  \n\
                                                                      \n\
void main()                                                           \n\
{                                                                     \n\
	vec4 pixel = texture2D(u_texture, v_texCoord);                    \n\
	pixel.r = pixel.r / pixel.a;                                      \n\
	pixel.g = pixel.g / pixel.a;                                      \n\
	pixel.b = pixel.b / pixel.a;                                      \n\
                                                                      \n\
	float rate = v_fragmentColor.a;                                   \n\
	vec4 blend = v_fragmentColor * rate;                              \n\
    int selecter = u_selector;                                        \n\
    vec4 _blend = (selecter == 3) ? -blend : blend;                   \n\
    vec4 _color = (selecter <= 1) ? pixel * (1.0 -rate) : pixel;      \n\
    _color+=(selecter==1) ? (pixel * blend) : _blend;                 \n\
	pixel.rgb = _color.rgb ;                                          \n\
	pixel.a *= u_alpha;                                               \n\
	if((u_partblend==1)||(u_partblend==3))                            \n\
	{                                                                 \n\
		pixel.rgb *= pixel.a ;                                        \n\
	}                                                                 \n\
	gl_FragColor = pixel;                                             \n\
}                                                                     \n\
";
