
uniform float time;
uniform int wind;

void main() {


	float y = cos( (gl_MultiTexCoord0.s * wind + time * wind * .5) * 3.14159265);
	
	vec4 updateXYZ = vec4(0, y * .03,0,1);
	
	gl_Position = gl_ModelViewProjectionMatrix * (gl_Vertex + updateXYZ);

	gl_TexCoord[0] = gl_MultiTexCoord0;
}
