package android.opengl.tutorial;

import android.opengl.GLES20;

public class VBO extends BufferObject {
	
	public VBO(float[] data) {
		super(data, Shaders.ATTR_POS, Model.COORDINATES_PER_VERTEX);		
	}
	
	public void render(boolean isFilled){
		if(!isFilled) {			
			GLES20.glDrawArrays(GLES20.GL_LINE_STRIP, 0, myBufferElements);
//			GLES20.glDrawArrays(GLES20.GL_LINE_LOOP, 0, myBufferElements);
//			for(int i = 0; i < 3*(int) Math.floor(myBufferElements/9.0); i += 3)				
//					GLES20.glDrawArrays(GLES20.GL_LINE_LOOP, i, 3);
		}
    	else GLES20.glDrawArrays(GLES20.GL_TRIANGLES, 0, myBufferElements);
		
//		GLES20.glBindBuffer(GLES20.GL_ARRAY_BUFFER, 0);
	}

}
