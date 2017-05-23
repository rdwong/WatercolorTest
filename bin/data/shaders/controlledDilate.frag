#version 120
#extension GL_ARB_texture_rectangle : enable

uniform sampler2DRect src_tex_unit0;
uniform vec2 wsize; // window size (width, height)
uniform vec2 dropPos; // drop position
uniform float radius; // drop radius
uniform float amt; // dilate amt
varying vec2 texCoordVarying;

void main(void) {
    
    // original pixel color
    vec4 c = texture2DRect(src_tex_unit0, texCoordVarying);
    
    // get pixel value of frag
    vec2 vpos = gl_FragCoord.xy;
    
    //vpos.x *= wsize.x;
    //vpos.y *= wsize.y;
    
    // get distance in pixels
    float d = distance(dropPos, vpos);
    float strength = 0.5*clamp(1.0 - d/radius, 0.0, 1.0);
    
    // get src vertex
    float angle = atan(dropPos.y - vpos.y, dropPos.x - vpos.x);
    vec2 srcCoord = vec2(vpos.x + strength*cos(angle), vpos.y + strength*sin(angle));
    
    // get src Color
    vec4 src = texture2DRect(src_tex_unit0, srcCoord);
    
    // merge over c
    c += amt*(src - c);
    
    gl_FragColor = c;
    
}