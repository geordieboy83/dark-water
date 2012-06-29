package android.opengl.tutorial;

public class Vertex {
	
	public float[] myData;
	
	public Vertex(float xyz[], float rgba[], float st[], float vn[], short ixyz, short irgba, short ist, short ivn){
		try{
			myData=new float[Model.COORDINATES_PER_VERTEX+
			                 (rgba!=null?Model.COLOUR_COMPONENTS_PER_VERTEX:0)+
			                 (st!=null?Model.TEXTURE_COORDINATES_PER_VERTEX:0)+
			                 (vn!=null?Model.COORDINATES_PER_NORMAL:0)];
			
			try{ for(int i=0; i<Model.COORDINATES_PER_VERTEX;i++)
				myData[i]=xyz[ixyz+i]; }catch(Throwable t){}
			try{ for(int i=0; i<Model.COLOUR_COMPONENTS_PER_VERTEX;i++)
				myData[Model.COORDINATES_PER_VERTEX+i]=rgba[irgba+i]; }catch(Throwable t){}
			try{ for(int i=0; i<Model.TEXTURE_COORDINATES_PER_VERTEX;i++)
				myData[Model.COORDINATES_PER_VERTEX+
				       (rgba!=null?Model.COLOUR_COMPONENTS_PER_VERTEX:0)+i]=st[ist+i]; }catch(Throwable t){}
			try{ for(int i=0; i<Model.COORDINATES_PER_NORMAL;i++)
				myData[Model.COORDINATES_PER_VERTEX+
		                 (rgba!=null?Model.COLOUR_COMPONENTS_PER_VERTEX:0)+
		                 (st!=null?Model.TEXTURE_COORDINATES_PER_VERTEX:0)+i]=vn[ivn+i]; }catch(Throwable t){}			
		}catch(Throwable t){}	
		
	}
	
}
