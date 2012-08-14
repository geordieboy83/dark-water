package android.opengl.tutorial;

import android.opengl.GLES20;

public class IBO extends BufferObject {

	public IBO(short[] data) {
		super(data,"",1);		
	}


	@Override public void draw (Program shaders){}
	
	public void render(boolean isFilled){
		
	
		GLES20.glBindBuffer(GLES20.GL_ELEMENT_ARRAY_BUFFER, myGPUBuffer);
		

    	if(!isFilled)
    		GLES20.glDrawElements(GLES20.GL_LINE_LOOP, myBufferElements,GLES20.GL_UNSIGNED_SHORT, 0);
//    		for(int i = 0; i < myBufferElements/3; i++){    		
//    			GLES20.glDrawElements(GLES20.GL_LINE_LOOP, 3,GLES20.GL_UNSIGNED_SHORT, 3*i);
//    		}
    		
    		
//    	
    	else{    		
    		GLES20.glDrawElements(GLES20.GL_TRIANGLES, myBufferElements,GLES20.GL_UNSIGNED_SHORT, 0);
    	}		 
		
		GLES20.glBindBuffer(GLES20.GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	
}
