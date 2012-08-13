package android.opengl.tutorial;

import java.nio.FloatBuffer;

import android.opengl.GLES20;

public class TBO extends BufferObject {

	
	protected int myTexture;
	protected String mySampler2D;
	protected int myTextureUnit;
	
	public int getTextureUnit() { return myTextureUnit; }
	public void setTextureUnit(int TextureUnit) { if(TextureUnit<0) return; myTextureUnit=TextureUnit;} 
	
	public TBO(float[] data, String attribute, int elementspervertex, int textureid) {
		super(data,attribute, elementspervertex);
		myTexture=textureid;
		mySampler2D=Shaders.UNI_TEX;
		// TODO Auto-generated constructor stub
	}
	
	
	public TBO(float[] data, String attribute, int elementspervertex, int textureid, String Uniform) {
		this(data,attribute, elementspervertex, textureid);
		mySampler2D=Uniform;
		// TODO Auto-generated constructor stub
	}

	@Override public void draw(Program shaders){		
		
		Textures.useTexture(myTextureUnit, myTexture, shaders, mySampler2D);
		super.draw(shaders);
		
	}

}
