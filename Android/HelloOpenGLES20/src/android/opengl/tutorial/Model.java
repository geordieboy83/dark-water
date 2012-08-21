package android.opengl.tutorial;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;
import java.nio.ShortBuffer;
import java.util.ArrayList;
import java.util.HashMap;

import android.opengl.GLES20;

public class Model {
	
	public static final int VERTICES_PER_FACE=3;
	public static final int COORDINATES_PER_VERTEX=3;
	public static final int COLOUR_COMPONENTS_PER_VERTEX=4;
	public static final int TEXTURE_COORDINATES_PER_VERTEX=2;
	public static final int COORDINATES_PER_NORMAL=3;
	
	
	protected static final int POS_VERTEX=1;
	protected static final int POS_COLOUR=2;
	protected static final int POS_TEXTURE=3;
	protected static final int POS_NORMALS=4;
	
	
	protected static final int DATA_VERTEX=1;
	protected static final int DATA_COLOUR=2;
	protected static final int DATA_TEXTURE=3;
	protected static final int DATA_NORMALS=4;
	protected static final int DATA_INDICES=5;
	
	
//	protected int myVBO[]=new int[1];
//	protected int myIBO[]=new int[1];	
	protected ArrayList<TBO> myTBOs=new ArrayList<TBO>();
	protected VBO myVBO;
	protected IBO myIBO;
	protected BufferObject myCBO, myNBO;
	protected int myVertexCount, myIndexCount;

	protected FloatBuffer myVertices=null, myColours=null, myNormals=null;
	protected HashMap<Integer,FloatBuffer> myTextures=new HashMap<Integer,FloatBuffer>();
	protected ShortBuffer myIndices=null;
	
	protected boolean hasColours=false;
	protected boolean hasTextures=false;
	protected boolean hasNormals=false;
	
	protected boolean usesColours=false;
	protected boolean usesTextures=false;
	protected boolean usesNormals=false;
	
	protected boolean isFilled=true;
	
	protected int myTexture=0;
	
	protected boolean drawPacked=false;
	
	protected long now=0, start=0;	
	protected float myTime=0;
	
	public Model(){}
	
	public Model(float xyz[], float rgba[], float st[], float vn[], short idx[]){
		make(xyz,rgba,st,vn,idx);		
	}
	
	public Model(float xyz[], float rgba[], float st[], float vn[], short ixyz[], short irgba[], short ist[], short ivn[]){
		make(xyz,rgba,st,vn,ixyz, irgba, ist, ivn);		
	}
	
	
		
	public void addTypedBufferObject(BufferObject BO){
		
		if(BO==null)return;
		if(BO instanceof VBO) { myVBO=(VBO) BO; }
		else if(BO instanceof IBO) { myIBO=(IBO) BO; }
		else if(BO instanceof CBO) { myCBO=BO; hasColours=true; usesColours(true); }
		else if(BO instanceof TBO) {	
			hasTextures=true; 
			usesTextures(true);
			myTBOs.add((TBO) BO);
			myTBOs.get(myTBOs.size()-1).setTextureUnit(myTBOs.size()-1);
			return;
		}
		
		drawPacked=false;

		
	}
	
	
	
	public void addBufferObject(BufferObject BO, int type){
		
		if(BO==null)return;
		switch(type){
			case DATA_VERTEX:
				myVBO=(VBO) BO;
				break;
			case DATA_COLOUR:
				myCBO=BO;
				hasColours=true;
				usesColours(true);
				break;
			case DATA_TEXTURE:				
				hasTextures=true;
				usesTextures(true);
				myTBOs.add((TBO) BO);
				myTBOs.get(myTBOs.size()-1).setTextureUnit(myTBOs.size()-1);
				break;
			case DATA_NORMALS:
				myNBO=BO;
				hasNormals=true;
				usesNormals(true);
				break;
			case DATA_INDICES:
				myIBO=(IBO) BO;
				break;
			default:
				break;
		}
		drawPacked=false;

		
	}
	
	
	protected int position(int ofwhat){
		switch(ofwhat){
			case POS_COLOUR: return COORDINATES_PER_VERTEX;
			case POS_TEXTURE: 
				return COORDINATES_PER_VERTEX+
					(hasColours?COLOUR_COMPONENTS_PER_VERTEX:0);
			case POS_NORMALS: 
				return COORDINATES_PER_VERTEX+
						(hasColours?COLOUR_COMPONENTS_PER_VERTEX:0)+
						(hasTextures?TEXTURE_COORDINATES_PER_VERTEX:0);
			default: return 0;
		}
	}
	
	
	protected int stride() { 
		return COORDINATES_PER_VERTEX+
				(hasColours?COLOUR_COMPONENTS_PER_VERTEX:0)+
				(hasTextures?TEXTURE_COORDINATES_PER_VERTEX:0)+
				(hasNormals?COORDINATES_PER_NORMAL:0);
	}
	
	
	public void setTexture(int id){ myTexture=id; }
	
	public void setMode(int Mode){
		System.out.println("Mode "+ Integer.toBinaryString(Mode)+": "+
				((Mode&Models.WIREFRAME)==0?"Is filled, ":"Is not filled ,")+
				((Mode&Models.COLOURS)!=0?"Uses colours, ":"Does not use colours, ")+
				((Mode&Models.TEXTURE)!=0?"Uses textures, ":"Does not use textures, ")+
				((Mode&Models.NORMALS)!=0?"Uses normals":"Does not use normals"));
		
		
		
		if(Mode==0){
			isFilled=true;
			usesColours=false;
			usesTextures=false;
			usesNormals=false;
			return;
		}		
		isFilled=(Mode&Models.WIREFRAME)==0;
		usesColours((Mode&Models.COLOURS)!=0);
		usesTextures((Mode&Models.TEXTURE)!=0);
		usesNormals((Mode&Models.NORMALS)!=0);
	}
	
	public int getMode(){
		return ((usesColours?Models.COLOURS:0)|(usesTextures?Models.TEXTURE:0)|(usesNormals?Models.NORMALS:0)|(!isFilled?Models.WIREFRAME:0));
	}
	
	public void make(float data[], int...typeAndOthers){
		if(data==null||data.length==0||typeAndOthers==null||typeAndOthers.length==0)return;
		switch(typeAndOthers[0]){
			case DATA_VERTEX:
				myVertices=Models.fromArray(data);
				break;
			case DATA_COLOUR:
				myColours=Models.fromArray(data);
				hasColours=true;
				usesColours(true);
				break;
			case DATA_TEXTURE:
				if(typeAndOthers.length<2) return;
				hasTextures=true;
				myTextures.put(typeAndOthers[1], Models.fromArray(data));
				break;
			case DATA_NORMALS:
				myNormals=Models.fromArray(data);
				hasNormals=true;
				usesNormals(true);
				break;
			case DATA_INDICES:
				short indexdata[]=new short[data.length];
				for(int i=0;i<indexdata.length; i++) indexdata[i]=(short) data[i];
				myIndices=Models.fromArray(indexdata);
				break;
			default:
				break;
		}
		drawPacked=false;
	}
	
	
	
	public void make(short indices[]){
		if(indices==null||indices.length==0) return;
		myIndices=Models.fromArray(indices);
	}
	
	public void make(float xyz[], float rgba[], float st[], float vn[], short ixyz[], short irgba[], short ist[], short ivn[]){
		if(xyz==null||xyz.length==0) return;
		
		hasColours=(rgba!=null&&rgba.length>0); usesColours(true);
		hasTextures=(st!=null&&st.length>0); usesTextures(true);
		hasNormals=(vn!=null&&vn.length>0); usesNormals(true);
				
		int xyzs=xyz.length/COORDINATES_PER_VERTEX;
		
		float data[]=new float[xyzs*stride()];
		int j=0,k=0,l=0,m=0;
		for(int i=0; i<data.length;){
			
			for(int jj=0; jj<COORDINATES_PER_VERTEX; jj++) data[i++]=xyz[j+jj];  j+=COORDINATES_PER_VERTEX;
		
			if(hasColours) try{
				for(int kk=0; kk<COLOUR_COMPONENTS_PER_VERTEX; kk++) data[i++]=rgba[k+kk];	k+=COLOUR_COMPONENTS_PER_VERTEX;
			}catch(Throwable t){System.out.println(t);}
			
			if(hasTextures) try{
				for(int ll=0; ll<TEXTURE_COORDINATES_PER_VERTEX; ll++) data[i++]=st[l+ll]; l+=TEXTURE_COORDINATES_PER_VERTEX;
			}catch(Throwable t){System.out.println(t);}
			
			if(hasNormals) try{
				for(int mm=0; mm<COORDINATES_PER_NORMAL; mm++) data[i++]=st[m+mm]; m+=COORDINATES_PER_NORMAL;
			}catch(Throwable t){System.out.println(t);}
		}
		
		FloatBuffer Vertices=Models.fromArray(data);
        myVertexCount=Vertices.capacity();
        
        ShortBuffer Indices=null;
        if(ixyz!=null&&ixyz.length>=3){        	
        	Indices=Models.fromArray(ixyz);    	
            myIndexCount=Indices.capacity();
        }
        
        
            myVertices=Vertices;
            myIndices=Indices;
       
        
    	drawPacked=true;
        
        
	}
	
	
	
	
	
	
	
	public void make(float xyz[], float rgba[], float st[], float vn[], short idx[]){
		if(xyz==null||xyz.length==0) return;
		
		hasColours=(rgba!=null&&rgba.length>0); usesColours(true);
		hasTextures=(st!=null&&st.length>0); usesTextures(true);
		hasNormals=(vn!=null&&vn.length>0); usesNormals(true);
				
		int xyzs=xyz.length/COORDINATES_PER_VERTEX;
		
		float data[]=new float[xyzs*stride()];
		int j=0,k=0,l=0,m=0;
		for(int i=0; i<data.length;){
			
			for(int jj=0; jj<COORDINATES_PER_VERTEX; jj++) data[i++]=xyz[j+jj];  j+=COORDINATES_PER_VERTEX;
		
			if(hasColours) try{
				for(int kk=0; kk<COLOUR_COMPONENTS_PER_VERTEX; kk++) data[i++]=rgba[k+kk];	k+=COLOUR_COMPONENTS_PER_VERTEX;
			}catch(Throwable t){System.out.println(t);}
			
			if(hasTextures) try{
				for(int ll=0; ll<TEXTURE_COORDINATES_PER_VERTEX; ll++) data[i++]=st[l+ll]; l+=TEXTURE_COORDINATES_PER_VERTEX;
			}catch(Throwable t){System.out.println(t);}
			
			if(hasNormals) try{
				for(int mm=0; mm<COORDINATES_PER_NORMAL; mm++) data[i++]=st[m+mm]; m+=COORDINATES_PER_NORMAL;
			}catch(Throwable t){System.out.println(t);}
		}
		
		// initialize vertex Buffer for triangle
		FloatBuffer Vertices=Models.fromArray(data);
        myVertexCount=Vertices.capacity();
        
        ShortBuffer Indices=null;
        if(idx!=null&&idx.length>=3){
        	Indices=Models.fromArray(idx);        	
            myIndexCount=Indices.capacity();
        }    
        
            myVertices=Vertices;
            myIndices=Indices;
        
        drawPacked=true;
        
	}	
	
	protected float getTime(){		
		now=System.currentTimeMillis();
		if(start==0) start=now;
		
		float result=(now-start)/1000f;
		System.out.println("Time: "+result+" s");
		return result;
//		if(before==0) return 0f;
//		else return (now-before)/1000f;
	}
	
	public void draw(float[] ModelView, Program shaders){		
		
		myTime=getTime();
				
		if(myVBO!=null){
			drawSeparateGPU(ModelView, shaders);
		}
		else if(myVertices!=null){
			if(drawPacked) drawCPU(ModelView,shaders);
			else drawSeparateCPU(ModelView, shaders);
		}
		
	}
	
	protected void drawSeparateCPU(float[] ModelView, Program shaders){
		System.out.println("Draw Separate CPU");
		
		
		shaders.use();
		
		// Pass in the position information
		myVertices.position(0);
        GLES20.glVertexAttribPointer(shaders.getPosition(), COORDINATES_PER_VERTEX, GLES20.GL_FLOAT, false,
        		COORDINATES_PER_VERTEX*BufferObject.BYTES_PER_FLOAT, myVertices);        
                
        GLES20.glEnableVertexAttribArray(shaders.getPosition());        
        
        if(hasColours&&myColours!=null){
        	// Pass in the color information
        	
        	GLES20.glUniform1i(shaders.getColourUse(), usesColours?Shaders.YES:0);
        	
        	myColours.position(0);
        	GLES20.glVertexAttribPointer(shaders.getColour(), COLOUR_COMPONENTS_PER_VERTEX, GLES20.GL_FLOAT, false,
        			COLOUR_COMPONENTS_PER_VERTEX*BufferObject.BYTES_PER_FLOAT, myColours);        
        
        	GLES20.glEnableVertexAttribArray(shaders.getColour());
        
        }
        
        if(hasTextures&&!myTextures.isEmpty()){
        	
        	int i=0;
        	for(Integer texture:myTextures.keySet()){
        		Textures.useTexture(i++, texture, shaders);
        		// Pass in the texture coordinate information        	
            	GLES20.glUniform1i(shaders.getTextureUse(), usesTextures?Shaders.YES:0);        	
            	
                FloatBuffer texturecoords=myTextures.get(texture);
                texturecoords.position(0);
                GLES20.glVertexAttribPointer(shaders.getTexture(), TEXTURE_COORDINATES_PER_VERTEX, GLES20.GL_FLOAT, false, 
                		TEXTURE_COORDINATES_PER_VERTEX*BufferObject.BYTES_PER_FLOAT, texturecoords);
                
                GLES20.glEnableVertexAttribArray(shaders.getTexture());
        	}
        	
        	
        	
           
        }        
        
        if(hasNormals){
        	
        }        


        GLES20.glUniformMatrix4fv(shaders.getModelView(), 1, false, ModelView, 0);
        
        GLES20.glUniform1f(shaders.getTime(), myTime);
        
        if(myIndices==null){        
        	if(!isFilled) 
//        		for(int i = 0; i < myVertices.capacity(); i += 3)  GLES20.glDrawArrays(GLES20.GL_LINE_LOOP, i, 3);
//        		 GLES20.glDrawArrays(GLES20.GL_LINE_LOOP, 0, myVertices.capacity());
        		GLES20.glDrawArrays(GLES20.GL_LINE_STRIP, 0, myVertices.capacity());
        	else GLES20.glDrawArrays(GLES20.GL_TRIANGLES, 0, myVertices.capacity());
        }
        else{
        	
        	
        	if(!isFilled){
//        		for(int i = 0; i < myIndices.capacity(); i += 3){ 
//        			myIndices.position(i);
//        			GLES20.glDrawElements(GLES20.GL_LINE_LOOP, 3,GLES20.GL_UNSIGNED_SHORT, myIndices);
//        		}
            		myIndices.position(0);
//            		GLES20.glDrawElements(GLES20.GL_LINE_LOOP, myIndices.capacity(),GLES20.GL_UNSIGNED_SHORT, myIndices);
            		GLES20.glDrawElements(GLES20.GL_LINE_STRIP, myIndices.capacity(),GLES20.GL_UNSIGNED_SHORT, myIndices);
        	}
        	else{
        		myIndices.position(0);
        		GLES20.glDrawElements(GLES20.GL_TRIANGLES, myIndices.capacity(),GLES20.GL_UNSIGNED_SHORT, myIndices);
        	}
        }
        
        GLES20.glBindBuffer(GLES20.GL_ARRAY_BUFFER, 0);
        GLES20.glBindBuffer(GLES20.GL_ELEMENT_ARRAY_BUFFER, 0);
        GLES20.glBindTexture(GLES20.GL_TEXTURE_2D, 0);
	}
	
	protected void drawSeparateGPU(float[] ModelView, Program shaders){
		System.out.println("Draw Separate GPU");
		
		
		shaders.use();		     
        
		GLES20.glUniform1i(shaders.getColourUse(), usesColours?Shaders.YES:0);
        if(usesColours&&myCBO!=null){
        	// Pass in the color information
        	
        	        	
        	myCBO.draw(shaders);
        
        }
        
        GLES20.glUniform1i(shaders.getTextureUse(), usesTextures?Shaders.YES:0);
        if(usesTextures&&!myTBOs.isEmpty()){        	
        	        	
        	for(TBO tbo:myTBOs){
        		tbo.draw(shaders);
        	}       	
           
        }        
        
        if(usesNormals){
        	
        }        


        GLES20.glUniformMatrix4fv(shaders.getModelView(), 1, false, ModelView, 0);

        GLES20.glUniform1f(shaders.getTime(), myTime);
        
        myVBO.draw(shaders);
        
        
        if(myIBO==null){        
        	myVBO.render(isFilled);
        }
        else{
        	myIBO.render(isFilled);
        }
        
        GLES20.glBindBuffer(GLES20.GL_ARRAY_BUFFER, 0);
        GLES20.glBindBuffer(GLES20.GL_ELEMENT_ARRAY_BUFFER, 0);
        GLES20.glBindTexture(GLES20.GL_TEXTURE_2D, 0);	
		
	}	
	
	protected void drawCPU(float[] ModelView, Program shaders){
		
		System.out.println("Draw CPU");
		
		
		shaders.use();
		
		// Pass in the position information
		myVertices.position(0);
        GLES20.glVertexAttribPointer(shaders.getPosition(), COORDINATES_PER_VERTEX, GLES20.GL_FLOAT, false,
        		stride()*BufferObject.BYTES_PER_FLOAT, myVertices);        
                
        GLES20.glEnableVertexAttribArray(shaders.getPosition());        
        
        if(hasColours){
        	// Pass in the color information
        	
        	GLES20.glUniform1i(shaders.getColourUse(), usesColours?Shaders.YES:0);
        	
        	myVertices.position(position(POS_COLOUR));
        	GLES20.glVertexAttribPointer(shaders.getColour(), COLOUR_COMPONENTS_PER_VERTEX, GLES20.GL_FLOAT, false,
        			stride()*BufferObject.BYTES_PER_FLOAT, myVertices);        
        
        	GLES20.glEnableVertexAttribArray(shaders.getColour());
        
        }
        
        if(hasTextures&&myTexture>0){
        	
        	Textures.useTexture(0, myTexture, shaders);        	
        	
        	// Pass in the texture coordinate information        	
        	GLES20.glUniform1i(shaders.getTextureUse(), usesTextures?Shaders.YES:0);        	
        	
            myVertices.position(position(POS_TEXTURE));
            GLES20.glVertexAttribPointer(shaders.getTexture(), TEXTURE_COORDINATES_PER_VERTEX, GLES20.GL_FLOAT, false, 
            		stride()*BufferObject.BYTES_PER_FLOAT, myVertices);
            
            GLES20.glEnableVertexAttribArray(shaders.getTexture());
           
        }        
        
        if(hasNormals){
        	
        }        


        GLES20.glUniformMatrix4fv(shaders.getModelView(), 1, false, ModelView, 0);
        
        GLES20.glUniform1f(shaders.getTime(), myTime);
        
        if(myIndices==null){        
        	if(!isFilled)
//        		for(int i = 0; i < myVertices.capacity()/stride(); i += 3)  GLES20.glDrawArrays(GLES20.GL_LINE_LOOP, i, 3);
        		GLES20.glDrawArrays(GLES20.GL_LINE_STRIP, 0, myVertices.capacity()/stride());
        	else GLES20.glDrawArrays(GLES20.GL_TRIANGLES, 0, myVertices.capacity()/stride());
        }
        else{
        	
        	
        	if(!isFilled){ 
//        		for(int i = 0; i < myIndices.capacity(); i += 3){ 
//        			myIndices.position(i);
//        			GLES20.glDrawElements(GLES20.GL_LINE_LOOP, 3,GLES20.GL_UNSIGNED_SHORT, myIndices);
//        		}
        		myIndices.position(0);
//        		GLES20.glDrawElements(GLES20.GL_LINE_LOOP, myIndices.capacity(),GLES20.GL_UNSIGNED_SHORT, myIndices);
        		GLES20.glDrawElements(GLES20.GL_LINE_STRIP, myIndices.capacity(),GLES20.GL_UNSIGNED_SHORT, myIndices);
        	}
        	else{
        		myIndices.position(0);
        		GLES20.glDrawElements(GLES20.GL_TRIANGLES, myIndices.capacity(),GLES20.GL_UNSIGNED_SHORT, myIndices);
        	}
        }
        
        GLES20.glBindBuffer(GLES20.GL_ARRAY_BUFFER, 0);
        GLES20.glBindBuffer(GLES20.GL_ELEMENT_ARRAY_BUFFER, 0);
        GLES20.glBindTexture(GLES20.GL_TEXTURE_2D, 0);

	}
	
		
	public void usesColours(boolean uses) { usesColours=hasColours&&uses; }
	public boolean usesColours() { return usesColours; }
	
	public void usesTextures(boolean uses) { usesTextures=hasTextures&&uses; }
	public boolean usesTextures() { return usesTextures; }

	public void usesNormals(boolean uses) { usesNormals=hasNormals&&uses; }
	public boolean usesNormals() { return usesNormals; }

	
	
	public final FloatBuffer getBuffer() { return myVertices; }
	
	
	public void destroy(){
		if(myVBO!=null) myVBO.destroy();
		if(myCBO!=null) myCBO.destroy();
		if(myNBO!=null) myNBO.destroy();
		if(myIBO!=null) myIBO.destroy();
		for(TBO t: myTBOs) if(t!=null) t.destroy();
	}
	
}
