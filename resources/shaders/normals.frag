#version 330 core

// Light information
uniform vec4 lightPosition;
uniform vec3 lightIntensity;

// Material information
uniform vec3 Ka;
uniform vec3 Kd;
uniform vec3 Ks;
uniform float shininess;

// Input variables coming from vertex shader, interpolated to this fragment
in vec3 interpolatedPosition;
in vec3 interpolatedNormal;

out vec4 fragmentColor;

void main()
{

    // Calculate final color
    fragmentColor = vec4(interpolatedNormal, 1.0);
}
