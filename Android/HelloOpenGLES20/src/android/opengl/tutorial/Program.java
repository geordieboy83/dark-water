package android.opengl.tutorial;

import java.util.HashMap;
import java.util.HashSet;

import org.apache.commons.lang3.ArrayUtils;

import android.content.Context;
import android.opengl.GLES20;

public class Program {

	protected int myHandle;
	
//	protected HashMap<String,Integer> myAttributes=new HashMap<String,Integer>();
//	protected HashMap<String,Integer> myUniforms=new HashMap<String,Integer>();
	
//	protected HashSet<String> myAttributes=new HashSet<String>();
//	protected HashSet<String> myUniforms=new HashSet<String>();
	
	protected String myPosition="";
	protected String myColour="";
	protected String myTexture="";
	protected String myNormal="";
	protected String myModelView="";
	protected String myTexture2D="";
	protected String myColourUse="";
	protected String myTextureUse="";
	protected String myNormalUse="";
	protected String myLight="";
	protected String myTime="";
	
	public int getProgram() { return myHandle; }
	
	
//	public int getAttribute(String id){ return myAttributes.get(id)==null?0:myAttributes.get(id); }
//	public int addAttribute(String id){ 
//		myAttributes.put(id,GLES20.glGetAttribLocation(myHandle, id));
//		return getAttribute(id);
//	}
	
//	public int getUniform(String id){ return myUniforms.get(id)==null?0:myUniforms.get(id); }
//	public int addUniform(String id){ 
//		myUniforms.put(id,GLES20.glGetUniformLocation(myHandle, id));
//		return getUniform(id);
//	}
	
	public int getUniform(String id){ return GLES20.glGetUniformLocation(myHandle, id); }
	public int getAttribute(String id){ return GLES20.glGetAttribLocation(myHandle, id); }
	
	public int getPosition() { return getAttribute(myPosition); }
	public int getColour() { return getAttribute(myColour); }
	public int getTexture() { return getAttribute(myTexture); }
	public int getNormal() { return getAttribute(myNormal); }
	
	public int getModelView() { return getUniform(myModelView); }
	public int getTexture2D() { return getUniform(myTexture2D); }
	public int getColourUse() { return getUniform(myColourUse); }
	public int getTextureUse() { return getUniform(myTextureUse); }
	public int getNormalUse() { return getUniform(myNormalUse); }
	public int getTime() { return getUniform(myTime); }
	
	public Program(String vertexShaderCode, String fragmentShaderCode, String[] attributes, String[] uniforms){
		
		try{
			myPosition=attributes[0];
			myColour=attributes[1];
			myTexture=attributes[2];
			myNormal=attributes[3];
		}catch(Throwable t){}
		
		try{
			myModelView=uniforms[0];
			myLight=uniforms[1];
			myColourUse=uniforms[2];
			myTextureUse=uniforms[3];
			myNormalUse=uniforms[4];
			myTexture2D=uniforms[5];
			myTime=uniforms[6];
		}catch(Throwable t){}		
		
		myHandle=Shaders.makeProgram(vertexShaderCode, fragmentShaderCode, attributes);
		
//		for(String s: attributes) addAttribute(s);
//		for(String s: uniforms) addUniform(s);
		
	}
	
	public Program(String[] vertexShaderCode, String fragmentShaderCode[], String[] attributes, String[] uniforms){
		
		this(Shaders.fromArray(vertexShaderCode), Shaders.fromArray(fragmentShaderCode), attributes, uniforms);
	}
	
	public Program(Context context, int vertexShaderCode, int fragmentShaderCode, String[] attributes, String[] uniforms){
		
		this(Shaders.fromResource(context, vertexShaderCode), Shaders.fromResource(context, fragmentShaderCode),
				attributes, uniforms);
		
	}
	
	public Program(String vertexShaderCode, String fragmentShaderCode){
		this(vertexShaderCode, fragmentShaderCode,
				Shaders.makeAttributes(Shaders.ATTR_POS, Shaders.ATTR_COL, Shaders.ATTR_TEX,Shaders.ATTR_NOR),
        		Shaders.makeUniforms(Shaders.UNI_MVP, Shaders.UNI_LIT, Shaders.UNI_USE_COL, Shaders.UNI_USE_TEX,
        				Shaders.UNI_USE_NOR, Shaders.UNI_TEX, Shaders.UNI_TIME));
	}
	
	public Program(String[] vertexShaderCode, String[] fragmentShaderCode){
		this(Shaders.fromArray(vertexShaderCode),Shaders.fromArray(fragmentShaderCode));
	}
	
	public Program(Context context, int vShader, int fShader){
		this(Shaders.fromResource(context, vShader), Shaders.fromResource(context, fShader));
	}
	
	
	public void use() { 
		if(Shaders.currentShader!=this) {
			Shaders.currentShader=this;
			GLES20.glUseProgram(myHandle); 
		}
//		else { System.out.println("Shader already in use"); }
	}

	
	
	
}
