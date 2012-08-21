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
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.AdapterView.OnItemSelectedListener;
import android.widget.Button;
import android.widget.CompoundButton;
import android.widget.CompoundButton.OnCheckedChangeListener;
import android.widget.FrameLayout;
import android.widget.RelativeLayout;
import android.widget.Spinner;
import android.widget.TextView;
import android.widget.Toast;
import android.widget.ToggleButton;

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
        
        /*long now=System.currentTimeMillis();
        
        System.out.println(
     			"On Begin Model: "+
     			"Maximum Memory: "+ (int) (Runtime.getRuntime().maxMemory()/(1024*1024))+" MB, "+
				"Allocated Memory: "+ (int) (Runtime.getRuntime().totalMemory()/(1024*1024))+" MB, "+
				"Used Memory: "+ (int) ((Runtime.getRuntime().totalMemory()-Runtime.getRuntime().freeMemory())/(1024*1024))+" MB");
        
        OBJ test= new OBJ(R.raw.model_just_grid,this);
        
        System.out.println(
     			"On End Model: "+
     			"Maximum Memory: "+ (int) (Runtime.getRuntime().maxMemory()/(1024*1024))+" MB, "+
				"Allocated Memory: "+ (int) (Runtime.getRuntime().totalMemory()/(1024*1024))+" MB, "+
				"Used Memory: "+ (int) ((Runtime.getRuntime().totalMemory()-Runtime.getRuntime().freeMemory())/(1024*1024))+" MB. "+
				"Loading took "+(System.currentTimeMillis()-now)+" ms.");*/
        
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
    	
    	ToggleButton wireframe=(ToggleButton) l.findViewById(R.id.btn_wireframe);
    	wireframe.setTypeface(myFont);
    	wireframe.setChecked(true);
    	wireframe.setOnCheckedChangeListener(new OnCheckedChangeListener(){

			public void onCheckedChanged(CompoundButton buttonView,
					boolean isChecked) {
				if(isChecked){
					int oldMode=mGLView.getMode();
					int newMode=Models.NONE;
					newMode=(newMode|(oldMode&Models.COLOURS)|(oldMode&Models.TEXTURE)|(oldMode&Models.NORMALS));
					
					mGLView.setMode(newMode);
				}
				else{
					mGLView.setMode((byte) (mGLView.getMode()|Models.WIREFRAME));
				}
				
			}});
    	
    	Spinner axis=(Spinner) l.findViewById(R.id.spn_rotation);
    	axis.setOnItemSelectedListener(new OnItemSelectedListener(){
			

			public void onItemSelected(AdapterView<?> arg0, View arg1,
					int arg2, long arg3) {
				//Toast.makeText(mGLView.getContext(), arg2+" clicked", Toast.LENGTH_SHORT).show();
				mGLView.setRotationAxis(arg2);
				
			}

			public void onNothingSelected(AdapterView<?> arg0) {
				// TODO Auto-generated method stub
				
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
    
    @Override protected void onDestroy(){
    	super.onDestroy();
    	mGLView.onDestroy();
    }
    
}
  
