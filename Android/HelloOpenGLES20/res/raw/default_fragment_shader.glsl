
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
        
    varying vec4 v_Position;
        
	void main(){        
        
        vec4 interpolatedColour=(
			(uses_Colours==YES?v_Colour:vec4(1,1,1,1))*
        	(uses_Textures==YES?texture2D(u_Texture, v_Texture+vec2(X_PER_SEC*u_Time, Y_PER_SEC*u_Time)):vec4(1,1,1,1))
        	);
        
        float diffuse;	
        if(uses_Normals==YES){
        	vec3 u_LightPos=vec3(0.0,0.0,10.0);
        	vec3 pos=vec3(v_Position);
        	
        	// Will be used for attenuation.
    		float distance = length(u_LightPos - pos);
	 
   			// Get a lighting direction vector from the light to the vertex.
    		vec3 lightVector = normalize(u_LightPos - pos);
 
    		// Calculate the dot product of the light vector and vertex normal. If the normal and light vector are
    		// pointing in the same direction then it will get max illumination.
    		diffuse = max(dot(v_Normal, lightVector), 0.1);
 
    		// Add attenuation.
    		diffuse = diffuse * (1.0 / (1.0 + (0.25 * distance * distance)));
 		}
 		else{
 			diffuse=1.0;
 		}
    
    		
        	       
        
		//gl_FragColor =(
		//	(uses_Colours==YES?v_Colour:vec4(1,1,1,1))*
        //	(uses_Textures==YES?texture2D(u_Texture, v_Texture):vec4(1,1,1,1))
        //	);
        
        //gl_FragColor = interpolatedColour;  
        
        gl_FragColor = interpolatedColour * diffuse;      
        	
	}