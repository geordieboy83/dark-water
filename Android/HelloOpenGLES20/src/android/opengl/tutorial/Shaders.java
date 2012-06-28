package android.opengl.tutorial;

import android.content.Context;
import android.opengl.GLES20;
import android.util.Log;

public class Shaders {
	
	public static Program currentShader=null;

	public static String vertexShaderCode="";
	
	public static String fragmentShaderCode="";
	
	public static String fromArray(String[] array){
		String s="";
		if(array==null||array.length==0) return s;		
		for(String ss: array) s+=ss+"\n";
		return s;
	}
	
	public static String fromArray(Context context, int rID){
		return fromArray(context.getResources().getStringArray(rID));
	}
	
	public static int makeShader(int type, String shaderCode){
        
        // create a vertex shader type (GLES20.GL_VERTEX_SHADER)
        // or a fragment shader type (GLES20.GL_FRAGMENT_SHADER)
        int shader = GLES20.glCreateShader(type); 
        
        // add the source code to the shader and compile it
        GLES20.glShaderSource(shader, shaderCode);
        GLES20.glCompileShader(shader);
        
        // get the compilation status.
     	final int[] compileStatus = new int[1];
     	GLES20.glGetShaderiv(shader, GLES20.GL_COMPILE_STATUS, compileStatus, 0);

     	// If the compilation failed, delete the shader.    	
     	
     	if (compileStatus[0] == 0){    		
     		System.out.println(
     				"Error compiling "+
     				(type==GLES20.GL_VERTEX_SHADER?"vertex":"fragment")+		
     				" shader: " + GLES20.glGetShaderInfoLog(shader));
     		GLES20.glDeleteShader(shader);
     		shader = 0;
     	}     
        
        return shader;
    }	
	
	public static int makeShader(int type, String[] shaderCode){
		return makeShader(type,fromArray(shaderCode)); 
	}

	public static int makeShader(int type, Context context, int rID){
		return makeShader(type,fromArray(context,rID)); 
	}
	
	public static int vertexShader(String[] shaderCode){
		return makeShader(GLES20.GL_VERTEX_SHADER,shaderCode);
	}
	
	public static int vertexShader(String shaderCode){
		return makeShader(GLES20.GL_VERTEX_SHADER,shaderCode);
	}
	
	public static int vertexShader(Context context, int rID){
		return makeShader(GLES20.GL_VERTEX_SHADER,context,rID);
	}
	
	
	public static int fragmentShader(String[] shaderCode){
		return makeShader(GLES20.GL_FRAGMENT_SHADER,shaderCode);
	}
	
	public static int fragmentShader(String shaderCode){
		return makeShader(GLES20.GL_FRAGMENT_SHADER,shaderCode);
	}
	
	public static int fragmentShader(Context context, int rID){
		return makeShader(GLES20.GL_FRAGMENT_SHADER,context,rID);
	}
	
	public static int makeProgram(int vertexShader, int fragmentShader, String ...attributes){
		 int mProgram = GLES20.glCreateProgram();           // create empty OpenGL Program
	     GLES20.glAttachShader(mProgram, vertexShader);   	// add the vertex shader to program
	     GLES20.glAttachShader(mProgram, fragmentShader);	// add the fragment shader to program
	     
	     if(attributes!=null)								// bind attributes, if any
	    	 for(int i=0; i<attributes.length; i++)
	    		 if(attributes[i]!=null&&!attributes[i].isEmpty())
	    			 GLES20.glBindAttribLocation(mProgram, i, attributes[i]);
	     
	     GLES20.glLinkProgram(mProgram);					// create OpenGL program executables
	     
	     final int[] linkStatus = new int[1];				// Get the link status.
	  	 GLES20.glGetProgramiv(mProgram, GLES20.GL_LINK_STATUS, linkStatus, 0);
	  	 	  	 								
	  	 if (linkStatus[0] == 0){ 							// If the link failed, delete the program.
	  		 System.out.println("Error compiling program: " + GLES20.glGetProgramInfoLog(mProgram));
	  		 GLES20.glDeleteProgram(mProgram);
	  		 mProgram = 0;
	  	}
	  	 
	     return mProgram;
	}
	
	
	public static int makeProgram(String[] vertexShaderCode, String[] fragmentShaderCode, String ... attributes){
		return makeProgram(vertexShader(vertexShaderCode), fragmentShader(fragmentShaderCode),attributes);
	}
	
	public static int makeProgram(String vertexShaderCode, String fragmentShaderCode, String ... attributes){
		return makeProgram(vertexShader(vertexShaderCode), fragmentShader(fragmentShaderCode),attributes);
	}
	
	public static int makeProgram(Context context, int vertexShaderCode, int fragmentShaderCode, String...attributes){
		return makeProgram(vertexShader(context, vertexShaderCode), fragmentShader(context,fragmentShaderCode),attributes);
	}
	
}
