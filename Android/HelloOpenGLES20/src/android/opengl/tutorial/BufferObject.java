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
	
	public void draw(Program shaders){}
	
	public void create(){}
	
	public void destroy(){ GLES20.glDeleteBuffers(1, new int[]{myGPUBuffer}, 0); }
    
}