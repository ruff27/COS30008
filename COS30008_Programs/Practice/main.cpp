#include <iostream>

using namespace std;

class Animal {
  public:
	  void animalSound() {
		  cout << "Animal sound" << endl;
	  }
};

class Pig : public Animal {
  public:
	  void animalSound() {
		  cout << "wee wee" << endl;
	  }
};

class Dog : public Animal {
  public:
	  void animalSound() {
		  cout << "woof woof" << endl;
	  }
};

class Cat : public Animal {
  public:
	  void animalSound() {
		  cout << "meow meow" << endl;
	  }
};

int main() {
	Animal myAnimal;
	Pig myPig;
	Dog myDog;
	Cat myCat;

	myAnimal.animalSound();
	myPig.animalSound();
	myDog.animalSound();
	myCat.animalSound();

	return 0;
}