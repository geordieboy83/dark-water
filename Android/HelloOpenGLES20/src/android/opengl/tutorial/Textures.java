package android.opengl.tutorial;

import java.util.HashMap;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.opengl.GLES20;
import android.opengl.GLUtils;

public class Textures {	
	protected static HashMap<Integer, Integer> myTexturesI = new HashMap<Integer, Integer>();
	protected static HashMap<String, Integer> myTexturesS = new HashMap<String, Integer>();
	
	public static int getTexture(int id) { return (myTexturesI.get(id)==null?0:myTexturesI.get(id)); }
	public static int getTexture(String id) { return (myTexturesS.get(id)==null?0:myTexturesS.get(id)); }	
	
	
	public static void useTexture(int textureunit, int textureid, Program shader){
		
		if(textureunit<0) return;
	
		// Set the active texture unit to texture unit 0.
    	GLES20.glActiveTexture(GLES20.GL_TEXTURE0+textureunit);
    
    	// Bind the texture to this unit.
    	GLES20.glBindTexture(GLES20.GL_TEXTURE_2D, textureid);
    
    	// Tell the texture uniform sampler to use this texture in the shader by binding to texture unit 0.
    	GLES20.glUniform1i(shader.getTexture2D(), textureunit);
	}
	
	
	public static int loadTexture(final Context context, final int resourceId)
	{
		final int[] textureHandle = new int[1];
		
		GLES20.glGenTextures(1, textureHandle, 0);
		
		if (textureHandle[0] != 0)
		{
			final BitmapFactory.Options options = new BitmapFactory.Options();
			options.inScaled = false;	// No pre-scaling

			// Read in the resource
			final Bitmap bitmap = BitmapFactory.decodeResource(context.getResources(), resourceId, options);
						
			// Bind to the texture in OpenGL
			GLES20.glBindTexture(GLES20.GL_TEXTURE_2D, textureHandle[0]);
			
			// Set filtering
			GLES20.glTexParameteri(GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_MIN_FILTER, GLES20.GL_NEAREST);
			GLES20.glTexParameteri(GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_MAG_FILTER, GLES20.GL_NEAREST);
			
			// Load the bitmap into the bound texture.
			GLUtils.texImage2D(GLES20.GL_TEXTURE_2D, 0, bitmap, 0);
			
			// Recycle the bitmap, since its data has been loaded into OpenGL.
			bitmap.recycle();						
		}

		if(textureHandle[0]!=0){
			myTexturesI.put(resourceId, textureHandle[0]);			
		}
		else {
			System.out.println("Error creating texture");
		}

		return textureHandle[0];
	}
	
	
}
