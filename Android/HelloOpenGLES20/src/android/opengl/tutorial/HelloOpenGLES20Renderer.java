package android.opengl.tutorial;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.content.Context;
import android.opengl.GLES20;
import android.opengl.GLSurfaceView;
import android.opengl.Matrix;
import android.os.SystemClock;

public class HelloOpenGLES20Renderer implements GLSurfaceView.Renderer {

	 
	public static final int WIREFRAME=-1;
    public static final int FILLED=-2;
    public static final int NONE=0;
    public static final int COLOURS_ONLY=1;
    public static final int TEXTURE_ONLY=2;
    public static final int COLOURS_AND_TEXTURE=3;
	
	protected int myRenderMode=FILLED;
    
	Program myProgram;
	 
    private float[] mMVPMatrix = new float[16];
    private float[] mMMatrix = new float[16];
	private float[] mVMatrix = new float[16];
	private float[] mProjMatrix = new float[16];
	    
	 
	public float mAngle;  
	
	public Model myModel;
	 
	protected Context myContext;
	
	
	public void setMode(int mode) { myModel.setMode(mode); }
	public int getMode() { return myModel.getMode(); }	
	  
	public HelloOpenGLES20Renderer(Context context){
		myContext=context;
		
	}
	
	 public void onSurfaceCreated(GL10 unused, EGLConfig config) {
		    
	        // Set the background frame color
	        GLES20.glClearColor(0f, 0f, 0f, 1.0f);
	        
	        // Enable texture mapping
			GLES20.glEnable(GLES20.GL_TEXTURE_2D);
	        
	        // initialize the triangle vertex array
	        initShapes();	        

	        myProgram=new Program(myContext, R.raw.default_vertex_shader, R.raw.default_fragment_shader);	        		
	        
	        myModel.setTexture(Textures.loadTexture(myContext, R.drawable.bumpy_bricks_public_domain));
	        
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
        setMode((Models.COLOURS|Models.TEXTURE));

    
    }    
    
    
}
