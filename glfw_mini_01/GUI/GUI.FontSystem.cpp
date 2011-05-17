#include "GUI.FontSystem.h"

FontSystem::FontSystem(string FontMap)
{
	load(FontMap);	
}

void FontSystem::reset()
{

	for(map<string,vector<FTFont*>>::iterator i=FontDB.begin(); i!=FontDB.end(); i++) 
		for(int j=0; j<i->second.size(); j++)
			i->second[j]->FaceSize(j+MIN_FONT_SIZE);
	

}


FontSystem::~FontSystem()
{
	for(map<string,vector<FTFont*>>::iterator i=FontDB.begin(); i!=FontDB.end(); i++) 
		for(int j=0; j<i->second.size(); j++)
			delete i->second[j];
}

bool FontSystem::load(string FontMap)
{
	string PATH = //PhysicsWorld::getPhysicsWorld()->projectDir + 
		"assets\\UI\\";
	
	// Test if file can be opened.
	fstream in(FontMap,ios::in);		
	if (in.fail()) {
		cout <<"Unable to open " << FontMap << "!" << endl;
		return false;
	}

	// Parse the font database file. If this fails, the process cannot continue.
	int IDs=0;
	string s;

	// Count and skim through data.
	do IDs++; while (in >> s);

	// If number of elements in file not divisible by 3
	if (--IDs % 3!=0) {	cout << endl << "Invalid file!" << endl;  in.close(); return false;	}

	// Multitude of identifiers
	IDs=IDs/3;

	string* types = new string[IDs];
	string* identifiers = new string[IDs];
	string* filenames = new string[IDs];
	
	// Reset the input file.
	in.clear();
	in.seekg(0, ios::beg);

	// Read data into memory.
	for(int i=0; i<IDs; i++){
		in >> types[i];
		in >> identifiers[i];
		in >> filenames[i];
	}

	in.close();

	for(int i=0; i<IDs; i++)
	{
		vector<FTFont*> v;
		v.clear();
		v.reserve(MAX_FONT_SIZE-MIN_FONT_SIZE+1U);
	
		for(int j=0;j<=MAX_FONT_SIZE-MIN_FONT_SIZE;j++){
	
			if(types[i]=="TEXTURE"){
				v.push_back(new FTTextureFont((PATH+filenames[i]).c_str()));
				v.back()->FaceSize(j+MIN_FONT_SIZE);
			} else
				if(types[i]=="POLYGON"){
				v.push_back(new FTPolygonFont((PATH+filenames[i]).c_str()));
				v.back()->FaceSize(j+MIN_FONT_SIZE);
			} else
				if(types[i]=="EXTRUDE"){
				v.push_back(new FTExtrudeFont((PATH+filenames[i]).c_str()));
				v.back()->FaceSize(j+MIN_FONT_SIZE);
			} else
				if(types[i]=="BITMAP"){
				v.push_back(new FTBitmapFont((PATH+filenames[i]).c_str()));
				v.back()->FaceSize(j+MIN_FONT_SIZE);
			} else
				if(types[i]=="BUFFER"){
				v.push_back(new FTBufferFont((PATH+filenames[i]).c_str()));
				v.back()->FaceSize(j+MIN_FONT_SIZE);
			} else
				if(types[i]=="OUTLINE"){
				v.push_back(new FTOutlineFont((PATH+filenames[i]).c_str()));
				v.back()->FaceSize(j+MIN_FONT_SIZE);
			} else
				if(types[i]=="PIXMAP"){
				v.push_back(new FTPixmapFont((PATH+filenames[i]).c_str()));
				v.back()->FaceSize(j+MIN_FONT_SIZE);
			}
		}
		
		FontDB.insert(FontDB.begin(),pair<string,vector<FTFont*>>(identifiers[i],v));		
	}
	return true;
}

void FontSystem::print_centred(string text, string font_id, unsigned int font_size, float x, float y)// Vertex text_centre)
{
	FTFont* fnt=get_font(font_id,font_size);
	glPushMatrix();
	glLoadIdentity();
	fnt->Render(text.c_str(),-1,stringseed(text.c_str(),Pixel(x,y),fnt));
	glPopMatrix();	
}

void FontSystem::print(string text, string font_id, unsigned int font_size, float x, float y)// Vertex text_centre)
{
	FTFont* fnt=get_font(font_id,font_size);
	glPushMatrix();
	glLoadIdentity();
	fnt->Render(text.c_str(),-1,FTPoint(x,y));
	glPopMatrix();
}


FTFont* FontSystem::get_font(string font_id,unsigned int font_size)
{
	if(font_id=="") {
		return NULL;
	}
	int returnidx;
	if(font_size>MAX_FONT_SIZE) returnidx=MAX_FONT_SIZE; else returnidx=font_size;
	returnidx-=MIN_FONT_SIZE;
	if(returnidx<=0) returnidx=0;
	return FontDB[font_id][returnidx];
}