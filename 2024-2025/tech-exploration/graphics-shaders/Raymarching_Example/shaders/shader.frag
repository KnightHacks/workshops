#version 330 core
uniform float iTime;
uniform vec2 iMouse;
uniform vec2 iResolution;

in vec2 fragCoord;
out vec4 fragColor;


struct Object {
    vec4 col;
    float d;
};

float sdBox( vec3 p, vec3 b )
{
  vec3 q = abs(p) - b;
  return length(max(q,0.0)) + min(max(q.x,max(q.y,q.z)),0.0);
}

mat2 rot2D(float a) {
    return mat2(cos(a), -sin(a), sin(a), cos(a));
}

Object map(vec3 p) {
    vec3 q = fract(p) - 0.5;
    q.xz *= rot2D(iTime*2.);

    float d = 0.02/abs(sin(length(q)*8. + iTime)/8.);

    Object box = Object(vec4(d, 0.0, 0.0, 1.0), sdBox(q, vec3(0.2)));
    Object scene = Object(vec4(vec3(0.), 1.0), p.y+.75);
    
    return box.d < scene.d ? box : scene;
}

void main() {
    vec2 uv = fragCoord;

    vec3 ro = vec3(0., 0., -3.);
    vec3 rd = normalize(vec3(uv, 1.0));

    vec2 m = (iMouse * 2 - iResolution) / iResolution;
    m.y = clamp(m.y, -1, 0);
    ro.xz *= rot2D(-m.x);
    rd.xz *= rot2D(-m.x);

    ro.yz *= rot2D(-m.y);
    rd.yz *= rot2D(-m.y);
    

    float t = 0.;

    Object o;
    int i;
    for (i = 0; i < 80; i++) {
        vec3 p = ro + rd*t;

        o = map(p);

        t += o.d;
        if (o.d < 0.01 || o.d > 100) break; 
    }

    if (t*.02 < 1) {
        fragColor = vec4(o.col.xyz + float(i)*0.01, 1.0);
    } else {
        fragColor = vec4(1.0);
    }
}