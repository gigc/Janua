uniform MatrixBuffer {
    mat4 matWorld;
	mat4 matWorldView;
	mat4 matWorldViewProj;
	mat4 matInverseTransposeWorld;
};

attribute vec4 Position;
attribute vec4 Normal;
attribute vec4 Color;

varying vec4 vNormal;
varying vec4 vColor;

void main() {
	gl_Position = matWorldViewProj * Position;
	vNormal = matWorldViewProj * Normal;
	vColor = Color;
}