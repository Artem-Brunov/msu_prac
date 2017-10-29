#include <iostream>
#include <list>
#include <string>

using std::string;
using std::list;
using std::cout;
using std::endl;

#include "align.h"

class Observable;
class Observer
{
	public:
		virtual void HandleEvent(Observable) = 0;
		virtual ~Observer(){}
};

class Observable
{
	list<Observer*> _observers = list<Observer*>(0);
	public:
		void Notify()
		{
			for(list<Observer*>::iterator iter = _observers.begin(); iter != _observers.end(); ++iter)
			{
				(*iter) -> HandleEvent(*this);
			}
		}
	
		void add(Observer* rfr)
		{
			_observers.push_back(rfr);
		}
		Image _image = Image(0,0);
		string message = string("");
		string way = string("");
		
};


class View: public Observer
{
	void printt(string message)
	{
		cout << message << endl;
	}
	void _save_image(Image _image, char* way)
	{
		save_image(_image, way);
	}
	void HandleEvent(Observable bac)
	{
		printt(bac.message);
		_save_image(bac._image, &(bac.way[0]));
	}
};
		
class Model: public Observable
{
	public:	
		Model(){}
		Model(Observer* Jon, string way_2)
		{
			add(Jon);
			way = way_2;
		}
		void _load_image(string way_2)
		{
			_image = load_image(&(way_2[0]));
			message = string("Image is loaded");
			Notify();
		}
		void _align()
		{
			_image = align(_image);
			message = string("Received a color picture");
			Notify();
		}
};

class Controller
{
	public:
		Model mod_1 = Model();
		Controller(Model mod_2)
		{
			mod_1 = mod_2;
		}
		
		void _load_image(string way_2)
		{
			mod_1._load_image(way_2);
		}
		
		void _align()
		{
			mod_1._align();
		}
};

int main(int argc, char** argv)
{

	View _view;
	Model _model = Model(&_view, string(argv[2]));
	Controller _controller = Controller(_model);

	_controller._load_image(string(argv[1]));
	_controller._align();
	
	return 0;	
}
