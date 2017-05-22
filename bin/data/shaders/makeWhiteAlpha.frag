#version 120
#extension GL_ARB_texture_rectangle : enable

uniform sampler2DRect src_tex_unit0;
varying vec2 texCoordVarying;

void main(void) {
    vec4 color = texture2DRect(src_tex_unit0, texCoordVarying);
    vec4 newfrag = vec4(0.0, 0.0, 0.0, 1.0 - color.r);
    gl_FragColor = newfrag;
}