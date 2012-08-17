package android.opengl.tutorial;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;

import org.apache.commons.io.IOUtils;

import android.content.Context;

public class OBJ {
	
	protected float[] myVertices, myNormals, myTextures, myMaterial;

		
	protected long load(int obj, Context context, ArrayList<Float> v, ArrayList<Float> vn, ArrayList<Float> vt, ArrayList<int[]> f){
		long now=System.currentTimeMillis();
		
		if(v==null||vn==null||vt==null||f==null) return 0;
		
		v.clear(); vn.clear(); vt.clear(); f.clear();
		
		final InputStream inputStream = context.getResources().openRawResource(obj);
		final InputStreamReader inputStreamReader = new InputStreamReader(inputStream);
		final BufferedReader bufferedReader = new BufferedReader(inputStreamReader);
		
		String nextLine;
		
		try
		{
			while ((nextLine = bufferedReader.readLine()) != null)
			{
				if(nextLine.isEmpty()||nextLine.startsWith("#")) continue;
				
				if(nextLine.startsWith("vn")){
					readFloatData(nextLine,vn);
				}
				else if(nextLine.startsWith("vt")){
					readFloatData(nextLine,vt);
				}
				else if(nextLine.startsWith("v")){
					readFloatData(nextLine,v);
				}
				else if(nextLine.startsWith("f")){
					readIntegerData(nextLine,f);
				}
			}
			bufferedReader.close();
		}
		catch (Throwable t)
		{
			
		}
		return System.currentTimeMillis()-now;
	}	
	
	protected void readFloatData(String line, ArrayList<Float> list){
		String substrings[]=line.split(" ");
		for(int i=substrings.length-3; i<substrings.length; i++){
			try{
				list.add(Float.valueOf(substrings[i]));
			}catch(Throwable t){
				list.add(0f);
			}
		}
	}
	
	protected void readIntegerData(String line, ArrayList<int[]> list){
		String substrings[]=line.split(" ");
		int vertex[]= new int[3];
		for(int i=substrings.length-3; i<substrings.length; i++){
			String vertexindices[]=substrings[i].split("/");
			
			for(int j=vertexindices.length-3; j<vertexindices.length; j++){
				if(vertexindices[j].isEmpty()) vertex[j]=-1;
				else vertex[j]=Integer.valueOf(vertexindices[j]);							
			}
		}
		list.add(vertex);
	}
	
	
	protected void make(ArrayList<Float> v, ArrayList<Float> vt, ArrayList<Float> vn, ArrayList<int[]> f){
		
	}
	
	public OBJ(int objresource, Context context){
		ArrayList<Float> vertices=new ArrayList<Float>(), normals=new ArrayList<Float>(), textures=new ArrayList<Float>();
		ArrayList<int[]> faces=new ArrayList<int[]>();
	
		long loadtime=load(objresource, context, vertices, normals, textures, faces);
		
		System.out.println("Model: "+vertices.size()/3+" v, "+normals.size()/3+" vn, "+ textures.size()/3+" vt, "+ faces.size()+" f, "+loadtime+" ms.");

	}

}
