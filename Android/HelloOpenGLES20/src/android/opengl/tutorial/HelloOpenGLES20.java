package android.opengl.tutorial;

import android.app.Activity;
import android.content.Context;
import android.graphics.Typeface;
import android.opengl.GLSurfaceView;
import android.os.Build;
import android.os.Bundle;
import android.view.MotionEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.FrameLayout;
import android.widget.RelativeLayout;

public class HelloOpenGLES20 extends Activity {
  
    private HelloOpenGLES20SurfaceView mGLView;
    protected String myFontAsset="fonts/tt1141m.ttf";
  
    protected Typeface myFont;
    
    protected FrameLayout myContent;
    
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        
        // Create a GLSurfaceView instance and set it
        // as the ContentView for this Activity
        
        this.setTheme(android.R.style.Theme_Light_NoTitleBar_Fullscreen);
		
        myFont=Typeface.createFromAsset(getAssets(), myFontAsset);
        
        myContent=new FrameLayout(this);
        
        mGLView = new HelloOpenGLES20SurfaceView(this);
        myContent.addView(mGLView);        
        myContent.addView(makeTestButtons());
        setContentView(myContent);
    }
    
    protected View makeTestButtons(){
    	RelativeLayout l=(RelativeLayout) this.getLayoutInflater().inflate(R.layout.test_buttons, null);
    	
    	Button none=(Button) l.findViewById(R.id.btn_none);
    	none.setTypeface(myFont);
    	none.setOnClickListener(new OnClickListener(){
			public void onClick(View v) {
				mGLView.setMode((mGLView.getMode()&Models.WIREFRAME)|Models.NONE);
			}});    	
    	
    	Button colours_only=(Button) l.findViewById(R.id.btn_colours_only);
    	colours_only.setTypeface(myFont);
    	colours_only.setOnClickListener(new OnClickListener(){
			public void onClick(View v) {
				mGLView.setMode((byte) ((mGLView.getMode()&Models.WIREFRAME)|Models.COLOURS));
			}});
    	
    	Button texture_only=(Button) l.findViewById(R.id.btn_texture_only);
    	texture_only.setTypeface(myFont);
    	texture_only.setOnClickListener(new OnClickListener(){
			public void onClick(View v) {
				mGLView.setMode((byte) ((mGLView.getMode()&Models.WIREFRAME)|Models.TEXTURE));
			}});
    	
    	Button texture_and_colours=(Button) l.findViewById(R.id.btn_colours_and_texture);
    	texture_and_colours.setTypeface(myFont);
    	texture_and_colours.setOnClickListener(new OnClickListener(){
			public void onClick(View v) {				
				mGLView.setMode((byte) ((mGLView.getMode()&Models.WIREFRAME)|Models.COLOURS|Models.TEXTURE));
			}});
    	
    	Button wireframe=(Button) l.findViewById(R.id.btn_wireframe);
    	wireframe.setTypeface(myFont);
    	wireframe.setOnClickListener(new OnClickListener(){
			public void onClick(View v) {				
				mGLView.setMode((byte) (mGLView.getMode()|Models.WIREFRAME));
			}});
    	
    	Button filled=(Button) l.findViewById(R.id.btn_filled);
    	filled.setTypeface(myFont);
    	filled.setOnClickListener(new OnClickListener(){
			public void onClick(View v) {
				int oldMode=mGLView.getMode();
				int newMode=Models.NONE;
				newMode=(newMode|(oldMode&Models.COLOURS)|(oldMode&Models.TEXTURE)|(oldMode&Models.NORMALS));
				
				mGLView.setMode(newMode);
			}});    	
    	
    	
    	return l;
    }
    
    
    @Override
    protected void onPause() {
        super.onPause();
        // The following call pauses the rendering thread.
        // If your OpenGL application is memory intensive,
        // you should consider de-allocating objects that
        // consume significant memory here.
        mGLView.onPause();
    }
    
    @Override
    protected void onResume() {
        super.onResume();
        // The following call resumes a paused rendering thread.
        // If you de-allocated graphic objects for onPause()
        // this is a good place to re-allocate them.
        mGLView.onResume();
    }
}
  
