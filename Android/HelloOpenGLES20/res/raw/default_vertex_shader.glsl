// This matrix member variable provides a hook to manipulate
// the coordinates of the objects that use this vertex shader
        
	uniform mat4 uMVPMatrix;
	uniform mat4 uNMatrix;
	attribute vec4 a_Position;
	attribute vec4 a_Colour;
	attribute vec2 a_Texture;
	attribute vec3 a_Normal;
        
	varying vec4 v_Colour;
	varying vec2 v_Texture;
	varying vec3 v_Normal;
	
	varying vec3 v_Position;
	
	uniform float u_Time;
        
	void main(){
        
		v_Colour = a_Colour;
		v_Texture = a_Texture;
		v_Normal = mat3(uNMatrix)*a_Normal;
        
        
		// the matrix must be included as a modifier of gl_Position
		//gl_Position = uMVPMatrix * (a_Position*vec4(1.0+sin(u_Time*0.1),1.0+sin(u_Time*0.1),1.0,1.0));
		//gl_Position = uMVPMatrix * a_Position;
		
		//vec4 t_Pos=uMVPMatrix * (a_Position*vec4(1.0+sin(u_Time*0.1),1.0+sin(u_Time*0.1),1.0,1.0));
		//vec4 t_Pos=uMVPMatrix * (a_Position+vec4(a_Normal*sin(u_Time*0.1),0.0));
		//vec4 t_Pos=uMVPMatrix * (a_Position+vec4(100.0*sin(u_Time*0.1)*a_Normal,0.0));
		vec4 t_Pos=uMVPMatrix * a_Position;
		
        v_Position=t_Pos.xyz;
        
        gl_Position=t_Pos;
        
        
	}