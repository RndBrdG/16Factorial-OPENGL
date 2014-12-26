uniform sampler2D feupImage;

void main() {
	gl_FragColor = texture2D(feupImage, gl_TexCoord[0].st);
}
