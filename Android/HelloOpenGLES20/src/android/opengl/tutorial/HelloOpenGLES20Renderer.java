package android.opengl.tutorial;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.opengl.GLES20;
import android.opengl.GLSurfaceView;
import android.opengl.Matrix;
import android.os.SystemClock;

public class HelloOpenGLES20Renderer implements GLSurfaceView.Renderer {
  
//	private FloatBuffer triangleVB;
	 
	Program myProgram;
	 
    private float[] mMVPMatrix = new float[16];
    private float[] mMMatrix = new float[16];
	private float[] mVMatrix = new float[16];
	private float[] mProjMatrix = new float[16];
	    
	 
	public float mAngle;  
	
	public Model myModel;
	    
	    
	
	 public void onSurfaceCreated(GL10 unused, EGLConfig config) {
		    
	        // Set the background frame color
	        GLES20.glClearColor(0f, 0f, 0f, 1.0f);
	        
	        // initialize the triangle vertex array
	        initShapes();	        

	        myProgram=new Program(
	        		Shaders.vertexShaderCode, Shaders.fragmentShaderCode,
	        		Program.makeAttributes("a_Position", "a_Colour", "",""),
	        		Program.makeUniforms("uMVPMatrix"));
	    }
    
    public void onDrawFrame(GL10 unused) {
    
        // Redraw background color
        GLES20.glClear(GLES20.GL_COLOR_BUFFER_BIT | GLES20.GL_DEPTH_BUFFER_BIT);
     
        
      
        // Create a rotation for the triangle (Boring! Comment this out:)
        // long time = SystemClock.uptimeMillis() % 4000L;
        // float angle = 0.090f * ((int) time);
//        Matrix.setRotateM(mMMatrix, 0, angle, 0, 0, 1.0f);

        // Use the mAngle member as the rotation value
        Matrix.setRotateM(mMMatrix, 0, mAngle, 0, 0, 1.0f);

        Matrix.multiplyMM(mMVPMatrix, 0, mVMatrix, 0, mMMatrix, 0);
        Matrix.multiplyMM(mMVPMatrix, 0, mProjMatrix, 0, mMVPMatrix, 0);
        
        myModel.draw(mMVPMatrix, myProgram);
        
 /*    // Add program to OpenGL environment
        myProgram.use();
        
        // Prepare the triangle data
        GLES20.glVertexAttribPointer(myProgram.getPosition(), 3, GLES20.GL_FLOAT, false, 12, myModel.getBuffer());
        GLES20.glEnableVertexAttribArray(myProgram.getPosition());
        
        // Apply a ModelView Projection transformation
        GLES20.glUniformMatrix4fv(myProgram.getModelView(), 1, false, mMVPMatrix, 0);
        
        // Draw the triangle
        GLES20.glDrawArrays(GLES20.GL_TRIANGLES, 0, myModel.getBuffer().capacity()/3);*/
    }
    
    public void onSurfaceChanged(GL10 unused, int width, int height) {
        GLES20.glViewport(0, 0, width, height);
        
        float ratio = (float) width / height;
        
        // this projection matrix is applied to object coodinates
        // in the onDrawFrame() method
        Matrix.frustumM(mProjMatrix, 0, -ratio, ratio, -1, 1, 3, 7);
        Matrix.setLookAtM(mVMatrix, 0, 0, 0, 3, 0f, 0f, 0f, 0f, 1.0f, 0.0f);
    }  
  
    
    private void initShapes(){
        
        float triangleCoords[] = {
            // X, Y, Z
            -0.5f, -0.25f, 0,
             0.5f, -0.25f, 0,
             0.0f,  0.559016994f, 0,
             
             -0.5f, -0.5f, 0,
             -0.75f, -0.5f, 0,
             -0.55f,  0.559016994f, 0,
             
             0.5f, -0.5f, 0,
             0.75f, -0.5f, 0,
             0.55f,  0.559016994f, 0
             
             
        }; 
        
        
        float colourCoords[]= {
				// R, G, B, A
	            1.0f, 0.0f, 0.0f, 1.0f,
	            0.0f, 0.0f, 1.0f, 1.0f,
	            0.0f, 1.0f, 0.0f, 1.0f,
		
				// R, G, B, A
	            1.0f, 1.0f, 0.0f, 1.0f,
	            0.0f, 1.0f, 1.0f, 1.0f,
	            1.0f, 0.0f, 1.0f, 1.0f,
		
	            // R, G, B, A
	            1.0f, 1.0f, 1.0f, 1.0f,
	            0.5f, 0.5f, 0.5f, 1.0f,
	            0.0f, 0.0f, 0.0f, 1.0f};        
        

        
        float texCoords[]={
        		0,0,
        		1,0,
        		0.5f,1,
        		0,0,
        		1,0,
        		0.5f,1,
        		0,0,
        		1,0,
        		0.5f,1,
        };
        
        myModel=new Model(triangleCoords,colourCoords,texCoords,null);
//        myModel=new Model(triangleCoords,colourCoords,null,null);
//        myModel=new Model(triangleCoords,null,texCoords,null);
    
    }    
    
    
}
