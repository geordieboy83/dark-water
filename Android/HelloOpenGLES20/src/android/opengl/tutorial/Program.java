package android.opengl.tutorial;

import java.util.HashMap;

import org.apache.commons.lang3.ArrayUtils;

import android.content.Context;
import android.opengl.GLES20;

public class Program {

	protected int myHandle;
	
	protected HashMap<String,Integer> myAttributes=new HashMap<String,Integer>();
	protected HashMap<String,Integer> myUniforms=new HashMap<String,Integer>();
	
	protected String myPosition="";
	protected String myColour="";
	protected String myTexture="";
	protected String myNormal="";
	protected String myModelView="";
	protected String myTexture2D="";
	protected String myColourUse="";
	protected String myTextureUse="";
	protected String myNormalUse="";
	
	public int getProgram() { return myHandle; }
	
	public int getAttribute(String id){ return myAttributes.get(id)==null?0:myAttributes.get(id); }
	public int addAttribute(String id){ 
		myAttributes.put(id,GLES20.glGetAttribLocation(myHandle, id));
		return getAttribute(id);
	}
	
	public int getUniform(String id){ return myUniforms.get(id)==null?0:myUniforms.get(id); }
	public int addUniform(String id){ 
		myUniforms.put(id,GLES20.glGetUniformLocation(myHandle, id));
		return getUniform(id);
	}
	
	public int getPosition() { return getAttribute(myPosition); }
	public int getColour() { return getAttribute(myColour); }
	public int getTexture() { return getAttribute(myTexture); }
	public int getNormal() { return getAttribute(myNormal); }
	
	public int getModelView() { return getUniform(myModelView); }
	public int getTexture2D() { return getUniform(myTexture2D); }
	public int getColourUse() { return getUniform(myColourUse); }
	public int getTextureUse() { return getUniform(myTextureUse); }
	public int getNormalUse() { return getUniform(myNormalUse); }
	
	public Program(String vertexShaderCode, String fragmentShaderCode, String[] attributes, String[] uniforms){
		
		try{
			myPosition=attributes[0];
			myColour=attributes[1];
			myTexture=attributes[2];
			myNormal=attributes[3];
		}catch(Throwable t){}
		
		try{
			myModelView=uniforms[0];
			myTexture2D=uniforms[1];
			myColourUse=uniforms[2];
			myTextureUse=uniforms[3];
			myNormalUse=uniforms[4];
		}catch(Throwable t){}		
		
		myHandle=Shaders.makeProgram(vertexShaderCode, fragmentShaderCode, attributes);
		
		for(String s: attributes) addAttribute(s);
		for(String s: uniforms) addUniform(s);
		
	}
	
	public Program(String[] vertexShaderCode, String fragmentShaderCode[], String[] attributes, String[] uniforms){
		
		this(Shaders.fromArray(vertexShaderCode), Shaders.fromArray(fragmentShaderCode), attributes, uniforms);
	}
	
	public Program(Context context, int vertexShaderCode, int fragmentShaderCode, String[] attributes, String[] uniforms){
		
		this(Shaders.fromArray(context, vertexShaderCode), Shaders.fromArray(context, fragmentShaderCode),
				attributes, uniforms);
		
	}
	
	
	public void use() { 
		if(Shaders.currentShader!=this) {
			Shaders.currentShader=this;
			GLES20.glUseProgram(myHandle); 
		}
//		else { System.out.println("Shader already in use"); }
	}
	
	public static String[] makeAttributes(String position, String colour, String texture, String normal, String ...other){		
		String[] basics= new String[]{position, colour, texture,normal};
		if(other==null||other.length==0) return basics;
		else return ArrayUtils.addAll(basics, other);
	}
	
	public static String[] makeUniforms(String ModelView, String Texture2D,
			String usesColours, String usesTextures, String usesNormals, String ...other){		
		String[] basics= new String[]{ModelView,Texture2D, usesColours, usesTextures, usesNormals};
		if(other==null||other.length==0) return basics;
		else return ArrayUtils.addAll(basics, other);
	}
	
}
