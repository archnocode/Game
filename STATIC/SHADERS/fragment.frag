#version 120

uniform sampler2D texture;
uniform vec2 offset;

void main() {
    vec4 color = vec4(0.0);
    color += texture2D(texture, gl_TexCoord[0].xy - offset * 4.0) * 0.05;
    color += texture2D(texture, gl_TexCoord[0].xy - offset * 3.0) * 0.09;
    color += texture2D(texture, gl_TexCoord[0].xy - offset * 2.0) * 0.12;
    color += texture2D(texture, gl_TexCoord[0].xy - offset * 1.0) * 0.15;
    color += texture2D(texture, gl_TexCoord[0].xy) * 0.18;
    color += texture2D(texture, gl_TexCoord[0].xy + offset * 1.0) * 0.15;
    color += texture2D(texture, gl_TexCoord[0].xy + offset * 2.0) * 0.12;
    color += texture2D(texture, gl_TexCoord[0].xy + offset * 3.0) * 0.09;
    color += texture2D(texture, gl_TexCoord[0].xy + offset * 4.0) * 0.05;
    gl_FragColor = color;
}