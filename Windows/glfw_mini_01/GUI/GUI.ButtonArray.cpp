#include "GUI.ButtonArray.h"

Button* ButtonArray::add_button(Button& btn)
{
	btn.set_sticky();
	buttons.insert(buttons.begin(),pair<string,Button>(btn.get_ID(),btn));
	return &buttons[btn.get_ID()];
}

bool ButtonArray::update()
{
	bool flag=false;
	map<string,Button>::iterator i=buttons.begin();
	int j=0;
	vector<GLuint> states_before(buttons.size()),states_after(buttons.size());
	vector<bool> diff(buttons.size());
	
	for(i;i!=buttons.end();i++)
	{
		bool flag2=false;
		states_before[j]=i->second.get_state();
			
		flag2=i->second.update();
		flag=flag||flag2;
	
		states_after[j]=i->second.get_state();
		diff[j]=states_before[j]!=states_after[j];
	
		j++;
	}
	
	if(!flag) return false;

	i=buttons.begin();
	for(j=0; j<buttons.size(); j++){
		if(diff[j]&&states_after[j]==BTN_ACTIVE){
			active=i->first;
			cout << "Active: " << i->first << endl;
			break;
		}
		i++;
	}
	i=buttons.begin();
	for(j=0; j<buttons.size(); j++){
		if(states_before[j]==BTN_ACTIVE&&i->first!=active){
				i->second.reset();
				cout << "Deactivated: " << i->first << endl;
				break;
		}
		i++;
	}
	return true;
}

void ButtonArray::display()
{
	map<string,Button>::iterator i=buttons.begin();
	for(i;i!=buttons.end();i++)
		i->second.display();
}