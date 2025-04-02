#version 330 core
uniform float iTime;  // Time passed since the start of the program
uniform vec2 iResolution;
in vec2 fragCoord;  // The coordinates from the vertex shader
out vec4 fragColor;

vec3 red = vec3(225./255., 95./255., 60./255.); //We divide by 255 so we can get a decimal value for the color, we can of course make an rgb function for this
vec3 white = vec3(1,1,1);
vec3 blue = vec3(0.,128./255.,1.);
vec3 black = vec3(0.,0.,0.);
vec3 pink = vec3(255./255.,192./255.,203./255.);

void main()	{

    vec2 uv = (fragCoord + 1)/2;
    
    float ratio = iResolution.x / iResolution.y; //Ratio of the resolution of the entire screen
    uv.x *= ratio; //Basically normalizes the x cordinate of the uv to be correspondent to the entire screen. If we maximize our screen, the x cordinate should match the ratio!

    vec2 shapePos = vec2(0.5 * ratio, 0.5);  //Creates the position in which the shape will be drawn in, so the center
    float dist = distance(shapePos,uv); //The distance from the shape being drawn to the UV. the UV is [0,1] so think of it as basically finding the center
    
    uv -= shapePos; //Subtracing the uv by the shapePos and assigning it to that value basically centers the UV to where the shape is, allowing us to now use the UV variable to draw out the shape. We are now essentially at the origin
    
	float theta = atan(uv.y, uv.x)  + iTime ; //We are able to get the angle needed to create the rose curve, cartesian to polar coordinates
    float radius = cos(9. * theta + iTime ) * .3; //We add more petals here, it is based on the rose curve equation
    
	vec3 color = black;
    
    //We need this to draw the petals. Step acts like a binary threshold, checks for what is inside the petals, and what is outside. Based on this we can color in the petals so we can render it!
    float value = 1 - step(radius,dist);
    
    //Petals start at red, and this basically helps us draw the actual petals that are supposed to be on the screen
    color = mix(color,red,value);
    
    vec3 color2 = mix(red,white,uv.y);
    
    //Switching from red to blue for the petals
    color2 = mix(red,color, sin(iTime - uv.y)) + mix(blue,color,sin(iTime + uv.y)) ;
    
    // Output to screen
    color = mix(color,color2,1);
    
    fragColor = vec4(color,1);

}