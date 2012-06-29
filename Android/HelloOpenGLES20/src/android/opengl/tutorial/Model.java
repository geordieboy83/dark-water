package android.opengl.tutorial;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;
import java.nio.ShortBuffer;

import android.opengl.GLES20;

public class Model {
	
	protected static final int VERTICES_PER_FACE=3;
	protected static final int COORDINATES_PER_VERTEX=3;
	protected static final int COLOUR_COMPONENTS_PER_VERTEX=4;
	protected static final int TEXTURE_COORDINATES_PER_VERTEX=2;
	protected static final int COORDINATES_PER_NORMAL=3;
	protected static final int BYTES_PER_FLOAT=4;
	
	protected static final int POS_VERTEX=1;
	protected static final int POS_COLOUR=2;
	protected static final int POS_TEXTURE=3;
	protected static final int POS_NORMALS=4;
	protected static final int BYTES_PER_SHORT = 2;
	
	

	protected FloatBuffer myVertices=null;
	protected ShortBuffer myIndices=null;
	
	protected boolean hasColours=false;
	protected boolean hasTextures=false;
	protected boolean hasNormals=false;
	
	protected boolean usesColours=false;
	protected boolean usesTextures=false;
	protected boolean usesNormals=false;
	
	protected boolean isFilled=true;
	
	protected int myTexture=0;
	
	
	public Model(){}
	
	public Model(float xyz[], float rgba[], float st[], float vn[], short idx[]){
		make(xyz,rgba,st,vn,idx);		
	}
	
	public Model(float xyz[], float rgba[], float st[], float vn[], short ixyz[], short irgba[], short ist[], short ivn[]){
		make(xyz,rgba,st,vn,ixyz, irgba, ist, ivn);		
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
		
		// initialize vertex Buffer for triangle  
        ByteBuffer vbb = ByteBuffer.allocateDirect(
                // (# of coordinate values * 4 bytes per float)
                data.length * BYTES_PER_FLOAT); 
        vbb.order(ByteOrder.nativeOrder());// use the device hardware's native byte order
        myVertices = vbb.asFloatBuffer();  // create a floating point buffer from the ByteBuffer
        myVertices.put(data);    // add the coordinates to the FloatBuffer
        myVertices.position(0);            // set the buffer to read the first coordinate
        
        if(ixyz!=null&&ixyz.length>=3){
        	ByteBuffer ibb = ByteBuffer.allocateDirect(
                    // (# of coordinate values * 4 bytes per float)
                    ixyz.length * BYTES_PER_FLOAT); 
            ibb.order(ByteOrder.nativeOrder());// use the device hardware's native byte order
            myIndices = ibb.asShortBuffer();  // create a short buffer from the ByteBuffer
            myIndices.put(ixyz);    // add the coordinates to the ShortBuffer
            myIndices.position(0);        	
        }
        
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
        ByteBuffer vbb = ByteBuffer.allocateDirect(
                // (# of coordinate values * 4 bytes per float)
                data.length * BYTES_PER_FLOAT); 
        vbb.order(ByteOrder.nativeOrder());// use the device hardware's native byte order
        myVertices = vbb.asFloatBuffer();  // create a floating point buffer from the ByteBuffer
        myVertices.put(data);    // add the coordinates to the FloatBuffer
        myVertices.position(0);            // set the buffer to read the first coordinate
        
        if(idx!=null&&idx.length>=3){
        	ByteBuffer ibb = ByteBuffer.allocateDirect(
                    // (# of coordinate values * 4 bytes per float)
                    idx.length * BYTES_PER_FLOAT); 
            ibb.order(ByteOrder.nativeOrder());// use the device hardware's native byte order
            myIndices = ibb.asShortBuffer();  // create a floating point buffer from the ByteBuffer
            myIndices.put(idx);    // add the coordinates to the FloatBuffer
            myIndices.position(0);        	
        }
        
	}
	
	
	public void draw(float[] ModelView, Program shaders){
		
		shaders.use();
		
		// Pass in the position information
		myVertices.position(0);
        GLES20.glVertexAttribPointer(shaders.getPosition(), COORDINATES_PER_VERTEX, GLES20.GL_FLOAT, false,
        		stride()*BYTES_PER_FLOAT, myVertices);        
                
        GLES20.glEnableVertexAttribArray(shaders.getPosition());        
        
        if(hasColours){
        	// Pass in the color information
        	
        	GLES20.glUniform1i(shaders.getColourUse(), usesColours?Shaders.YES:0);
        	
        	myVertices.position(position(POS_COLOUR));
        	GLES20.glVertexAttribPointer(shaders.getColour(), COLOUR_COMPONENTS_PER_VERTEX, GLES20.GL_FLOAT, false,
        			stride()*BYTES_PER_FLOAT, myVertices);        
        
        	GLES20.glEnableVertexAttribArray(shaders.getColour());
        
        }
        
        if(hasTextures&&myTexture>0){
        	
        	Textures.useTexture(0, myTexture, shaders);
        	
        	// Pass in the texture coordinate information        	
        	GLES20.glUniform1i(shaders.getTextureUse(), usesTextures?Shaders.YES:0);        	
        	
            myVertices.position(position(POS_TEXTURE));
            GLES20.glVertexAttribPointer(shaders.getTexture(), COORDINATES_PER_VERTEX, GLES20.GL_FLOAT, false, 
            		stride()*BYTES_PER_FLOAT, myVertices);
            
            GLES20.glEnableVertexAttribArray(shaders.getTexture());
           
        }        
        
        if(hasNormals){
        	
        }        


        GLES20.glUniformMatrix4fv(shaders.getModelView(), 1, false, ModelView, 0);
        
        if(myIndices==null){        
        	if(!isFilled) for(int i = 0; i < myVertices.capacity()/stride(); i += 3)  GLES20.glDrawArrays(GLES20.GL_LINE_LOOP, i, 3);
        	else GLES20.glDrawArrays(GLES20.GL_TRIANGLES, 0, myVertices.capacity()/stride());
        }
        else{
        	if(!isFilled) for(int i = 0; i < myIndices.capacity(); i += 3){ 
        		myIndices.position(i);
        		GLES20.glDrawElements(GLES20.GL_LINE_LOOP, 3,GLES20.GL_UNSIGNED_SHORT, myIndices);
        	}
        	else
        		GLES20.glDrawElements(GLES20.GL_TRIANGLES, myIndices.capacity(),GLES20.GL_UNSIGNED_SHORT, myIndices);
        }
        
        GLES20.glBindTexture(GLES20.GL_TEXTURE_2D, 0);

	}
	
		
	public void usesColours(boolean uses) { usesColours=hasColours&&uses; }
	public boolean usesColours() { return usesColours; }
	
	public void usesTextures(boolean uses) { usesTextures=hasTextures&&uses; }
	public boolean usesTextures() { return usesTextures; }

	public void usesNormals(boolean uses) { usesNormals=hasNormals&&uses; }
	public boolean usesNormals() { return usesNormals; }

	
	
	public final FloatBuffer getBuffer() { return myVertices; }
	
}
