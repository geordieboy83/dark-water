package android.opengl.tutorial;

import android.app.Activity;
import android.graphics.Color;
import android.graphics.Typeface;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemSelectedListener;
import android.widget.Button;
import android.widget.CompoundButton;
import android.widget.CompoundButton.OnCheckedChangeListener;
import android.widget.FrameLayout;
import android.widget.RelativeLayout;
import android.widget.SeekBar;
import android.widget.SeekBar.OnSeekBarChangeListener;
import android.widget.Spinner;
import android.widget.TextView;
import android.widget.ToggleButton;

public class HelloOpenGLES20 extends Activity {
  
    private HelloOpenGLES20SurfaceView mGLView;
    protected String myFontAsset="fonts/tt1141m.ttf";
  
    protected Typeface myFont;
    
    protected FrameLayout myContent;
    
    protected ToggleButton btn_lights, btn_colours, btn_textures, btn_wireframe;
    protected Button btn_none, btn_all;
    protected TextView txt_light, txt_camera, txt_ortho, txt_angle;
    protected SeekBar bar_hi, bar_lo;
    protected Spinner ortho_plane;
    
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
        
        OBJ test= new OBJ(R.raw.model_missile,this);
//        OBJ test= new OBJ(R.raw.model_just_grid,this);
        
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
    	
    	btn_none=(Button) l.findViewById(R.id.btn_none);
    	btn_none.setTypeface(myFont);
    	btn_none.setOnClickListener(new OnClickListener(){
			public void onClick(View v) {
				btn_colours.setChecked(false);
				btn_textures.setChecked(false);
				btn_lights.setChecked(false);
//				int oldMode=mGLView.getMode();
//				mGLView.setMode((mGLView.getMode()&Models.WIREFRAME)|Models.NONE);
			}});    	
    	
    	btn_colours=(ToggleButton) l.findViewById(R.id.btn_colours_only);
    	btn_colours.setTypeface(myFont);
    	btn_colours.setOnCheckedChangeListener(new OnCheckedChangeListener() {

			public void onCheckedChanged(CompoundButton buttonView,
					boolean isChecked) {
				
				int oldMode=mGLView.getMode();
				int newMode=Models.NONE;
				newMode=(newMode|(oldMode&Models.WIREFRAME)|(isChecked?Models.COLOURS:Models.NONE)|(oldMode&Models.TEXTURE)|(oldMode&Models.NORMALS));
				mGLView.setMode(newMode);
				
				
				
//				mGLView.setMode(mGLView.getMode()|
//						(btn_lights.isChecked()?Models.NORMALS:Models.NONE)|
//						(btn_textures.isChecked()?Models.TEXTURE:Models.NONE)|
//						(isChecked?Models.COLOURS:Models.NONE));
				
			}});
    	
    	btn_textures=(ToggleButton) l.findViewById(R.id.btn_texture_only);
    	btn_textures.setTypeface(myFont);
    	btn_textures.setOnCheckedChangeListener(new OnCheckedChangeListener() {

			public void onCheckedChanged(CompoundButton buttonView,
					boolean isChecked) {
				
				int oldMode=mGLView.getMode();
				int newMode=Models.NONE;
				newMode=(newMode|(oldMode&Models.WIREFRAME)|(oldMode&Models.COLOURS)|(isChecked?Models.TEXTURE:Models.NONE)|(oldMode&Models.NORMALS));
				mGLView.setMode(newMode);
				
//				mGLView.setMode(mGLView.getMode()|
//						(btn_lights.isChecked()?Models.NORMALS:Models.NONE)|
//						(isChecked?Models.TEXTURE:Models.NONE)|
//						(btn_colours.isChecked()?Models.COLOURS:Models.NONE));
				
			}});
    	
    	btn_all=(Button) l.findViewById(R.id.btn_all);
    	btn_all.setTypeface(myFont);
    	btn_all.setOnClickListener(new OnClickListener(){
			public void onClick(View v) {
				
				btn_colours.setChecked(true);
				btn_textures.setChecked(true);
				btn_lights.setChecked(true);
//				btn_wireframe.setChecked(true);
				
//				int oldMode=mGLView.getMode();
//				mGLView.setMode((byte) ((mGLView.getMode()&Models.WIREFRAME)|Models.COLOURS|Models.TEXTURE|Models.NORMALS));
			}});
    	
    	btn_wireframe=(ToggleButton) l.findViewById(R.id.btn_wireframe);
    	btn_wireframe.setTypeface(myFont);
    	btn_wireframe.setChecked(true);
    	btn_wireframe.setOnCheckedChangeListener(new OnCheckedChangeListener(){

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
    	
    	btn_lights=(ToggleButton) l.findViewById(R.id.btn_normals);
    	btn_lights.setTypeface(myFont);
    	btn_lights.setChecked(true);
    	btn_lights.setOnCheckedChangeListener(new OnCheckedChangeListener(){

			public void onCheckedChanged(CompoundButton buttonView,
					boolean isChecked) {
				
				int oldMode=mGLView.getMode();
				int newMode=Models.NONE;
				newMode=(newMode|(oldMode&Models.WIREFRAME)|(oldMode&Models.COLOURS)|(oldMode&Models.TEXTURE)|(isChecked?Models.NORMALS:Models.NONE));
				mGLView.setMode(newMode);
				
				
//				mGLView.setMode(mGLView.getMode()|
//						(isChecked?Models.NORMALS:Models.NONE)|
//						(btn_textures.isChecked()?Models.TEXTURE:Models.NONE)|
//						(btn_colours.isChecked()?Models.COLOURS:Models.NONE));				
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
    	
    	txt_camera=(TextView) l.findViewById(R.id.txt_camera);
    	txt_camera.setTypeface(myFont);
    	txt_camera.setTextColor(Color.WHITE);
    	
    	txt_light=(TextView) l.findViewById(R.id.txt_light);
    	txt_light.setTypeface(myFont);
    	txt_light.setTextColor(Color.WHITE);
    	
    	txt_ortho=(TextView) l.findViewById(R.id.txt_ortho);
    	txt_ortho.setTypeface(myFont);
    	txt_ortho.setTextColor(Color.WHITE);
    	txt_ortho.setVisibility(View.GONE);
    	
    	txt_angle=(TextView) l.findViewById(R.id.txt_angle);
    	txt_angle.setTypeface(myFont);
    	txt_angle.setTextColor(Color.WHITE);
    	
    	Button plusx=(Button) l.findViewById(R.id.btn_plus_x);
    	plusx.setTypeface(myFont);
    	plusx.setOnClickListener(new OnClickListener(){
			public void onClick(View v) {
				mGLView.mRenderer.myLight[0]+=HelloOpenGLES20Renderer.MV_LIGHT;
				
				txt_light.setText("Light: "+
						String.format("%.2f",mGLView.mRenderer.myLight[0])+"x, "+
						String.format("%.2f",mGLView.mRenderer.myLight[1])+"y, "+
						String.format("%.2f",mGLView.mRenderer.myLight[2])+"z.");
				
				System.out.println("Light: "+mGLView.mRenderer.myLight[0]+"x, "+mGLView.mRenderer.myLight[1]+"y, "+mGLView.mRenderer.myLight[2]+"z.");
				
			}});
    	
    	Button minusx=(Button) l.findViewById(R.id.btn_minus_x);
    	minusx.setTypeface(myFont);
    	minusx.setOnClickListener(new OnClickListener(){
			public void onClick(View v) {
				mGLView.mRenderer.myLight[0]-=HelloOpenGLES20Renderer.MV_LIGHT;
				txt_light.setText("Light: "+
						String.format("%.2f",mGLView.mRenderer.myLight[0])+"x, "+
						String.format("%.2f",mGLView.mRenderer.myLight[1])+"y, "+
						String.format("%.2f",mGLView.mRenderer.myLight[2])+"z.");
				System.out.println("Light: "+mGLView.mRenderer.myLight[0]+"x, "+mGLView.mRenderer.myLight[1]+"y, "+mGLView.mRenderer.myLight[2]+"z.");
			}});
    	
    	Button plusy=(Button) l.findViewById(R.id.btn_plus_y);
    	plusy.setTypeface(myFont);
    	plusy.setOnClickListener(new OnClickListener(){
			public void onClick(View v) {
				mGLView.mRenderer.myLight[1]+=HelloOpenGLES20Renderer.MV_LIGHT;
				txt_light.setText("Light: "+
						String.format("%.2f",mGLView.mRenderer.myLight[0])+"x, "+
						String.format("%.2f",mGLView.mRenderer.myLight[1])+"y, "+
						String.format("%.2f",mGLView.mRenderer.myLight[2])+"z.");
				System.out.println("Light: "+mGLView.mRenderer.myLight[0]+"x, "+mGLView.mRenderer.myLight[1]+"y, "+mGLView.mRenderer.myLight[2]+"z.");
			}});
    	
    	Button minusy=(Button) l.findViewById(R.id.btn_minus_y);
    	minusy.setTypeface(myFont);
    	minusy.setOnClickListener(new OnClickListener(){
			public void onClick(View v) {
				mGLView.mRenderer.myLight[1]-=HelloOpenGLES20Renderer.MV_LIGHT;
				txt_light.setText("Light: "+
						String.format("%.2f",mGLView.mRenderer.myLight[0])+"x, "+
						String.format("%.2f",mGLView.mRenderer.myLight[1])+"y, "+
						String.format("%.2f",mGLView.mRenderer.myLight[2])+"z.");
				System.out.println("Light: "+mGLView.mRenderer.myLight[0]+"x, "+mGLView.mRenderer.myLight[1]+"y, "+mGLView.mRenderer.myLight[2]+"z.");
			}});
    	
    	Button plusz=(Button) l.findViewById(R.id.btn_plus_z);
    	plusz.setTypeface(myFont);
    	plusz.setOnClickListener(new OnClickListener(){
			public void onClick(View v) {
				mGLView.mRenderer.myLight[2]+=HelloOpenGLES20Renderer.MV_LIGHT;
				txt_light.setText("Light: "+
						String.format("%.2f",mGLView.mRenderer.myLight[0])+"x, "+
						String.format("%.2f",mGLView.mRenderer.myLight[1])+"y, "+
						String.format("%.2f",mGLView.mRenderer.myLight[2])+"z.");
				System.out.println("Light: "+mGLView.mRenderer.myLight[0]+"x, "+mGLView.mRenderer.myLight[1]+"y, "+mGLView.mRenderer.myLight[2]+"z.");
			}});
    	
    	Button minusz=(Button) l.findViewById(R.id.btn_minus_z);
    	minusz.setTypeface(myFont);
    	minusz.setOnClickListener(new OnClickListener(){
			public void onClick(View v) {				
				mGLView.mRenderer.myLight[2]-=HelloOpenGLES20Renderer.MV_LIGHT;
				txt_light.setText("Light: "+
						String.format("%.2f",mGLView.mRenderer.myLight[0])+"x, "+
						String.format("%.2f",mGLView.mRenderer.myLight[1])+"y, "+
						String.format("%.2f",mGLView.mRenderer.myLight[2])+"z.");
				System.out.println("Light: "+mGLView.mRenderer.myLight[0]+"x, "+mGLView.mRenderer.myLight[1]+"y, "+mGLView.mRenderer.myLight[2]+"z.");
			}});
    	
    	
    	Button plusxc=(Button) l.findViewById(R.id.btn_plus_x_c);
    	plusxc.setTypeface(myFont);
    	plusxc.setOnClickListener(new OnClickListener(){
			public void onClick(View v) {
				mGLView.mRenderer.myEye[0]+=HelloOpenGLES20Renderer.MV_CAMERA;
				
				txt_camera.setText("Camera: "+
						String.format("%.2f",mGLView.mRenderer.myEye[0])+"x, "+
						String.format("%.2f",mGLView.mRenderer.myEye[1])+"y, "+
						String.format("%.2f",mGLView.mRenderer.myEye[2])+"z.");
				
				System.out.println("Camera: "+mGLView.mRenderer.myEye[0]+"x, "+mGLView.mRenderer.myEye[1]+"y, "+mGLView.mRenderer.myEye[2]+"z.");
				
			}});
    	
    	Button minusxc=(Button) l.findViewById(R.id.btn_minus_x_c);
    	minusxc.setTypeface(myFont);
    	minusxc.setOnClickListener(new OnClickListener(){
			public void onClick(View v) {
				mGLView.mRenderer.myEye[0]-=HelloOpenGLES20Renderer.MV_CAMERA;
				txt_camera.setText("Camera: "+
						String.format("%.2f",mGLView.mRenderer.myEye[0])+"x, "+
						String.format("%.2f",mGLView.mRenderer.myEye[1])+"y, "+
						String.format("%.2f",mGLView.mRenderer.myEye[2])+"z.");
				
				System.out.println("Camera: "+mGLView.mRenderer.myEye[0]+"x, "+mGLView.mRenderer.myEye[1]+"y, "+mGLView.mRenderer.myEye[2]+"z.");
			}});
    	
    	Button plusyc=(Button) l.findViewById(R.id.btn_plus_y_c);
    	plusyc.setTypeface(myFont);
    	plusyc.setOnClickListener(new OnClickListener(){
			public void onClick(View v) {
				mGLView.mRenderer.myEye[1]+=HelloOpenGLES20Renderer.MV_CAMERA;
				txt_camera.setText("Camera: "+
						String.format("%.2f",mGLView.mRenderer.myEye[0])+"x, "+
						String.format("%.2f",mGLView.mRenderer.myEye[1])+"y, "+
						String.format("%.2f",mGLView.mRenderer.myEye[2])+"z.");
				
				System.out.println("Camera: "+mGLView.mRenderer.myEye[0]+"x, "+mGLView.mRenderer.myEye[1]+"y, "+mGLView.mRenderer.myEye[2]+"z.");
			}});
    	
    	Button minusyc=(Button) l.findViewById(R.id.btn_minus_y_c);
    	minusyc.setTypeface(myFont);
    	minusyc.setOnClickListener(new OnClickListener(){
			public void onClick(View v) {
				mGLView.mRenderer.myEye[1]-=HelloOpenGLES20Renderer.MV_CAMERA;
				txt_camera.setText("Camera: "+
						String.format("%.2f",mGLView.mRenderer.myEye[0])+"x, "+
						String.format("%.2f",mGLView.mRenderer.myEye[1])+"y, "+
						String.format("%.2f",mGLView.mRenderer.myEye[2])+"z.");
				
				System.out.println("Camera: "+mGLView.mRenderer.myEye[0]+"x, "+mGLView.mRenderer.myEye[1]+"y, "+mGLView.mRenderer.myEye[2]+"z.");
			}});
    	
    	Button pluszc=(Button) l.findViewById(R.id.btn_plus_z_c);
    	pluszc.setTypeface(myFont);
    	pluszc.setOnClickListener(new OnClickListener(){
			public void onClick(View v) {
				mGLView.mRenderer.myEye[2]+=HelloOpenGLES20Renderer.MV_CAMERA;
				txt_camera.setText("Camera: "+
						String.format("%.2f",mGLView.mRenderer.myEye[0])+"x, "+
						String.format("%.2f",mGLView.mRenderer.myEye[1])+"y, "+
						String.format("%.2f",mGLView.mRenderer.myEye[2])+"z.");
				
				System.out.println("Camera: "+mGLView.mRenderer.myEye[0]+"x, "+mGLView.mRenderer.myEye[1]+"y, "+mGLView.mRenderer.myEye[2]+"z.");
			}});
    	
    	Button minuszc=(Button) l.findViewById(R.id.btn_minus_z_c);
    	minuszc.setTypeface(myFont);
    	minuszc.setOnClickListener(new OnClickListener(){
			public void onClick(View v) {
				mGLView.mRenderer.myEye[2]-=HelloOpenGLES20Renderer.MV_CAMERA;
				txt_camera.setText("Camera: "+
						String.format("%.2f",mGLView.mRenderer.myEye[0])+"x, "+
						String.format("%.2f",mGLView.mRenderer.myEye[1])+"y, "+
						String.format("%.2f",mGLView.mRenderer.myEye[2])+"z.");
				
				System.out.println("Camera: "+mGLView.mRenderer.myEye[0]+"x, "+mGLView.mRenderer.myEye[1]+"y, "+mGLView.mRenderer.myEye[2]+"z.");
			}});
    	
    	
    	
    	Spinner ortho=(Spinner) l.findViewById(R.id.spn_ortho);
    	ortho.setOnItemSelectedListener(new OnItemSelectedListener(){
			

			public void onItemSelected(AdapterView<?> arg0, View arg1,
					int arg2, long arg3) {
				//Toast.makeText(mGLView.getContext(), arg2+" clicked", Toast.LENGTH_SHORT).show();
				txt_ortho.setVisibility(View.VISIBLE);
				bar_hi.setVisibility(View.VISIBLE);
				bar_lo.setVisibility(View.VISIBLE);
				mGLView.mRenderer.mOrthoPlane=arg2;
				bar_hi.setMax(mGLView.mRenderer.myOrthoLimits[2*arg2+1]);
				bar_hi.setProgress((int) mGLView.mRenderer.myOrtho[2*arg2+1]);				
				bar_lo.setMax(mGLView.mRenderer.myOrthoLimits[2*arg2]);
				bar_lo.setProgress(bar_lo.getMax()+(int) mGLView.mRenderer.myOrtho[2*arg2]);
				
			}

			public void onNothingSelected(AdapterView<?> arg0) {
				// TODO Auto-generated method stub
				
			}});
    	
    	
    	bar_lo=(SeekBar) l.findViewById(R.id.bar_plane_low);
    	bar_lo.setOnSeekBarChangeListener(new OnSeekBarChangeListener(){

			public void onProgressChanged(SeekBar seekBar, int progress,
					boolean fromUser) {
				if(progress==0) return;
				mGLView.mRenderer.myOrtho[2*mGLView.mRenderer.mOrthoPlane]=Math.min(progress-bar_lo.getMax(),-1);
				
				txt_ortho.setText("Orthographic Projection: "+
						String.format("%.2f",mGLView.mRenderer.myOrtho[0]*mGLView.mRenderer.ratio)+" to "+
						String.format("%.2f",mGLView.mRenderer.myOrtho[1]*mGLView.mRenderer.ratio)+"x, "+
						String.format("%.2f",mGLView.mRenderer.myOrtho[2])+" to "+
						String.format("%.2f",mGLView.mRenderer.myOrtho[3])+"y, "+
						String.format("%.2f",mGLView.mRenderer.myOrtho[4])+" to "+
						String.format("%.2f",mGLView.mRenderer.myOrtho[5])+"z.");
				
						
			}

			public void onStartTrackingTouch(SeekBar seekBar) {
				// TODO Auto-generated method stub
				
			}

			public void onStopTrackingTouch(SeekBar seekBar) {
				// TODO Auto-generated method stub
				
			}});
    	bar_lo.setVisibility(View.GONE);
    	
    
    	bar_hi=(SeekBar) l.findViewById(R.id.bar_plane_high);
    	bar_hi.setOnSeekBarChangeListener(new OnSeekBarChangeListener(){

		public void onProgressChanged(SeekBar seekBar, int progress,
				boolean fromUser) {
			mGLView.mRenderer.myOrtho[2*mGLView.mRenderer.mOrthoPlane+1]=Math.max(progress,1);
			
			txt_ortho.setText("Orthographic Projection: "+
					String.format("%.2f",mGLView.mRenderer.myOrtho[0]*mGLView.mRenderer.ratio)+" to "+
					String.format("%.2f",mGLView.mRenderer.myOrtho[1]*mGLView.mRenderer.ratio)+"x, "+
					String.format("%.2f",mGLView.mRenderer.myOrtho[2])+" to "+
					String.format("%.2f",mGLView.mRenderer.myOrtho[3])+"y, "+
					String.format("%.2f",mGLView.mRenderer.myOrtho[4])+" to "+
					String.format("%.2f",mGLView.mRenderer.myOrtho[5])+"z.");
			
		}

		public void onStartTrackingTouch(SeekBar seekBar) {
			// TODO Auto-generated method stub
			
		}

		public void onStopTrackingTouch(SeekBar seekBar) {
			// TODO Auto-generated method stub
			
		}});
    	bar_hi.setVisibility(View.GONE);
	
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
        btn_all.performClick();
        txt_light.setText("Light: "+
				String.format("%.2f",mGLView.mRenderer.myLight[0])+"x, "+
				String.format("%.2f",mGLView.mRenderer.myLight[1])+"y, "+
				String.format("%.2f",mGLView.mRenderer.myLight[2])+"z.");
		txt_camera.setText("Camera: "+
				String.format("%.2f",mGLView.mRenderer.myEye[0])+"x, "+
				String.format("%.2f",mGLView.mRenderer.myEye[1])+"y, "+
				String.format("%.2f",mGLView.mRenderer.myEye[2])+"z.");
		txt_ortho.setText("Orthographic Projection: "+
				String.format("%.2f",mGLView.mRenderer.myOrtho[0]*mGLView.mRenderer.ratio)+" to "+
				String.format("%.2f",mGLView.mRenderer.myOrtho[1]*mGLView.mRenderer.ratio)+"x, "+
				String.format("%.2f",mGLView.mRenderer.myOrtho[2])+" to "+
				String.format("%.2f",mGLView.mRenderer.myOrtho[3])+"y, "+
				String.format("%.2f",mGLView.mRenderer.myOrtho[4])+" to "+
				String.format("%.2f",mGLView.mRenderer.myOrtho[5])+"z.");
		txt_angle.setText("Angle: "+String.format("%.2f",mGLView.mRenderer.mAngle%360));
		
		
    }
    
    @Override protected void onDestroy(){
    	super.onDestroy();
    	mGLView.onDestroy();
    }
    
}
  
