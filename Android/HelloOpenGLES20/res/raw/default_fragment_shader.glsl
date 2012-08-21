
	precision mediump float;
        
	const int YES=1;
	const float X_PER_SEC=0.8;
	const float Y_PER_SEC=0.8;
        
    uniform float u_Time;
	uniform int uses_Colours;
	uniform int uses_Textures;
	uniform int uses_Normals;
    uniform sampler2D u_Texture;
    uniform vec3 u_Light;
        
    varying vec4 v_Colour;
	varying vec2 v_Texture;   // Interpolated texture coordinate per fragment.
	varying vec3 v_Normal;
        
        
	void main(){        
        
        vec4 interpolatedColour=(
			(uses_Colours==YES?v_Colour:vec4(1,1,1,1))*
        	(uses_Textures==YES?texture2D(u_Texture, v_Texture+vec2(X_PER_SEC*u_Time, Y_PER_SEC*u_Time)):vec4(1,1,1,1))
        	);       
        
		//gl_FragColor =(
		//	(uses_Colours==YES?v_Colour:vec4(1,1,1,1))*
        //	(uses_Textures==YES?texture2D(u_Texture, v_Texture):vec4(1,1,1,1))
        //	);
        
        gl_FragColor = interpolatedColour;        
        	
	}