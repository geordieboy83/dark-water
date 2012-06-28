package android.opengl.tutorial;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.view.MotionEvent;

class HelloOpenGLES20SurfaceView extends GLSurfaceView {

	   private final float TOUCH_SCALE_FACTOR = 180.0f / 320;
	    private HelloOpenGLES20Renderer mRenderer;
	    private float mPreviousX;
	    private float mPreviousY;
	
	 public void setRenderMode(int mode){
		 mRenderer.setRenderMode(mode);
		 requestRender();
	 }
	 
	 public void setModelMode(int mode){
		 mRenderer.setModelMode(mode);
		 requestRender();
	 }
	    
	    
	 public HelloOpenGLES20SurfaceView(Context context){
	        super(context);
	        // Create an OpenGL ES 2.0 context.
	        setEGLContextClientVersion(2);
	            
	        // set the mRenderer member
	        mRenderer = new HelloOpenGLES20Renderer(context);
	        setRenderer(mRenderer);
	        
	        // Render the view only when there is a change
	        setRenderMode(GLSurfaceView.RENDERMODE_WHEN_DIRTY);
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
	                requestRender();
	        }

	        mPreviousX = x;
	        mPreviousY = y;
	        return true;
	    } 
	 
	 public void switchRenderMode(int mode){
		 
	 }
 
}