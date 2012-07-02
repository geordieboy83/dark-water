package android.opengl.tutorial;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;
import java.nio.ShortBuffer;

public class Models {

	public static final int WIREFRAME=Integer.valueOf("1000000",2);    
    public static final int NONE=Byte.valueOf("0000000",2);
    public static final int COLOURS=Byte.valueOf("0000001",2);
    public static final int TEXTURE=Byte.valueOf("0000010",2);
    public static final int NORMALS=Byte.valueOf("0000100",2);
    
    public static final int BYTES_PER_FLOAT=4;
    public static final int BYTES_PER_SHORT = 2;
    
    public static FloatBuffer fromArray(float data[]){
		if(data==null||data.length==0) return null;
        ByteBuffer vbb = ByteBuffer.allocateDirect(data.length * BYTES_PER_FLOAT); 
        vbb.order(ByteOrder.nativeOrder());
        FloatBuffer result = vbb.asFloatBuffer();
        result.put(data);
        result.position(0);
        return result;
	}
	
	public static ShortBuffer fromArray(short data[]){
		if(data==null||data.length==0) return null;
        ByteBuffer vbb = ByteBuffer.allocateDirect(data.length * BYTES_PER_SHORT); 
        vbb.order(ByteOrder.nativeOrder());
        ShortBuffer result = vbb.asShortBuffer();
        result.put(data);
        result.position(0);
        return result;
	}
	
	
	
}
