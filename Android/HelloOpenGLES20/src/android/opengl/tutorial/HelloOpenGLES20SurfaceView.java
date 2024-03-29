package android.opengl.tutorial;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.view.MotionEvent;

class HelloOpenGLES20SurfaceView extends GLSurfaceView {

	   private final float TOUCH_SCALE_FACTOR = 180.0f / 320;
	    protected HelloOpenGLES20Renderer mRenderer;
	    private float mPreviousX;
	    private float mPreviousY;
	 
	    public static final int AXIS_X=0;
	    public static final int AXIS_Y=1;
	    public static final int AXIS_Z=2;
	    
	    
	    
	    public void setRotationAxis(int axis){
	    	if(axis<AXIS_X||axis>AXIS_Z) return;
	    	mRenderer.mAxis=axis;
	    	mRenderer.mAngle=0;
	    	((HelloOpenGLES20)getContext()).txt_angle.setText("Angle: "+String.format("%.2f",mRenderer.mAngle%360));
	    	requestRender();
	    }
	    
	    
	 public void setMode(int mode){
		 mRenderer.setMode(mode);
		 requestRender();
	 }
	    
	 public int getMode() { return mRenderer.getMode(); }
	    
	 public HelloOpenGLES20SurfaceView(Context context){
	        super(context);
	        // Create an OpenGL ES 2.0 context.
	        setEGLContextClientVersion(2);
	            
	        // set the mRenderer member
	        mRenderer = new HelloOpenGLES20Renderer(context);
	        setRenderer(mRenderer);
	        
	        // Render the view only when there is a change
//	        setRenderMode(GLSurfaceView.RENDERMODE_WHEN_DIRTY);
	        setRenderMode(GLSurfaceView.RENDERMODE_CONTINUOUSLY);
	    }
	 
	 @Override 
	    public boolean onTouchEvent(MotionEvent e) {
	        // MotionEvent reports input details from the touch screen
	        // and other input controls. In this case, you are only
	        // interested in events where the touch position changed.

	        float x = e.getX();
	        float y = e.getY();
	        
	        switch (e.getAction()) {
	            case MotionEvent.ACTION_MOVE:
	    
	                float dx = x - mPreviousX;
	                float dy = y - mPreviousY;
	    
	                // reverse direction of rotation above the mid-line
	                if (y > getHeight() / 2) {
	                  dx = dx * -1 ;
	                }
	    
	                // reverse direction of rotation to left of the mid-line
	                if (x < getWidth() / 2) {
	                  dy = dy * -1 ;
	                }
	              
//	                mRenderer.mAngle += (dx + dy) * TOUCH_SCALE_FACTOR;
	                mRenderer.mAngle -= (dx + dy) * TOUCH_SCALE_FACTOR;
	                ((HelloOpenGLES20)getContext()).txt_angle.setText("Angle: "+String.format("%.2f",mRenderer.mAngle%360));
	                requestRender();
	        }

	        mPreviousX = x;
	        mPreviousY = y;
	        return true;
	    } 
	 
	 public void switchRenderMode(int mode){
		 
	 }


	public void onDestroy() {
		if(mRenderer!=null) mRenderer.destroy();
		
	}
 
}