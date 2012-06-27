package android.opengl.tutorial;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;

import android.opengl.GLES20;
import android.opengl.Matrix;

public class Model {
	
	protected static final int COORDINATES_PER_VERTEX=3;
	protected static final int COLOUR_COMPONENTS_PER_VERTEX=4;
	protected static final int TEXTURE_COORDINATES_PER_VERTEX=2;
	protected static final int BYTES_PER_FLOAT=4;

	protected FloatBuffer myVertices=null;
	
	protected boolean hasColours=false;
	protected boolean hasTextures=false;	
	
	public Model(){}
	
	public Model(float xyz[], float rgba[], float st[]){
		make(xyz,rgba,st);		
	}
	
	
	protected int stride() { 
		return COORDINATES_PER_VERTEX+
				(hasColours?COLOUR_COMPONENTS_PER_VERTEX:0)+
				(hasTextures?TEXTURE_COORDINATES_PER_VERTEX:0);
	}
	
	public void make(float xyz[], float rgba[], float st[]){
		if(xyz==null||xyz.length==0) return;
		
		hasColours=(rgba!=null&&rgba.length>0);
		hasTextures=(st!=null&&st.length>0);
				
		int xyzs=xyz.length/COORDINATES_PER_VERTEX;
		
		float data[]=new float[xyzs*stride()];
		int j=0,k=0,l=0;
		for(int i=0; i<data.length;){
			
			for(int jj=0; jj<COORDINATES_PER_VERTEX; jj++) data[i++]=xyz[j+jj];  j+=COORDINATES_PER_VERTEX;
		
			if(hasColours) try{
				for(int kk=0; kk<COLOUR_COMPONENTS_PER_VERTEX; kk++) data[i++]=rgba[k+kk];	k+=COLOUR_COMPONENTS_PER_VERTEX;
			}catch(Throwable t){System.out.println(t);}
			
			if(hasTextures) try{
				for(int ll=0; ll<COLOUR_COMPONENTS_PER_VERTEX; ll++) data[i++]=st[l+ll]; l+=TEXTURE_COORDINATES_PER_VERTEX;
			}catch(Throwable t){System.out.println(t);}		
		}
		
		// initialize vertex Buffer for triangle  
        ByteBuffer vbb = ByteBuffer.allocateDirect(
                // (# of coordinate values * 4 bytes per float)
                data.length * BYTES_PER_FLOAT); 
        vbb.order(ByteOrder.nativeOrder());// use the device hardware's native byte order
        myVertices = vbb.asFloatBuffer();  // create a floating point buffer from the ByteBuffer
        myVertices.put(data);    // add the coordinates to the FloatBuffer
        myVertices.position(0);            // set the buffer to read the first coordinate
	}
	
	
	public void draw(float[] ModelView, Program shaders)
	{	
		
		System.out.println("Draw");
		
		shaders.use();
		
		// Pass in the position information
		myVertices.position(0);
        GLES20.glVertexAttribPointer(shaders.getPosition(), COORDINATES_PER_VERTEX, GLES20.GL_FLOAT, false,
        		stride()*BYTES_PER_FLOAT, myVertices);        
                
        GLES20.glEnableVertexAttribArray(shaders.getPosition());        
        
        if(hasColours){
        	// Pass in the color information        
        	myVertices.position(COORDINATES_PER_VERTEX);
        	GLES20.glVertexAttribPointer(shaders.getColour(), COLOUR_COMPONENTS_PER_VERTEX, GLES20.GL_FLOAT, false,
        			stride()*BYTES_PER_FLOAT, myVertices);        
        
        	GLES20.glEnableVertexAttribArray(shaders.getColour());
        
        }
/*		// This multiplies the view matrix by the model matrix, and stores the result in the MVP matrix
        // (which currently contains model * view).
        Matrix.multiplyMM(mMVPMatrix, 0, mViewMatrix, 0, mModelMatrix, 0);
        
        // This multiplies the modelview matrix by the projection matrix, and stores the result in the MVP matrix
        // (which now contains model * view * projection).
        Matrix.multiplyMM(mMVPMatrix, 0, mProjectionMatrix, 0, mMVPMatrix, 0);*/

        GLES20.glUniformMatrix4fv(shaders.getModelView(), 1, false, ModelView, 0);
        GLES20.glDrawArrays(GLES20.GL_TRIANGLES, 0, myVertices.capacity()/(stride()));
	}
	
		
	public final FloatBuffer getBuffer() { return myVertices; }
	
}
