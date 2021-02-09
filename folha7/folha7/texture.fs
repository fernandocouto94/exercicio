#version 330 core
out vec4 FragColor;
  
in vec3 ourColor;
in vec2 TexCoord;
in float ts;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    if(ts > 0.5f){
        FragColor = texture(texture1, TexCoord) * vec4(ourColor, 1.0);
    }
    else{
        FragColor = texture(texture2, TexCoord) * vec4(ourColor, 1.0);
    }
}
