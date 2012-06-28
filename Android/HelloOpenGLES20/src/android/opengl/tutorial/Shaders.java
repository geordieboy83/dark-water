package android.opengl.tutorial;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;

import org.apache.commons.lang3.StringUtils;

import android.content.Context;
import android.opengl.GLES20;
import android.util.Log;

public class Shaders {
	
	public static final int YES=1;
	
	
	public static Program currentShader=null;

	public static String vertexShaderCode="";
	
	public static String fragmentShaderCode="";
	
	public static String fromResource(Context context, int code_id) {
		try{
			return fromArray(context, code_id);
		}catch(Throwable t){
			return fromRaw(context, code_id);
		}
	}
	
	
	public static String fromArray(String[] array){ return ((array==null||array.length==0)?"":StringUtils.join(array, "\n")); }
	
	public static String fromArray(Context context, int rID){
		return fromArray(context.getResources().getStringArray(rID));
	}
	
	public static String fromRaw(final Context context,	final int resourceId)
	{
		final InputStream inputStream = context.getResources().openRawResource(resourceId);
		final InputStreamReader inputStreamReader = new InputStreamReader(inputStream);
		final BufferedReader bufferedReader = new BufferedReader(inputStreamReader);

		String nextLine;
		final StringBuilder body = new StringBuilder();

		try
		{
			while ((nextLine = bufferedReader.readLine()) != null)
			{
				body.append(nextLine);
				body.append('\n');
			}
		}
		catch (IOException e)
		{
			return null;
		}

		return body.toString();
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
