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
	
	
//	protected String myAttribute="";
//	
//	public VBO(float data[], String attribute, int elementsPerVertex){
//		myData=fromArray(data);
//		myAttribute=attribute;
//		myPerVertexElements=elementsPerVertex;
//		create();
//	}
//	
//	@Override protected void create(){			
//		final int buffers[] = new int[1];
//		GLES20.glGenBuffers(1, buffers, 0);
//		
//		if(buffers[0]>0){
//		 
//			// Bind to the buffer. Future commands will affect this buffer specifically.
//			GLES20.glBindBuffer(GLES20.GL_ARRAY_BUFFER, buffers[0]);
//		 
//			// Transfer data from client memory to the buffer.
//			// We can release the client memory after this call.
//			GLES20.glBufferData(GLES20.GL_ARRAY_BUFFER, myData.capacity() * BYTES_PER_FLOAT, myData, GLES20.GL_STATIC_DRAW);
//		 
//			// IMPORTANT: Unbind from the buffer when we're done with it.
//			GLES20.glBindBuffer(GLES20.GL_ARRAY_BUFFER, 0);
//			
//			myBufferElements=myData.capacity();
//			myGPUBuffer=buffers[0];
//			
//			myData.limit(0);
//			myData=null;			
//			
//		}		
//	}
//	
//	@Override public void draw(Program shaders){
//		
//		if(myData==null){
//			GLES20.glBindBuffer(GLES20.GL_ARRAY_BUFFER, myGPUBuffer);
//			GLES20.glEnableVertexAttribArray(shaders.getAttribute(myAttribute));
//			GLES20.glVertexAttribPointer(shaders.getAttribute(myAttribute), myPerVertexElements, GLES20.GL_FLOAT, false, 0, 0);
//		}
//		else {			
//			myData.position(0);
//        	GLES20.glVertexAttribPointer(shaders.getColour(), myPerVertexElements, GLES20.GL_FLOAT, false,
//        			myPerVertexElements*BYTES_PER_FLOAT, myData);        
//        
//        	GLES20.glEnableVertexAttribArray(shaders.getAttribute(myAttribute));
//		}
//	}
}
