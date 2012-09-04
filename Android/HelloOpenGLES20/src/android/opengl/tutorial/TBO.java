package android.opengl.tutorial;

import java.nio.FloatBuffer;

import android.opengl.GLES20;

public class TBO extends BufferObject {

	
	protected int myTexture;
	protected String mySampler2D;
	protected int myTextureUnit;
	
	public int getTextureUnit() { return myTextureUnit; }
	public void setTextureUnit(int TextureUnit) { if(TextureUnit<0) return; myTextureUnit=TextureUnit;} 
	
	
	public TBO(float[] data) {
		super(data,Shaders.ATTR_TEX, Model.TEXTURE_COORDINATES_PER_VERTEX);
		myTexture=-1;
		mySampler2D=Shaders.UNI_TEX;
		// TODO Auto-generated constructor stub
	}
	
	
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
	
	public void setTexture(int textureid) { myTexture=textureid; }

	@Override public void draw(Program shaders){		
		if(myTexture<=0) return;
		Textures.useTexture(myTextureUnit, myTexture, shaders, mySampler2D);
		super.draw(shaders);
		
	}

}
