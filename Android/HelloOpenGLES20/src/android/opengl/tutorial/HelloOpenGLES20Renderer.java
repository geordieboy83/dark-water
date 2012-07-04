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
	public int mAxis=HelloOpenGLES20SurfaceView.AXIS_X;
	
	public Model myModel;
	 
	protected Context myContext;
	
	
	public void setMode(int mode) { myModel.setMode(mode); }
	public int getMode() { return myModel.getMode(); }	
	  
	public HelloOpenGLES20Renderer(Context context){
		myContext=context;
		
	}
	
	 public void onSurfaceCreated(GL10 unused, EGLConfig config) {
		    
	        // Set the background frame color
//	        GLES20.glClearColor(0f, 0f, 0f, 1.0f);
		 	GLES20.glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	        
	        // Enable texture mapping
//			GLES20.glEnable(GLES20.GL_TEXTURE_2D);
			
			myProgram=new Program(myContext, R.raw.default_vertex_shader, R.raw.default_fragment_shader);	 
			
	        // initialize the triangle vertex array
	        initShapes();	        

	               		
	        

	        
	    }
    
    public void onDrawFrame(GL10 unused) {
    
        // Redraw background color
        GLES20.glClear(GLES20.GL_COLOR_BUFFER_BIT | GLES20.GL_DEPTH_BUFFER_BIT);
     
        
      
        // Create a rotation for the triangle (Boring! Comment this out:)
//         long time = SystemClock.uptimeMillis() % 4000L;
//         mAngle = 0.090f * ((int) time);
        

//         Use the mAngle member as the rotation value
//        Matrix.setRotateM(mMMatrix, 0, mAngle, 0, 0, 1.0f);
        
        switch(mAxis){
        	case HelloOpenGLES20SurfaceView.AXIS_X:
        		Matrix.setRotateM(mMMatrix, 0, mAngle, 1, 0, 0);
        		break;
        	case HelloOpenGLES20SurfaceView.AXIS_Y:
        		Matrix.setRotateM(mMMatrix, 0, mAngle, 0, 1, 0);
        		break;
        	case HelloOpenGLES20SurfaceView.AXIS_Z:
        		Matrix.setRotateM(mMMatrix, 0, mAngle, 0, 0, 1);
        		break;
        	default:
        		break;
        }

        Matrix.multiplyMM(mMVPMatrix, 0, mVMatrix, 0, mMMatrix, 0);
        Matrix.multiplyMM(mMVPMatrix, 0, mProjMatrix, 0, mMVPMatrix, 0);
        
        
        myModel.draw(mMVPMatrix, myProgram);
        
    }
    
    public void onSurfaceChanged(GL10 unused, int width, int height) {
        GLES20.glViewport(0, 0, width, height);
        
        float ratio = (float) width / height;
        
        // this projection matrix is applied to object coodinates
        // in the onDrawFrame() method
//        Matrix.frustumM(mProjMatrix, 0, -ratio, ratio, -1, 1, 3, 7);
//        Matrix.frustumM(mProjMatrix, 0, -ratio, ratio, -1, 1, 1, 70);
        Matrix.orthoM(mProjMatrix, 0, -ratio, ratio, -1, 1, 1, 70);
        Matrix.setLookAtM(mVMatrix, 0, 0, 0, 3, 0f, 0f, 0f, 0f, 1.0f, 0.0f);
    }  
  
    
    private void initShapes(){
        
    	short indices[] = {
    			0,1,2,
    			2,3,0,
    			4,5,6,
    			7,8,9
    	};
    	
    	
        float triangleCoords[] = {
            // X, Y, Z
//            -0.5f, -0.25f, 0,
//             0.5f, -0.25f, 0,
//             0.0f,  0.559016994f, 0,
        		-0.5f, -0.25f, 0,
                0.5f, -0.25f, 0,
                0.5f,  0.559016994f, 0,
                -0.5f,  0.559016994f, 0,
             
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
	            0.7f, 0.3f, 0.7f, 1.0f,
		
				// R, G, B, A
	            1.0f, 1.0f, 0.0f, 1.0f,
	            0.0f, 1.0f, 1.0f, 1.0f,
	            1.0f, 0.0f, 1.0f, 1.0f,
		
	            // R, G, B, A
	            1.0f, 1.0f, 1.0f, 1.0f,
	            0.5f, 0.5f, 0.5f, 1.0f,
	            0.0f, 0.0f, 0.0f, 1.0f};        
        

        
        float texCoords[]={
        		0,2,
        		2,2,
//        		0.5f,1,
        		2,0,
        		0,0,
        		
        		1,1,
        		0,1,
        		0.5f,0,
        		
        		0,1,
        		1,1,
        		0.5f,0,
        };
        
//        myModel=new Model(triangleCoords,colourCoords,texCoords,null,indices);
        myModel=new Model();
        myModel.make(triangleCoords, Model.DATA_VERTEX);
        myModel.make(colourCoords, Model.DATA_COLOUR);
        myModel.make(texCoords, Model.DATA_TEXTURE, Textures.loadTexture(myContext, R.drawable.bumpy_bricks_public_domain));
        myModel.make(indices);
        setMode((Models.COLOURS|Models.TEXTURE));
        myModel.setTexture(Textures.loadTexture(myContext, R.drawable.bumpy_bricks_public_domain));	       
//        myModel.setTexture(Textures.loadTexture(myContext, R.drawable.ihs_black));

    
    }    
    
    
}
