package android.opengl.tutorial;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.content.Context;
import android.opengl.GLES20;
import android.opengl.GLSurfaceView;
import android.opengl.Matrix;
import android.os.SystemClock;

public class HelloOpenGLES20Renderer implements GLSurfaceView.Renderer {

	public static final float MV_LIGHT=0.1f;
	 
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
	protected float[] myLight = {0.0f,0.0f,0.0f};
	    
	 
	public float mAngle;
	public int mAxis=HelloOpenGLES20SurfaceView.AXIS_X;
	

	public Model myModel, myModel1, myModel2;
	 
	protected Context myContext;
	
	
	public void setMode(int mode) { myModel.setMode(mode); myModel1.setMode(mode); myModel2.setMode(mode); }

	public int getMode() { return myModel.getMode(); }	
	  
	public HelloOpenGLES20Renderer(Context context){
		myContext=context;
		
	}
	
	 public void onSurfaceCreated(GL10 unused, EGLConfig config) {
		    
	        // Set the background frame color
	        GLES20.glClearColor(0f, 0f, 0f, 1.0f);
//		 	GLES20.glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	        
	        // Enable texture mapping
//			GLES20.glEnable(GLES20.GL_TEXTURE_2D);
			
			myProgram=new Program(myContext, R.raw.default_vertex_shader, R.raw.default_fragment_shader);	 
			
	        // initialize the triangle vertex array
	        initShapes2();	        

	               		
	        

	        
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
//        		Matrix.setRotateM(mMMatrix, 0, mAngle, 1, 0, 0);
        		myModel.rotate(mAngle, 1, 0, 0);
        		myModel1.rotate(mAngle, 1, 0, 0);
        		myModel2.rotate(mAngle, 1, 0, 0);
        		break;
        	case HelloOpenGLES20SurfaceView.AXIS_Y:
//        		Matrix.setRotateM(mMMatrix, 0, mAngle, 0, 1, 0);
        		myModel.rotate(mAngle, 0, 1, 0);
        		myModel1.rotate(mAngle, 0, 1, 0);
        		myModel2.rotate(mAngle, 0, 1, 0);
        		break;
        	case HelloOpenGLES20SurfaceView.AXIS_Z:
//        		Matrix.setRotateM(mMMatrix, 0, mAngle, 0, 0, 1);
        		myModel.rotate(mAngle, 0, 0, 1);
        		myModel1.rotate(mAngle, 0, 0, 1);
        		myModel2.rotate(mAngle, 0, 0, 1);
        		break;
        	default:
        		break;
        }

//        Matrix.multiplyMM(mMVPMatrix, 0, mVMatrix, 0, mMMatrix, 0);
//        Matrix.multiplyMM(mMVPMatrix, 0, mProjMatrix, 0, mMVPMatrix, 0);
        
        Matrix.multiplyMM(mMVPMatrix, 0, mProjMatrix, 0, mVMatrix, 0);
       
        myModel.setLight(myLight);        
        myModel1.setLight(myLight);
        myModel2.setLight(myLight);
       
        myModel.draw(mMVPMatrix, myProgram);
        myModel1.draw(mMVPMatrix, myProgram);
        myModel2.draw(mMVPMatrix, myProgram);
        
    }
    
    public void onSurfaceChanged(GL10 unused, int width, int height) {
        GLES20.glViewport(0, 0, width, height);
        
        float ratio = (float) width / height;
        
        // this projection matrix is applied to object coodinates
        // in the onDrawFrame() method
//        Matrix.frustumM(mProjMatrix, 0, -ratio, ratio, -1, 1, 3, 7);
//        Matrix.frustumM(mProjMatrix, 0, -ratio, ratio, -1, 1, 1, 70);
        Matrix.orthoM(mProjMatrix, 0, -ratio, ratio, -1, 1, 1, 70);
        Matrix.setLookAtM(mVMatrix, 0, 0, 0, 30, 0f, 0f, 0f, 0f, 1.0f, 0.0f);
    }  
  
    

    private void initShapes2(){
        
    	short indices0[] = {
    			0,1,2,
    			2,3,0,};
    	short indices1[]={
    			1,0,2,};
    	short indices2[]={
    			0,1,2
    	};
    	
    	
        float coords0[] = {
            // X, Y, Z
        		-0.5f, -0.25f, 0,
                0.5f, -0.25f, 0,
                0.5f,  0.559016994f, 0,
                -0.5f,  0.559016994f, 0,};
        float coords1[]={
             
             -0.5f, -0.5f, 0,
             -0.75f, -0.5f, 0,
             -0.55f,  0.559016994f, 0,};
             
        float coords2[]={
             0.5f, -0.5f, 0,
             0.75f, -0.5f, 0,
             0.55f,  0.559016994f, 0
             
             
        }; 
        
        float normals0[]={
        	0,0,1,
        	0,0,1,
        	0,0,1,
        	0,0,1,
        };
        
        float normals1[]={
            	0,0,1,
            	0,0,1,
            	0,0,1,
            };
        
        float normals2[]={
            	0,0,1,
            	0,0,1,
            	0,0,1,
            };
        
        
   
        float colours0[]= {
				// R, G, B, A
	            1.0f, 0.0f, 0.0f, 1.0f,
	            0.0f, 0.0f, 1.0f, 1.0f,
	            0.0f, 1.0f, 0.0f, 1.0f,
	            0.7f, 0.3f, 0.7f, 1.0f,};
        float colours1[]={		
				// R, G, B, A
	            1.0f, 1.0f, 0.0f, 1.0f,
	            0.0f, 1.0f, 1.0f, 1.0f,
	            1.0f, 0.0f, 1.0f, 1.0f,};
        float colours2[]={
		
	            // R, G, B, A
	            1.0f, 1.0f, 1.0f, 1.0f,
	            0.5f, 0.5f, 0.5f, 1.0f,
	            0.0f, 0.0f, 0.0f, 1.0f};        
        

        
        float tex0[]={
        		0,2,
        		2,2,
        		2,0,
        		0,0,};
        float tex1[]={
        		
        		1,1,
        		0,1,
        		0.5f,0,};
        		
        float tex2[]={
        		0,1,
        		1,1,
        		0.5f,0,
        };
        
        myModel=new Model();
        myModel.addTypedBufferObject(new VBO(coords0));
        myModel.addTypedBufferObject(new CBO(colours0));        
        myModel.addTypedBufferObject(
        		new TBO(tex0,
        				Shaders.ATTR_TEX, Model.TEXTURE_COORDINATES_PER_VERTEX,
        				Textures.loadTexture(myContext, R.drawable.radiance)));
        myModel.addBufferObject(new BufferObject(normals0, Shaders.ATTR_NOR, Model.COORDINATES_PER_NORMAL), Model.DATA_NORMALS);
        myModel.addTypedBufferObject(new IBO(indices0));        
        myModel.setMode(Models.COLOURS|Models.TEXTURE|Models.NORMALS);
        
        myModel1=new Model();
        myModel1.addTypedBufferObject(new VBO(coords1));
        myModel1.addTypedBufferObject(new CBO(colours1));
        myModel1.addBufferObject(new BufferObject(normals1, Shaders.ATTR_NOR, Model.COORDINATES_PER_NORMAL), Model.DATA_NORMALS);
        myModel1.addTypedBufferObject(
        		new TBO(tex1,
        				Shaders.ATTR_TEX, Model.TEXTURE_COORDINATES_PER_VERTEX,
        				Textures.loadTexture(myContext, R.drawable.bumpy_bricks_public_domain)));
        myModel1.addTypedBufferObject(new IBO(indices1));
        myModel1.setMode(Models.COLOURS|Models.TEXTURE|Models.NORMALS);
        
        
        myModel2=new Model();
        myModel2.addTypedBufferObject(new VBO(coords2));
        myModel2.addTypedBufferObject(new CBO(colours2));
        myModel2.addBufferObject(new BufferObject(normals2, Shaders.ATTR_NOR, Model.COORDINATES_PER_NORMAL), Model.DATA_NORMALS);
//        myModel2.addTypedBufferObject(new CBO(coords2.length/Model.COORDINATES_PER_VERTEX,0f,0f,1f,0.5f));
        myModel2.addTypedBufferObject(
        		new TBO(tex2,
        				Shaders.ATTR_TEX, Model.TEXTURE_COORDINATES_PER_VERTEX,
        				Textures.loadTexture(myContext, R.drawable.bumpy_bricks_public_domain)));
        myModel2.addTypedBufferObject(new IBO(indices2));
        myModel2.setMode(Models.COLOURS|Models.TEXTURE|Models.NORMALS);

    
    }    
    
   
	public void destroy() {
		if(myModel!=null) myModel.destroy();
		if(myModel1!=null) myModel1.destroy();
		if(myModel2!=null) myModel2.destroy();
		Textures.destroy();
		Shaders.destroy();
		
	}    
    
    
}
