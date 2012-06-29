// This matrix member variable provides a hook to manipulate
// the coordinates of the objects that use this vertex shader
        
	uniform mat4 uMVPMatrix;
	attribute vec4 a_Position;
	attribute vec4 a_Colour;
	attribute vec2 a_Texture;
	attribute vec3 a_Normal;
        
	varying vec4 v_Colour;
	varying vec2 v_Texture;
	varying vec3 v_Normal;
        
	void main(){
        
		v_Colour = a_Colour;
		v_Texture = a_Texture;
		v_Normal = a_Normal;
        
		// the matrix must be included as a modifier of gl_Position
		gl_Position = uMVPMatrix * a_Position;
        
	}