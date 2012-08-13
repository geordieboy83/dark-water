package android.opengl.tutorial;

import java.nio.Buffer;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;
import java.nio.ShortBuffer;

import android.opengl.GLES20;

public class BufferObject {

	public static final int BYTES_PER_FLOAT = 4;
    public static final int BYTES_PER_SHORT = 2;
	
    protected Buffer myData=null; 
    protected int myGPUBuffer=0;
    protected int myBufferElements=0;
    protected int myPerVertexElements=0;
    
    
    protected static FloatBuffer fromArray(float data[]){
		if(data==null||data.length==0) return null;
        ByteBuffer vbb = ByteBuffer.allocateDirect(data.length * BufferObject.BYTES_PER_FLOAT); 
        vbb.order(ByteOrder.nativeOrder());
        FloatBuffer result = vbb.asFloatBuffer();
        result.put(data);
        result.position(0);
        return result;
	}
	
	protected static ShortBuffer fromArray(short data[]){
		if(data==null||data.length==0) return null;
        ByteBuffer vbb = ByteBuffer.allocateDirect(data.length * BufferObject.BYTES_PER_SHORT); 
        vbb.order(ByteOrder.nativeOrder());
        ShortBuffer result = vbb.asShortBuffer();
        result.put(data);
        result.position(0);
        return result;
	}
	
	
	public void destroy(){ GLES20.glDeleteBuffers(1, new int[]{myGPUBuffer}, 0); }
	
	
	protected String myAttribute="";
	
	public BufferObject(float data[], String attribute, int elementsPerVertex){
		myData=fromArray(data);
		myAttribute=attribute;
		myPerVertexElements=elementsPerVertex;
		create();
	}
	
	protected void create(){
		final int buffers[] = new int[1];
		GLES20.glGenBuffers(1, buffers, 0);
		
		if(buffers[0]>0){
		 
			// Bind to the buffer. Future commands will affect this buffer specifically.
			GLES20.glBindBuffer(GLES20.GL_ARRAY_BUFFER, buffers[0]);
		 
			// Transfer data from client memory to the buffer.
			// We can release the client memory after this call.
			GLES20.glBufferData(GLES20.GL_ARRAY_BUFFER, myData.capacity() * BYTES_PER_FLOAT, myData, GLES20.GL_STATIC_DRAW);
		 
			// IMPORTANT: Unbind from the buffer when we're done with it.
			GLES20.glBindBuffer(GLES20.GL_ARRAY_BUFFER, 0);
			
			myBufferElements=myData.capacity();
			myGPUBuffer=buffers[0];
			
			myData.limit(0);
			myData=null;			
			
		}		
	}
	
	public void draw(Program shaders){
		
		if(myData==null){
			GLES20.glBindBuffer(GLES20.GL_ARRAY_BUFFER, myGPUBuffer);
			GLES20.glEnableVertexAttribArray(shaders.getAttribute(myAttribute));
			GLES20.glVertexAttribPointer(shaders.getAttribute(myAttribute), myPerVertexElements, GLES20.GL_FLOAT, false, 0, 0);
		}
		else {			
			myData.position(0);
        	GLES20.glVertexAttribPointer(shaders.getColour(), myPerVertexElements, GLES20.GL_FLOAT, false,
        			myPerVertexElements*BYTES_PER_FLOAT, myData);        
        
        	GLES20.glEnableVertexAttribArray(shaders.getAttribute(myAttribute));
		}
	}
	
	
    
}